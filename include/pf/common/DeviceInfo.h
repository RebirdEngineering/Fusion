#ifndef _PF_COMMON_DEVICEINFO_H
#define _PF_COMMON_DEVICEINFO_H

#include <pf/DeviceInfo.h>

BEGIN_NAMESPACE(pf)

DeviceInfo::DeviceInfo()
{
	m_impl = new Impl();
}

DeviceInfo::~DeviceInfo()
{
}

std::string DeviceInfo::getOSName()
{
	return m_impl->getOSName();
}

std::string DeviceInfo::getOSVersion()
{
	return m_impl->getOSVersion();
}

std::string DeviceInfo::getModel()
{
	return m_impl->getModel();
}

std::string DeviceInfo::getManufacturer() const
{
	return m_impl->getManufacturer();
}

//ON IOS THESE LATER ONES ARE NOT IMPLEMENTED IN THE HEADER

std::string DeviceInfo::getProduct() const
{
	return m_impl->getProduct();
}

std::string DeviceInfo::getPlatform() const
{
	return m_impl->getPlatform();
}

std::string DeviceInfo::getHardware() const
{
	return m_impl->getHardware();
}

std::string DeviceInfo::getABI() const
{
	return m_impl->getABI();
}

int DeviceInfo::getDisplayWidth() const
{
	return m_impl->getDisplayWidth();
}

int DeviceInfo::getDisplayHeight() const
{
	return m_impl->getDisplayHeight();
}

int DeviceInfo::getDisplayDensityGroup() const
{
	return m_impl->getDisplayDensityGroup();
}

int DeviceInfo::getDisplayConfigurationGroup() const
{
	return m_impl->getDisplayConfigurationGroup();
}

int DeviceInfo::getTotalMemory() const
{
	return m_impl->getTotalMemory();
}

int DeviceInfo::getCPUCoreCount() const
{
	return m_impl->getCPUCoreCount();
}

int DeviceInfo::getCPUSpeed() const
{
	return m_impl->getCPUSpeed();
}

std::vector<std::string> DeviceInfo::getCPUFeatures() const
{
	return m_impl->getCPUFeatures();
}

std::string DeviceInfo::getCPUImplementer() const
{
	return m_impl->getCPUImplementer();
}

std::string DeviceInfo::getCPUPart() const
{
	return m_impl->getCPUPart();
}

std::string DeviceInfo::getCPUHardware() const
{
	return m_impl->getCPUHardware();
}

std::vector<std::string> DeviceInfo::getHardwareComponents() const
{
	return m_impl->getHardwareComponents();
}

int DeviceInfo::getPPI() const //Except this one
{
	return m_impl->getPPI();
}

}

#endif // !_PF_COMMON_DEVICEINFO_H