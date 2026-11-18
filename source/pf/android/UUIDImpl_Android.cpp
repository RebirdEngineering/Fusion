#include <pf/UUID.h>

//TODO

using namespace lang;

namespace pf
{
	class UUID::Impl : public Object //0x00 bytes
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

		std::string generateUUID()
		{
			//"java/util/UUID"
			//"randomUUID"
			return "";
		}
	};

#include <pf/common/UUID.h>

}