#include <pf/Commerce.h>

using namespace lang;

namespace pf
{
	class Commerce::CommerceImpl : public Object
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
			return m_items;
		}

		std::vector<P(CommerceItem)> getItemsRef()
		{
			return m_items;
		}

		bool isPurchaseHistoryImplemented()
		{
			return false;
		}

		bool getPurchaseHistory(CommerceListener*)
		{
			return false;
		}

		std::vector<P(CommerceItem)> m_items;
	};

//#include <pf/common/Commerce.h>

}