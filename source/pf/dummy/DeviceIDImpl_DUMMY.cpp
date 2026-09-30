#include <pf/DeviceID.h>
//#include <unistd.h>

using namespace lang;

namespace pf
{
	class DeviceID::Impl : public Object //Potentially unofficial.
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		std::vector<char> getDeviceID(); //TODO
		//{
			//if gethostuuid()
		//}

		std::map<std::string, std::string> getPlatformIDs() const; //TODO

		std::string getDeviceIDHash()
		{
			return "";
		}

		std::string emptyID()
		{
			return "unavailable";
		}

	};

#include <pf/common/DeviceID.h>

}