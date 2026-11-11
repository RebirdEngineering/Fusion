#include <pf/TextInput.h>

using namespace lang;

namespace pf
{
	class TextInput::TextInputImpl : public Object //0x2C bytes | HEAVILY BASED OFF iOS IMPL
	{
	public:

		static TextInputImpl* ActiveTextInput; //59BE70

		TextInputImpl() :
			m_input(""),
			m_observer(0)
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
			return false;
		}

		void activate(const std::string& string, TextInputObserver* observer) //4C5D30
		{
			ActiveTextInput = this;

			m_input = string;
			m_observer = observer;
		}

		void deactivate()
		{
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
		}
	
	private:
		std::string m_input;
		TextInputObserver* m_observer;
	};

#include <pf/common/TextInput.h>

}