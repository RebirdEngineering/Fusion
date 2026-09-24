#ifndef _AUDIO_AUDIOCLIPINSTANCE_H
#define _AUDIO_AUDIOCLIPINSTANCE_H

#include <audio/AudioClip.h>

namespace audio
{
	class AudioClipInstance
	{
	public:
		AudioClipInstance(); //13

		int fetchData(void* data, int size); //15

		P(AudioClip) m_clip; //17
		P(AudioClipCursor) m_cursor; //18
		float m_volume; //19
		int m_id; //20
		int m_track; //21
		bool m_looping; //22
		bool m_paused; //23
		bool m_ended; //24
	};
}

#endif