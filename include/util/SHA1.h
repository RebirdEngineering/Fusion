#ifndef _UTIL_SHA1_H
#define _UTIL_SHA1_H

#include <lang/pp.h>

namespace util
{

class SHA1
{
public:
	std::string hash(const void* src, int length);

	std::string hash(const std::string& str);

	std::string hash(const std::vector<char>& buffer);

	std::string hash(const std::vector<unsigned char>& buffer); // new
private:
	SHA1(const SHA1&);
	SHA1& operator=(const SHA1&);
};

}

#endif