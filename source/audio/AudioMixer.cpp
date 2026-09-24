#include <audio/AudioMixer.h>
#include <lang/Exception.h>

using namespace lang;

namespace audio
{

AudioMixer::AudioMixer()
{
    m_started = false;
    m_instanceID = 0;
    for (int i = 0; i < TRACKS_SUPPORTED; i++) //16
    {
        m_trackVolume[i] = 1.0f;
        m_trackClipLimits[i] = -1;
    }
}

AudioMixer::~AudioMixer() //25
{
	Mutex::Lock lock(m_mutex); //26
    stop();
}

void AudioMixer::start()
{
    m_started = true;
}

void AudioMixer::stop()
{
    m_started = false;
}

int AudioMixer::playClip(AudioClip* clip, float volume, int track, bool looping) //40
{
    if (!m_started || getPlayingClipCount(track) >= m_trackClipLimits[track])
        return -1;

    Mutex::Lock lock(m_mutex); //45
    AudioClipInstance inst; //46

    inst.m_clip = clip; //48
    inst.m_cursor = new AudioClipCursor(); //49
    inst.m_cursor->m_offset1 = 0;
    inst.m_cursor->m_offset2 = 0;
    inst.m_volume = volume;
    m_instanceID++;
    inst.m_id = m_instanceID;
    inst.m_track = track;
    inst.m_looping = looping;
    inst.m_paused = false;
    inst.m_ended = false;
	m_clipsAddQueue.push_back(inst); //57
    return inst.m_id;
}

void AudioMixer::resumeClip(int handle) //Not seen on iOS. | Correct?
{
    Mutex::Lock lock(m_mutex);

    for (int i = 0; i < m_clips.size(); i++)
    {
        if (m_clips[i].m_id == handle)
            m_clips[i].m_paused = false;
    }

    for (int i = 0; i < m_clipsAddQueue.size(); i++)
    {
        if (m_clipsAddQueue[i].m_id == handle)
            m_clipsAddQueue[i].m_paused = false;
    }

    //assert("void AudioMixer::resumeClip(int track) is not yet decompiled.");
}

void AudioMixer::resumeClips() //Not seen on iOS. Correct?
{
    Mutex::Lock lock(m_mutex);

    for (int i = 0; i < m_clips.size(); i++) //105
        m_clips[i].m_paused = false; //106

    for (int i = 0; i < m_clipsAddQueue.size(); i++) //109
        m_clipsAddQueue[i].m_paused = false; //110

    //assert("void AudioMixer::resumeClips() is not yet decompiled.");
}

bool AudioMixer::isClipPlaying(AudioClip* clip) //101
{
    Mutex::Lock lock(m_mutex); //103

    for (size_t i = 0; i < m_clips.size(); i++) //105
    {
        if (m_clips[i].m_clip == clip && !m_clips[i].m_ended) //106
            return true;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //109
    {
        if (m_clipsAddQueue[i].m_clip == clip && !m_clipsAddQueue[i].m_ended) //110
            return true;
    }
    //Correct?
    return false;
}

bool AudioMixer::isClipPlaying(int handle) //117
{
    Mutex::Lock lock(m_mutex); //119

    for (size_t i = 0; i < m_clips.size(); i++) //121
    {
        if (m_clips[i].m_id == handle)
            return true;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //125
    {
        if (m_clipsAddQueue[i].m_id == handle)
            return true;
    }
    //Correct?
    //assert("AudioMixer::isClipPlaying(int handle) is not yet decompiled.");
    return false;
}

void AudioMixer::stopClip(AudioClip* clip) //133
{
    Mutex::Lock lock(m_mutex); //135

    for (size_t i = 0; i < m_clips.size(); i++) //137
    {
        if (m_clips[i].m_clip == clip) //138
            m_clips[i].m_ended = true;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //141
    {
        if (m_clipsAddQueue[i].m_clip == clip) //142
            m_clipsAddQueue[i].m_ended = true;
    }
    //Correct?
    //assert("AudioMixer::stopClip(AudioClip* clip) is not yet decompiled.");
}

void AudioMixer::stopClip(int handle) //146
{
    Mutex::Lock lock(m_mutex); //148

    for (size_t i = 0; i < m_clips.size(); i++) //150
    {
        if (m_clips[i].m_id == handle)
            m_clips[i].m_ended = true;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //154
    {
        if (m_clipsAddQueue[i].m_id == handle)
            m_clipsAddQueue[i].m_ended = true;
    }
    //Correct?
    //assert("AudioMixer::stopClip(AudioClip* clip) is not yet decompiled.");
}

void AudioMixer::setClipVolume(AudioClip* clip, float volume) //159
{
    Mutex::Lock lock(m_mutex); //161

    for (size_t i = 0; i < m_clips.size(); i++) //163
    {
        if (m_clips[i].m_clip == clip) //164
            m_clips[i].m_volume = volume;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //167
    {
        if (m_clipsAddQueue[i].m_clip == clip) //168
            m_clipsAddQueue[i].m_volume = volume;
    }
    //Correct?
    //assert("AudioMixer::setClipVolume(AudioClip* clip, float volume) is not yet decompiled.");
}

void AudioMixer::stopClips()
{
    Mutex::Lock lock(m_mutex); //209

    for (size_t i = 0; i < m_clips.size(); i++) //211
        m_clips[i].m_ended = true;

    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //214
        m_clipsAddQueue[i].m_ended = true;

    //assert("AudioMixer::mixUnlimited8() is not yet decompiled.");
}

void AudioMixer::setTrackVolume(float volume, int track) //218
{
    //if (track > TRACKS_SUPPORTED)
        //throwError(Exception(Format("Track {0} out of bounds! Range [0-{1}]", track, TRACKS_SUPPORTED - 1))); //221 | In official code this is this a float just why

    //m_trackVolume[track] = volume; //For now
    //m_trackVolume[track] = fminf(1.0f, fmaxf(0.0f, volume)); //From MacOS
    //Correct?
    //m_trackVolume[track] = min(1.0f, max(0.0f, volume)); //Correct?
    //m_trackVolume[track] = min(max(volume, 0), 1);
    assert("AudioMixer::setTrackVolume(float volume, int track) is yet decompiled.");
}

void AudioMixer::setClipCountLimit(int track, int count) //229
{
    if (track > TRACKS_SUPPORTED)
        throwError(Exception(Format("Track {0} out of bounds! Range [0-{1}]", track, TRACKS_SUPPORTED - 1))); //232 | In official code this is this returned as a float just why

    m_trackClipLimits[track] = count;
}

float AudioMixer::getTrackVolume(int track) const //237
{
    if (track > TRACKS_SUPPORTED)
        throwError(Exception(Format("Track {0} out of bounds! Range [0-{1}]", track, TRACKS_SUPPORTED - 1))); //240

    return m_trackVolume[track];
}

int AudioMixer::getPlayingClipCount(int track) //245 |  Correct?
{
    if (track > TRACKS_SUPPORTED)
        throwError(Exception(Format("Track {0} out of bounds! Range [0-{1}]", track, TRACKS_SUPPORTED - 1))); //248

    Mutex::Lock lock(m_mutex);

    int count = 0; //252
    for (size_t i = 0; i < m_clips.size(); i++) //253 | ?
    {
        if (m_clips[i].m_track == track && !m_clips[i].m_ended)
            count++;
    }
    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //259
    {
        if (m_clipsAddQueue[i].m_track == track && !m_clipsAddQueue[i].m_ended)
            count++;
    }
    //assert("AudioMixer::getPlayingClipCount(AudioClip* clip, float volume) is not yet fully decompiled.");
    return count;
    //return 0;
}

void AudioMixer::flushQueueAndRemoveEndedClips()
{
    Mutex::Lock lock(m_mutex); //270

    for (size_t i = 0; i < m_clipsAddQueue.size(); i++) //272
        m_clips.push_back(m_clipsAddQueue[i]); //273

    for (int i = 0; i < m_clips.size(); i++) //275
    {
        if (m_clips[i].m_ended)
            delete &m_clips[i]; //277
    }

    m_clipsAddQueue.clear(); //281

    //assert("AudioMixer::flushQueueAndRemoveEndedClips() is not yet decompiled.");
}

void AudioMixer::mixUnlimited16(const AudioConfiguration& conf, void* output, unsigned int size) //355
{
    /*unsigned int sampleCount = size >> 1; //357

    if (sampleCount > m_intTemp.size()) //360
        m_intTemp.resize(sampleCount, 0); //361
    //m_intTemp[] //362

    memset(&m_intTemp, 0, 4 * sampleCount);

    flushQueueAndRemoveEndedClips();

    for (size_t clipIndex = 0; clipIndex < m_clips.size(); clipIndex++) //368
    {
        if (!m_clips[clipIndex].m_paused && !m_clips[clipIndex].m_ended)
        {
            float clipVolume = m_clips[clipIndex].m_volume; //374
            float trackVolume = m_trackVolume[m_clips[clipIndex].m_track]; //375
            int volume = clipVolume * trackVolume; //376

            unsigned int clipDataSize = conf.m_channels != 2 && m_clips[clipIndex].m_clip->channels() == 1 ? size : sampleCount; //385

            //if (m_clips[clipIndex].m_clip->channels() == 1)

            int dataSize = m_clips[clipIndex].fetchData(&m_unsignedCharTemp, clipDataSize); //399
        }

        //->AudioClip-> //378
        //m_unsignedCharTemp[]; //379

        

        //m_clips[] //386
        //m_clips[] //387
        //m_clips[] //388
        //m_unsignedCharTemp.size(); //396
        //m_unsignedCharTemp.resize(); //397

        //int dataSize = m_unsignedCharTemp[]; //399
    }

    //int dataCount = ; //404
    //int* output32 = &m_intTemp[]; //406
    //const short* clipData = m_unsignedCharTemp[]; //407

    //m_clips?[]; //409
    
    {
        //const short* end = []; //412

        //int result; //414
    }

    //m_clips?[] //419

    {
        //const short* end = []; //422
        {
            int sampleA; //424
            int sampleb; //425
        }
    }

    //const short* end = []; //433

    //m_intTemp[] //443
    int* it; //444

    int sample; //447

    //.size() //360
    //m_intTemp.resize() //360

    /*unsigned int sampleCount = m_intTemp.size();
    short* output16 = ; //442
    int* end; //443
    
    //.resize()
    //_ZNSt6vectorIiSaIiEEixEm
    //size_t clipIndex = m_clips.size(); //368 | ?
    float clipVolume; //374
    float trackVolume; //375
    unsigned int clipDataSize;
    int volume;
    int dataSize;
    int* output32;
    int dataCount;
    const short* clipData;*/
    //flushQueueAndRemoveEndedClips();*/
    assert("AudioMixer::mixUnlimited16() is not yet decompiled.");
}

void AudioMixer::mixUnlimited8(const AudioConfiguration& conf, void* output, unsigned int size) //453
{
    /*if (size > m_intTemp.size()) //456
        m_intTemp.resize(size, 0); //457
    memset(&m_intTemp, 0, 4 * size); //458 []//?

    flushQueueAndRemoveEndedClips();
    
    for (size_t clipIndex = 0; clipIndex < m_clips.size(); clipIndex++) //464
    {
        float clipVolume = m_clips[clipIndex].m_volume; //470
        float trackVolume = m_trackVolume[m_clips[clipIndex].m_track]; //471
        float volume = trackVolume * clipVolume * 256.0; //472
        
        unsigned int clipDataSize = 0; //481

        //int dataSize = ; //495

        {
            {
                {
                    {
                        //m_clips[]
                        {

                            //m_clips[] //513

                            {
                                //int* output32 = &m_intTemp[]; //516
                                //unsigned char* clipData = m_unsignedCharTemp[]; //517
                                //unsigned char* end; //518
                                {
                                    int sampleA; //520
                                    int sampleB; //521
                                }
                            }

                            //int* output32 = &m_intTemp[]; //529
                            //unsigned char* clipData = m_unsignedCharTemp[]; //530
                            unsigned char* end; //531
                        }
                    }
                }
            }
        }
    }

    //unsigned char* output8 = ; //540
    //int* end = m_intTemp.; //541
    //size_t clipIndex;
    //float clipVolume;
    //float trackVolume;
    //unsigned int clipDataSize;
    //int volume;
    //int dataSize;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //int sampleA;
    //int sampleB;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //int result;
    //int* it;
    //int sample;*/

    assert("AudioMixer::mixUnlimited8() is not yet decompiled.");
}

void AudioMixer::mixUnlimited8to16(const AudioConfiguration& conf, void* output, unsigned int size) //inline
{
    /*int sampleCount = size >> 1;

    if (sampleCount > m_unsignedCharTemp.size())
        m_unsignedCharTemp.resize(sampleCount, 0);

    if (sampleCount > m_intTemp.size())
        m_intTemp.resize(sampleCount, 0);

    memset(&m_intTemp, 0, 4 * size);

    flushQueueAndRemoveEndedClips();

    //for (size_t clipIndex = 0; < m_clips.size(); clipIndex++)
    {
        float clipVolume = m_clips[clipIndex].m_volume;
        float trackVolume = m_clips[clipIndex].m_volume;
        int volume = m_clips[clipIndex].m_volume;

        int clipDataSize;
        int dataSize;

        int* output32;
        unsigned char* clipData;

        unsigned char* clipData;
    }


    //unsigned char* output8 = ;
    //int* end = m_intTemp.;
    //size_t clipIndex;
    //float clipVolume;
    //float trackVolume;
    //unsigned int clipDataSize;
    //int volume;
    //int dataSize;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //int sampleA;
    //int sampleB;
    //unsigned char* clipData;
    //int* output32;
    //unsigned char* end;
    //int result;
    //int* it;
    //int sample;*/
    assert("AudioMixer::mixUnlimited8to16() is not yet decompiled.");
}

}