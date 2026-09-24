#include <audio/AudioClipInstance.h>

namespace audio
{
    AudioClipInstance::AudioClipInstance() {} //7

    int AudioClipInstance::fetchData(void* data, int size) //9
    {
        int dataReadTotal = 0; //11

        while (m_looping && size < dataReadTotal)
        {
            int bytes = m_clip->getData((char*)data + dataReadTotal, size - dataReadTotal, m_cursor); //15
            dataReadTotal += bytes;

            if (m_looping)
                m_cursor->reset();
            else
                m_ended = true;
        }

        return dataReadTotal;
    }
}