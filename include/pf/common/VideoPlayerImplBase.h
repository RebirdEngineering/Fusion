#ifndef _PF_COMMON_VIDEOPLAYERIMPLBASE_H
#define _PF_COMMON_VIDEOPLAYERIMPLBASE_H

#include <lang/Object.h>
#include <pf/VideoPlayer.h>

namespace pf
{
class VideoPlayer;

class VideoPlayerImplBase : public lang::Object //15
{
public:
	VideoPlayerImplBase(VideoPlayer*); //20

	virtual bool play(const std::string&, bool, float) = 0; //27
	virtual void show() = 0; //28
	virtual void hide() = 0; //29
	virtual void close() = 0; //30
	virtual void pause() = 0; //31
	virtual void resume() = 0; //32
	virtual bool isPaused() const //33
	{
		return false;
	}

	virtual bool playStart() //38
	{
		m_playlistIndex = 0;
		playTheNextPlayListItemIfAvailable();
	}

	virtual void addExtraButton(const std::string& buttonId, const std::string& image, VideoPlayer::ExtraButtonPosition position) //44
	{
		//_fusion_done, _fusion_done2, _fusion_done3, _fusion_broke, _fusion_range, _fusion_i, _fusion_e //Is this autogen?
		ExtraButtonInfo info;

		if (buttonId.size())
			info.buttonId = buttonId;
		if (image.size())
			info.image = image;

		info.position = position;

		m_extraButtons.push_back(info);
	}

	virtual void addExtraLayer(const std::string& image, float secondsVisible, VideoPlayer::ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize) //60
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

	virtual void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints) //72
	{
		m_cuePoints = cuePoints;
	}

	virtual void clearCuePoints() //77
	{
		m_cuePoints.clear();
	}

	virtual void announceVideoPreparing(const std::string& playedVideo) //82
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announceVideoStarted() //93
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announcePlay(float secondsPlayed) //104 | operator cuepoint?
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

	virtual void announceVideoEnded(VideoPlayerListener::PlaybackEndReason endReason, float secondsPlayed, float secondsTotal) //128
	{
		/*for (m_listeners.begin() != m_listeners.end())
		{
			//?
		}
		m_playlistIndex++;*/

	}

	virtual void announceVideoPlaylistEnded() //146
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//delete m_listeners[observerIt]; ?
		}
	}

	virtual void announceVideoCancelled() //159
	{
		//while (m_listeners.begin(); != )
	}

	virtual void announceExtraButtonClicked(const std::string& buttonId) //170
	{
		for (std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++)
		{
			//?
		}
	}

	virtual void setLooping(bool looping) //181
	{
		m_looping = looping;
	}

	virtual void addListener(VideoPlayerListener* listener) //186
	{
		if (listener)
			m_listeners.insert(listener);
	}

	virtual void removeListener(VideoPlayerListener* listener) //194
	{
		if (listener)
			m_listeners.erase(listener);
	}

	virtual void setFullscreen() {} //202

	virtual void setSize(int, int, int, int) //207 | Unknown parameters, no code.
	{
	}

	virtual void setSource(const std::string& filename, float startPositionSeconds) //212
	{
		m_playlistIndex = 0;
		m_playList.clear();
		VideoPlayerPlayListItem newPlayListItem;
		//newPlayListItem.setInterfaceType();
		newPlayListItem.setStartPositionSeconds(startPositionSeconds);
		m_playList.push_back(newPlayListItem); //?
	}

	virtual void setSource(const VideoPlayerPlayListItem& item) //223
	{
		m_playlistIndex = 0;
		m_playList.clear();
		m_playList.push_back(item);
	}

	virtual void setSource(const std::vector<VideoPlayerPlayListItem>& playlist) //230
	{
		m_playlistIndex = 0;
		m_playList = playlist;
	}

	virtual bool isPlayListEnded() //236
	{
		return false; //(*m_playlistIndex) >= (*(? )) - () ? )) >> 3; //?
	}

	void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed) //241
	{
		m_imagePath_normal = imageNormal;
		m_imagePath_pressed = imagePressed;
	}

	const std::string& getCloseButtonImagePathNormal() //247 | Not defined on iOS
	{
		return m_imagePath_normal;
	}

	const std::string& getCloseButtonImagePathPressed() //252 | Not defined on iOS
	{
		return m_imagePath_pressed;
	}

	virtual bool playTheNextPlayListItemIfAvailable() //259
	{
		if (m_looping && isPlayListEnded()) //?
		{
			m_playList.clear();
			return false;
		}
		//m_playList.size();
		//m_playList.size();
		//std::string url = m_playList->getUrl();

		return false; //?
	}
protected:
	VideoPlayer* m_videoPlayer; //274
	std::set<VideoPlayerListener*> m_listeners; //275
	std::vector<VideoPlayerPlayListItem> m_playList; //276
	int m_playlistIndex; //277
	bool m_looping; //278
	std::string m_imagePath_normal; //279 | Huh? Why split with another underscore
	std::string m_imagePath_pressed; //280 | Why split with another underscore

	struct ExtraButtonInfo //282
	{
		std::string buttonId; //284
		std::string image; //285
		VideoPlayer::ExtraButtonPosition position; //286
	};
	std::vector<ExtraButtonInfo> m_extraButtons; //288

	struct ExtraLayerInfo //290
	{
		std::string image; //292
		std::string text; //293
		std::string font; //294
		VideoPlayer::ExtraButtonPosition position; //295
		float secondsVisible; //296
		float fontSize; //297
	};
	std::vector<ExtraLayerInfo> m_extraLayers; //299
	std::vector<VideoPlayerListener::CuePoint> m_cuePoints; //301

private:
	VideoPlayerImplBase(); //304
};

}

#endif //! _PF_COMMON_VIDEOPLAYERIMPLBASE_H