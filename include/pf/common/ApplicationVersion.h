#ifndef _PF_COMMON_APPLICATIONVERSION_H
#define _PF_COMMON_APPLICATIONVERSION_H

#include <pf/ApplicationVersion.h>

BEGIN_NAMESPACE(pf)

bool ApplicationVersion::isSupported()
{
	return Impl::isSupported();
}

std::string ApplicationVersion::getVersionString()
{
	Impl::getVersionString();
}

}

#endif // !_PF_COMMON_APPLICATIONVERSION_H