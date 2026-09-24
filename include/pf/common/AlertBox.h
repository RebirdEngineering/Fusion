#ifndef _PF_COMMON_ALERTBOX_H
#define _PF_COMMON_ALERTBOX_H

#include <pf/AlertBox.h>

BEGIN_NAMESPACE(pf)

AlertBox::AlertBox()
{
	m_impl = new AlertBoxImpl();
}

AlertBox::~AlertBox()
{
}

bool AlertBox::isSupported() //UNIMPLEMENTED ON IOS
{
	return m_impl->isSupported();
}

void AlertBox::setCustomButtons(const std::vector<std::string>& customButtons)
{
	m_impl->setCustomButtons(customButtons);
}

void AlertBox::show(const std::string& title, const std::string& message, int type, AlertBoxListener* listener)
{
	m_impl->show(title, message, listener);
}

}

#endif // !_PF_TEXTINPUT_H