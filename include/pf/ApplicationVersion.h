#ifndef _PF_APPLICATIONVERSION_H
#define _PF_APPLICATIONVERSION_H

#include <lang/pp.h>

BEGIN_NAMESPACE(pf)

class ApplicationVersion
{
public:
	bool isSupported();

	std::string getVersionString();

	class Impl; //No m_impl?
};

}

#endif // !_PF_APPLICATIONVERSION_H