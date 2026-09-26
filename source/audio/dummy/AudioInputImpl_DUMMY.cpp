#include <audio/AudioInput.h>
#include <audio/AudioInputListener.h>
#include <lang/Thread.h>
#include <lang/Mutex.h>
#include <lang/Exception.h>

USING_NAMESPACE(lang)

BEGIN_NAMESPACE(audio)

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

class AudioInputImpl : //ABS410, OSX
	public Object
{
public:
	AudioInputImpl(const AudioConfiguration& configuration) //32
	{
		m_configuration.m_samplesPerSecond = configuration.m_samplesPerSecond;
		m_configuration.m_channels = configuration.m_channels;
		m_currPos = 0;
		m_bufferSize = 0;
		m_started = false;
		//if (m_configuration.m_channels > 2 || m_configuration.m_channels < 1) //? from XNA
		if ((m_configuration.m_channels - 1) >= 2) //?
			throwError(Exception(Format("Unsupported count of channels while creating AudioInput")));
		if (m_configuration.m_bitsPerSample != 8 && m_configuration.m_bitsPerSample != 16) //?
			throwError(Exception(Format("Unsupported bits per sample while creating AudioInput")));
		//if (m_configuration.m_samplesPerSecond < 8000 || m_configuration.m_samplesPerSecond > 48000) //?
		if (m_configuration.m_samplesPerSecond != 11025 && m_configuration.m_samplesPerSecond != 8000 && m_configuration.m_samplesPerSecond != 16000 && m_configuration.m_samplesPerSecond != 22050 && m_configuration.m_samplesPerSecond != 32000 && m_configuration.m_samplesPerSecond != 44100 && m_configuration.m_samplesPerSecond != 48000 &&m_configuration.m_samplesPerSecond != 88200 && m_configuration.m_samplesPerSecond != 96000 && m_configuration.m_samplesPerSecond != 12000 && m_configuration.m_samplesPerSecond != 24000 && m_configuration.m_samplesPerSecond != 64000)
			throwError(Exception(Format("Unsupported samples per second while creating AudioInput")));
	}

	~AudioInputImpl() //53
	{}

	bool startInput() //57
	{
		return true;
	}

	void stopInput() //62
	{}

	bool isStarted() const //66
	{
		return m_started;
	}

	int recordClip(float duration) //71
	{
		P(RecordInfo) info = new RecordInfo();

		int memoryRequired = ((((m_configuration.m_bitsPerSample / 8) * duration) * m_configuration.m_channels) * m_configuration.m_samplesPerSecond);
		info->m_data.resize(memoryRequired);
		info->m_handle = m_nextAvailableHandle;

		m_records.push_back(info);

		m_nextAvailableHandle++;
		return info->m_handle;
	}

	void stopRecord(int handle) //85
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
	void addListener(AudioInputListener* listener) //98
	{
		m_listeners.resize(m_listeners.size());
		m_listeners.push_back(listener);
	}

	void removeListener(AudioInputListener* listener) //104
	{
		if (listener)
			m_listeners.resize(0);

		else
		{
			for (int index = 0; index < m_listeners.size(); index++) //Given sparatic line numbers it's very likely they do this
				delete m_listeners[index];
		}
	}

private:
	static int m_nextAvailableHandle; //117

	AudioConfiguration m_configuration; //119
	std::vector<AudioInputListener*> m_listeners; //120
	std::vector<P(RecordInfo)> m_records; //121
	P(RecordInfo) m_recordBuffer; //122

	P(Thread) m_thread; //124

	Mutex m_outputIsRunning; //126
	Mutex m_workerThreadRunning; //127

	int m_currPos; //129
	unsigned int m_bufferSize; //130

	bool m_started; //132

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

END_NAMESPACE()

#include <audio/common/AudioInput.h> //Yeah