#include <audio/AudioReader.h>
#include <io/IOException.h>
#include <io/InputStream.h>

USING_NAMESPACE(io)
USING_NAMESPACE(lang)

namespace audio
{
    AudioReader::AudioReader() :
        m_in(0),
        m_filefmt(FILEFORMAT_RAW),
        m_userData(0),
        m_blockAlign(0LL),
        m_dataSize(0LL),
        m_dataBegin(0LL),
        m_audioFormat(0LL),
        m_sampleRate(0LL),
        m_numChannels(0LL),
        m_byteRate(0LL),
        m_bitsPerSample(0LL)
    {
    }

    AudioReader::AudioReader(P(InputStream) in, FileFormat filefmt) //27
    {
        reset(m_in, filefmt, AudioConfiguration(0, 0, 0));
    }

    AudioReader::AudioReader(P(InputStream) in, const AudioConfiguration& configuration) //32
    {
        reset(in, FILEFORMAT_RAW, configuration);
    }

    void AudioReader::reset(P(InputStream) in, FileFormat filefmt, const AudioConfiguration& configuration) //37
    {
        m_in = in;
        m_filefmt = filefmt;
        m_userData = 0;
        m_blockAlign = 0LL;
        m_dataSize = 0LL;
        m_audioFormat = 0LL;
        m_sampleRate = 0LL;
        switch (filefmt)
        {
        case FILEFORMAT_RAW: readHeader_raw(configuration); break;
        case FILEFORMAT_WAV: readHeader_wav(); break;
        case FILEFORMAT_MP3: init_mp3(); readHeader_mp3(); break;
        default: throwError(IOException(Format("Unsupported audio file format while reading {0}", in->toString()))); //70
        }
    }

    AudioReader::~AudioReader() //86
    {
        if (m_filefmt == FILEFORMAT_MP3)
            deinit_mp3();
    }

    int AudioReader::readData(void* data, int offset, int size) //103
    {
        switch (m_filefmt)
        {
        case FILEFORMAT_WAV: return readData_wav(data, offset, size); break;
        case FILEFORMAT_MP3: return readData_mp3(data, offset, size); break;
        default: throwError(IOException(Format("Unsupported audio file format while reading {0}", m_in->toString()))); return 1; //116
        }
    }

    void AudioReader::readFully(P(InputStream) in, void* buf, int bytes) //120 | Carbon copy of ImageReader::readFully couldn't you use smth like FileReader::readFully this is function bloat
    {
        if (in->read(buf, bytes) != bytes)
            throwError(IOException(Format("Failed to read {0} bytes from {1}", bytes, in->toString()))); //122
    }

    uint16_t AudioReader::getUInt16LE(const void* data, int offset) //126 | Carbon copy of ImageReader::getUInt16LE, couldn't you just define it in one module?
    {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data) + offset;
        return uint16_t((unsigned(bytes[1]) << 8) + unsigned(bytes[0]));
    }

    uint32_t AudioReader::getUInt32LE(const void* data, int offset) //134 | Carbon copy of ImageReader::getUInt32LE, couldn't you just define it in one module?
    {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data) + offset;
        return (uint32_t(bytes[3]) << 24) + (uint32_t(bytes[2]) << 16) + (uint32_t(bytes[1]) << 8) + uint32_t(bytes[0]);
    }

    int AudioReader::audioFormat() const
    {
        return m_audioFormat;
    }

    int AudioReader::channels() const
    {
        return m_numChannels;
    }

    int AudioReader::sampleRate() const
    {
        return m_sampleRate;
    }

    int AudioReader::byteRate() const
    {
        return m_byteRate;
    }

    int AudioReader::blockAlign() const
    {
        return m_blockAlign;
    }

    int AudioReader::bitsPerSample() const
    {
        return m_bitsPerSample;
    }

    int AudioReader::dataSize() const
    {
        return m_dataSize;
    }
}