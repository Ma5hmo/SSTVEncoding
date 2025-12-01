#include <fstream>
#include "Image.h"

// BMP format conversion
Image::Image(const std::string& filepath)
    : _pixels()
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file || !file.is_open()) throw std::runtime_error("Cannot open file");

    BMPFileHeader fileHeader = { 0 };
    BMPInfoHeader infoHeader = { 0 };
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42) throw std::runtime_error("Not a BMP file");
    if (infoHeader.biBitCount != 24) throw std::runtime_error("Only 24-bit BMP supported");
    if (infoHeader.biCompression != 0) throw std::runtime_error("Compressed BMP not supported");
    
    _height = infoHeader.biHeight;
    _width = infoHeader.biWidth;

    file.seekg(fileHeader.bfOffBits, std::ios_base::beg); // seek pixel array
    _pixels.reserve(fileHeader.bfSize / sizeof(Pixel));
    for (int i = 0; i < fileHeader.bfSize; i += sizeof(Pixel))
    {
        Pixel p;
        file.read(reinterpret_cast<char*>(&p), 3);
        _pixels.push_back(std::move(p));
    }
}

const std::vector<YUVPixel> Image::GetYUVPixels() const
{
    std::vector<YUVPixel> newPixels(_pixels.size());
    for (const Pixel& p : _pixels) {
        newPixels.push_back(pixelRgbToYUV(p));
    }
    return newPixels;
}

const std::vector<Pixel>& Image::GetPixels() const
{
    return _pixels;
}

YUVPixel Image::pixelRgbToYUV(const Pixel& p) const
{
    YUVPixel newP;
    newP.y = 0.257 * p.red + 0.504 * p.green + 0.098 * p.blue + 16;
    newP.u = -0.148 * p.red - 0.291 * p.green + 0.439 * p.blue + 128;
    newP.v = 0.439 * p.red - 0.368 * p.green - 0.071 * p.blue + 128;
    return newP;
}
