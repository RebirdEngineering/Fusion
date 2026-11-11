#include <pf/DeviceID.h>

#include <windows.h>

using namespace lang;

namespace pf
{
	class DeviceID::Impl : public Object //TODO
	{
	public:
		Impl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		std::vector<char> getDeviceID(); //TODO
		//{
			//if gethostuuid()
		//}

		std::map<std::string, std::string> getPlatformIDs() const; //TODO

		std::string getDeviceIDHash() //4CE270 | TODO
		{
			//HKEY result;
			//if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, 0x01u, &result))
			{

				//if (RegQueryValueExW(result, L"InstallDate", 0, 0, ))
				{
				}
			}

			//else
				return emptyID();
		}

		std::string emptyID()
		{
			return "unavailable";
		}

	};

#include <pf/common/DeviceID.h>

}