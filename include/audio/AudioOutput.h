#ifndef _AUDIO_AUDIOOUTPUT_H
#define _AUDIO_AUDIOOUTPUT_H

#include <lang/Object.h>
#include <audio/AudioConfiguration.h>

namespace audio
{

class AudioClip;
class AudioOutputImpl;

class AudioOutput : //17
    public lang::Object
{
public:
    AudioOutput(const AudioConfiguration& configuration); //24

    ~AudioOutput(); //29

    bool startOutput(); //34

    void stopOutput(); //39

    int playClip(AudioClip* clip, float volume, bool loop, int track); //48

    void resumeClip(int handle); //54

    void pauseClip(AudioClip* clip); //60

	void pauseClip(int handle); //66

    void stopClip(AudioClip* clip); //72

    void stopClip(int handle); //78

    bool isClipPlaying(AudioClip* clip); //84

    bool isClipPlaying(int handle); //90

    void resumeClips(); //95

    void pauseClips(); //100

    void stopClips(); //105

    void setMasterVolume(float volume); //111

    void setTrackVolume(int track, float volume); //118

    void setClipCountLimit(int track, int count); //125

    void setClipVolume(AudioClip* clip, float volume); //130

    void setClipVolume(int handle, float volume); //135

    float getMasterVolume() const; //140

    float getTrackVolume(int handle) const; //146

    int getPlayingClipCount(int track); //152

    bool isStarted() const; //157

private:
    P(AudioOutputImpl) m_impl; //160
    AudioOutput(const AudioOutput&); //161
    AudioOutput& operator=(const AudioOutput&); //162
};

}

#endif