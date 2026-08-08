#include "WAVFile.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

WAVFile::WAVFile(const std::string& filename)
: _filename(filename),
_riffHdr(),
_fmtHdr(),
_dataHdr(),
_audioData()
{
}

void WAVFile::AddAudioData(double frequency, double duration)
{
    auto newData = genAudioData(frequency, duration, _phase, SAMPLE_RATE, 30000);
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

std::vector<int16_t> WAVFile::genAudioData(
    double frequency,
    double duration,
    double& currPhase,
    uint32_t sampleRate,
    uint16_t amplitude,
    uint16_t numChannels)
{
    uint32_t numSamples = static_cast<uint32_t>(duration * sampleRate);
    std::vector<int16_t> audioData;
    audioData.resize(numSamples * numChannels);

    const double phaseIncrement =
        2.0 * std::numbers::pi * frequency / sampleRate;

    for (uint32_t n = 0; n < numSamples; ++n) {
        int16_t sample = static_cast<int16_t>(amplitude * std::sin(currPhase));

        // Fill all channels (interleaved)
        for (uint16_t ch = 0; ch < numChannels; ++ch) {
            audioData[n * numChannels + ch] = sample;
        }

        // Preserve phase when changing frequencies.
        currPhase += phaseIncrement;

        if (currPhase >= 2.0 * std::numbers::pi) {
            currPhase = std::fmod(currPhase, 2.0 * std::numbers::pi);
        }
    }

    return audioData;
}