#ifndef _LANG_SYSTEM_H
#define _LANG_SYSTEM_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang) 

/** 
 * System class provides running environment related information.
 * 
 * @ingroup lang
 */
class System //13
{
public:
	/** 
	 * Returns current system time in milliseconds. 
	 */
	static int64_t currentTimeMillis(); //20
	
	/** 
	 * 
	 */
	static int64_t currentTimeMicros(); //26

private:
	System(); //29
	System( const System& ); //30
	System& operator=( const System& ); //31
};


END_NAMESPACE() // lang


#endif // _LANG_SYSTEM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
