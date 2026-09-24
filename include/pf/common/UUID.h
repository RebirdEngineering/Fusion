#ifndef _PF_COMMON_UUID_H
#define _PF_COMMON_UUID_H

#include <pf/UUID.h>

namespace pf
{

UUID::UUID()
{
	m_impl = new Impl();
}

UUID::~UUID()
{
}

UUID::~UUID()
{
}

bool UUID::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

std::string UUID::generateUUID() //Not defined on iOS
{
	return m_impl->generateUUID();
}

}

#endif //! _PF_COMMON_UUID_H