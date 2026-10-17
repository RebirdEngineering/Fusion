#ifndef _PF_COMMON_UUID_H
#define _PF_COMMON_UUID_H

//Includes and namespaces are redundant since we're including this file in the namespace

UUID::UUID() //UUIDImpl_DUMMY, UUID_ios+osx
{
	m_impl = new Impl(); //8
}

UUID::~UUID()
{
}

bool UUID::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

std::string UUID::generateUUID()
{
	return m_impl->generateUUID(); //22
}

#endif //! _PF_COMMON_UUID_H