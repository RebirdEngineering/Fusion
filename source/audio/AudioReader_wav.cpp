#include <audio/AudioReader.h>
#include <io/IOException.h>
#include <io/InputStream.h>

USING_NAMESPACE(io)
USING_NAMESPACE(lang)

BEGIN_NAMESPACE(audio)

void AudioReader::readHeader_wav() //TODO | It's clear they copied stuff from imagereader
{
    int fullSize = m_in->available(); //15

    char fileHeader[12]; //18 | Read 12 bytes of header (correct)
    memset(fileHeader, 0, sizeof(fileHeader));

	readFully(m_in, fileHeader, sizeof(fileHeader)); //Read the header
    if (strncmp(fileHeader, "RIFF", 4))
        throwError( Exception( Format("Only RIFF/WAVE sounds are currently supported"))); //23 | Currently they said, yet it was never supported even past Nibblers

    if (strncmp(&fileHeader[8], "WAVE", 4)) //27 | For now 0
        throwError( Exception( Format("Only RIFF/WAVE sounds are currently supported"))); //27

    bool fmtChunkFound = true; //29 | set to true

    while (m_in->available() > 0) //31
    {
        char chunkHeader[8]; //34 | Read 8 bytes [name, size] (correct)
        readFully(m_in, chunkHeader, sizeof(chunkHeader));
        int chunkSize = getUInt32LE(chunkHeader, 4); //38
        assert(chunkSize <= 128); //44 in ABCOSX

        if (strncmp(chunkHeader, "fmt ", 4))
            break;

        uint8_t fmtChunk[16]; //44
        m_in->read(fmtChunk, chunkSize);
        m_audioFormat = getUInt16LE(&fmtChunk, 0);
        if (m_audioFormat != 1)
            throwError(Exception(Format("WAV was not PCM! RIFF AudioEncoding TwoCC value: 0x{0,x}", m_audioFormat))); //49

        m_numChannels = getUInt16LE(fmtChunk, 2); //channels
        m_sampleRate = getUInt32LE(fmtChunk, 4); //avg samples p sec
        m_byteRate = getUInt32LE(fmtChunk, 8); //avg bytes p sec
        m_blockAlign = getUInt16LE(fmtChunk, 12); //align
        m_bitsPerSample = getUInt16LE(fmtChunk, 14); //bps

        if (!strncmp(chunkHeader, "data", 4))
            fmtChunkFound = false;

        if (!fmtChunkFound)
            throwError(Exception(Format("WAV was not PCM! RIFF AudioEncoding TwoCC value: 0x{0,x}", m_audioFormat))); //64
        
        //Correct?
        m_dataSize = chunkSize;
        m_dataBegin = fullSize - m_in->available();
    }
    
    //assert("AudioReader::readHeader_wav() is not yet decompiled.");
}

void AudioReader::readHeader_raw(const AudioConfiguration& configuration) //79
{
    m_audioFormat = 1; //PCM
    m_numChannels = configuration.m_channels;
    m_sampleRate = configuration.m_samplesPerSecond;
    m_bitsPerSample = configuration.m_bitsPerSample;
    m_blockAlign = (configuration.m_channels * configuration.m_bitsPerSample) / 8;
    m_byteRate = configuration.m_samplesPerSecond * (configuration.m_channels * configuration.m_bitsPerSample / 8);
    m_dataBegin = 0;
    m_dataSize = m_in->available();
    m_filefmt = FILEFORMAT_WAV;
}

int AudioReader::readData_wav(void* data, int offset, int size) //92
{
    m_in->seek(size + m_dataBegin, InputStream::SEEKMODE_SET); //98
    return m_in->read(data, size + offset > m_dataSize ? m_dataSize - offset : size); //return m_in->read(data, min(m_dataSize + size, m_dataSize - size)); //99 min is not called according to DWARF
}

}