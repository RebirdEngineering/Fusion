#include <pf/VideoPlayer.h>

#include <pf/common/VideoPlayerImplBase.h> //Right use?

namespace pf
{
	class VideoPlayer::VideoPlayerImpl : public VideoPlayerImplBase //ABFM 113-115, OSX ABC 3.0.1
	{
	public:
		VideoPlayerImpl(bool separateActivityOnAndroid) :
			VideoPlayerImplBase(m_videoPlayer)
		{
		}

		~VideoPlayerImpl()
		{
		}

		void show()
		{
		}

		void hide()
		{
		}

		bool play(const std::string& filename, bool enableUserControl, float startPositionSeconds)
		{
			return false;
		}

		void pause()
		{
		}

		void resume()
		{
		}

		void close()
		{
		}

		bool isSupported()
		{
			return false;
		}
	};

#include <pf/common/VideoPlayer.h>

}