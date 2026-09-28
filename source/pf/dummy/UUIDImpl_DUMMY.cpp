#include <pf/UUID.h>

using namespace lang;

namespace pf
{
	class UUID::Impl : public Object //Only known in ABTrilogii
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		static bool isSupported()
		{
			return false;
		}

		static std::string generateUUID()
		{
			return "";
		}
	};

//#include <pf/common/UUID.h> //TODO

}