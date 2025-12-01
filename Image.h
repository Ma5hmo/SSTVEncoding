#pragma once
#include "BMPImage.h"

class Image
{
public:
	Image(const std::string& filename);
	const std::vector<YUVPixel> GetYUVPixels() const;
	const std::vector<Pixel>& GetPixels() const;
	uint32_t _height;
	uint32_t _width;
private:
	YUVPixel pixelRgbToYUV(const Pixel& p) const;

	std::vector<Pixel> _pixels;
};

