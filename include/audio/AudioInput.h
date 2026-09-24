#ifndef _AUDIO_AUDIOINPUT_H
#define _AUDIO_AUDIOINPUT_H

//Functions are in common

#include <lang/Object.h>

namespace audio {

class AudioInputImpl;
class AudioConfiguration;
class AudioInputListener;

struct RecordInfo;

class AudioInput :
	public lang::Object
{
public:
	AudioInput(const AudioConfiguration& configuration); //24

	~AudioInput(); //29

	bool startInput(); //34

	void stopInput(); //39

	bool isStarted() const; //44

	int recordClip(float duration); //52

	void stopRecord(int handle); //58

	void addListener(AudioInputListener* listener); //63

	void removeListener(AudioInputListener* listener); //68

private:
	P(AudioInputImpl) m_impl; //71
	AudioInput(const AudioInput&); //72
	AudioInput& operator=(const AudioInput&); //73
};

}

#endif