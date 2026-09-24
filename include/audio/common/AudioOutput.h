#ifndef _AUDIO_COMMMON_AUDIOOUTPUT_H
#define _AUDIO_COMMMON_AUDIOOUTPUT_H

//#include <audio/AudioOutput.h>

namespace audio
{

AudioOutput::AudioOutput(const AudioConfiguration& configuration) //6
{
    m_impl = new AudioOutputImpl(configuration);
}

AudioOutput::~AudioOutput() //12
{
}

bool AudioOutput::startOutput() //17
{
    return m_impl->startOutput();
}

void AudioOutput::stopOutput() //22
{
    return m_impl->stopOutput();
}

int AudioOutput::playClip(AudioClip* clip, float volume, bool loop, int track) //25 | ABS410 labels loop as bool despite the mangled symbol is float
{
	return m_impl->playClip(clip, volume, loop, track);
}

void AudioOutput::resumeClip(int handle) //inline
{
    m_impl->resumeClip(handle);
}

void AudioOutput::pauseClip(AudioClip* clip) //inline
{
    m_impl->pauseClip(clip);
}

void AudioOutput::pauseClip(int handle) //inline
{
    m_impl->pauseClip(handle);
}

void AudioOutput::stopClip(AudioClip* clip) //47
{
    m_impl->stopClip(clip);
}

void AudioOutput::stopClip(int handle) //50
{
    m_impl->stopClip(handle);
}

bool AudioOutput::isClipPlaying(AudioClip* clip) //55
{
    return m_impl->isClipPlaying(clip);
}

bool AudioOutput::isClipPlaying(int handle) //60
{
    return m_impl->isClipPlaying(handle);
}

void AudioOutput::resumeClips() //inline
{
	m_impl->resumeClips();
}

void AudioOutput::pauseClips() //inline
{
    m_impl->pauseClips();
}

void AudioOutput::stopClips() //77
{
    m_impl->stopClips();
}

void AudioOutput::setMasterVolume(float volume) //80
{
    m_impl->setMasterVolume(volume);
}

void AudioOutput::setTrackVolume(int track, float volume) //85
{
    m_impl->setTrackVolume(track, volume);
}

void AudioOutput::setClipCountLimit(int track, int count) //90
{
	m_impl->setClipCountLimit(track, count);
}

void AudioOutput::setClipVolume(AudioClip* clip, float volume) //95
{
	m_impl->setClipVolume(clip, volume);
}

void AudioOutput::setClipVolume(int handle, float volume) //inline
{
    m_impl->setClipVolume(handle, volume);
}

float AudioOutput::getMasterVolume() const //107
{
    return m_impl->getMasterVolume();
}

float AudioOutput::getTrackVolume(int track) const //110
{
    return m_impl->getTrackVolume(track);
}

int AudioOutput::getPlayingClipCount(int track)
{
	return m_impl->getPlayingClipCount(track);
}

bool AudioOutput::isStarted() const //122
{
	return m_impl->isStarted();
}

}

#endif