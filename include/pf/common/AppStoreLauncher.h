#ifndef _PF_COMMON_APPSTORELAUNCHER_H
#define _PF_COMMON_APPSTORELAUNCHER_H

#include <pf/AppStoreLauncher.h>

BEGIN_NAMESPACE(pf)

AppStoreLauncher::AppStoreLauncher()
{
}

AppStoreLauncher::~AppStoreLauncher()
{
}

bool AppStoreLauncher::isVariantSupported(AppStoreVariant storeVariant)
{
	return AppStoreLauncherImpl::isVariantSupported(storeVariant);
}

bool AppStoreLauncher::launchAppStore(const std::string& applicationID, AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener)
{
	return AppStoreLauncherImpl::launchAppStore(applicationID, storeVariant, gotoReviews, listener);
}

AppStoreLauncher::AppStoreVariant AppStoreLauncher::defaultVariant() //Not on iOS
{
	return AppStoreLauncherImpl::defaultVariant();
}

}

#endif // !_PF_COMMON_APPSTORELAUNCHER_H