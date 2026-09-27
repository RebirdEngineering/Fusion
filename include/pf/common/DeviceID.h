#ifndef _PF_COMMON_DEVICEID_H
#define _PF_COMMON_DEVICEID_H

#include <util/SHA1.h>

using namespace util;

//Includes and namespaces are redundant since we're including this file in the namespace

DeviceID::DeviceID()
{
	m_impl = new Impl();
}

DeviceID::~DeviceID()
{
}

bool DeviceID::isSupported()
{
	return m_impl->isSupported();
}

std::vector<char> DeviceID::getDeviceID() //Not on iOS
{
	return m_impl->getDeviceID();
}

std::map<std::string, std::string> DeviceID::getPlatformIDs() const
{
	return m_impl->getPlatformIDs();
}

std::string DeviceID::getDeviceIDHash()
{
	return SHA1::hash(m_impl->getDeviceIDHash());
}

std::string DeviceID::emptyID() //Not on iOS
{
	return m_impl->emptyID();
}

#endif // !_PF_COMMON_DEVICEID_H