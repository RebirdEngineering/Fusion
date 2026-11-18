#include <pf/RemoteNotifications.h>
#include <pf/detail.h>

//TODO

using namespace lang;

namespace pf
{
	class RemoteNotifications::Impl : public Object //0x00 bytes.
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		void addListener(RemoteNotificationsListener* listener)
		{
			pf::detail::addRemoteNotificationListener(listener);
		}

		void removeListener(RemoteNotificationsListener* listener)
		{
			detail::removeRemoteNotificationListener(listener);
		}

		void setEnabled(bool enabled)
		{
			//"com/rovio/fusion/RemoteNotificationsClientWrapper"
			//"setEnabled"
		}

		bool areSettingsProvidedByThePlatform()
		{
			//"com/rovio/fusion/RemoteNotificationsClientWrapper"
			//"areSettingsProvidedByThePlatform"
			return false;
		}
	};

#include <pf/common/RemoteNotifications.h>

}