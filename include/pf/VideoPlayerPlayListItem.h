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

	const std::string& getUrl() const { return m_url; } //56

	void setInterfaceType(InterfaceType newInterfaceType);

	InterfaceType getInterfaceType() const { return m_interfaceType; } //66

	float getStartPositionSeconds() { return m_startPositionSeconds; } //68
	void setStartPositionSeconds(float seconds) { m_startPositionSeconds = seconds; } //69

private:
	std::string m_url; //72
	InterfaceType m_interfaceType; //73
	float m_startPositionSeconds; //74
};

}

#endif