#ifndef _AUDIO_AUDIOWRITER_H
#define _AUDIO_AUDIOWRITER_H

#include <lang/Object.h>
#include <audio/AudioConfiguration.h>

namespace audio
{

class AudioWriter : //Never seen in Fusion, possibly an unofficial header
	public lang::Object //?
{
	bool writeWav(const std::string& filename, AudioConfiguration const&, void const*, int);
	bool write(const std::string& filename, AudioConfiguration const&, void const*, int);
};

}

#endif