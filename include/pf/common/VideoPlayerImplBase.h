#ifndef _PF_COMMON_VIDEOPLAYERIMPLBASE_H
#define _PF_COMMON_VIDEOPLAYERIMPLBASE_H

#include <lang/Log.h>

namespace pf
{

//class VideoPlayer;

class VideoPlayerImplBase : //15
	public lang::Object
{
public:
	VideoPlayerImplBase(VideoPlayer* videoPlayer) //20 | Guess from iOS impl
	{
		m_videoPlayer = videoPlayer;
		m_playlistIndex = 0;
		m_looping = false;
	}

	virtual bool play(const std::string& filename, bool enableUserControl, float startPositionSeconds) = 0; //27 | Recover names from pf::VideoPlayer
	virtual void show() = 0; //28
	virtual void hide() = 0; //29
	virtual void close() = 0; //30
	virtual void pause() = 0; //31
	virtual void resume() = 0; //32
	virtual bool isPaused() const //33
	{
		return false;
	}

	virtual void playStart() //38
	{
		m_playlistIndex = 0;
		playTheNextPlayListItemIfAvailable();
	}

	virtual bool addExtraButton(const std::string& buttonId, const std::string& image, VideoPlayer::ExtraButtonPosition position) //44 | TODO
	{
		/*//const bool _fusion_done, _fusion_done2, _fusion_done3, _fusion_broke, _fusion_range, _fusion_i, _fusion_e = false; //Is this autogen? //46
		ExtraButtonInfo info; //46

		if (buttonId.size())
			info.buttonId = buttonId;
		if (image.size())
			info.image = image;

		info.position = position;

		m_extraButtons.push_back(info); //56*/
		assert("virtual bool pf::VideoPlayerImplBase::addExtraButton(const std::string& buttonId, const std::string& image, pf::VideoPlayer::ExtraButtonPosition position) was not yet decompiled.");
		return false;
	}

	virtual void addExtraLayer(const std::string& image, float secondsVisible, VideoPlayer::ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize) //60
	{
		ExtraLayerInfo info; //62
		info.image = image;
		info.secondsVisible = secondsVisible;
		info.position = position;
		info.text = text;
		info.font = font;
		info.fontSize = fontSize;
		m_extraLayers.push_back(info); //69
	}

	virtual void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints) //72
	{
		m_cuePoints = cuePoints;
	}

	virtual void clearCuePoints() //77
	{
		m_cuePoints.clear(); //79
	}

	virtual void announceVideoPreparing(const std::string& playedVideo) //82 | TODO
	{
		//LANG_LOG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceVideoPreparing() playedVideo: %s", playedVideo.c_str()); //86 (RCSSDK debug)
		//std::set<VideoPlayerListener*>::iterator observerIt; //86
		//for (observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++) //87
			//m_listeners[observerIt]
		assert("virtual bool pf::VideoPlayerImplBase::announceVideoPreparing(const std::string& playedVideo) was not yet decompiled.");
	}

	virtual void announceVideoStarted() //93 | TODO
	{
		//LANG_LOG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceVideoStarted())"); //95 (RCSSDK debug)
		//while (m_listeners.begin() != m_listeners.end()) //98
		//{
			//m_listeners
		//}
		assert("virtual bool pf::VideoPlayerImplBase::announceVideoStarted() was not yet decompiled.");
	}

	virtual void announcePlay(float secondsPlayed) //104 | operator cuepoint? | TODO
	{
		/*std::vector<VideoPlayerListener::CuePoint> reachedCuePoints; //106
		for (int p = 0; p < m_cuePoints.size(); p++) //107
		{
			if (m_cuePoints[p].secondsFromBeginning >= secondsPlayed)
				reachedCuePoints.push_back(m_cuePoints[p]); //111
		}
		
		//std::remove_if<VideoPlayerListener::CuePoint>(m_cuePoints.begin(), m_cuePoints.end(), ); //116 operator() //remove_if, find_if

		if (reachedCuePoints.size()) //118
		{
			std::set<VideoPlayerListener*>::iterator observerIt; //120
			for (observerIt = m_listeners.begin(); observerIt != m_listeners.end(); observerIt++) //121
				//onCuePointReached(m_videoPlayer);
		}*/
		assert("virtual bool pf::VideoPlayerImplBase::announceVideoStarted(float secondsPlayed) was not yet decompiled.");
	}

