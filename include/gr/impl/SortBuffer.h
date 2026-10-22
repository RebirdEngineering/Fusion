#ifndef _GR_SORTBUFFER_H
#define _GR_SORTBUFFER_H

#include <lang/pp.h>

BEGIN_NAMESPACE(gr) 

class SortGreater //8
{
public:
	explicit SortGreater( const float* z ) : m_z(z) {} //11

	inline bool operator()( int a, int b ) const //13
	{
		return m_z[a] > m_z[b];
	}

private:
	const float* m_z; //19
};

class SortLess //22
{
public:
	explicit SortLess( const float* z ) : m_z(z) {} //25

	inline bool operator()( int a, int b ) const //27
	{
		return m_z[a] < m_z[b];
	}

private:
	const float* m_z; //33
};

/*
 * Temporary buffer used by the gr platform dependent implementations
 * to sort polygons.
 */
class SortBuffer
{
public:
	SortBuffer(); //43
	~SortBuffer(); //44

	void reset( int intbuffersize, int floatbuffersize ); //46

	uint16_t*	intBuffer()			{return m_intBuffer;} //48
	float*		floatBuffer()		{return m_floatBuffer;} //49

private:
	std::vector<uint8_t>	m_buf; //52
	uint16_t*				m_intBuffer; //53
	float*					m_floatBuffer; //54

	SortBuffer( const SortBuffer& ); //56
	SortBuffer& operator=( const SortBuffer& ); //57
};


} // gr


#endif // _GR_SORTBUFFER_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
