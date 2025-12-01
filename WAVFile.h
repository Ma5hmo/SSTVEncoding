#pragma once
#include <string>

#include <cstdint>
#include <array>
#include <vector>

#pragma pack(push, 1)  // ensures no padding is added by the compiler

struct RIFFHeader {
    std::array<char, 4> chunkID{ 'R', 'I', 'F', 'F' };
    uint32_t chunkSize{ 0 };    // file size - 8
    std::array<char, 4> format{ 'W', 'A', 'V', 'E' };
};

struct FmtSubchunk {
    std::array<char, 4> subchunk1ID{ 'f', 'm', 't', ' ' };
    uint32_t subchunk1Size{ 16 };  // PCM
    uint16_t audioFormat{ 1 };     // PCM
    uint16_t numChannels{ 2 };     // stereo by default
    uint32_t sampleRate{ 44100 };
    uint32_t byteRate{ 176400 };   // calculated as sampleRate * numChannels * bitsPerSample/8
    uint16_t blockAlign{ 4 };      // numChannels * bitsPerSample/8
    uint16_t bitsPerSample{ 16 };

    /*void computeDerivedValues() {
        blockAlign = numChannels * bitsPerSample / 8;
        byteRate = sampleRate * blockAlign;
    }*/
};

struct DataSubchunkHeader {
    std::array<char, 4> subchunk2ID{ 'd', 'a', 't', 'a' };
    uint32_t subchunk2Size{ 0 };  // number of bytes of audio data

    // data goes here
};
#pragma pack(pop)


class WAVFile
{
public:
    WAVFile(const std::string& filename);
    void addAudioData(double frequency, double duration);


private:
    static std::vector<uint16_t> genAudioData(double frequency, double duration,
        uint32_t sampleRate = 44100,
        uint16_t amplitude = 30000,
        uint16_t numChannels = 1);
	std::string _filename;
    RIFFHeader _riffHdr;
    FmtSubchunk _fmtHdr;
    DataSubchunkHeader _dataHdr;
    std::vector<uint16_t> _audioData;
};

