#ifndef _PF_APPSTORELAUNCHER_H
#define _PF_APPSTORELAUNCHER_H

#include <pf/StoreListener.h>
#include <lang/Object.h>

namespace pf
{

//class AppStoreLauncherImpl; //iOS + OSX + Android: 12 bytes [iOS]

class AppStoreLauncher : //19 | No RTTI on Seasons 4.1.0 Win and WP8! Doesn't exist?
	public lang::Object
{
public:
	enum AppStoreVariant //24
	{
		ANDROID_GOOGLE_PLAY,
		ANDROID_AMAZON,
		IOS_IN_APP_STORE,
		IOS_STORE,
		OSX_STORE
	};

	static bool launchAppStore(const std::string& applicationID, AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener); //49

	static bool isSupported(); //56

	static bool isVariantSupported(AppStoreVariant storeVariant); //63

	AppStoreVariant defaultVariant(); //70
};

}

#endif // !_PF_APPSTORELAUNCHER_H