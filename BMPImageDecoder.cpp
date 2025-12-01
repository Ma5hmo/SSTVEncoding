#include "BMPImageDecoder.h"
#include <fstream>

std::vector<Pixel> BMPImageDecoder::DecodeBMP(const std::string& filepath)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open file");

    BMPFileHeader fileHeader = { 0 };
    BMPInfoHeader infoHeader = { 0 };
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42) throw std::runtime_error("Not a BMP file");
    if (infoHeader.biBitCount != 24) throw std::runtime_error("Only 24-bit BMP supported");
    if (infoHeader.biCompression != 0) throw std::runtime_error("Compressed BMP not supported");

    file.seekg(fileHeader.bfOffBits, std::ios_base::beg); // seek pixel array

    std::vector<Pixel> pixels;
    for (int i = 0; i < infoHeader.biSizeImage; i++)
    {
        Pixel p;
        file.read(reinterpret_cast<char*>(&p), 3);
        pixels.push_back(std::move(p));
    }
    return pixels;
}
