#include <pf/UUID.h>

using namespace lang;

namespace pf
{
	class UUID::Impl : public Object //Only known in ABTrilogii
	{
	public:
		bool isSupported()
		{
			return false;
		}

		std::string generateUUID()
		{
			return "";
		}
	};

#include <pf/common/UUID.h>

}