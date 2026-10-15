#ifndef _UTIL_REGISTRYACCESSOR_H
#define _UTIL_REGISTRYACCESSOR_H

#include <util/JSON.h>
#include <lang/Mutex.h>

namespace util
{

class RegistryAccessor //13
{
public:
	RegistryAccessor(); //20

	~RegistryAccessor(); //26

	JSON& registry(); //31

private:
	lang::Mutex::Lock m_lock; //34
};

}

#endif