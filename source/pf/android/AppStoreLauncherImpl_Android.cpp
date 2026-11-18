#include <pf/AppStoreLauncher.h>

//TODO

using namespace lang;

namespace pf
{
	class AppStoreLauncherImpl : public Object
	{
	public:
		static bool launchAppStore(const std::string& applicationID, AppStoreLauncher::AppStoreVariant storeVariant, bool gotoReviews, StoreListener* listener)
		{
			if (!isVariantSupported(storeVariant))
				throw Exception(Format("AppStoreLauncher does not support this storeVariant"));

			//? = launch_GooglePlay : launch_Amazon;
			//"com/rovio/fusion/AppStoreLauncher"
			return false;
		}

		static bool isSupported()
		{
			return false;
		}

		static bool isVariantSupported(AppStoreLauncher::AppStoreVariant storeVariant)
		{
			//? = isSupported_GooglePlay : isSupported_Amazon;
			//"Z"
			//"com/rovio/fusion/AppStoreLauncher"
			return false;
		}

		static AppStoreLauncher::AppStoreVariant defaultVariant()
		{
			return AppStoreLauncher::ANDROID_GOOGLE_PLAY;
		}
	};

#include <pf/common/AppStoreLauncher.h>

}