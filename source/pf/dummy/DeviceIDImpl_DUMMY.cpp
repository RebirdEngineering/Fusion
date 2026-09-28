#include <pf/DeviceID.h>

using namespace lang;

namespace pf
{
	class DeviceID::Impl : public Object //OSX
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

		std::map<std::string, std::string> getPlatformIDs() const; //TODO

		std::string getDeviceIDHash()
		{
			return "";
		}

		std::string emptyID()
		{
			return "";
		}

	};

#include <pf/common/DeviceID.h>

}