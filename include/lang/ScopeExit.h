#ifndef _LANG_SCOPEEXIT_H
#define _LANG_SCOPEEXIT_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)

template <class F> class ScopeExit //Lambda at line 290?
{
public:
	F f; //13
	bool active; //14

	ScopeExit(const F&); //16

	//ScopeExit(F); //22
	
	//ScopeExit(F); //28

	operator=(F); //35?

	~ScopeExit(); //42

	
private:
	ScopeExit(const F&); //51
	ScopeExit& operator=(const F&); //52
};

}

#endif