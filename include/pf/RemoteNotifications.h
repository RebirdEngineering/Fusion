#ifndef _PF_REMOTENOTIFICATIONS_H
#define _PF_REMOTENOTIFICATIONS_H

#include <lang/Object.h>

namespace pf
{

class RemoteNotificationsListener
{
public:
	virtual void onRemoteNotificationReceived(const std::string&);
	virtual void onRemoteNotificationTokenReceived(const std::string&);
};

class RemoteNotifications : public lang::Object
{
public:
	RemoteNotifications();
	~RemoteNotifications();

	bool isSupported();

	void addListener(RemoteNotificationsListener* listener);

	void removeListener(RemoteNotificationsListener* listener);

	void setEnabled(bool enabled);

	bool areSettingsProvidedByThePlatform();
private:
	class Impl;
	P(Impl) m_impl;

	RemoteNotifications(const RemoteNotifications&);
	RemoteNotifications& operator=(const RemoteNotifications&);
};

}

#endif