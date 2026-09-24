#ifndef _PF_COMMON_LOCALNOTIFICATIONS_H
#define _PF_COMMON_LOCALNOTIFICATIONS_H

#include <pf/LocalNotifications.h>

BEGIN_NAMESPACE(pf)

LocalNotifications::LocalNotifications()
{
	m_impl = new LocalNotificationsImpl();
}

LocalNotifications::~LocalNotifications()
{
}

bool LocalNotifications::isAvailable() //Not defined on iOS
{
	return m_impl->isAvailable();
}

bool LocalNotifications::addNotificationAfter(const std::string& eventName, float seconds, const std::string& eventText, const std::string& eventIcon, const std::string& eventSound)
{
	return m_impl->addNotificationAfter(eventName, seconds, eventText, eventIcon, eventSound);
}

bool LocalNotifications::removeNotification(const std::string& eventName)
{
	return m_impl->removeNotification(eventName);
}

void LocalNotifications::removeAllNotifications()
{
	m_impl->removeAllNotifications();
}

void LocalNotifications::checkForNotifications() //Not defined on iOS
{
	m_impl->checkForNotifications();
}

void LocalNotifications::addListener(LocalNotificationsListener* l)
{
	m_impl->addListener(l);
}

void LocalNotifications::removeListener(LocalNotificationsListener* l)
{
	m_impl->removeListener(l);
}

}

#endif // ! _PF_COMMON_LOCALNOTIFICATIONS_H