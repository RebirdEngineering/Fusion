#ifndef _LANG_FLOAT_H
#define _LANG_FLOAT_H


#include <lang/pp.h>


BEGIN_NAMESPACE(lang) 


/** 
 * Float type information.
 * 
 * @ingroup lang
 */
class Float //12
{
public:
	/** 
	 * Maximum float value.
	 */
	static const float	MAX_VALUE; //18

	/** 
	 * Minimum float value. 
	 * This is smallest (positive) value that returns valid results when inverted.
	 */
	static const float	MIN_VALUE; //24
	
	static float parse(const char**, const char**, int*); //33 | Not on iOS
};


} // lang


#endif // _LANG_FLOAT_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
