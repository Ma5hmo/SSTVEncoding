#include "Robot36Encoder.h"
#include <span>
#include <iostream>

Robot36Encoder::Robot36Encoder(const std::string& wavFileName, const std::string& bmpFileName)
	: SSTVEncoder(wavFileName, bmpFileName)
{}

void Robot36Encoder::WriteAudioHeaders()
{
	_wavFile.AddAudioData(1900, 0.3); // VIS leader tone
	_wavFile.AddAudioData(1200, 0.01); // break
	_wavFile.AddAudioData(1900, 0.3); // VIS leader tone
	_wavFile.AddAudioData(1200, 0.03); // VIS start bit

	for (int i = 0; i < 7; ++i) {
		if (ROBOT36_VIS_CODE & (1 << i)) {
			_wavFile.AddAudioData(1100, 0.03); // 1 bit
		}
		else {
			_wavFile.AddAudioData(1300, 0.03); // 0 bit
		}
	}

	_wavFile.AddAudioData(1100, 0.03); // parity bit
	_wavFile.AddAudioData(1200, 0.03); // VIS stop bit
}

// robot36 image size is 320x240 pixels, 320 pixels per line, 240 lines
void Robot36Encoder::WriteImageLine(std::span<const YUVPixel> yuvPixels, std::span<const Pixel> rgbPixels, bool isOddLine)
{
	_wavFile.AddAudioData(1200, 0.009); // sync pulse
	_wavFile.AddAudioData(1500, 0.003); // sync porch
	if (yuvPixels.size() != rgbPixels.size() || yuvPixels.size() != IMAGE_WIDTH) {
		std::cout << "YUV and RGB pixel arrays must be the same size" << std::endl;
		return;
	}

	for (const YUVPixel& yuv : yuvPixels) {
		double freq = 1500 + (yuv.y / 255) * 800;
		_wavFile.AddAudioData(freq, 0.088 / IMAGE_WIDTH);
	}

	// seperator - 2300hz for odd lines, 1500hz for even lines
	if (isOddLine) {
		_wavFile.AddAudioData(2300, 0.0045);
	}
	else {
		_wavFile.AddAudioData(1500, 0.0045);
	}
	_wavFile.AddAudioData(1900, 0.0015); // porch
	
	for (int i = 0; i < yuvPixels.size(); ++i) {
		const YUVPixel& yuv = yuvPixels[i];
		const Pixel& rgb = rgbPixels[i];
		double scanData;
		if (isOddLine) {
			scanData = rgb.blue - yuv.y;
		}
		else {
			scanData = rgb.red - yuv.y;
		}
		double freq = 1500 + (scanData / 255) * 800;
		_wavFile.AddAudioData(freq, 0.044 / IMAGE_WIDTH);
	}
}

void Robot36Encoder::EncodeImage()
{
	if (_bmpImage._height != IMAGE_HEIGHT || _bmpImage._width != IMAGE_WIDTH) {
		std::cout << "Image must be 320x240 pixels" << std::endl;
		return;
	}
	WriteAudioHeaders();
	const auto& rgbPixels = _bmpImage.GetPixels();
	const auto& yuvPixels = _bmpImage.GetYUVPixels();
	for (int line = 0; line < IMAGE_HEIGHT; ++line) {
		std::span<const Pixel> rgbLine(rgbPixels.data() + line * IMAGE_WIDTH, IMAGE_WIDTH);
		std::span<const YUVPixel> yuvLine(yuvPixels.data() + line * IMAGE_WIDTH, IMAGE_WIDTH);
		WriteImageLine(yuvLine, rgbLine, line % 2 == 1);
	}
}

void Robot36Encoder::WriteToFile()
{
	_wavFile.WriteToFile();
}
