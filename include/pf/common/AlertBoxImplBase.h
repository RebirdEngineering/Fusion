#ifndef _PF_COMMON_ALERTBOXIMPLBASE_H
#define _PF_COMMON_ALERTBOXIMPLBASE_H

#include <lang/Object.h>

namespace pf
{

class AlertBoxImplBase : //11
	public Object
{
public:
	AlertBoxImplBase() //15
	{
	}

	void setCustomButtons(const std::vector<std::string>& customButtons) //19
	{
		m_customButtons = customButtons;
	}

protected:
	std::vector<std::string> m_customButtons; //25
};

}

#endif // !_PF_COMMON_ALERTBOXIMPLBASE_H