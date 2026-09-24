#ifndef _PF_COMMON_REMOTENOTIFICATIONS_H
#define _PF_COMMON_REMOTENOTIFICATIONS_H

#include <pf/RemoteNotifications.h> //For now

BEGIN_NAMESPACE(pf)

RemoteNotifications::RemoteNotifications()
{
	m_impl = new Impl();
}

RemoteNotifications::~RemoteNotifications()
{
}

bool RemoteNotifications::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

void RemoteNotifications::addListener(RemoteNotificationsListener* listener)
{
	m_impl->addListener(listener);
}

void RemoteNotifications::removeListener(RemoteNotificationsListener* listener) //Not defined on iOS
{
	m_impl->removeListener(listener);
}

void RemoteNotifications::setEnabled(bool enabled)
{
	m_impl->setEnabled(enabled);
}

bool RemoteNotifications::areSettingsProvidedByThePlatform() //Not defined on iOS
{
	return m_impl->areSettingsProvidedByThePlatform();
}

}

#endif //! _PF_COMMON_REMOTENOTIFICATIONS_H