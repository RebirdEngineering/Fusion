#ifndef _PF_COMMON_VIDEOPLAYER_H
#define _PF_COMMON_VIDEOPLAYER_H

//Includes and namespaces are redundant since we're including this file in the namespace

VideoPlayer::VideoPlayer(bool separateActivityOnAndroid) //7
{
	m_impl = new VideoPlayerImpl(separateActivityOnAndroid); //10
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::addListener(VideoPlayerListener* listener) //22
{
	m_impl->addListener(listener); //24
}

void VideoPlayer::removeListener(VideoPlayerListener* listener) //27
{
	m_impl->removeListener(listener); //29
}

void VideoPlayer::setSource(const std::string& filename, float startPositionSeconds) //32
{
	m_impl->setSource(filename, startPositionSeconds); //34
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
	m_impl->show(); //54
}

void VideoPlayer::hide()
{
	m_impl->hide(); //59
}

void VideoPlayer::play()
{
	m_impl->play(); //64
}

void VideoPlayer::pause()
{
	m_impl->pause(); //69
}

void VideoPlayer::resume()
{
	m_impl->resume(); //74
}

void VideoPlayer::close()
{
	m_impl->close(); //79
}

bool VideoPlayer::isPaused() const
{
	return m_impl->isPaused(); //84
}

bool VideoPlayer::isSupported()
{
	return m_impl->isSupported();
}

void VideoPlayer::setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed) //87
{
	m_impl->setCloseButtonImagePaths(imageNormal, imagePressed); //89
}

void VideoPlayer::addExtraButton(const std::string& buttonId, const std::string& image, ExtraButtonPosition position) //92
{
	m_impl->addExtraButton(buttonId, image, position); //94
}

void VideoPlayer::addExtraLayer(const std::string& image, float secondsVisible, ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize) //Not defined on iOS
{
	m_impl->addExtraLayer(image, secondsVisible, position, font, text, fontSize);
}

void VideoPlayer::setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints) //104
{
	m_impl->setCuePoints(cuePoints); //106
}

void VideoPlayer::clearCuePoints()
{
	m_impl->clearCuePoints(); //111
}

#endif //! _PF_COMMON_VIDEOPLAYER_H