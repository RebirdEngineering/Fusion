#include <pf/AlertBox.h>

using namespace lang;

namespace pf
{
	class AlertBox::AlertBoxImpl : public lang::Object
	{
	public:
		AlertBoxImpl()
		{
		}

		~AlertBoxImpl()
		{
		}

		bool isSupported() const
		{
			return false;
		}

		void setCustomButtons(const std::vector<std::string>& customButtons)
		{
		}

		void show(const std::string& title, const std::string& message, int type, AlertBoxListener* listener)
		{
		}
	};

#include <pf/common/AlertBox.h>

}