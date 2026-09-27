#ifndef _PF_COMMON_UUID_H
#define _PF_COMMON_UUID_H

//Includes and namespaces are redundant since we're including this file in the namespace

UUID::UUID() //UUIDImpl_DUMMY, UUID_ios+osx
{
	m_impl = new Impl();
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

#endif //! _PF_COMMON_UUID_H