#ifndef _PF_COMMON_DRMV2_H
#define _PF_COMMON_DRMV2_H

//Includes and namespaces are redundant since we're including this file in the namespace

DrmV2::DrmV2()
{
}

DrmV2::~DrmV2()
{
}

bool DrmV2::consumeKey(std::string key, std::string udid, bool*, bool*)
{
	return m_impl->consumeKey(key, udid, ?, ?);
}

std::string DrmV2::getDeviceID()
{
	return m_impl->getDeviceID();
}

bool DrmV2::areDeviceIDsEqual(const std::string&, const std::string&)
{
	return m_impl->areDeviceIDsEqual();
}

#endif // !_PF_COMMON_DRMV2_H