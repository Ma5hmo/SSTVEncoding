#pragma once
#include "BMPStructs.h"

class BMPImage
{
public:
	BMPImage(const std::string& filename);
	const std::vector<YUVPixel> GetYUVPixels() const;
	const std::vector<Pixel>& GetPixels() const;
	uint32_t _height;
	uint32_t _width;
	static YUVPixel PixelRgbToYUV(const Pixel& p);
private:

	std::vector<Pixel> _pixels;
};

