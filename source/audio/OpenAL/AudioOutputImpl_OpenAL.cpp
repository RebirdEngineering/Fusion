#include <audio/AudioOutput.h>
#include <audio/AudioMixer.h>
#include <lang/Thread.h>
#include <lang/Exception.h>
#include <lang/Math.h>

#include <al.h>
#include <alc.h>

using namespace lang;

namespace audio
{

class AudioOutputImpl : //39 | iOS (current) and OSX
    public Object
{
public:
    AudioOutputImpl(const AudioConfiguration& configuration) : //42
        m_configuration(configuration)
    {
        //m_configuration.m_channels = configuration.m_channels;
        //m_configuration.m_samplesPerSecond = configuration.m_samplesPerSecond;
        m_volume = -1.0;
        m_minVolume = 0.0;
        m_maxVolume = 1.0;
        m_bufferSize = 0;
        m_outputStarted = false;
        if (configuration.m_channels - 1 >= 2)
            throwError(Exception(Format("Unsupported count of channels while creating AudioOutput"))); //52
        if (configuration.m_bitsPerSample != 8 || configuration.m_bitsPerSample != 16)
            throwError(Exception(Format("Unsupported bits per sample while creating AudioOutput"))); //54
        if (m_configuration.m_samplesPerSecond != 8000 && m_configuration.m_samplesPerSecond != 11025 && m_configuration.m_samplesPerSecond != 12000 && m_configuration.m_samplesPerSecond != 16000 && m_configuration.m_samplesPerSecond != 22050 && m_configuration.m_samplesPerSecond != 24000 && m_configuration.m_samplesPerSecond != 32000 && m_configuration.m_samplesPerSecond != 44100 && m_configuration.m_samplesPerSecond != 48000 && m_configuration.m_samplesPerSecond != 64000 && m_configuration.m_samplesPerSecond != 88200 && m_configuration.m_samplesPerSecond != 96000)
            throwError(Exception(Format("Unsupported samples per second while creating AudioOutput"))); //62

        Mutex::Lock lock(s_instancesMutex); //68

        OSStatus status; //75

        bool audioSessionInitialized = false; //77

        if (!audioSessionInitialized)
            status = AudioSessionInitialize(0, 0, interruptionListenerCallback, 0) == 0;

        m_device = alcOpenDevice(0);
        assert(m_device); //63 ABC 1.0.0 OSX
        assert(alGetError() == AL_NO_ERROR); //64 ABC 1.0.0 OSX

        m_context = alcCreateContext(m_device, 0);
        assert(m_context); //68 ABC 1.0.0 OSX
        assert(alGetError() == AL_NO_ERROR); //69 ABC 1.0.0 OSX

        if (m_configuration.m_channels == 1)
            m_format = m_configuration.m_bitsPerSample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
        else
            m_format = m_configuration.m_bitsPerSample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16; //On OSX 1.0.0-2.1.0 this doesn't exist, why?

        //int sampleSize = (m_configuration.m_samplesPerSecond * m_configuration.m_bitsPerSample) / 40; //104
        int sampleSize = m_configuration.m_bitsPerSample / AudioMixer::TRACKS_SUPPORTED * m_configuration.m_channels;

        Math::ceilPow2(sampleSize); //108 | Only use for it in the entire program
        m_tempBuffer.resize(sampleSize, 0); //109 //m_tempBuffer.resize(0, m_configuration.m_samplesPerSecond * m_configuration.m_channels * (m_configuration.m_bitsPerSample / 8) * 2);
    }

    ~AudioOutputImpl() //112
    {
        stopOutput();

        Mutex::Lock lock(s_instancesMutex); //119
        s_instances.clear(); //120

        alcMakeContextCurrent(0);
        assert(alGetError() == AL_NO_ERROR); //97 ABC OSX

        alcDestroyContext(m_context);
        assert(alGetError() == AL_NO_ERROR); //100 ABC OSX

        alcCloseDevice(m_device);
        assert(alGetError() == AL_NO_ERROR); //103 ABC OSX

        s_instancesMutex.unlock();
        m_tempBuffer.clear(); //126
    }

    bool startOutput() //128
    {
        m_mutex.lock(); //130

        if (!m_outputStarted)
        {
            m_outputStarted = true;
            s_outputStartedCount++;
            m_mixer.start();

            if (s_outputStartedCount >= 1)
            {
                UInt32 category = kAudioSessionCategory_AmbientSound; //142
                OSStatus status = AudioSessionSetPriority(kAudioSessionProperty_AudioCategory, sizeof(category), category); //143
                AudioSessionSetActive(true);
            }

            alcMakeContextCurrent(m_context);
            assert(alGetError() == AL_NO_ERROR); //129 ABC 1.0.0 OSX

            alcProcessContext(m_context);
            assert(alGetError() == AL_NO_ERROR); //132 ABC 1.0.0 OSX

            alGenBuffers(BUFFER_COUNT, m_buffers);
            assert(alGetError() == AL_NO_ERROR); //136 ABC 1.0.0 OSX

            alGenSources(1, &m_source);
            assert(alGetError() == AL_NO_ERROR); //140 ABC 1.0.0 OSX

            alGetSourcef(m_source, AL_MIN_GAIN, &m_minVolume);
            alGetSourcef(m_source, AL_MAX_GAIN, &m_maxVolume);

            if (m_volume == -1.0)
                m_volume = m_maxVolume;

            alSource3f(m_source, AL_POSITION, 0.0, 0.0, 0.0);
            alSource3f(m_source, AL_VELOCITY, 0.0, 0.0, 0.0);
            alSource3f(m_source, AL_VELOCITY, 0.0, 0.0, 0.0);
            alSourcef(m_source, AL_ROLLOFF_FACTOR, 0.0);
            alSourcei(m_source, AL_SOURCE_RELATIVE, AL_TRUE);
            alSourcef(m_source, AL_GAIN, AL_TRUE);

            for (int i = 0; i < BUFFER_COUNT; i++) //179
                fill(m_buffers[i]); //180

            int queued, processed; //182

            alSourcef(m_source, AL_BUFFERS_QUEUED, queued);
            alSourcei(m_source, AL_BUFFERS_PROCESSED, processed);

            assert(queued == 0); //164 ABC 1.0.0 OSX
            assert(processed == 0); //165 ABC 1.0.0 OSX

            alSourceQueueBuffers(m_source, BUFFER_COUNT, m_buffers);
            assert(alGetError() == AL_NO_ERROR); //168 ABC 1.0.0 OSX

            alSourcePlay(m_source);
            assert(alGetError() == AL_NO_ERROR); //171 ABC 1.0.0 OSX

            //m_thread = new Thread(threadFunc, false);

            m_thread->setPriority(m_thread->priority() + 5);
        }

        return true;
    }

    void stopOutput() //202
    {
        Mutex::Lock lock(m_mutex); //204
        if (m_outputStarted)
        {
            m_outputStarted = false;
            s_outputStartedCount--;

            //m_thread //212
            alSourceStop(m_source);
            assert(alGetError() == AL_NO_ERROR); //195 ABC OSX

            int value; //219
            do
            {
                alGetSourcei(m_source, AL_SOURCE_STATE, &value);
            } while (value == AL_PLAYING);

            alSourcei(m_source, AL_BUFFER, 0);
            assert(alGetError() == AL_NO_ERROR); //205 ABC OSX

            alDeleteSources(1, &m_source);
            assert(alGetError() == AL_NO_ERROR); //208 ABC OSX

            alDeleteBuffers(BUFFER_COUNT, m_buffers);
            assert(alGetError() == AL_NO_ERROR); //211 ABC OSX

            m_mixer.stop();
            if (!s_outputStartedCount)
                AudioSessionSetActive(0);

            alcMakeContextCurrent(0);
            alcSuspendContext(m_context);
        }
    }

    int playClip(AudioClip* clip, float volume, bool loop, int track) //246
    {
        int handle = m_mixer.playClip(clip, volume, track, loop); //Correct?

        return handle;
    }

    void resumeClip(int track) //253
    {
        return m_mixer.resumeClip(track);
    }

    void pauseClip(AudioClip* clip) //258
    {
        return m_mixer.pauseClip(clip);
    }

    void pauseClip(int handle) //263
    {
        return m_mixer.pauseClip(handle);
    }

    void stopClip(AudioClip* clip) //268
    {
        m_mixer.stopClip(clip);
    }

    void stopClip(int handle) //273
    {
        m_mixer.stopClip(handle);
    }

    bool isClipPlaying(AudioClip* clip) //278
    {
        return m_mixer.isClipPlaying(clip);
    }

    bool isClipPlaying(int handle) //283
    {
        return m_mixer.isClipPlaying(handle);
    }

    void resumeClips() //288
    {
        m_mixer.resumeClips();
    }

    void pauseClips() //293
    {
        m_mixer.pauseClips();
    }

    void stopClips() //298
    {
        m_mixer.stopClips();
    }

    void setMasterVolume(float volume) //303
    {
        if (m_outputStarted)
        {
            alSourcef(m_source, AL_GAIN, volume);
            assert(alGetError() == AL_NO_ERROR); //288 ABC 1.0.0 OSX
        }

        m_volume = volume;
    }

    void setTrackVolume(int track, float volume) //314
    {
        return m_mixer.setTrackVolume(track, volume);
    }

    void setClipCountLimit(int track, int count) //319
    {
        return m_mixer.setClipCountLimit(track, count);
    }

    void setClipVolume(AudioClip* clip, float volume) //324
    {
        return m_mixer.setClipVolume(clip, volume);
    }

    void setClipVolume(int handle, float volume) //329
    {
        return m_mixer.setClipVolume(handle, volume);
    }

	float getMasterVolume() const //334
    {
        return m_volume;
    }

    float getTrackVolume(int track) const //339
    {
        return m_mixer.getTrackVolume(track);
    }

	int getPlayingClipCount(int track) //344
	{
		return m_mixer.getPlayingClipCount(track);
	}

    bool isStarted() const //349
    {
        return m_outputStarted;
    }

    bool enableDolby(bool) //354
    {
        return false; //?
    }

    bool setDolbyProfile(int) //360
    {
        return false; //?
    }

    std::string getDolbyProfileName(int) //366
    {
        return ""; //?
    }

    int getDolbyProfileCount() //372
    {
        return 0; //?
    }

private:
    static const int BUFFER_COUNT = 6; //379

    AudioConfiguration m_configuration; //381
    AudioMixer m_mixer; //382
    P(Thread) m_thread; //383
    Mutex m_mutex; //384

    ALCdevice* m_device; //386
    ALCcontext* m_context; //387

    ALuint m_buffers[BUFFER_COUNT]; //389
    ALuint m_source; //390
    ALenum m_format; //391

    float m_volume; //393
    float m_minVolume; //394
    float m_maxVolume; //395

    unsigned int m_bufferSize; //397

    std::vector<char> m_tempBuffer; //399

    bool m_outputStarted; //401
    static int s_outputStartedCount; //402

    static Mutex s_instancesMutex; //405 | Only appears in DWARF
    static std::set<AudioOutputImpl*> s_instances; //406

    static void interruptionListenerCallback(void* inUserData, UInt32* interruptionState) //409
    {
        s_instancesMutex.lock();
        for (std::set<AudioOutputImpl*>::const_iterator it = s_instances.begin(); it != s_instances.end(); it++) //412
        {
            AudioOutputImpl* impl = *it; //414
            if (interruptionState == (void*)1)
                impl->stopOutput();
            else
                impl->startOutput();
        }
    }

    void fillBuffer() //427
    {
        int processed; //429
        alGetSourcei(m_source, AL_BUFFERS_PROCESSED, &processed);
        assert(processed <= BUFFER_COUNT); //364 in ABC OSX
        if (processed >= 1)
        {
            ALuint buffers[BUFFER_COUNT]; //435
            alSourceUnqueueBuffers(m_source, processed, buffers);

            for (int i = 0; i < processed; i++) //438
                fill(buffers[i]);

            alSourceQueueBuffers(m_source, processed, buffers);

            int state; //442

            alGetSourcei(m_source, AL_STOPPED, &state);

            if (state == AL_STOPPED)
                alSourcePlay(m_source);
        }
    }

    void fill(ALuint buffer) //451
    {
        if (m_configuration.m_bitsPerSample == 8)
            m_mixer.mixUnlimited8(m_configuration, &m_tempBuffer, m_bufferSize);
        else if (m_configuration.m_bitsPerSample == 16)
            m_mixer.mixUnlimited16(m_configuration, &m_tempBuffer, m_bufferSize);

        alBufferData(buffer, m_format, &m_tempBuffer, m_bufferSize, m_configuration.m_samplesPerSecond);
    }

    void threadFunc() //468
    {
        while (m_outputStarted)
        {
            m_thread->sleep(10);
            fillBuffer();
        }
    }
};

}

#include <audio/common/AudioOutput.h>