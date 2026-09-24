#ifndef UTIL_BASE64_H
#define UTIL_BASE64_H

#include <util/BaseN.h>

BEGIN_NAMESPACE(util)

class Base64
{
public:
	std::string encode(const std::string& str);

	std::string decode(const std::string& str);
private:
	Base64();
	static BaseN<3, 4> sm_impl;
};

}

#endif // !UTIL_BASE64_H
