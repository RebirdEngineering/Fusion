#ifndef _AUDIO_AUDIOINPUTLISTENER_H
#define _AUDIO_AUDIOINPUTLISTENER_H

#include <audio/AudioConfiguration.h>

namespace audio
{

class AudioInputListener
{
public:
	virtual void audioDataReceived(const void* data, int size, const AudioConfiguration& configuration, int handle) = 0;

	virtual void audioRecordingCompleted(const void* data, int size, const AudioConfiguration& configuration, int handle) = 0;
};

}

#endif