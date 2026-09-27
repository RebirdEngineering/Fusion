#ifndef _PF_REMOTENOTIFICATIONS_H
#define _PF_REMOTENOTIFICATIONS_H

#include <lang/Object.h>

namespace pf //6
{

class RemoteNotificationsListener //12
{
public:
	virtual void onRemoteNotificationReceived(const std::string&); //19

	virtual void onRemoteNotificationTokenReceived(const std::string&); //26
};

class RemoteNotifications : public lang::Object //34 | Ok so this kind of file is named RemoteNotifications_* and not RemoteNotificationsImpl_*? We've only seen it in Trilogii? | RemoteNotificationsImpl_* (iOS), RemoteNotifications_DUMMY (Trilogii, likely Win), RemoteNotifications_* (iOS)
{
public:
	RemoteNotifications(); //38
	~RemoteNotifications(); //39

	bool isSupported(); //44

	void addListener(RemoteNotificationsListener* listener); //52

	void removeListener(RemoteNotificationsListener* listener); //58

	void setEnabled(bool enabled); //66

	bool areSettingsProvidedByThePlatform(); //73
private:
	class Impl;
	P(Impl) m_impl; //77

	RemoteNotifications(const RemoteNotifications&); //79
	RemoteNotifications& operator=(const RemoteNotifications&); //80
};

}

#endif