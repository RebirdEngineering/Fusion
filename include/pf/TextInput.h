#ifndef _PF_TEXTINPUT_H
#define _PF_TEXTINPUT_H

#include <lang/Object.h> //For now

namespace pf
{
	class TextInputObserver
	{
	public:
		virtual bool acceptInput(const std::string&, unsigned short) = 0;

		virtual void inputChanged(const std::string& newString) = 0; //Recover from common/DebugConsole.h and common/TextInput.h
	};

	class TextInput :
		public Object
	{
	public:
		TextInput();

		~TextInput();

		bool isSupported();

		bool isActive() const;

		void activate(const std::string& string, TextInputObserver* observer);

		void deactivate();

		std::string input() const;

		bool isVirtualKeyboardVisible();

		void  hideVirtualKeyboard();
	private:
		class TextInputImpl;
		P(TextInputImpl) m_impl;

		TextInput(const TextInput&);
		TextInput& operator=(const TextInput&);
	};
}

#endif