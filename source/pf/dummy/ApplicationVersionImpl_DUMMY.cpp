#include <pf/ApplicationVersion.h>

namespace pf
{
	class ApplicationVersion::Impl //Potentially an unofficial name.
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		static bool isSupported()
		{
			return false;
		}

		static std::string getVersionString()
		{
			return "";
		}
	};

#include <pf/common/ApplicationVersion.h>

}