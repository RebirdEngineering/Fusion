#include <pf/DeviceID.h>

//TODO

#include <jni.h>

using namespace lang;

namespace pf
{
	class DeviceID::Impl : public Object //0x00 bytes. Potentially unofficial filename.
	{
	public:
		Impl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		std::vector<char> getDeviceID();/* //TODO
		{
			//"com/rovio/fusion/DeviceIDCreator"
			//"getUniqueId"
		}*/

		std::map<std::string, std::string> getPlatformIDs() const; //TODO

		std::string getDeviceIDHash()
		{
			return SHA1::hash(getDeviceID());
		}

		std::string emptyID()
		{
			return "unavailable";
		}

	};

#include <pf/common/DeviceID.h>

}