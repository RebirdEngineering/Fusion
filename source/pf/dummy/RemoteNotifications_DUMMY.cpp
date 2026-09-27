#include <pf/RemoteNotifications.h>

using namespace lang;

namespace pf
{
	class RemoteNotifications::Impl : public Object
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		bool isSupported() //Not defined on iOS
		{
			return false;
		}

		void addListener(RemoteNotificationsListener* listener)
		{
		}

		void removeListener(RemoteNotificationsListener* listener)
		{
		}

		void setEnabled(bool enabled)
		{
		}

		bool areSettingsProvidedByThePlatform()
		{
			return false;
		}
	};

#include <pf/common/RemoteNotifications.h>

}