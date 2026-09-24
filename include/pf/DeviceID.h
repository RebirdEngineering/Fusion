#ifndef _PF_DEVICEID_H
#define _PF_DEVICEID_H

#include <lang/Object.h>

namespace pf
{

class DeviceID :
	public lang::Object
{
public:
	DeviceID();

	~DeviceID();

	bool isSupported();

	std::vector<char> getDeviceID();

	std::map<std::string, std::string> getPlatformIDs() const;

	std::string getDeviceIDHash();

	std::string emptyID();
private:
	class Impl;
	P(Impl) m_impl;

	DeviceID(const DeviceID&);
	DeviceID& operator=(const DeviceID&);
};

}

#endif // !_PF_TEXTINPUT_H