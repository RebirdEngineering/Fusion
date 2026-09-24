#ifndef _PF_COMMON_VIDEOPLAYER_H
#define _PF_COMMON_VIDEOPLAYER_H

#include <pf/VideoPlayer.h>

BEGIN_NAMESPACE(pf)

VideoPlayer::VideoPlayer(bool separateActivityOnAndroid)
{
	m_impl = VideoPlayerImpl(separateActivityOnAndroid);
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::addListener(VideoPlayerListener* listener)
{
	m_impl->addListener(listener);
}

void VideoPlayer::removeListener(VideoPlayerListener* listener)
{
	m_impl->removeListener(listener);
}

void VideoPlayer::setSource(const std::string& filename, float startPositionSeconds)
{
	m_impl->setSource(filename, startPositionSeconds);
}

void VideoPlayer::setSource(const VideoPlayerPlayListItem& item) //Not defined on iOS
{
	m_impl->setSource(item);
}

void VideoPlayer::setSource(const std::vector<VideoPlayerPlayListItem>& playlist) //Not defined on iOS
{
	m_impl->setSource(playlist);
}

void VideoPlayer::setLooping(bool looping) //Not defined on iOS
{
	m_impl->setLooping(looping);
}

void VideoPlayer::show()
{
	m_impl->show();
}

void VideoPlayer::hide()
{
	m_impl->hide();
}

void VideoPlayer::play()
{
	m_impl->play();
}

void VideoPlayer::pause()
{
	m_impl->pause();
}

void VideoPlayer::resume()
{
	m_impl->resume();
}

bool VideoPlayer::isPaused() const
{
	return m_impl->isPaused();
}

void VideoPlayer::setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed)
{
	m_impl->setCloseButtonImagePaths(imageNormal, imagePressed);
}

void VideoPlayer::addExtraButton(const std::string& buttonId, const std::string& image, ExtraButtonPosition position)
{
	m_impl->addExtraButton(buttonId, image, position);
}

void VideoPlayer::addExtraLayer(const std::string& image, float secondsVisible, ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize) //Not defined on iOS
{
	m_impl->addExtraLayer(image, seconds, secondsVisible, position, text, font);
}

void VideoPlayer::setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints)
{
	m_impl->setCuePoints(cuePoints);
}

void VideoPlayer::clearCuePoints()
{
	m_impl->clearCuePoints();
}

}

#endif //! _PF_COMMON_VIDEOPLAYER_H