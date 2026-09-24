#ifndef _PF_VIDEOPLAYER_H
#define _PF_VIDEOPLAYER_H

#include <lang/Object.h> //For now
#include <pf/VideoPlayerListener.h> //For now

BEGIN_NAMESPACE(pf)

class VideoPlayer :
	public Object
{
public:
	enum ExtraButtonPosition
	{
		LEFT,
		CENTER,
		RIGHT,
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
	VideoPlayer(bool separateActivityOnAndroid);

	~VideoPlayer();

	void addListener(VideoPlayerListener* listener);

	void removeListener(VideoPlayerListener* listener);

	void setSource(const std::string& filename, float startPositionSeconds);

	void setSource(const VideoPlayerPlayListItem& item); //Recover from iOS VideoPlayerImplBase

	void setSource(const std::vector<VideoPlayerPlayListItem>&); //Recover from iOS VideoPlayerImplBase

	void setLooping(bool looping); //Recover from iOS VideoPlayerImplBase

	void show();

	void hide();

	void play();

	void pause();

	void resume();

	void close();

	bool isPaused() const;

	bool isSupported();

	void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed);

	void addExtraButton(const std::string& buttonId, const std::string& image, ExtraButtonPosition position);

	void addExtraLayer(const std::string& image, float secondsVisible, ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize); //Recover from iOS VideoPlayerImplBase

	void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints);

	void clearCuePoints();
private:
	class VideoPlayerImpl;
	P(VideoPlayerImpl) m_impl;

	VideoPlayer(const VideoPlayer&);
	VideoPlayer& operator=(const VideoPlayer&);
};

}

#endif