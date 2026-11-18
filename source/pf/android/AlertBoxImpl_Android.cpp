#include <pf/AlertBox.h>
#include <pf/common/AlertBoxImplBase.h>

//TODO

namespace pf
{
	class AlertBox::AlertBoxImpl : public AlertBoxImplBase //0x18 bytes
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
			return true;
		}

		void setCustomButtons(const std::vector<std::string>& customButtons) //Blank since implbase covers it
		{
		}

		void show(const std::string& title, const std::string& message, int type, AlertBoxListener* listener)
		{
			//"com/rovio/fusion/ShowAlertRunnable"
			//"showAlert"

			//switch (type)
			//{
			//case BUTTON_OK:
			//case BUTTON_OKCANCEL:
			//case BUTTON_ABORTRETRYIGNORE:
			//case BUTTON_YESNO:
			//case BUTTON_RETRYCANCEL:
			//case BUTTON_CUSTOM:
			//}
		}
	};

#include <pf/common/AlertBox.h>

}