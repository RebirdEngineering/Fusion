#ifndef _PF_COMMON_VIDEOPLAYERIMPLBASE_H
#define _PF_COMMON_VIDEOPLAYERIMPLBASE_H

#include <pf/VideoPlayer.h>

namespace pf
{

class VideoPlayerImplBase : public lang::Object
{
public:
	VideoPlayerImplBase(VideoPlayer*);

	virtual bool play(const std::string&, bool float) = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void close() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual bool isPaused();
	virtual bool playStart();

	virtual void addExtraButton(const std::string& buttonId, const std::string& image, VideoPlayer::ExtraButtonPosition position)
	{
		//_fusion_done, _fusion_done2, _fusion_done3, _fusion_broke, _fusion_range, _fusion_i, _fusion_e //Is this autogen?
		ExtraButtonInfo info;
		info.buttonId = buttonId;
		info.image = image;
		info.position = position;
		m_extraButtons.push_back(info);
	}

	virtual void addExtraLayer(const std::string& image, float secondsVisible, VideoPlayer::ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize)
	{
		ExtraLayerInfo info;
		info.image = image;
		info.secondsVisible = secondsVisible;
		info.position = position;
		info.text = text;
		info.font = font;
		info.fontSize = fontSize;
		m_extraLayers.push_back(info);
	}

	virtual void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints)
	{
		m_cuePoints = cuePoints;
	}

	virtual void clearCuePoints()
	{
		m_cuePoints.clear();
	}

	virtual void announceVideoPreparing(const std::string& playedVideo)
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announceVideoStarted()
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announcePlay(float secondsPlayed) //operator cuepoint?
	{
		//std::vector<VideoPlayerListener::CuePoint> reachedCuePoints = m_cuePoints;
		//int p;
		//reachedCuePoints.end();
		// 
		//reachedCuePoints.size();
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announceVideoEnded(VideoPlayerListener::PlaybackEndReason endReason, float secondsPlayed, float secondsTotal)
	{
		/*for (m_listeners.begin() != m_listeners.end())
		{
			//?
		}
		m_playlistIndex++;*/

	}

	virtual void announceVideoPlaylistEnded()
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announceVideoCancelled()
	{
		//while (m_listeners.begin(); != )
	}

	virtual void announceExtraButtonClicked(const std::string& buttonId)
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//?
		}
	}

	virtual void setLooping(bool looping)
	{
		m_looping = looping;
	}

	virtual void addListener(VideoPlayerListener* listener)
	{
		if (listener)
			m_listeners.insert(listener);
	}

	virtual void removeListener(VideoPlayerListener* listener)
	{
		if (listener)
			m_listeners.erase(listener);
	}

	virtual void setFullscreen() {}

	virtual void setSize(int, int, int, int) {} //Unknown parameters, no code.

	virtual void setSource(const std::string& filename, float startPositionSeconds)
	{
		m_playListIndex = 0;
		m_playList.clear();
		VideoPlayerPlayListItem newPlayListItem;
		newPlayListItem.setInterfaceType();
		newPlayListItem.setStartPositionSeconds(startPositionSeconds);
		m_playList.push_back(newPlayListItem); //?
	}

	virtual void setSource(const VideoPlayerPlayListItem& item)
	{
		m_playlistIndex = 0;
		m_playList.clear();
		m_playList.push_back(item);
	}

	virtual void setSource(const std::vector<VideoPlayerPlayListItem>& playlist)
	{
		m_playlistIndex = 0;
		m_playList = playlist;
	}

	virtual bool isPlayListEnded()
	{
		return false; //(*m_playlistIndex) >= (*(? )) - () ? )) >> 3; //?
	}

	void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed)
	{
		m_imagePath_normal = imageNormal;
		m_imagePath_pressed = imagePressed;
	}

	const std::string& getCloseButtonImagePathNormal() //Not defined on iOS
	{
		return m_imagePath_normal;
	}

	const std::string& getCloseButtonImagePathPressed() //Not defined on iOS
	{
		return m_imagePath_pressed;
	}

	virtual bool playTheNextPlayListItemIfAvailable()
	{
		if (m_looping && isPlayListEnded()) //?
		{
			m_playList = 0;
			return false;
		}
		//m_playList.size();
		//m_playList.size();
		std::string url = m_playList[0]->getUrl();

		return false; //?
	}
protected:
	VideoPlayer* m_videoPlayer;
	std::set<VideoPlayerListener*> m_listeners;
	std::vector<VideoPlayerPlayListItem*> m_playList;
	int m_playlistIndex;
	bool m_looping;
	std::string m_imagePath_normal; //Huh? Why split with another underscore
	std::string m_imagePath_pressed; //Huh? Why split with another underscore
	struct ExtraButtonInfo
	{
		std::string buttonId;
		std::string image;
		VideoPlayer::ExtraButtonPosition position;
	};
	std::vector<ExtraButtonInfo> m_extraButtons;
	struct ExtraLayerInfo
	{
		std::string image;
		std::string text;
		std::string font;
		VideoPlayer::ExtraButtonPosition position;
		float secondsVisible;
		float fontSize;
	};
	std::vector<ExtraLayerInfo> m_extraLayers;
	std::vector<VideoPlayerListener::CuePoint> m_cuePoints;
private:
	VideoPlayerImplBase();
};

}

#endif //! _PF_COMMON_VIDEOPLAYERIMPLBASE_H