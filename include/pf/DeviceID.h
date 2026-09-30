#ifndef _PF_DEVICEID_H
#define _PF_DEVICEID_H

#include <lang/Object.h>

namespace pf
{

class DeviceID : //15
	public lang::Object
{
public:
	DeviceID(); //22

	~DeviceID(); //27

	bool isSupported(); //32

	std::vector<char> getDeviceID(); //45

	std::map<std::string, std::string> getPlatformIDs() const; //65

	std::string getDeviceIDHash(); //70

	std::string emptyID(); //76
private:
	class Impl;
	P(Impl) m_impl; //80 | All are 12 bytes.

	DeviceID(const DeviceID&); //82
	DeviceID& operator=(const DeviceID&); //83
};

}

#endif // !_PF_DEVICEID_H