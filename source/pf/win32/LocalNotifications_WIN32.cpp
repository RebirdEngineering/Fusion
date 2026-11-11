#include <pf/LocalNotifications.h>
#include <lang/System.h>

using namespace lang;

namespace pf
{
	class LocalNotification : Object //0x50 bytes
	{
	public:
		LocalNotification(int param1, int param2, std::string param3, std::string param4) /*:
			unk(param1),
			unk2(param2),
			unk3(param3),
			unk4(param4),
			unk5(param4)*/
		{
		}

		//sub_4C6910(int); //4C6910

		void sub_4C66D0(int) //4C66D0
		{
		}

	private:
		int unk;
		int unk2;
		int unk3;
		std::string unk4;
		std::string unk5;
	};

	class LocalNotifications::LocalNotificationsImpl : public Object //0x2C bytes
	{
	public:
		LocalNotificationsImpl()
		{
			//System::currentTimeMillis();

			//localnotification1c->sub_4414E0
		}

		~LocalNotificationsImpl()
		{
			localnotification1c->sub_4C66D0(0);
		}

		bool isSupported()
		{
			return true;
		}

		bool isAvailable()
		{
			return true;
		}

		bool addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound) //4C67F0 | Mangled symbol suggests this
		{
			//= new LocalNotification()
			return true;
		}

		bool removeNotification(const std::string& eventName)
		{
			return false;
		}

		void removeAllNotifications()
		{
			localnotification1c->sub_4C66D0(0);
		}

		void checkForNotifications() //4C6540 TODO
		{
		}

		void addListener(LocalNotificationsListener* l)
		{
		}

		void removeListener(LocalNotificationsListener* l)
		{
		}

	private:
		std::vector<std::string> unk;
		LocalNotification* localnotification1c; //0x1C
		char unk2[12];
	};

#include <pf/common/LocalNotifications.h>

}