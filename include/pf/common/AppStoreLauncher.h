#ifndef _PF_COMMON_APPSTORELAUNCHER_H
#define _PF_COMMON_APPSTORELAUNCHER_H

bool AppStoreLauncher::isVariantSupported(AppStoreVariant storeVariant) //11
{
	return AppStoreLauncherImpl::isVariantSupported(storeVariant); //13
}

bool AppStoreLauncher::launchAppStore(const std::string& applicationID, AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener) //16
{
	return AppStoreLauncherImpl::launchAppStore(applicationID, storeVariant, gotoReviews, listener);
}

AppStoreLauncher::AppStoreVariant AppStoreLauncher::defaultVariant() //Not on iOS
{
	return AppStoreLauncherImpl::defaultVariant();
}

#endif // !_PF_COMMON_APPSTORELAUNCHER_H