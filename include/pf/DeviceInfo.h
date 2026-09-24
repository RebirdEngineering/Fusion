#ifndef _PF_DEVICEINFO_H
#define _PF_DEVICEINFO_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class DeviceInfo :
	public Object
{
public:
	DeviceInfo();

	~DeviceInfo();

	bool isSupported();

	std::string getOSName();

	std::string getOSVersion();

	std::string getModel();

	std::string getManufacturer() const;

	std::string getProduct() const;

	std::string getPlatform() const;

	std::string getHardware() const;

	std::string getABI() const;

	int getDisplayWidth() const;

	int getDisplayHeight() const;

	int getDisplayDensityGroup() const;

	int getDisplayConfigurationGroup() const;

	int getTotalMemory() const;

	int getCPUCoreCount() const;

	int getCPUSpeed() const;

	std::vector<std::string> getCPUFeatures() const;

	std::string getCPUImplementer() const;

	std::string getCPUPart() const;

	std::string getCPUHardware() const;

	std::vector<std::string> getHardwareComponents() const;

	int getPPI() const;
private:
	class Impl;
	P(Impl) m_impl;

	DeviceInfo(const DeviceInfo&);
	DeviceInfo& operator=(const DeviceInfo&);
};

}

#endif // !_PF_DEVICEINFO_H