#include <pf/TextInput.h>

using namespace lang;

namespace pf
{
	class TextInput::TextInputImpl : public Object //Ok so this kind of file is officially named TextInputImpl_* yet some platforms call it TextInput_*, where's the consistency? We've only seen this variant in Trilogii? Not on Win.
	{
	public:
		TextInputImpl()
		{
		}

		~TextInputImpl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		bool isActive() const
		{
			return false;
		}

		void activate(const std::string& string, TextInputObserver* observer)
		{
		}

		void deactivate()
		{
		}

		std::string input() const
		{
			return "";
		}

		bool isVirtualKeyboardVisible()
		{
			return false;
		}

		void hideVirtualKeyboard()
		{
		}
	};

#include <pf/common/TextInput.h>

}