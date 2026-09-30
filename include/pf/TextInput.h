#ifndef _PF_TEXTINPUT_H
#define _PF_TEXTINPUT_H

#include <lang/Object.h> //For now

namespace pf
{
	class TextInputObserver //11
	{
	public:
		virtual bool acceptInput(const std::string&, unsigned short) = 0; //18

		virtual void inputChanged(const std::string& newString) = 0; //24 | Recover from AB common/DebugConsole.h and AB common/TextInput.h
	};

	class TextInput : //31 | TextInputImpl_OSX, TextInputImpl_Dummy (OSX [legacy], Blackberry), TextInput_* (iOS, IPHONE)
		public lang::Object
	{
	public:
		TextInput(); //37

		~TextInput(); //42

		bool isSupported(); //47

		bool isActive() const; //52

		void activate(const std::string& string, TextInputObserver* observer); //59

		void deactivate(); //64

		std::string input() const; //69

		bool isVirtualKeyboardVisible(); //74

		void  hideVirtualKeyboard(); //79
	private:
		class TextInputImpl;
		P(TextInputImpl) m_impl; //85 | Impl sizes [iOS: 16 bytes, Android: 16 bytes, WP8: 12 bytes {DUMMY}, Win32: 44 bytes, OSX: 24 bytes}
		TextInput(const TextInput&); //86
		TextInput& operator=(const TextInput&); //87
	};
}

#endif