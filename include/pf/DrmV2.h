#ifndef _PF_DRMV2_H
#define _PF_DRMV2_H

#include <lang/Object.h>

namespace pf
{

class DrmV2Impl;

class DrmV2 : //16, class only known in ABS410 iPhone, impl no, it's likely there due to GameLua.h included the base header, assuming from TrilogyU. Win: 40 bytes
	public lang::Object
{
public:
	DrmV2(); //25

	~DrmV2(); //30

	bool consumeKey(std::string key, std::string udid, bool*, bool*); //39

	std::string getDeviceID(); //47

	bool areDeviceIDsEqual(const std::string&, const std::string&); //52
private:
	P(DrmV2Impl) m_impl; //55
	DrmV2(const DrmV2&); //56
	DrmV2& operator=(const DrmV2&); //57
};

}

#endif // !_PF_DRMV2_H