#ifndef _PF_LOCALNOTIFICATIONS_H
#define _PF_LOCALNOTIFICATIONS_H

#include <lang/Object.h>

namespace pf
{

class LocalNotificationsListener //This reeks of identical code
{
public:
	virtual ~LocalNotificationsListener(); //11

	virtual void notificationReceived(const std::string&) = 0; //13
};

class LocalNotifications : public lang::Object //20 | 44 byte Impl on Win32
{
public:
	LocalNotifications(); //25
	~LocalNotifications(); //26

	bool isSupported(); //31

	bool isAvailable(); //33

	bool addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound); //45 | Mangled symbol suggests this

	bool removeNotification(const std::string& eventName); //53

	void removeAllNotifications(); //58

	void checkForNotifications(); //63

	void addListener(LocalNotificationsListener* l); //68

	void removeListener(LocalNotificationsListener* l); //73
protected:
	class LocalNotificationsImpl;
	LocalNotificationsImpl* m_impl; //79
};

}

#endif