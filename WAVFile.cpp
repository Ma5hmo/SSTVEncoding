#include "WAVFile.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>

static const int M_PI = 3.14159265359;

std::vector<uint16_t> WAVFile::genAudioData(double frequency, double duration, 
	uint32_t sampleRate = 44100, uint16_t amplitude = 30000, uint16_t numChannels = 1)
{
    uint32_t numSamples = static_cast<uint32_t>(duration * sampleRate);
    std::vector<uint16_t> audioData(numSamples * numChannels);

    for (uint32_t n = 0; n < numSamples; ++n) {
        // Calculate sample value in range [-amplitude, amplitude]
        double t = static_cast<double>(n) / sampleRate;
        int16_t sampleValue = static_cast<int16_t>(amplitude * std::sin(2.0 * M_PI * frequency * t));

        // Convert signed int16 to unsigned uint16 (WAV PCM unsigned for 16-bit)
        uint16_t uSample = static_cast<uint16_t>(sampleValue + 32768);

        // Fill all channels (interleaved)
        for (uint16_t ch = 0; ch < numChannels; ++ch) {
            audioData[n * numChannels + ch] = uSample;
        }
    }

    return audioData;
}
