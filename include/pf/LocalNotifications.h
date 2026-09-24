#ifndef _PF_LOCALNOTIFICATIONS_H
#define _PF_LOCALNOTIFICATIONS_H

#include <lang/Object.h>

namespace pf
{

class LocalNotificationsListener //This reeks of identical code
{
public:
	virtual ~LocalNotificationsListener();

	virtual void notificationReceived(const std::string&) = 0;
};

class LocalNotifications : public lang::Object
{
public:
	LocalNotifications();
	~LocalNotifications();

	bool isSupported();

	bool isAvailable();

	bool addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound); //Mangled symbol suggests this

	bool removeNotification(const std::string& eventName);

	void removeAllNotifications();

	void checkForNotifications();

	void addListener(LocalNotificationsListener* l);

	void removeListener(LocalNotificationsListener* l);
protected:
	class LocalNotificationsImpl;
	LocalNotificationsImpl m_impl;
};

}

#endif