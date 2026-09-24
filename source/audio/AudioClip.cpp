#include <audio/AudioClip.h>
#include <io/ByteArrayInputStream.h>

using namespace io;

namespace audio
{
    AudioClip::~AudioClip()
    {
    }

    AudioClip::AudioClip(P(InputStream) in, FileFormat fmt)
    {
        m_in = in;
        m_reader = new AudioReader(in, fmt);
    }

    AudioClip::AudioClip(const void* data, int size, const AudioConfiguration& configuration)
    {
        m_in = new ByteArrayInputStream(data, size);
        m_reader = new AudioReader(m_in, configuration);
    }

    int AudioClip::getData(void* data, int size, AudioClipCursor* cursor)
    {
        int bytes = m_reader->readData(data, cursor->m_offset1, size); //?
        return bytes += cursor->m_offset1;
    }

    int AudioClip::audioFormat() const
    {
        return m_reader->audioFormat();
    }

    int AudioClip::bitsPerSample() const
    {
        return m_reader->bitsPerSample();
    }

    int AudioClip::blockAlign() const
    {
        return m_reader->blockAlign();
    }

    int AudioClip::byteRate() const
    {
        return m_reader->byteRate();
    }

    int AudioClip::channels() const
    {
        return m_reader->channels();
    }

    int AudioClip::sampleRate() const
    {
        return m_reader->sampleRate();
    }

    int AudioClip::dataSize() const
    {
        return m_reader->dataSize();
    }
}