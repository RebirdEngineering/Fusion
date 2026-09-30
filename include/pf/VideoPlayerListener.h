#ifndef _PF_VIDEOPLAYERLISTENER_H
#define _PF_VIDEOPLAYERLISTENER_H

#include <pf/VideoPlayerPlayListItem.h>
//#include <pf/VideoPlayer.h>

namespace pf
{
	class VideoPlayer;

class VideoPlayerListener //12
{
public:
	enum PlaybackEndReason //19
	{
		PLAYBACK_COMPLETED,
		CLOSED,
		SKIPPED,
		FILE_NOT_FOUND,
		CONNECTION_LOST,
		UNSUPPORTED_MEDIA_TYPE,
		UNKNOWN_ERROR
	};

	struct CuePoint //30
	{
		std::string name; //32
		std::string type; //33
		float secondsFromBeginning; //34
	};

	virtual void onVideoPreparing(VideoPlayer&, VideoPlayerPlayListItem); //40

	virtual void onVideoStarted(VideoPlayer&, VideoPlayerPlayListItem); //45

	virtual void onVideoCancelled(VideoPlayer&); //50

	virtual void onVideoEnded(VideoPlayer&, VideoPlayerPlayListItem, PlaybackEndReason, float, float); //55

	virtual void onVideoPlaylistEnded(VideoPlayer&, std::vector<VideoPlayerPlayListItem>); //60

	virtual void onExtraButtonClicked(VideoPlayer&, const std::string&); //62

	virtual void onCuePointReached(VideoPlayer&, std::vector <VideoPlayerListener>); //67
};

}

#endif