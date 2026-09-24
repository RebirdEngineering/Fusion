#ifndef _AUDIO_AUDIOCLIP_H
#define _AUDIO_AUDIOCLIP_H

#include <audio/AudioReader.h>
#include <io/InputStream.h>

namespace audio
{

class AudioClipCursor : //19
	public NS(lang, Object)
{
public:
	AudioClipCursor(); //22

	void reset() //28
	{
		m_offset1 = 0;
		m_offset2 = 0;
	}

	unsigned int m_offset1; //34
	unsigned int m_offset2; //35
};

class AudioClip :
	public NS(lang, Object)
{
public:
	AudioClip();

	AudioClip(P(NS(io,InputStream)) in, NS(io, FileFormat) fmt);

	AudioClip(const void* data, int size, const AudioConfiguration& configuration);

	~AudioClip();

	virtual int getData(void* data, int size, AudioClipCursor* cursor);

	virtual int audioFormat() const;

	virtual int channels() const;

	virtual int sampleRate() const;

	virtual int byteRate() const;

	virtual int blockAlign() const;

	virtual int bitsPerSample() const;

	virtual int dataSize() const;
private:
	P(NS(io, InputStream)) m_in;
	P(AudioReader) m_reader;

	AudioClip(const AudioClip&);
	AudioClip& operator=(const AudioClip&);
};
}

#endif