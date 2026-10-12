#include <util/Base64.h>

namespace util
{

std::string Base64::encode(const std::string& str) //7 | TODO
{
	std::string result; //9
	sm_impl.encode((std::iterator<const char*, std::string>&)str.begin(), (std::iterator<const char*, std::string>&)str.end(), std::back_inserter(result)); //10 | Correct?
	//assert("std::string Base64::encode(const std::string& str) is not yet decompiled. Returning blank string.");
	return result;
}

std::string Base64::decode(const std::string& str) //TODO
{
	std::string result;
	sm_impl.decode((std::iterator<const char*, std::string>&)str.begin(), (std::iterator<const char*, std::string>&)str.end(), std::back_inserter(result)); //Correct?
	//assert("std::string Base64::decode(const std::string& str) is not yet decompiled. Returning blank string.");
	return result;
}

}