	virtual void announceVideoEnded(VideoPlayerListener::PlaybackEndReason endReason, float secondsPlayed, float secondsTotal) //128-144 | TODO
	{
		//LANG_LOG_DEBUG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceVideoEnded() endReason: %i secondsPlayed: %f secondsTotal: %f", endReason, secondsPlayed, secondsTotal); //130 (RCSSDK debug)

		/*while (m_listeners.begin() != m_listeners.end())
		{
			m_playList[m_playlistIndex].
		}

		if (playTheNextPlayListItemIfAvailable())
			announceVideoPlaylistEnded();*/
		assert("virtual void pf::VideoPlayerImplBase::announceVideoEnded(pf::VideoPlayerListener::PlaybackEndReason endReason, float secondsPlayed, float secondsTotal) was not yet decompiled.");
	}

	virtual void announceVideoPlaylistEnded() //146 | TODO
	{
		//LANG_LOG_DEBUG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceVideoPlaylistEnded() "); //150 (RCSSDK debug)
		//close();
		//std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); //152
		//for (observerIt; observerIt != m_listeners.end(); observerIt++) //153
		//{
			//*observerIt->announceVideoPlaylistEnded();
		//}
		assert("virtual void pf::VideoPlayerImplBase::announceVideoPlaylistEnded() was not yet decompiled.");
	}

	virtual void announceVideoCancelled() //159 | TODO
	{
		//LANG_LOG_DEBUG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceVideoCancelled() "); //163
		//while (m_listeners.begin(); != )
		assert("virtual void pf::VideoPlayerImplBase::announceVideoCancelled() was not yet decompiled.");
	}

	virtual void announceExtraButtonClicked(const std::string& buttonId) //170 | TODO
	{
		//LANG_LOG_DEBUG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::announceExtraButtonClicked() buttonId: %s ", buttonId.c_str()); //174 (RCSSDK debug)
		//std::set<VideoPlayerListener*>::iterator observerIt = m_listeners.begin(); //174
		//for (observerIt; observerIt != m_listeners.end(); observerIt++) //175
		//{
			//m_listeners[observerIt]->onExtraButtonClicked(buttonId.c_str());
		//}
		assert("virtual void pf::VideoPlayerImplBase::announceExtraButtonClicked(const std::string& buttonId) was not yet decompiled.");
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
			m_listeners.erase(listener); //198
	}

	virtual void setFullscreen() //202
	{
		//Blank!
	}

	virtual void setSize(int, int, int, int) //207 | Unknown parameters
	{
		//Blank!
	}

	virtual void setSource(const std::string& filename, float startPositionSeconds) //212
	{
		m_playlistIndex = 0;
		m_playList.clear(); //215
		VideoPlayerPlayListItem newPlayListItem; //216

		newPlayListItem.setInterfaceType(VideoPlayerPlayListItem::USER_CONTROL_ENABLED); //218
		newPlayListItem.setStartPositionSeconds(startPositionSeconds); //219
		setSource(newPlayListItem);
	}

	virtual void setSource(const VideoPlayerPlayListItem& item) //223
	{
		m_playlistIndex = 0;
		m_playList.clear(); //226
		m_playList.push_back(item); //227
	}

	virtual void setSource(const std::vector<VideoPlayerPlayListItem>& playlist) //230
	{
		m_playlistIndex = 0;
		m_playList = playlist;
	}

	virtual bool isPlayListEnded() //236
	{
		return m_playlistIndex >= m_playList.size(); //238
	}

	void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed) //241
	{
		m_imagePath_normal = imageNormal; //243
		m_imagePath_pressed = imagePressed; //244
	}

	const std::string& getCloseButtonImagePathNormal() //247 | Not defined on iOS
	{
		return m_imagePath_normal;
	}

	const std::string& getCloseButtonImagePathPressed() //252 | Not defined on iOS
	{
		return m_imagePath_pressed;
	}

	virtual bool playTheNextPlayListItemIfAvailable() //259-272 | Correct?
	{
		LANG_LOG_DEBUG("VideoPlayer", LANG_LOG_PRIORITY_DEBUG, "VideoPlayerImplBase::playTheNextPlayListItemIfAvailable() playlist size:%llu", m_playList.size()); //263 (RCSSDK debug)
		
		if (m_looping && m_playlistIndex >= m_playList.size()) //263 | not isPlayListEnded macro according to lines
			m_playlistIndex = 0;

		if (m_playList.size() > 0) //264
		{
			std::string url = m_playList[m_playlistIndex].getUrl(); //267

			return play(url, m_playList[m_playlistIndex].isUserControlEnabled(), m_playList[m_playlistIndex].getStartPositionSeconds()); //271
		}

		return false;
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