#include <audio/CompositeAudioClip.h>

namespace audio
{
	CompositeAudioClip::CompositeAudioClip(const std::vector<P(AudioClip)>& clips) //10
	{
		m_clips = clips;
	}

	CompositeAudioClip::~CompositeAudioClip() //17
	{
		m_clips.clear(); //18
	}

	int CompositeAudioClip::getData(void* data, int size, AudioClipCursor* cursor) //20 | Correct?
	{
		int dataReadTotal = 0; //22
		unsigned int bytes = 0; //23
		while (dataReadTotal < size)
		{
			bytes = dataReadTotal += m_clips[cursor->m_offset2]->getData(&data + dataReadTotal, size - dataReadTotal, cursor); //26 | Correct?
			dataReadTotal += bytes;
		}
		if (cursor->m_offset2 < m_clips.size()) //29
		{
			cursor->m_offset1 = 0;
			cursor->m_offset2 += 1;
		}

		return dataReadTotal;
		//assert("int CompositeAudioClip::getData(void* data, int size, AudioClipCursor * cursor) is not yet decompiled.");
	}

	int CompositeAudioClip::audioFormat() const
	{
		return m_clips.begin()->ptr()->audioFormat(); //43
	}

	int CompositeAudioClip::channels() const
	{
		return m_clips.begin()->ptr()->channels(); //48
	}

	int CompositeAudioClip::sampleRate() const
	{
		return m_clips.begin()->ptr()->sampleRate(); //53
	}

	int CompositeAudioClip::byteRate() const
	{
		return m_clips.begin()->ptr()->byteRate(); //58
	}

	int CompositeAudioClip::blockAlign() const
	{
		return m_clips.begin()->ptr()->blockAlign(); //63
	}

	int CompositeAudioClip::bitsPerSample() const
	{
		return m_clips.begin()->ptr()->bitsPerSample(); //68
	}

	int CompositeAudioClip::dataSize() const
	{
		int bytes = 0; //73
		for (int i = 0; i < m_clips.size(); i++) //74
		{
			bytes += m_clips[i]->dataSize(); //76
		}
		return bytes;
	}
}