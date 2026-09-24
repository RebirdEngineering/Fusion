#ifndef _PF_DETAIL_H
#define _PF_DETAIL_H

#include <pf/RemoteNotifications.h>

namespace pf
{
	namespace detail
	{
		void addRemoteNotificationListener(RemoteNotificationsListener* listener);
		void notifyRemoteNotificationListeners(const std::string& payloadAsJSON);
		void remoteNotificationTokenReceived(const std::string& token);
	}
}

#endif // !_PF_DETAIL_H