#ifndef UTIL_BASE64_H
#define UTIL_BASE64_H

#include <util/BaseN.h>

namespace util
{

class Base64 //14
{
public:
	static std::string encode(const std::string& str); //22

	static std::string decode(const std::string& str); //29

private:
	Base64(); //32
	static BaseN<3, 4> sm_impl; //33
};

}

#endif // !UTIL_BASE64_H
