#ifndef _LANG_THREADINTRRRUPTEDEXCEPTION_H
#define _LANG_THREADINTRRRUPTEDEXCEPTION_H

#include <lang/pp.h>
#include <lang/Exception.h>

BEGIN_NAMESPACE(lang) 

class ThreadInterruptedException : //11
	public Exception
{
public:
	/** Creates an exception with the specified error description. */
	ThreadInterruptedException( const NS(lang,Format)& msg )						: Exception(msg) {} //15
};


END_NAMESPACE() // lang


#endif // _LANG_THREADINTRRRUPTEDEXCEPTION_H
