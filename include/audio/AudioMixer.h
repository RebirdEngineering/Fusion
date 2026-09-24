#ifndef _AUDIO_AUDIOMIXER_H
#define _AUDIO_AUDIOMIXER_H

#include <lang/Mutex.h>
#include <audio/AudioClipInstance.h>

namespace audio
{

class AudioMixer :
	public lang::Object
{
public:
	static const int TRACKS_SUPPORTED = 8; //22

	AudioMixer(); //27

	~AudioMixer(); //32

	void start(); //37

	void stop(); //42

	int playClip(AudioClip* clip, float volume, int track, bool looping); //52

	void resumeClip(int handle); //58 | Recovered from ABFM.

	void pauseClip(AudioClip* clip); //64

	void pauseClip(int track); //70

	void stopClip(AudioClip* clip); //76

	void stopClip(int handle); //82

	bool isClipPlaying(AudioClip* clip); //88

	bool isClipPlaying(int handle); //94

	void resumeClips(); //99

	void pauseClips(); //104

	void stopClips(); //109

	void setTrackVolume(float volume, int track); //116

	void setClipCountLimit(int track, int count); //123

	void setClipVolume(AudioClip* clip, float volume); //130

	void setClipVolume(int, float volume); //137

	float getTrackVolume(int track) const; //143

	int getPlayingClipCount(int track); //149

	void mixUnlimited8(const AudioConfiguration& conf, void* output, unsigned int size); //156

	void mixUnlimited16(const AudioConfiguration& conf, void* output, unsigned int size); //163

	void mixUnlimited8to16(const AudioConfiguration& conf, void* output, unsigned int size); //172

private:
	void flushQueueAndRemoveEndedClips(); //175

	lang::Mutex m_mutex; //177

	float m_trackVolume[TRACKS_SUPPORTED]; //180

	unsigned int m_trackClipLimits[TRACKS_SUPPORTED]; //183

	std::vector<unsigned char> m_unsignedCharTemp; //186
	std::vector<int> m_intTemp; //187

	std::vector<AudioClipInstance> m_clips; //190
	std::vector<AudioClipInstance> m_clipsAddQueue; //191

	int m_instanceID; //194

	bool m_started; //196
};

}

#endif