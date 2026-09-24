#ifndef _AUDIO_COMMMON_AUDIOINPUT_H
#define _AUDIO_COMMMON_AUDIOINPUT_H

//#include <audio/AudioInput.h>

namespace audio
{

AudioInput::AudioInput(const AudioConfiguration& configuration) //6
{
	m_impl = new AudioInputImpl(configuration);
}

AudioInput::~AudioInput()
{
}

bool AudioInput::startInput()
{
	return m_impl->startInput();
}

void AudioInput::stopInput()
{
	m_impl->stopInput();
}

bool AudioInput::isStarted() const
{
	return m_impl->isStarted();
}

int AudioInput::recordClip(float duration)
{
	return m_impl->recordClip(duration);
}

void AudioInput::stopRecord(int handle)
{
	m_impl->stopRecord(handle);
}

void AudioInput::addListener(AudioInputListener* listener)
{
	m_impl->addListener(listener);
}

void AudioInput::removeListener(AudioInputListener* listener)
{
	m_impl->removeListener(listener);
}

}