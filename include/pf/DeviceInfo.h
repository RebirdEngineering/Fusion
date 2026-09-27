#ifndef _PF_DEVICEINFO_H
#define _PF_DEVICEINFO_H

#include <lang/Object.h>

namespace pf
{

class DeviceInfo : //13
	public lang::Object
{
public:
	DeviceInfo(); //20

	~DeviceInfo(); //25

	bool isSupported(); //32

	std::string getOSName() const; //41

	std::string getOSVersion() const; //50

	std::string getModel() const; //59

	std::string getManufacturer() const; //68

	std::string getProduct() const; //77

	std::string getPlatform() const; //86

	std::string getHardware() const; //96

	std::string getABI() const; //104

	int getDisplayWidth() const; //111

	int getDisplayHeight() const; //118

	int getDisplayDensityGroup() const; //125

	int getDisplayConfigurationGroup() const; //132

	int getTotalMemory() const; //139

	int getCPUCoreCount() const; //146

	int getCPUSpeed() const; //153

	std::vector<std::string> getCPUFeatures() const; //160

	std::string getCPUImplementer() const; //167

	std::string getCPUPart() const; //174

	std::string getCPUHardware() const; //181

	std::vector<std::string> getHardwareComponents() const; //188

	int getPPI() const; //201

private:
	class Impl;
	P(Impl) m_impl; //205

	DeviceInfo(const DeviceInfo&); //207
	DeviceInfo& operator=(const DeviceInfo&); //208
};

}

#endif // !_PF_DEVICEINFO_H