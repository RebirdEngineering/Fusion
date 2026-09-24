#ifndef _LANG_SCOPEEXIT_H
#define _LANG_SCOPEEXIT_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)

template <class F> class ScopeExit //Lambda at line 290?
{
public:
	F f;
	bool active;

	ScopeExit(const F&);

	//ScopeExit(void); //?
	
	//ScopeExit(void); //?

	operator=(F); //?

	~ScopeExit();

	
private:
	ScopeExit(const F&);
	ScopeExit& operator=(void);
};

}

#endif