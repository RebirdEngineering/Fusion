#include <pf/ApplicationVersion.h>

//TODO

namespace pf
{
	class ApplicationVersion::Impl //Potentially an unofficial name.
	{
	public:
		static bool isSupported()
		{
			return true;
		}

		static std::string getVersionString() //TODO
		{
			//"com/rovio/fusion/ApplicationVersion"
			//"getApplicationVersionString"
			return "";
		}
	};

#include <pf/common/ApplicationVersion.h>

}