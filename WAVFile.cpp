#include "WAVFile.h"
#include <fstream>
#include <cmath>
#include <cstdint>

static const int M_PI = 3.14159265359;

WAVFile::WAVFile(const std::string& filename)
    : _filename(filename),
      _riffHdr(), _fmtHdr(), _dataHdr(), _audioData()
{
}

void WAVFile::AddAudioData(double frequency, double duration)
{
    auto newData = genAudioData(frequency, duration);
    _audioData.insert(_audioData.end(), newData.begin(), newData.end());
}

void WAVFile::WriteToFile()
{
    std::ofstream file(_filename, std::ios::binary);
    if (!file || !file.is_open()) throw std::runtime_error("Can't open file");

    _riffHdr.chunkSize = sizeof(RIFFHeader) + sizeof(FmtSubchunk)
        + sizeof(DataSubchunkHeader) + _audioData.size() * sizeof(int16_t) - 8;
    _fmtHdr.computeDerivedValues();
    _dataHdr.subchunk2Size = _audioData.size() * sizeof(int16_t);

    file.write(reinterpret_cast<const char*>(&_riffHdr), sizeof(RIFFHeader));
    file.write(reinterpret_cast<const char*>(&_fmtHdr), sizeof(FmtSubchunk));
    file.write(reinterpret_cast<const char*>(&_dataHdr), sizeof(DataSubchunkHeader));
    file.write(reinterpret_cast<const char*>(_audioData.data()), _audioData.size() * sizeof(int16_t));

    file.close();
}

std::vector<int16_t> WAVFile::genAudioData(double frequency, double duration,
	uint32_t sampleRate, uint16_t amplitude, uint16_t numChannels)
{
    uint32_t numSamples = static_cast<uint32_t>(duration * sampleRate);
    std::vector<int16_t> audioData;
    audioData.resize(numSamples * numChannels);

    for (uint32_t n = 0; n < numSamples; ++n) {
        // Calculate sample value in range [-amplitude, amplitude]
        double t = static_cast<double>(n) / sampleRate;
        int16_t sample = static_cast<int16_t>(amplitude * std::sin(2 * M_PI * frequency * t));

        // Fill all channels (interleaved)
        for (uint16_t ch = 0; ch < numChannels; ++ch) {
            audioData[n * numChannels + ch] = sample;
        }
    }

    return audioData;
}
