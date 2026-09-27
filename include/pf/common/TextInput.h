#ifndef _PF_COMMON_TEXTINPUT_H
#define _PF_COMMON_TEXTINPUT_H

//Includes and namespaces are redundant since we're including this file in the namespace

TextInput::TextInput()
{
	m_impl = new TextInputImpl(); //8
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

void TextInput::activate(const std::string& string, TextInputObserver* observer) //25
{
	m_impl->activate(string, observer); //27
}

void TextInput::deactivate()
{
	m_impl->deactivate(); //32
}

std::string TextInput::input() const
{
	return m_impl->input(); //37
}

bool TextInput::isVirtualKeyboardVisible() //Not defined on iOS
{
	return m_impl->isVirtualKeyboardVisible();
}

void TextInput::hideVirtualKeyboard() //Not defined on iOS
{
	return m_impl->hideVirtualKeyboard();
}

#endif // !_PF_COMMON_TEXTINPUT_H