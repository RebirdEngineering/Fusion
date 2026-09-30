#include <pf/Launcher.h>

using namespace lang;

namespace pf
{
	class Launcher::LauncherImpl : public Object //Unofficial?
	{
	public:
		LauncherImpl()
		{
		}

		~LauncherImpl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		bool open()
		{
			return false;
		}

		bool openURL(const std::string& target)
		{
			return false;
		}

		bool openProgram(const std::string& target)
		{
			return false;
		}

		bool canOpenProgram(const std::string& target, const std::string& minVersion)
		{
			return false;
		}

		bool openSMS(const std::string&, const std::string&, const std::string&, const std::string&)
		{
			return false;
		}

		bool openEmail(const std::string&, const std::string&, const std::string&)
		{
			return false;
		}

		bool canOpenEmail()
		{
			return false;
		}

		void setDelegate(LauncherDelegate*)
		{
			//_delegate = delgate;
		}
	};

#include <pf/common/Launcher.h>

}