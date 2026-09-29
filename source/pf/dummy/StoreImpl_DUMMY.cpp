#include <pf/Store.h>

using namespace lang;

namespace pf
{
	class Store::Impl : public Object
	{
	public:
		static void showProductInStore(const std::string& iTunesItemIdentifier, StoreListener* listener)
		{
		}

		static bool isSupported()
		{
			return false;
		}
	};

#include <pf/common/Store.h>

}