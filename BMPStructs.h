#pragma once
#include <string>
#include <vector>

#pragma pack(push, 1)
struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct YUVPixel {
    double y;
    double u;
    double v;
};

struct BMPFileHeader {
    uint16_t bfType; // 0x42 0x4D
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression; // 0 for now
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant; // generally ignored
};

#pragma pack(pop)
