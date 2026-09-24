#include <audio/AudioOutput.h>
#include <audio/AudioMixer.h>
#include <lang/Thread.h>
#include <lang/Mutex.h>
#include <lang/Exception.h>
#include <lang/Log.h>

#include <dsound.h>
#include <ddraw.h>

using namespace lang;

namespace audio
{
	class AudioOutputImpl : public lang::Object
	{
	public:

        AudioOutputImpl(const AudioConfiguration& configuration) : m_configuration(configuration)
        {
            //m_configuration.m_channels = configuration.m_channels;
            //m_configuration.m_samplesPerSecond = configuration.m_samplesPerSecond;
            //if (m_configuration.m_channels > 2 || m_configuration.m_channels < 1) //? from XNA
            if ((m_configuration.m_channels - 1) >= 2) //?
                throwError(Exception(Format("Unsupported count of channels while creating AudioOutput")));
            if (m_configuration.m_bitsPerSample != 8 && m_configuration.m_bitsPerSample != 16) //?
                throwError(Exception(Format("Unsupported bits per sample while creating AudioOutput")));
            //if (m_configuration.m_samplesPerSecond < 8000 || m_configuration.m_samplesPerSecond > 48000) //?
            if (m_configuration.m_samplesPerSecond != 11025 && m_configuration.m_samplesPerSecond != 8000 && m_configuration.m_samplesPerSecond != 16000 && m_configuration.m_samplesPerSecond != 22050 && m_configuration.m_samplesPerSecond != 32000 && m_configuration.m_samplesPerSecond != 44100 && m_configuration.m_samplesPerSecond != 48000 && m_configuration.m_samplesPerSecond != 88200 && m_configuration.m_samplesPerSecond != 96000 && m_configuration.m_samplesPerSecond != 12000 && m_configuration.m_samplesPerSecond != 24000 && m_configuration.m_samplesPerSecond != 64000)
                throwError(Exception(Format("Unsupported samples per second while creating AudioOutput")));

            HRESULT hr = DirectSoundCreate8(NULL, &m_device, 0);

            if (FAILED(hr))
                throwError(Exception(Format("DirectSoundCreate8 failed")));

            hr = m_device->SetCooperativeLevel(GetTopWindow(0), 1);

            if (FAILED(hr))
                throwError(Exception(Format("SetCooperativeLevel failed")));

            short bitsPerSample = m_configuration.m_bitsPerSample;
            int samplesPerSecond = m_configuration.m_samplesPerSecond;
            short channels = m_configuration.m_channels;
            short align = bitsPerSample * channels / 8;

            WAVEFORMATEX fmt;
            memset(&fmt, 0, sizeof(WAVEFORMATEX));
            fmt.nChannels = channels;
            fmt.wFormatTag = WAVE_FORMAT_PCM;
            fmt.nBlockAlign = align;
            fmt.nAvgBytesPerSec = samplesPerSecond * align;
            fmt.wBitsPerSample = bitsPerSample;
            fmt.nSamplesPerSec = samplesPerSecond;

            int unk = channels * (samplesPerSecond / 8);
            int unk2 = channels * (bitsPerSample / 8);

            m_bufferBytes = unk;

            if (unk2 % unk)
                m_bufferBytes = unk + unk2 - unk2 % unk;

            DSBUFFERDESC desc;
            memset(&desc, 0, sizeof(DSBUFFERDESC));
            desc.dwBufferBytes = m_bufferBytes;
            desc.lpwfxFormat = (LPWAVEFORMATEX)&fmt;
            desc.dwSize = sizeof(DSBUFFERDESC);
            desc.dwFlags = 33248;

            //0 (4) //?

            hr = m_device->CreateSoundBuffer(&desc, &m_soundBuffer, 0);

            if (FAILED(hr))
                throwError(Exception(Format("AudioOutput creation failed")));

            setNotifications(m_soundBuffer, 10, m_bufferBytes);

            if (m_configuration.m_bitsPerSample == 8)
            {
                m_soundBuffer->Lock(0, m_bufferBytes, 0, 0, 0, 0, 0);
                //memset(0, 127, )
            }
        }

