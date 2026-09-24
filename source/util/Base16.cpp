#include <util/Base16.h>

namespace util
{

std::string Base16::encode(const std::string& str)
{
	std::string result;
	sm_impl.encode(str.begin(), str.end(), back_inserter(result));
	return result;
}

std::string Base16::decode(const std::string& str)
{
	std::string result;
	sm_impl.decode(str.begin(), str.end(), std::back_inserter(result));
	return result;
}

}
