#pragma once
#include "SSTVEncoder.h"

class Robot36Encoder :
    public SSTVEncoder
{
public:
	void WriteAudioHeaders() override;
	void EncodeImage() override;
	void WriteToFile() override;
};

