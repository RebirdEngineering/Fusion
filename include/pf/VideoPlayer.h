#ifndef _PF_VIDEOPLAYER_H
#define _PF_VIDEOPLAYER_H

#include <lang/Object.h>
#include <pf/VideoPlayerListener.h>

namespace pf
{

//class VideoPlayerImplBase;
class VideoPlayerListener;

class VideoPlayer :
	public lang::Object
{
public:
	enum ExtraButtonPosition //23
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

	~VideoPlayer(); //44

	void addListener(VideoPlayerListener* listener); //50

	void removeListener(VideoPlayerListener* listener); //55

	void setSource(const std::string& filename, float startPositionSeconds); //62

	void setSource(const VideoPlayerPlayListItem& item); //69 | Recover from iOS VideoPlayerImplBase

	void setSource(const std::vector<VideoPlayerPlayListItem>&); //76 | Recover from iOS VideoPlayerImplBase

	void setLooping(bool looping); //82 | Recover from iOS VideoPlayerImplBase

	void show(); //87

	void hide(); //92

	void play(); //92

	void pause(); //102

	void resume(); //107

	void close(); //112

	bool isPaused() const; //117

	bool isSupported(); //122

	void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed); //127

	void addExtraButton(const std::string& buttonId, const std::string& image, ExtraButtonPosition position); //132

	void addExtraLayer(const std::string& image, float secondsVisible, ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize); //137 | Recover from iOS VideoPlayerImplBase

	void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints); //142

	void clearCuePoints(); //147
private:
	class VideoPlayerImpl;
	P(VideoPlayerImpl) m_impl; //152 | Impl sizes: [Win32: 160 bytes, OSX: 68 bytes, iOS: 108 bytes, WP8: 160 bytes, Android: 160 bytes]
	VideoPlayer(const VideoPlayer&); //153
	VideoPlayer& operator=(const VideoPlayer&); //154
};

}

#endif