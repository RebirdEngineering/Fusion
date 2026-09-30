#ifndef _PF_VIDEOPLAYERLISTITEM_H
#define _PF_VIDEOPLAYERLISTITEM_H

#include <lang/pp.h>

namespace pf
{

class VideoPlayerPlayListItem //11
{
public:
	enum InterfaceType //19
	{
		INTERFACE_TYPE_UNKNOWN,
		NO_USER_CONTROL,
		USER_CONTROL_ENABLED
	};

	VideoPlayerPlayListItem(std::string, InterfaceType); //31

	VideoPlayerPlayListItem(); //36

	virtual ~VideoPlayerPlayListItem(); //41

	bool isUserControlEnabled(); //46

	void setUrl(std::string); //51

	const std::string& getUrl() const; //56

	void setInterfaceType(InterfaceType);

	InterfaceType getInterfaceType() const; //66

	float getStartPositionSeconds(); //68
	void setStartPositionSeconds(float); //69
private:
	std::string m_url; //72
	InterfaceType m_interfaceType; //73
	float m_startPositionSeconds; //74
};

}

#endif