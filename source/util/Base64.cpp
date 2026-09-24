#include <util/Base64.h>

namespace util
{

//alphabet __cxx_global_var_init

std::string Base64::encode(const std::string& str)
{
	std::string result;
	sm_impl.encode(str.begin(), str.end(), back_inserter(result));
	return result;
}

}