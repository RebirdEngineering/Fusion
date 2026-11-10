#include <pf/Launcher.h>
#include <lang/String.h>

#include <windows.h>
#include <shellapi.h>

using namespace lang;

namespace pf
{
	class Launcher::LauncherImpl : public Object //Unofficial name?
	{
	public:
		LauncherImpl()
		{
			_delegate = 0;
		}

		~LauncherImpl()
		{
		}

		bool isSupported() //Very likely true.
		{
			return true;
		}

		bool open() //?
		{
			return true;
		}

		bool openURL(const std::string& target) //4C96A0
		{
			SHELLEXECUTEINFOW execInfo;
			execInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
			execInfo.lpVerb = L"open";
			execInfo.lpFile = string::toUTF16string(target).c_str();
			execInfo.nShow = SW_SHOWNORMAL;
			ShellExecuteExW(&execInfo);

			if (_delegate)
				_delegate->LauncherCompleted(LauncherDelegate::UNKNOWN);

			return true;
		}

		bool openProgram(const std::string& target) //4C96A0
		{
			SHELLEXECUTEINFOW execInfo;
			execInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
			execInfo.lpVerb = L"open";
			execInfo.lpFile = string::toUTF16string(target).c_str();
			execInfo.nShow = SW_SHOWNORMAL;
			ShellExecuteExW(&execInfo);

			if (_delegate)
				_delegate->LauncherCompleted(LauncherDelegate::UNKNOWN);

			return true;
		}

		bool canOpenProgram(const std::string& target, const std::string& minVersion) //4C9780
		{
			return (GetFileAttributesW(string::toUTF16string(target).c_str()) & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}

		bool openSMS(const std::string&, const std::string&, const std::string&, const std::string&) //Unused?
		{
			return false;
		}

		bool openEmail(const std::string&, const std::string&, const std::string&) //Unused?
		{
			return false;
		}

		bool canOpenEmail() //Unused?
		{
			return false;
		}

		void setDelegate(LauncherDelegate* delegate)
		{
			_delegate = delegate;
		}

	private:
		LauncherDelegate* _delegate; //Unused in the iOS impl!

	};

#include <pf/common/Launcher.h>

}