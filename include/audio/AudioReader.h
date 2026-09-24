#ifndef _AUDIO_AUDIOREADER_H
#define _AUDIO_AUDIOREADER_H

#include <io/FileFormat.h>
#include <lang/Object.h>
#include <audio/AudioConfiguration.h>

BEGIN_NAMESPACE(audio)

class AudioReader : //18
	public NS(lang, Object)
{
public:
	AudioReader(); //22

	AudioReader(P(NS(io, InputStream)) in, NS(io, FileFormat) filefmt); //28

	//typedef unsigned short uint16_t; //31
	//typedef unsigned int uint32_t; //31

	AudioReader(P(NS(io, InputStream)) in, const AudioConfiguration& configuration); //34

	~AudioReader(); //39

	void reset(P(NS(io, InputStream)) in, NS(io, FileFormat) filefmt, const AudioConfiguration& configuration); //45

	int readData(void* data, int offset, int size); //52

	int audioFormat() const; //57

	int channels() const; //62

	int sampleRate() const; //67

	int byteRate() const; //72

	int blockAlign() const; //77

	int bitsPerSample() const; //82

	int dataSize() const; //89

private:
	P(NS(io, InputStream)) m_in; //92
	NS(io, FileFormat) m_filefmt; //93
	int m_audioFormat; //95
	int m_numChannels; //96
	int m_sampleRate; //97
	int m_byteRate; //98
	int m_blockAlign; //99
	int m_bitsPerSample; //100
	int m_dataSize; //101
	int m_dataBegin; //102

	static void readFully(P(NS(io, InputStream)) in, void* buf, int bytes); //104
	static uint16_t getUInt16LE(const void* data, int offset); //105
	static uint32_t getUInt32LE(const void* data, int offset); //106

	void readHeader_wav(); //108
	void readHeader_mp3(); //109
	void readHeader_raw(const AudioConfiguration & configuration); //110

	int readData_wav(void* data, int offset, int size); //112
	int readData_mp3(void* data, int offset, int sizerequested); //113

	void init_mp3();//115
	void deinit_mp3(); //116

	void* m_userData; //118
	static int sm_refCount; //119

	AudioReader(const AudioReader&); //121
	AudioReader& operator=(const AudioReader&); //122
};

END_NAMESPACE()

#endif