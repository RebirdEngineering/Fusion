#ifndef _PF_VIDEOPLAYERLISTENER_H
#define _PF_VIDEOPLAYERLISTENER_H

#include <pf/VideoPlayerPlayListItem.h>

BEGIN_NAMESPACE(pf)

class VideoPlayerListener
{
public:
	enum PlaybackEndReason
	{
		PLAYBACK_COMPLETED,
		CLOSED,
		SKIPPED,
		FILE_NOT_FOUND,
		CONNECTION_LOST,
		UNSUPPORTED_MEDIA_TYPE,
		UNKNOWN_ERROR
	};
	struct CuePoint
	{
	public:
		std::string name;
		std::string type;
		float secondsFromBeginning;
	};
	virtual void onVideoPreparing(VideoPlayer&, VideoPlayerPlayListItem);

	virtual void onVideoStarted(VideoPlayer&, VideoPlayerPlayListItem);

	virtual void onVideoCancelled(VideoPlayer&);

	virtual void onVideoEnded(VideoPlayer&, VideoPlayerPlayListItem, PlaybackEndReason, float, float);

	virtual void onVideoPlaylistEnded(VideoPlayer&, std::vector<VideoPlayerPlayListItem>);

	virtual void onExtraButtonClicked(VideoPlayer&, const std::string&);

	virtual void onCuePointReached(VideoPlayer&, std::vector <VideoPlayerListener>);
};

}

#endif