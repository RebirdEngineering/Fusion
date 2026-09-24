#include <pf/detail/detail.h>
#include <lang/Mutex.h>

using namespace lang;

namespace pf
{
namespace detail
{

static std::vector<RemoteNotificationsListener*> sm_remoteNotificationListeners; //14
static std::string sm_lastRemoteNotification; //15
static std::string sm_remoteNotificationToken; //16
static Mutex sm_mutex; //17

static void addRemoteNotificationListener(RemoteNotificationsListener* listener) //20
{
	Mutex::Lock lock(sm_mutex); //22
	if (!listener)
		return;
	if (sm_remoteNotificationListeners.empty())
		return;
	sm_remoteNotificationListeners.push_back(listener);
	if (sm_remoteNotificationToken.size())
		listener->onRemoteNotificationTokenReceived(sm_remoteNotificationToken);
	if (sm_lastRemoteNotification.size())
		listener->onRemoteNotificationReceived(sm_lastRemoteNotification);
}

static void notifyRemoteNotificationListeners(const std::string& payloadAsJSON) //55
{
	Mutex::Lock lock(sm_mutex); //57

	std::vector <RemoteNotificationsListener*>::iterator begin = sm_remoteNotificationListeners.begin(); //59
	std::vector <RemoteNotificationsListener*>::iterator end = sm_remoteNotificationListeners.end(); //60
	while (begin != end)
	{
		//::iterator<RemoteNotificationsListener**, std::vector<RemoteNotificationsListener*> > a;
		//::iterator<RemoteNotificationsListener**, std::vector<RemoteNotificationsListener*> > i; //62
		//i->onRemoteNotificationReceived(payloadAsJSON);
		//i++;
	}
	
	sm_lastRemoteNotification = payloadAsJSON;
}

static void remoteNotificationTokenReceived(const std::string& token) //70
{
	Mutex::Lock lock(sm_mutex); //72

	if (sm_remoteNotificationListeners.empty())
		return;

	//iterator<pf::RemoteNotificationsListener**, std::vector<pf::RemoteNotificationsListener*> > a;
	std::vector<RemoteNotificationsListener*>::iterator begin = sm_remoteNotificationListeners.begin(); //74
	std::vector<RemoteNotificationsListener*>::iterator end = sm_remoteNotificationListeners.end(); //75

	//while (iterator<RemoteNotificationsListener**, std::vector<RemoteNotificationsListener*>> i != end); //77
	//RemoteNotificationsListener::onRemoteNotificationTokenReceived(token);
	/*while (begin != end)
	{
		sm_remoteNotificationListeners[**begin]->onRemoteNotificationReceived(payloadAsJSON);
		i++;
	}*/
	sm_remoteNotificationToken = token;
}

}

}