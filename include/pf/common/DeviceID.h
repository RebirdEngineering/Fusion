#ifndef _PF_COMMON_DEVICEID_H
#define _PF_COMMON_DEVICEID_H

#include <pf/DeviceID.h>
#include <util/SHA1.h>

namespace pf
{

DeviceID::DeviceID()
{
	m_impl = new Impl();
}

DeviceID::~DeviceID()
{
}

std::string DeviceID::getDeviceIDHash()
{
	return SHA1::hash(m_impl->getDeviceIDHash());
}

std::map<std::string, std::string> DeviceID::getDeviceID() //Not on iOS
{
	return m_impl->getDeviceID();
}

std::map<std::string, std::string> DeviceID::getPlatformIDs() const
{
	return m_impl->getPlatformIDs();
}

std::string DeviceID::emptyID() //Not on iOS
{
	return m_impl->emptyID();
}

}

#endif // !_PF_COMMON_DEVICEID_H