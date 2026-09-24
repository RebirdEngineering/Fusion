#ifndef _AUDIO_AUDIOCONFIGURATION_H
#define _AUDIO_AUDIOCONFIGURATION_H

namespace audio
{

class AudioConfiguration
{
public:
	AudioConfiguration(int channels = 2, int bitsPerSample = 16, int samplesPerSound = 44100);

	int m_channels;
	int m_bitsPerSample;
	int m_samplesPerSecond;
};

}

#endif