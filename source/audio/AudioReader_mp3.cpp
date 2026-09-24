#include <audio/AudioReader.h>
#include <io/InputStream.h>
#include <external/mpg123/src/libmpg123/mpg123.h>
#include <lang/Log.h>
#include <io/IOException.h>

USING_NAMESPACE(lang)
USING_NAMESPACE(io)

BEGIN_NAMESPACE(audio)

void AudioReader::init_mp3() //26
{
    if (!sm_refCount++ && !mpg123_init())
        throwError(IOException(Format("Failed to initialize MPG123 while reading {0}", m_in->toString())));
}

void AudioReader::deinit_mp3()
{
    mpg123_delete((mpg123_handle*)m_userData);
    if (!--sm_refCount)
        mpg123_exit();
}

void AudioReader::readHeader_mp3() //[TODO] | https://github.com/nadult/FreeFT/blob/d0b09a3bbc189fc777b4f62864ccbd4838fd146b/src/audio/mp3_decoder.cpp
{
    const int BUFFER_SIZE = 2048; //41
    unsigned char buf[BUFFER_SIZE]; //42

    int ret; //44

    m_userData = mpg123_new(0, &ret);
    if (!m_userData || ret) //?
        throwError( IOException( Format("Failed to allocate MPG123 while reading {0}", m_in->toString()) ) ); //47

    if (mpg123_open_feed((mpg123_handle*)m_userData))
        throwError( IOException( Format("Failed to open MPG123 feed while reading {0}", m_in->toString()) ) ); //50

    do //Correct?
    {
        int sizeRead = m_in->read(buf, BUFFER_SIZE); //54
        ret = mpg123_decode((mpg123_handle*)m_userData, buf, sizeRead, 0, 0, 0);

        if (ret != MPG123_NEW_FORMAT && ret != MPG123_NEED_MORE)
            throwError(IOException(Format("Failed to read MP3 header while reading {0}", m_in->toString()))); //58
    } while (ret != MPG123_NEW_FORMAT);

    long int rate; //62 | long int? 
    int enc; //63

    mpg123_getformat((mpg123_handle*)m_userData, &rate, &m_numChannels, &enc); //?
    m_sampleRate = rate;

    if ((enc & MPG123_ENC_8) == 15) //?
        m_bitsPerSample = 8;

    else if ((enc & MPG123_ENC_16) != 0)
        m_bitsPerSample = 16;

    else if ((enc & MPG123_ENC_32) != 0)
        m_bitsPerSample = 32;

    else
        throwError(IOException(Format("Invalid bits per sample while reading {0}",m_in->toString()) ) ); //72

    m_dataSize = -1;
    //assert("AudioReader::readHeader_mp3() is not yet fully decompiled.");
}

int AudioReader::readData_mp3(void* data, int offset, int sizerequested) //77
{
    /*assert(offset >= 0); //105 ABC 1.0.0 OSX
    assert(sizerequested >= 0); //106 ABC 1.0.0 OSX

    const int BUFFER_SIZE = 2048; //82
    unsigned char buf[BUFFER_SIZE]; //83

    off_t currentOffset = mpg123_tell((mpg123_handle*)m_userData); //86
    int wantedOffset = offset / ((m_bitsPerSample >> 3) * m_numChannels); //87
    if (currentOffset != wantedOffset)
    {
        off_t input_offset; //91
        off_t result = mpg123_feedseek((mpg123_handle*)m_userData, wantedOffset, 0, &input_offset); //92
        do
        {
            int len = m_in->read(buf, BUFFER_SIZE); //95
            int ret = mpg123_feed((mpg123_handle*)m_userData, dataOut, sizeRead); //96
            assert(ret == MPG123_OK); //123 ABC OSX
        } while (m_in->seek(input_offset, InputStream::SEEKMODE_SET));

        size_t sizeread;
        int ret = mpg123_decode((mpg123_handle*)m_userData, 0, 0, data, sizerequested, ;// 107

        int len = m_in->available(); //116
        

        //if (mpg123_feed((mpg123_handle*)m_userData, dataOut, sizeRead))
        //assert(ret == MPG123_OK); //134 ABC OSX
        //while (currentOffset != mpg123_feedseek(m_userData, currentOffset, 0,))

        m_in->skip(BUFFER_SIZE);
    }

    unsigned char* dataOut; //103

    size_t sizeread; //106
    int ret; //107*/

    //return ? - data;*/

    /*

    off_t currentOffset = mpg123_tell((mpg123_handle*)m_userData); //86
    int wantedOffset = offset / ((m_bitsPerSample >> 3) * m_numChannels); //87
    if (wantedOffset != currentOffset)
    {
		off_t input_offset = mpg123_seek((mpg123_handle*)m_userData, wantedOffset, SEEK_SET);
		off_t result = mpg123_tell((mpg123_handle*)m_userData);
    }
    unsigned char* dataOut; //103

    size_t sizeread; //106
    int ret; //107

    {
        off_t input_offset; //91
        off_t result; //92

        {
            int len = m_in->; //95
            int ret; //96
        }
    }

    int len = m_in->available(); //116

    assert(ret == MPG123_OK); //123
    assert(ret == MPG123_DONE || ret == MPG123_NEED_MORE || ret == MPG123_OK); //134
    assert(ret == MPG123_DONE || ret == MPG123_NEED_MORE || ret == MPG123_OK); //146
    return outmemory - data;
    LANG_LOG_DEBUG("Audio", LANG_LOG_PRIORITY_ERROR, "AudioReader::readData_mp3() ANOMALOUS BUFFER READ, returned len: %d", mlen); //119 (ABC 3.0.1 OSX)*/
    assert("AudioReader::readData_mp3(void* data, int offset, int sizerequested) is not yet decompiled.");
    return 1;
}

}