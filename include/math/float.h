#ifndef _MATH_FLOAT_H
#define _MATH_FLOAT_H


#include <lang/pp.h>


#undef abs


BEGIN_NAMESPACE(math) 

/**
 * Returns scalar clamped to [min,max] range.
 */
template <class T> inline float clamp(const T& v, const T& minv, const T& maxv) //16 | Changed to template
{
	return v < minv ? minv : (v > maxv ? maxv : v);
}

/**
 * Returns scalar clamped to [0,1].
 */
template <class T> inline float saturate(const T& v) //25 | Changed to template
{
	return v < 0.f ? 0.f : (v > 1.f ? 1.f : v);
}

/**
 * Returns scalar absolute value.
 */
inline float abs(float v) //33
{
	return v < 0.f ? -v : v;
}

inline float remainder(float x, float y) //42
{
	return abs(x / y);
}

inline float wrap(float value, float lower, float upper) //55
{
	return 0; // remainder(; //TODO
}

static uint32_t halfToFloatBits(uint16_t y) //145 | Moved from SurfaceFormat
{
	int s = (y >> 15) & 0x00000001;
	int e = (y >> 10) & 0x0000001f;
	int m = y & 0x000003ff;

	if (e == 0)
	{
		if (m == 0)
		{
			//
			// Plus or minus zero
			//

			return s << 31;
		}
		else
		{
			//
			// Denormalized number -- renormalize it
			//

			while (!(m & 0x00000400))
			{
				m <<= 1;
				e -= 1;
			}

			e += 1;
			m &= ~0x00000400;
		}
	}
	else if (e == 31)
	{
		if (m == 0)
		{
			//
			// Positive or negative infinity
			//

			return (s << 31) | 0x7f800000;
		}
		else
		{
			//
			// Nan -- preserve sign and significand bits
			//

			return (s << 31) | 0x7f800000 | (m << 13);
		}
	}

	//
	// Normalized number
	//

	e = e + (127 - 15);
	m = m << 13;

	//
	// Assemble s, e and m.
	//

	return (s << 31) | (e << 23) | m;
}

static uint16_t floatToHalfBits(uint32_t i) //211 | Moved from SurfaceFormat
{
	//
	// Our floating point number, f, is represented by the bit
	// pattern in integer i.  Disassemble that bit pattern into
	// the sign, s, the exponent, e, and the significand, m.
	// Shift s into the position where it will go in in the
	// resulting half number.
	// Adjust e, accounting for the different exponent bias
	// of float and half (127 versus 15).
	//

	register int s = (i >> 16) & 0x00008000;
	register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
	register int m = i & 0x007fffff;

	//
	// Now reassemble s, e and m into a half:
	//

	if (e <= 0)
	{
		if (e < -10)
		{
			//
			// E is less than -10.  The absolute value of f is
			// less than HALF_MIN (f may be a small normalized
			// float, a denormalized float or a zero).
			//
			// We convert f to a half zero.
			//

			return 0;
		}

		//
		// E is between -10 and 0.  F is a normalized float,
		// whose magnitude is less than HALF_NRM_MIN.
		//
		// We convert f to a denormalized half.
		// 

		m = (m | 0x00800000) >> (1 - e);

		//
		// Round to nearest, round "0.5" up.
		//
		// Rounding may cause the significand to overflow and make
		// our number normalized.  Because of the way a half's bits
		// are laid out, we don't have to treat this case separately;
		// the code below will handle it correctly.
		// 

		if (m & 0x00001000)
			m += 0x00002000;

		//
		// Assemble the half from s, e (zero) and m.
		//

		return uint16_t(s | (m >> 13));
	}
	else if (e == 0xff - (127 - 15))
	{
		if (m == 0)
		{
			//
			// F is an infinity; convert f to a half
			// infinity with the same sign as f.
			//

			return uint16_t(s | 0x7c00);
		}
		else
		{
			//
			// F is a NAN; we produce a half NAN that preserves
			// the sign bit and the 10 leftmost bits of the
			// significand of f, with one exception: If the 10
			// leftmost bits are all zero, the NAN would turn 
			// into an infinity, so we have to set at least one
			// bit in the significand.
			//

			m >>= 13;
			return uint16_t(s | 0x7c00 | m | (m == 0));
		}
	}
	else
	{
		//
		// E is greater than zero.  F is a normalized float.
		// We try to convert f to a normalized half.
		//

		//
		// Round to nearest, round "0.5" up
		//

		if (m & 0x00001000)
		{
			m += 0x00002000;

			if (m & 0x00800000)
			{
				m = 0;		// overflow in significand,
				e += 1;		// adjust exponent
			}
		}

		//
		// Handle exponent overflow
		//

		if (e > 30)
		{
			return uint16_t(s | 0x7c00);	// if this returns, the half becomes an
		}   			// infinity with the same sign as f.

		//
		// Assemble the half from s, e and m.
		//

		return uint16_t(s | (e << 10) | (m >> 13));
	}
}

static uint16_t floatToHalf(float f) //338 | Moved from SurfaceFormat
{
	return floatToHalfBits(*reinterpret_cast<int*>(&f));
}

static float halfToFloat(uint16_t h) //343 | Moved from SurfaceFormat
{
	uint32_t f = halfToFloatBits(h);
	return *reinterpret_cast<float*>(&f);
}

/**
 * Linear interpolation in range [a,b] by s.
 */
template <class T> inline T lerp(const T& a, const T& b, float s) //Exists?
{
	return a + (b - a) * s;
}

/**
 * Returns not-a-number value (sqrt of -1).
 */
inline static float getNaN() //Exists?
{
	const int x = 0xFFC00000;
	return *(const float*)&x;
}


END_NAMESPACE() // math


#endif // _MATH_FLOAT_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
