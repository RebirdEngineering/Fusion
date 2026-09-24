#ifndef _UTIL_REGISTRYACCESSOR_H
#define _UTIL_REGISTRYACCESSOR_H

#include <util/JSON.h>
#include <lang/Mutex.h>

namespace util
{

class RegistryAccessor
{
public:
	RegistryAccessor();

	~RegistryAccessor();

	JSON& registry();
private:
	lang::Mutex::Lock m_lock;
};

}

#endif