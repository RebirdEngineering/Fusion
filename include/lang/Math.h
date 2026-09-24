#ifndef _LANG_MATH_H
#define _LANG_MATH_H


#include <lang/pp.h>


// Make sure there is no defines around
#undef E
#undef PI
#undef abs
#undef max
#undef min


BEGIN_NAMESPACE(lang) 


/** 
 * Math contains static methods for performing basic numeric operations.
 * 
 * @ingroup lang
 */
class Math
{
public:
	/** 
	 * A value as close as possible to <i>e</i>.
	 * (the base of the natural logarithms)
	 */
	static const float E;

	/** 
	 * A value as close as possible to <i>pi</i>.
	 * (the ratio of the circumference of a circle to its diameter)
	 */
	static const float PI;

	/** Returns -x if x is negative. */
	template <class T>
	static T		abs( T x )					{return x < T(0) ? -x : x;}

	/** Returns smaller of two values. */
	template <class T>
	static T		min( T a, T b )				{return b < a ? b : a;}

	/** Returns larger of two values. */
	template <class T>
	static T		max( T a, T b )				{return a < b ? b : a;}

	/**  */
	template <class T>
	static T		sgn(T a)					{ return (T(0) < a) - (a < T(0)); } //No clue what this is, assuming https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c or (a > T(0)) - (a < T(0));
	
	/** Returns the closest int to the argument. */ 
	static int		round( float x )			{return (int)::floorf(x+.5f);}

	/** Returns the arc cosine of an angle, in the range of 0.0 through pi. */ 
	static float	acos( float x )				{return ::acosf(x);}

	/** Returns the arc sine of an angle, in the range of -pi/2 through pi/2. */ 
	static float	asin( float x )				{return ::asinf(x);}

	/** Returns the arc tangent of an angle, in the range of -pi/2 through pi/2. */ 
	static float	atan( float x )				{return ::atanf(x);}

	/** Converts rectangular coordinates (b, a) to polar (r, theta). */ 
	static float	atan2( float x, float y )	{return ::atan2f(x,y);}

	/** Returns the smallest (closest to negative infinity) value that is not less than the argument and is equal to a mathematical integer. */ 
	static float	ceil( float x )				{return ::ceilf(x);}

	/** Returns the trigonometric cosine of an angle. */ 
	static float	cos( float x )				{return ::cosf(x);}

	/** Returns the exponential number e (i.e., 2.718...) raised to the power of a value. */ 
	static float	exp( float x )				{return ::expf(x);}

	/** Returns the largest (closest to positive infinity) value that is not greater than the argument and is equal to a mathematical integer. */ 
	static float	floor( float x )			{return ::floorf(x);}

	/** Returns the natural logarithm (base e) of a value. */ 
	static float	log( float x )				{return ::logf(x);}
	
	/**  */ 
	static int		log2i( unsigned int x )		{/*return x == 0 ? -1 : 31 - __builtin_clz(x);*/ /* //GCC (x > 1) ? 1 + log2(x >> 1) : 0;*/ return x;} //Unknownhttps://stackoverflow.com/a/22418446
	
	/**  */ 
	static float	log2( float x )				{return ::log2f(x);}

	/** Returns of value of the first argument raised to the power of the second argument. */ 
	static float	pow( float x, float y )		{return ::powf(x,y);}

	/** Returns the value that is closest in value to a and is equal to a mathematical integer. */ 
	static float	rint( float x )				{return ::floorf(x+.5f);}

	/** Returns the trigonometric sine of an angle. */ 
	static float	sin( float x )				{return ::sinf(x);}

	/** Returns the correctly rounded positive square root of a value. */ 
	static float	sqrt( float x )				{return ::sqrtf(x);}

	/** Returns the trigonometric tangent of an angle. */ 
	static float	tan( float x )				{return ::tanf(x);}
	
	/**  */ 
	static float	fmod( float x, float y )	{return ::fmodf(x, y);}

	/** Converts an angle measured in radians to the equivalent angle measured in degrees. */ 
	static float	toDegrees( float radians )	{return radians * 57.29577951308232f;}

	/** Converts an angle measured in degrees to the equivalent angle measured in radians. */ 
	static float	toRadians( float degrees )	{return degrees * 0.017453292519943295f;}
	
	/**  */ 
	static unsigned int	ceilPow2( unsigned int x )	{return 0; } //TODO | Copied from cudpp_util.h?
	
	/**  */ 
	static bool		isPow2( unsigned int x )		{return (x & (x - 1)) == 0 && (x != 0); }
	
	/**  */ 
	static bool		isSquare( unsigned int x )		{return ((static_cast<int>(::sqrt(x)) ^ 2) == x);} //Copied from something
	
	/**  */ 
	static bool		isNaN( float x )				{return ::isnan(x);}
	
	/**  */ 
	static bool		isInf( float x )				{return ::isinf(x);}

private:
	Math();
	Math( const Math& );
	Math& operator=( const Math& );
};


} // lang


#endif // _LANG_MATH_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
