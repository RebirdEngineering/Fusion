#ifndef _PF_STORELISTENER_H
#define _PF_STORELISTENER_H

namespace pf
{

class StoreListener
{
public:
	virtual void onOpeningTheStoreFailed() = 0;

	virtual void onStoreModalUIWillBeShown() = 0;

	virtual void onStoreModalUIWasHidden() = 0;
};

}

#endif // !_PF_STORELISTENER_H