        bool startOutput()
        {
            Mutex::Lock lock(m_mutex);
            if (!m_outputStarted)
            {
                m_mixer.start();

                HRESULT hr = m_soundBuffer->Play(0, 0, 1);

                if (FAILED(hr))
                    return false;

                m_outputStarted = true;

                //TODO
                //m_thread

                m_thread->setPriority(m_thread->priority() + 1);
            }

            return true;
        }

        void stopOutput()
        {
            m_mutex.lock();
            if (m_outputStarted)
            {
                m_outputStarted = false;
                m_soundBuffer->Stop();

                m_thread = 0;
                delete m_thread;

                m_mixer.stop();
            }
        }

        int playClip(AudioClip* clip, float volume, bool loop, int track)
        {
            return m_mixer.playClip(clip, volume, loop, track);
        }

        void resumeClip(int handle)
        {
            m_mixer.resumeClip(handle);
        }

        void pauseClip(AudioClip* clip)
        {
            m_mixer.pauseClip(clip);
        }

        void pauseClip(int handle)
        {
            m_mixer.pauseClip(handle);
        }

        void stopClip(AudioClip* clip)
        {
            m_mixer.stopClip(clip);
        }

        void stopClip(int handle)
        {
            m_mixer.stopClip(handle);
        }

        bool isClipPlaying(AudioClip* clip)
        {
            return m_mixer.isClipPlaying(clip);
        }

        bool isClipPlaying(int handle)
        {
            return m_mixer.isClipPlaying(handle);
        }

        void resumeClips()
        {
            m_mixer.resumeClips();
        }

        void pauseClips()
        {
            m_mixer.pauseClips();
        }

        void stopClips()
        {
            m_mixer.stopClips();
        }

        void setMasterVolume(float volume)
        {
            LONG value = volume * 10000.0 - 10000.0;
            m_soundBuffer->SetVolume(value);
            m_volume = volume;
        }

        void setTrackVolume(int track, float volume)
        {
            m_mixer.setTrackVolume(volume, track);
        }

        void setClipCountLimit(int track, int count)
        {
            m_mixer.setClipCountLimit(track, count);
        }

        void setClipVolume(AudioClip* clip, float volume)
        {
            m_mixer.setClipVolume(clip, volume);
        }

        void setClipVolume(int handle, float volume)
        {
            m_mixer.setClipVolume(handle, volume);
        }

        float getMasterVolume() const
        {
            return m_volume;
        }

        float getTrackVolume(int handle) const
        {
            return m_mixer.getTrackVolume(handle);
        }

        int getPlayingClipCount(int track)
        {
            return m_mixer.getPlayingClipCount(track);
        }

        bool isStarted() const
        {
            return m_outputStarted;
        }

    private:
        AudioConfiguration m_configuration; //0x0C
        AudioMixer m_mixer; //0x18
        byte unk[0x10]; //0xA0
        P(Thread) m_thread; //0xB0?
        Mutex m_mutex; //0xB4
        LPDIRECTSOUND8 m_device; //0xB8
        LPDIRECTSOUNDBUFFER m_soundBuffer; //0xBC
        float m_volume; //0xC0 | Assuming official name via ABFM.
        int unk2; //0xC4
        int m_bufferBytes; //0xC8
        bool m_outputStarted; //0xCC

        static HANDLE m_handle; //0xD0
        static int m_ten; //0xD0

        static void setNotifications(LPDIRECTSOUNDBUFFER buffer, int ten, int) //Known via log
        {
            HANDLE newHandle = CreateEventW(0, 0, 1, 0);
            CloseHandle(m_handle);
            m_handle = newHandle;
            if (FAILED(newHandle))
                throwError(Exception(Format("Unable to create audio buffer fill event object (error:%d)", GetLastError())));

            m_ten = ten;
            //TODO
            //IID_IDirectSoundNotify
            //CreateEventW(0, 0, 1, 0);
            //void* p;
            HRESULT hr; // = IDirectSoundBuffer_QueryInterface(buffer, &IID_IDirectSoundNotify, p);
            LANG_LOG("Audio", LANG_LOG_PRIORITY_ERROR, "Failed to retrieve the IDirectSoundNotify interface (hr=%d)", hr); //345
        }
	};
}

#include <audio/common/AudioOutput.h>