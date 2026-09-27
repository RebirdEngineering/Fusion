#ifndef _PF_COMMON_ALERTBOX_H
#define _PF_COMMON_ALERTBOX_H

//Includes and namespaces are redundant since we're including this file in the namespace

AlertBox::AlertBox()
{
	m_impl = new AlertBoxImpl(); //8
}

AlertBox::~AlertBox()
{
}

bool AlertBox::isSupported() //UNIMPLEMENTED ON IOS
{
	return m_impl->isSupported();
}

void AlertBox::setCustomButtons(const std::vector<std::string>& customButtons) //20
{
	m_impl->setCustomButtons(customButtons); //22
}

void AlertBox::show(const std::string& title, const std::string& message, int type, AlertBoxListener* listener) //26
{
	m_impl->show(title, message, type, listener); //27
}

#endif // !_PF_TEXTINPUT_H