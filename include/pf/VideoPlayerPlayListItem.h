#ifndef _PF_VIDEOPLAYERLISTITEM_H
#define _PF_VIDEOPLAYERLISTITEM_H

#include <lang/pp.h>

BEGIN_NAMESPACE(pf)

class VideoPlayerPlayListItem
{
public:
	enum InterfaceType
	{
		INTERFACE_TYPE_UNKNOWN,
		NO_USER_CONTROL,
		USER_CONTROL_ENABLED
	};

	VideoPlayerPlayListItem(std::string, InterfaceType);

	VideoPlayerPlayListItem();

	virtual ~VideoPlayerPlayListItem();

	bool isUserControlEnabled();

	void setUrl(std::string);

	const std::string& getUrl() const;

	void setInterfaceType(InterfaceType = USER_CONTROL_ENABLED);

	InterfaceType getInterfaceType() const;

	float getStartPositionSeconds();

	setStartPositionSeconds(float);
private:
	std::string m_url;
	InterfaceType m_interfaceType;
	float m_startPositionSeconds;
};

}

#endif