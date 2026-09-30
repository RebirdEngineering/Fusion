#include <pf/VideoPlayer.h>

using namespace lang;

namespace pf
{
	class VideoPlayer::VideoPlayerImpl : public Object //ABFM 113-115, OSX ABC 3.0.1
	{
	public:
		VideoPlayerImpl(bool separateActivityOnAndroid)
		{
		}

		~VideoPlayerImpl()
		{
		}

		void addListener(VideoPlayerListener* listener)
		{
		}

		void removeListener(VideoPlayerListener* listener)
		{
		}

		void setSource(const std::string& filename, float startPositionSeconds)
		{

		}

		void setSource(const VideoPlayerPlayListItem& item) //Recover from iOS VideoPlayerImplBase
		{
		}

		void setSource(const std::vector<VideoPlayerPlayListItem>&) //Recover from iOS VideoPlayerImplBase
		{
		}

		void setLooping(bool looping) //Recover from iOS VideoPlayerImplBase
		{
		}

		void show()
		{
		}

		void hide()
		{
		}

		void play()
		{
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

		bool isPaused() const
		{
			return false; //?
		}

		bool isSupported()
		{
			return false;
		}

		void setCloseButtonImagePaths(const std::string& imageNormal, const std::string& imagePressed)
		{
		}

		void addExtraButton(const std::string& buttonId, const std::string& image, ExtraButtonPosition position)
		{
		}

		void addExtraLayer(const std::string& image, float secondsVisible, ExtraButtonPosition position, const std::string& text, const std::string& font, float fontSize) //Recover from iOS VideoPlayerImplBase
		{
		}

		void setCuePoints(const std::vector<VideoPlayerListener::CuePoint>& cuePoints)
		{
		}

		void clearCuePoints()
		{
		}
	};

#include <pf/common/VideoPlayer.h>

}