#include <pf/AppStoreLauncher.h>

using namespace lang;

namespace pf
{
	class AppStoreLauncherImpl : public Object //Potentially unofficial name.
	{
	public:
		static bool launchAppStore(const std::string& applicationID, AppStoreLauncher::AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener)
		{
			return false;
		}

		static bool isSupported()
		{
			return false;
		}

		static bool isVariantSupported(AppStoreLauncher::AppStoreVariant storeVariant)
		{
			return false;
		}

		static AppStoreLauncher::AppStoreVariant defaultVariant()
		{
			return AppStoreLauncher::ANDROID_GOOGLE_PLAY; //?
		}
	};

#include <pf/common/AppStoreLauncher.h>

}