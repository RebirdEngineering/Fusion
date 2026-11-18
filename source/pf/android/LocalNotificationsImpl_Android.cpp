#include <pf/LocalNotifications.h>
#include <pf/RegistryAccessor.h>

//TODO

using namespace lang;
using namespace util;

namespace pf
{
	class LocalNotifications::LocalNotificationsImpl : public Object //0x00 bytes
	{
	public:
		static std::map<std::string, int> sm_pendingNotifications; //Official via JSON string

		LocalNotificationsImpl()
		{
			//RegistryAccessor reg;
			//reg.registry()["pf::LocalNotifications::sm_pendingNotifications"].visit();
		}

		~LocalNotificationsImpl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		bool isAvailable()
		{
			return true;
		}

		bool addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound) //Mangled symbol suggests this
		{
			return false;
		}

		bool removeNotification(const std::string& eventName)
		{
			//"com/rovio/fusion/LocalNotificationsWrapper"
			//"removeNotification"

			sm_pendingNotifications.erase(eventName);
			RegistryAccessor reg;
			JSON& id(reg.registry()["pf::LocalNotifications::sm_pendingNotifications"]);
			id.registry.remove(eventName);

			return false;
		}

		void removeAllNotifications()
		{
			//for (int i = 0; i < sm_pendingNotifications.size() i++)
				//removeNotification(sm_pendingNotifications[i]);
		}

		void checkForNotifications() //Blank
		{
		}

		void addListener(LocalNotificationsListener* l)
		{
			sm_listeners.push_back(l);
		}

		void removeListener(LocalNotificationsListener* l)
		{
			sm_listeners.erase(l);
		}
	};

#include <pf/common/LocalNotifications.h>

}