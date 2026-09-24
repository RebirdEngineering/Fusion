#ifndef _PF_APPSTORELAUNCHER_H
#define _PF_APPSTORELAUNCHER_H

#include <pf/StoreListener.h>
#include <lang/Object.h>

namespace pf
{

class AppStoreLauncherImpl;

class AppStoreLauncher :
	public lang::Object
{
public:
	enum AppStoreVariant
	{
		ANDROID_GOOGLE_PLAY,
		ANDROID_AMAZON,
		IOS_IN_APP_STORE,
		IOS_STORE,
		OSX_STORE
	};
	AppStoreLauncher();

	~AppStoreLauncher();

	bool launchAppStore(const std::string& applicationID, AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener);

	bool isSupported();

	bool isVariantSupported(AppStoreVariant storeVariant);

	AppStoreVariant defaultVariant();
};

}

#endif // !_PF_APPSTORELAUNCHER_H