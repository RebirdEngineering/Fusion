#include <audio/AudioInput.h>
#include <audio/AudioInputListener.h>
#include <audio/AudioConfiguration.h>
#include <lang/Thread.h>
#include <lang/Mutex.h>
#include <lang/Exception.h>
#include <lang/Log.h>

#include <dsound.h>

using namespace lang;

namespace audio
{
	struct RecordInfo :
		public Object
	{
	public:
		RecordInfo()
		{
			m_handle = -1;
			m_curPos = 0;
		}

		int m_handle;
		unsigned int m_curPos;
		std::vector<char> m_data;
	};

class AudioInputImpl : //0x50, Only seen in KA3D but theorhetically we could restore it for Fusion via ABS 2.5.0
	public Object
{
public:
	AudioInputImpl(const AudioConfiguration& configuration) : m_configuration(configuration)
	{
		if ((m_configuration.m_channels - 1) >= 2) //?
			throwError(Exception(Format("Unsupported count of channels while creating AudioInput")));
		if (m_configuration.m_bitsPerSample != 8 && m_configuration.m_bitsPerSample != 16) //?
			throwError(Exception(Format("Unsupported bits per sample while creating AudioInput")));
		//if (m_configuration.m_samplesPerSecond < 8000 || m_configuration.m_samplesPerSecond > 48000) //?
		if (m_configuration.m_samplesPerSecond != 11025 && m_configuration.m_samplesPerSecond != 8000 && m_configuration.m_samplesPerSecond != 16000 && m_configuration.m_samplesPerSecond != 22050 && m_configuration.m_samplesPerSecond != 32000 && m_configuration.m_samplesPerSecond != 44100 && m_configuration.m_samplesPerSecond != 48000 && m_configuration.m_samplesPerSecond != 88200 && m_configuration.m_samplesPerSecond != 96000 && m_configuration.m_samplesPerSecond != 12000 && m_configuration.m_samplesPerSecond != 24000 && m_configuration.m_samplesPerSecond != 64000)
			throwError(Exception(Format("Unsupported samples per second while creating AudioInput")));

		HRESULT hr = DirectSoundCaptureCreate8(0, &m_soundCapture, 0);
		//LANG_LOG()

		//90?

		DSCBUFFERDESC desc;
		memset(&desc, 0, sizeof(DSCBUFFERDESC));
		desc.dwBufferBytes = m_bufferSize;
		desc.dwSize = sizeof(DSCBUFFERDESC);

		hr = m_soundCapture->CreateCaptureBuffer(&desc, &m_buffer, 0);

		m_recordBuffer = new RecordInfo();

		Mutex::Lock lock(m_outputIsRunning);

		//?
	}

	~AudioInputImpl()
	{
		m_buffer->Stop();
		m_buffer->Release();
		m_soundCapture->Release();
	}

	bool startInput()
	{
		return m_buffer->Start(1);
	}

	void stopInput()
	{
		m_buffer->Stop();
		m_started = false;
	}

	bool isStarted() const
	{
		return m_started;
	}

	int recordClip(float duration)
	{
		P(RecordInfo) info = new RecordInfo();

		int memoryRequired = ((((m_configuration.m_bitsPerSample / 8) * duration) * m_configuration.m_channels) * m_configuration.m_samplesPerSecond);
		info->m_data.resize(memoryRequired);
		info->m_handle = m_nextAvailableHandle;

		m_records.push_back(info);

		m_nextAvailableHandle++;
		return info->m_handle;
	}

	void stopRecord(int handle)
	{
		for (int i = 0; i < m_records.size(); i++)
		{
			if (m_records[i]->m_handle == handle)
			{
				informListenersRecordComplete(m_records[i]);
				delete m_records[i];
			}
		}
	}

	void addListener(AudioInputListener* listener)
	{
		m_listeners.resize(m_listeners.size());
		m_listeners.push_back(listener);
	}

	void removeListener(AudioInputListener* listener)
	{
		if (listener)
			m_listeners.resize(0);

		else
		{
			for (int index = 0; index < m_listeners.size(); index++)
				delete m_listeners[index];
		}
	}

private:
	static int m_nextAvailableHandle; //117

	AudioConfiguration m_configuration;
	std::vector<AudioInputListener*> m_listeners;
	std::vector<P(RecordInfo)> m_records;
	LPDIRECTSOUNDCAPTURE8 m_soundCapture; //0x30
	LPDIRECTSOUNDCAPTUREBUFFER m_buffer; //0x34
	P(RecordInfo) m_recordBuffer;
	P(Thread) m_thread; //0x38
	Mutex m_outputIsRunning;
	Mutex m_workerThreadRunning;
	unsigned int m_bufferSize;
	bool m_started; //4C

	/*
	lang::Object lang__object0;
  audio::AudioConfiguration audio__audioconfiguration8;
  _DWORD dword14;
  _DWORD dword18;
  _DWORD dword1C;
  _DWORD dword20;
  _DWORD dword24;
  _DWORD dword28;
  _DWORD dword2C;
  IDirectSoundCapture idirectsoundcapturevtbl30;
  _DWORD dword48;
  _BYTE byte4C;
	*/

	void handleFreshData(void*, int, void*, int) //134
	{
		//Unknown.
	}

	void handleRecords(void*, int, void*, int) //145
	{
		//Unknown.
	}

	void informListenersRecordComplete(const RecordInfo* ri) //167
	{
		for (int i = 0; i < m_listeners.size(); i++)
			m_listeners[i]->audioRecordingCompleted(&ri->m_data, ri->m_data.size(), m_configuration, ri->m_handle);
	}

	void informListenersRecentData(const RecordInfo* ri) //175 | Guessed, unknown use.
	{
		for (int i = 0; i < m_listeners.size(); i++)
			m_listeners[i]->audioDataReceived(&ri->m_data, ri->m_data.size(), m_configuration, ri->m_handle);
	}
};

}

#include <audio/common/AudioInput.h>