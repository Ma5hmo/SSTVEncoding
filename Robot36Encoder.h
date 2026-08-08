#pragma once
#include "SSTVEncoder.h"
#include <span>

class Robot36Encoder :
    public SSTVEncoder
{
public:
	Robot36Encoder(const std::string& wavFileName, const std::string& bmpFileName);
	void WriteAudioHeaders() override;
	void EncodeImage() override;
	void WriteToFile() override;

	// Derives from SSTVEncoder:
	//		WAVFile _wavFile;
	//		BMPImage _bmpImage;

private:
	void WriteImageLine(std::span<const YUVPixel> yuv, std::span<const Pixel> rgb, bool isOddLine);

	constexpr static int IMAGE_WIDTH = 320;
	constexpr static int IMAGE_HEIGHT = 240;
	constexpr static uint8_t ROBOT36_VIS_CODE = 0b0001000; // 7 bits, LSB first

};

