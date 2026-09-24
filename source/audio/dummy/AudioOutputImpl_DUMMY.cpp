#include <audio/AudioOutput.h>

using namespace lang;

namespace audio
{

class AudioOutputImpl : //Unofficial
	public Object
{
public:
    AudioOutputImpl(const AudioConfiguration& configuration)
    {

    }

    ~AudioOutputImpl()
    {
    }

    bool startOutput()
    {
        return false;
    }

    void stopOutput()
    {
    }

    int playClip(AudioClip* clip, float loop, bool track, float volume)
    {
        return 0;
    }

    void resumeClip(int handle) //inline
    {
    }

    void pauseClip(AudioClip* clip) //inline
    {
    }

    void pauseClip(int handle) //inline
    {
    }

    void stopClip(AudioClip* clip)
    {
    }

    void stopClip(int handle)
    {
    }

    bool isClipPlaying(AudioClip* clip) //inline
    {
        return false;
    }

    bool isClipPlaying(int handle)
    {
        return false;
    }

    void resumeClips() //inline
    {
    }

    void pauseClips() //inline
    {
    }

    void stopClips()
    {
    }

    void setMasterVolume(float volume)
    {
    }

    void setTrackVolume(int track, float volume)
    {
    }

    void setClipCountLimit(int track, int count)
    {
    }

    void setClipVolume(AudioClip* clip, float volume)
    {
    }

    void setClipVolume(int handle, float volume) //inline
    {
    }

    float getMasterVolume() const
    {
        return 0.0f;
    }

    float getTrackVolume(int track) const
    {
        return 0.0f;
    }

    int getPlayingClipCount(int track)
    {
        return 0;
    }

    bool isStarted() const
    {
        return false;
    }
};

}

#include <audio/common/AudioOutput.h>