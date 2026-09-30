#include <pf/Commerce.h>

using namespace lang;

namespace pf
{
	class Commerce::CommerceImpl : public Object //Potentially unofficial.
	{
	public:
		CommerceImpl(unsigned int, const char**, CommerceListener*);
		~CommerceImpl();

		bool isSupported()
		{
			return false;
		}

		bool isEnabled()
		{
			return false;
		}

		void checkForCallback()
		{
		}

		bool buyItemId()
		{
			return false;
		}

		bool buyItem(CommerceItem&, CommerceListener*)
		{
			return false;
		}

		bool restoreItems(CommerceListener*)
		{
			return false;
		}

		bool listAvailableItems(CommerceListener*)
		{
			return false;
		}

		const std::vector<P(CommerceItem)> getItems(CommerceListener*)
		{
			std::vector<P(CommerceItem)> result;
			return result;
		}

		std::vector<P(CommerceItem)> getItemsRef()
		{
			std::vector<P(CommerceItem)> result;
			return result;
		}

		bool isPurchaseHistoryImplemented()
		{
			return false;
		}

		bool getPurchaseHistory(CommerceListener*)
		{
			return false;
		}
	};

//#include <pf/common/Commerce.h> //Doesn't exist? Well then how does this work?

}