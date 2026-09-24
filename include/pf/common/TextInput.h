#ifndef _PF_COMMON_TEXTINPUT_H
#define _PF_COMMON_TEXTINPUT_H

#include <pf/TextInput.h> //For now

BEGIN_NAMESPACE(pf)

TextInput::TextInput()
{
	m_impl = new TextInputImpl();
}

TextInput::~TextInput()
{
}

bool TextInput::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

bool TextInput::isActive() const //Not defined on iOS
{
	return m_impl->isActive();
}

void TextInput::activate(const std::string& string, TextInputObserver* observer)
{
	m_impl->activate(string, observer);
}

void TextInput::deactivate()
{
	m_impl->deactivate();
}

std::string TextInput::input() const
{
	return m_impl->input();
}

bool TextInput::isVirtualKeyboardVisible() //Not defined on iOS
{
	return m_impl->isVirtualKeyboardVisible();
}

void TextInput::hideVirtualKeyboard() //Not defined on iOS
{
	return m_impl->hideVirtualKeyboard();
}

}

#endif // !_PF_COMMON_TEXTINPUT_H