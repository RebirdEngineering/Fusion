#ifndef _PF_STORE_H
#define _PF_STORE_H

#include <lang/Object.h> //For now
#include <pf/StoreListener.h>

BEGIN_NAMESPACE(pf)

class Store :
	public Object
{
public:
	void showProductInStore(const string&, StoreListener*);

	bool isSupported();
private:
	Store(const Store&);
	Store& operator=(const Store&);
};

}

#endif