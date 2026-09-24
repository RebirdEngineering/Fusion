#ifndef UTIL_BASE16_H
#define UTIL_BASE16_H

#include <util/BaseN.h>

namespace util //9
{

class Base16 //11
{
public:
	static std::string encode(const std::string& str); //19

	static std::string decode(const std::string& str); //26
private:
	Base16(); //29
	static BaseN<1, 2> sm_impl; //30
};

}

#endif // !UTIL_BASE16_H
