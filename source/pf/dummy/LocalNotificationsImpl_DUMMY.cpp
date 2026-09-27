#include <pf/LocalNotifications.h>

using namespace lang;

namespace pf
{
	class LocalNotifications::LocalNotificationsImpl : public Object //OSX
	{
	public:
		LocalNotificationsImpl()
		{
		}

		~LocalNotificationsImpl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		bool isAvailable()
		{
			return false;
		}

		bool addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound) //Mangled symbol suggests this
		{
			return false;
		}

		bool removeNotification(const std::string& eventName)
		{
			return false;
		}

		void removeAllNotifications()
		{
		}

		void checkForNotifications()
		{
		}

		void addListener(LocalNotificationsListener* l)
		{
		}

		void removeListener(LocalNotificationsListener* l)
		{
		}
	};

#include <pf/common/LocalNotifications.h>

}