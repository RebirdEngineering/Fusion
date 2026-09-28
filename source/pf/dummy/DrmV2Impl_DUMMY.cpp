#include <pf/DrmV2.h>

using namespace lang;

namespace pf
{
	class DrmV2Impl : public Object //Not in ABS410 DWARF at all, it's likely there due to GameLua.h included the base header, assuming from TrilogyU.
	{
	public:
		DrmV2Impl()
		{
		}

		~DrmV2Impl()
		{
		}

		bool consumeKey(std::string key, std::string udid, bool*, bool*)
		{
			return false;
		}

		std::string getDeviceID()
		{
			return "";
		}

		bool areDeviceIDsEqual(const std::string&, const std::string&)
		{
			return false;
		}
	};

//#include <pf/common/DrmV2.h> //TODO

}