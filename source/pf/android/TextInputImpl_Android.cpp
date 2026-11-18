#include <pf/TextInput.h>

//TODO

using namespace lang;

namespace pf
{
	class TextInput::TextInputImpl : public Object //0x14 bytes.
	{
	public:

		static TextInputImpl* ActiveTextInput;

		TextInputImpl() :
			m_observer(0),
			m_input("")
		{
		}

		~TextInputImpl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		bool isActive() const
		{
			return this == ActiveTextInput;
		}

		void activate(const std::string& string, TextInputObserver* observer)
		{
			deactivate();

			m_input = string;
			ActiveTextInput = this;
			m_observer = observer;
		}

		void deactivate()
		{
			enableTextInput(false);
			if (ActiveTextInput == this)
				ActiveTextInput = 0;
		}

		std::string input() const
		{
			return m_input;
		}

		bool isVirtualKeyboardVisible()
		{
			return false;
		}

		void hideVirtualKeyboard()
		{
			deactivate();
		}

	private:
		std::string m_input;
		TextInputObserver* m_observer;

		static void addChar(int theChar)
		{
		}

		static void enableTextInput(bool enable)
		{
			//"com/rovio/fusion/TextInput"
			//"Z"
			//"enableTextInput"
		}
	};

#include <pf/common/TextInput.h>

}