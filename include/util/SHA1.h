#ifndef _UTIL_SHA1_H
#define _UTIL_SHA1_H

#include <lang/pp.h>

namespace util
{

class SHA1 //13
{
public:
	static std::string hash(const void* src, int length); //22

	static std::string hash(const std::string& str); //29

	static std::string hash(const std::vector<unsigned char>& buffer); //36

	static std::string hash(const std::vector<char>& buffer); //44

private:
	SHA1(const SHA1&); //47
	SHA1& operator=(const SHA1&); //48
};

}

#endif