#ifndef _AUDIO_COMPOSITEAUDIOCLIP_H
#define _AUDIO_COMPOSITEAUDIOCLIP_H

#include <audio/AudioClip.h>

namespace audio
{

class CompositeAudioClip :
	public AudioClip
{
public:
	CompositeAudioClip(const std::vector<P(AudioClip)>& clips);

	~CompositeAudioClip();

	int getData(void* data, int size, AudioClipCursor* cursor);

	int audioFormat() const;

	int channels() const;

	int sampleRate() const;

	int byteRate() const;

	int blockAlign() const;

	int bitsPerSample() const;

	int dataSize() const;
private:
	std::vector<P(AudioClip)> m_clips;

	CompositeAudioClip(const CompositeAudioClip&);
	CompositeAudioClip& operator=(const CompositeAudioClip&);
};

}

#endif