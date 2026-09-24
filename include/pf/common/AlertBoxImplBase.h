#ifndef _PF_COMMON_ALERTBOXIMPLBASE_H
#define _PF_COMMON_ALERTBOXIMPLBASE_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)


class AlertBoxImplBase :
	public Object
{
public:
	AlertBoxImplBase()
	{
	}

	~AlertBoxImplBase()
	{
	}

	void setCustomButtons(const std::vector<std::string>& customButtons)
	{
		m_customButtons = customButtons;
	}

protected:
	std::vector<std::string> m_customButtons;
};

}

#endif // !_PF_TEXTINPUT_H