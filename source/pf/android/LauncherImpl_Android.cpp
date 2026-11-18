#include <pf/Launcher.h>

//#include <java/jni.h>

using namespace lang;
//using namespace java;

namespace pf
{
	class Launcher::LauncherImpl : public Object
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

		bool openURL(const std::string& target) //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"openURL"
			return false;
		}

		bool openProgram(const std::string& target) //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"openProgram"
			return false;
		}

		bool canOpenProgram(const std::string& target, const std::string& minVersion) //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"canOpenProgram"
			return false;
		}

		bool openSMS(const std::string&, const std::string&, const std::string&, const std::string&) //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"openSMS"
			return false;
		}

		bool openEmail(const std::string&, const std::string&, const std::string&) //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"openEmail"
			if (_delegate)
				_delegate->LauncherCompleted()
			return false;
		}

		bool canOpenEmail() //TODO
		{
			//"com/rovio/fusion/Launcher"
			//"V"
			//"canOpenEmail"
			return false;
		}

		void setDelegate(LauncherDelegate* delegate)
		{
			_delegate = delegate;
		}

	private:
		LauncherDelegate* _delegate; //0x0C

	};

#include <pf/common/Launcher.h>

}