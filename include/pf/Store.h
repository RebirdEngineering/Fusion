#ifndef _PF_STORE_H
#define _PF_STORE_H

#include <lang/Object.h> //For now

namespace pf
{

class StoreListener;

class Store : //14
	public lang::Object
{
public:
	static void showProductInStore(const std::string& iTunesItemIdentifier, StoreListener* listener); //36

	static bool isSupported(); //41
private:
	class Impl; //Ok so there's no Impl and m_impl? We at least need this defined. Only exists in ABS 4.1.0?
	Store(const Store&); //46
	Store& operator=(const Store&); //47
};

}

#endif