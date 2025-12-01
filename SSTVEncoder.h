#pragma once
#include "WAVFile.h"
#include "BMPImage.h"

class SSTVEncoder
{
public:
	SSTVEncoder(const std::string& wavFileName, const std::string& bmpFileName);
	virtual void WriteAudioHeaders() = 0;
	virtual void EncodeImage() = 0;
	virtual void WriteToFile() = 0;

private:
	WAVFile _wavFile;
	BMPImage _bmpImage;
};

