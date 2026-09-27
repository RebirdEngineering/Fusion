#ifndef _PF_COMMON_APPLICATIONVERSION_H
#define _PF_COMMON_APPLICATIONVERSION_H

bool ApplicationVersion::isSupported() //Includes and namespaces are redundant since we're including this file in the namespace
{
	return Impl::isSupported();
}

std::string ApplicationVersion::getVersionString()
{
	return Impl::getVersionString(); //14
}

#endif // !_PF_COMMON_APPLICATIONVERSION_H