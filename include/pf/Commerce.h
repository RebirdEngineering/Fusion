#ifndef _PF_COMMERCE_H
#define _PF_COMMERCE_H

#include <lang/Object.h>

class CommerceListener;

namespace pf
{

class CommerceItem : //12
	public lang::Object
{
public:
	enum ItemType //19
	{
		CONSUMABLE,
		NONCONSUMABLE,
		SUBSCRIPTION,
	};

	CommerceItem(); //24
	CommerceItem(const std::string& i, ItemType t, const std::string& n, const std::string& d, const std::string& price); //25

	CommerceItem(const CommerceItem&); //27

	~CommerceItem(); //33

	const std::string& getId() const; //38

	ItemType getType() const; //43

	bool isPurchased() const; //48

	int getPurchasedQuantity() const; //53
	void setPurchasedQuantity(int p); //54

	const std::string& getName() const; //59

	const std::string& getDescription() const; //64

	const std::string& getPrice() const; //69

	void setDescription(const std::string&); //74

	const std::vector<char> getReceipt() const; //82

	void setReceipt(const std::vector<char>& receipt); //87

	CommerceItem& operator=(CommerceItem&) const; //92
protected:
	std::string m_id; //106
	ItemType m_type; //107
	int m_purchasedQuantity; //108
	std::string m_name; //109
	std::string m_description; //110
	std::string m_price; //111
	std::vector<char> m_receipt; //112
};

class Commerce :
	public lang::Object
{
public:
	enum CommerceError { ERROR_UNKNOWN, ERROR_INVALID_CLIENT, ERROR_USER_CANCEL, ERROR_PAYMENT_INVALID, ERROR_DEVICE_NOT_ALLOWED, ERROR_PRODUCT_IDS, ERROR_OTHER }; //132

	Commerce(unsigned int, const char**, CommerceListener*); //134
	~Commerce(); //135

	bool isSupported(); //140

	bool isEnabled(); //146

	void checkForCallback(); //151

	bool buyItemId(); //159

	bool buyItem(CommerceItem&, CommerceListener*); //167

	bool restoreItems(CommerceListener*); //174

	bool listAvailableItems(CommerceListener*); //180

	const std::vector<P(CommerceItem)>& getItems(CommerceListener*); //183
	std::vector<P(CommerceItem)>& getItemsRef(); //184

	bool isPurchaseHistoryImplemented(); //191

	bool getPurchaseHistory(CommerceListener*); //198
private:
	class CommerceImpl;
	P(CommerceImpl) m_impl; //203
	Commerce(const Commerce&); //204
	Commerce& operator=(const Commerce&); //205
};

class CommerceListener //208
{
public:
	enum PaymentStatus //212
	{
		UNKNOWN,
		SUCCESS,
		FAILED,
		RESTORED,
		PENDING,
		REFUNDED,
	};
	enum PaymentProviderStatus //221
	{
		INACTIVE,
		ACTIVE,
	};

	virtual ~CommerceListener();

	virtual void initFinished(PaymentProviderStatus); //227

	virtual void getPurchaseHistoryFinished(const std::string&); //236

	virtual void paymentFinished(const std::string&, PaymentStatus, Commerce::CommerceError); //225
};

}

#endif // !_PF_COMMERCE_H