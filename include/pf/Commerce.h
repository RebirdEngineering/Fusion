#ifndef _PF_COMMERCE_H
#define _PF_COMMERCE_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class CommerceItem :
	public Object
{
public:
	enum ItemType
	{
		CONSUMABLE,
		NONCONSUMABLE,
		SUBSCRIPTION,
	};

	CommerceItem();
	CommerceItem(const std::string& i, ItemType t, const std::string& n, const std::string& d, const std::string& price);

	CommerceItem(const CommerceItem&);

	~CommerceItem();

	const std::string& getId() const;

	ItemType getType() const;

	bool isPurchased() const;

	int getPurchasedQuantity() const;
	void setPurchasedQuantity(int p);

	const std::string& getName() const;

	const std::string& getDescription() const;

	const std::string& getPrice() const;

	void setDescription(const std::string&);

	const std::vector<char> getReceipt() const;

	void setReceipt(const std::vector<char>& receipt);
	CommerceItem& operator=(CommerceItem&) const;
protected:
	std::string m_id;
	ItemType m_type;
	int m_purchasedQuantity;
	std::string m_name;
	std::string m_price;
	std::vector<char> m_receipt;
};

class Commerce :
	public NS(lang,Object)
{
public:
	enum CommerceError { ERROR_UNKNOWN, ERROR_INVALID_CLIENT, ERROR_USER_CANCEL, ERROR_PAYMENT_INVALID, ERROR_DEVICE_NOT_ALLOWED, ERROR_PRODUCT_IDS, ERROR_OTHER };

	Commerce(unsigned int, const char**, CommerceListener*);
	~Commerce();

	bool isSupported();

	bool isEnabled();

	void checkForCallback();

	bool buyItemId();

	bool buyItem(CommerceItem&, CommerceListener*);

	bool restoreItems(CommerceListener*);

	bool listAvailableItems(CommerceListener*);

	const std::vector<P(CommerceItem)> getItems(CommerceListener*);
	std::vector<P(CommerceItem)> getItemsRef();

	bool isPurchaseHistoryImplemented();

	bool getPurchaseHistory(CommerceListener*);
private:
	class CommerceImpl;
	P(CommerceImpl) m_impl;

	Commerce(const Commerce&);
	Commerce& operator=(const Commerce&);
};

class CommerceListener
{
public:
	enum PaymentStatus
	{
		UNKNOWN,
		SUCCESS,
		FAILED,
		RESTORED,
		PENDING,
		REFUNDED,
	};

	enum PaymentProviderStatus
	{
		INACTIVE,
		ACTIVE,
	};

	virtual ~CommerceListener();

	virtual void initFinished(PaymentProviderStatus);

	virtual void getPurchaseHistoryFinished(const std::string&);

	virtual void paymentFinished(const std::string&, PaymentStatus, CommerceError);
};

}

#endif // !_PF_COMMERCE_H