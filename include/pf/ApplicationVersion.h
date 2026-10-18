#ifndef _PF_APPLICATIONVERSION_H
#define _PF_APPLICATIONVERSION_H

#include <lang/pp.h>

namespace pf //6
{

class ApplicationVersion //15, not seen on Windows.
{
public:
	bool isSupported(); //24

	std::string getVersionString(); //31

	class Impl; //No m_impl?
};

}

#endif // !_PF_APPLICATIONVERSION_H