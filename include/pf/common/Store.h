#ifndef _PF_COMMON_STORE_H
#define _PF_COMMON_STORE_H

//Includes and namespaces are redundant since we're including this file in the namespace

void Store::showProductInStore(const std::string& iTunesItemIdentifier, StoreListener* listener) //6
{
	Impl::showProductInStore(iTunesItemIdentifier, listener);
}

bool Store::isSupported() //13
{
	return Impl::isSupported();
}

#endif // !_PF_COMMON_STORE_H