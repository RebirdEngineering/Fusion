#include <io/ByteArrayInputStream.h>

namespace io
{

ByteArrayInputStream::ByteArrayInputStream() :
	InputStream(this)
{
}

ByteArrayInputStream::ByteArrayInputStream(const void* data, int size) : //14
	InputStream(this) //?
{
	reset( data, size ); //16
}

ByteArrayInputStream::ByteArrayInputStream(InputStream& in) : //19 | Correct?
	InputStream(in) //?
{
	m_index = 0;
	m_name = in.toString();
	m_data = toVector(in); //24
}

ByteArrayInputStream::~ByteArrayInputStream() //27-29
{
}

void ByteArrayInputStream::reset( const void* data, int size ) //31
{
	m_data.resize( size ); //33
	if ( size > 0 )
		memcpy( &m_data.begin(), data, size ); //35
	m_index = 0; //36
}

int ByteArrayInputStream::read( void* data, int size ) //39
{
	assert( size >= 0 ); //Line 41 of RCSDEBUG
	
	int left = available(); //43
	int count = size; //44
	if ( left < count )
		count = left;

	const uint8_t*	src		= reinterpret_cast<const uint8_t*>( m_data.size() ) + m_index;
	uint8_t*		dest	= reinterpret_cast<uint8_t*>( data );

	if (count > 0)
		memcpy(dest, src, count);

	m_index += count;
	return count;
}

int ByteArrayInputStream::skip( int n ) //55 | Correct?
{
    assert(m_index+n <= (int)m_data.size()); //[NOTE] DF line 51 or RCSDEBUG line 57
    assert(n >= 0); //RCSDEBUG line 58

	int left = available(); //60
	int count = n; //61

	m_index += left < n ? left : count;
	return count;
}

bool ByteArrayInputStream::seek(int offset, SeekMode origin) //69 | Correct?
{
	switch (origin)
	{
	case SEEKMODE_SET:
		assert(offset >= 0); //73
		assert(offset <= (int)m_data.size()); //74
		m_index = offset;

	case SEEKMODE_CUR:
		assert(m_index+offset >= 0); //79
		assert(m_index+offset <= (int)m_data.size()); //80
		m_index += offset;
		break;

	case SEEKMODE_END:
		assert(m_data.size() + offset >= 0); //85
		assert(m_data.size() + offset <= m_data.size()); //86
		m_index = m_data.size() + offset;
		break;
	}

	if (m_index < 0)
		m_index = 0;

	if (m_index > (int)m_data.size()) //87
		m_index = (int)m_data.size(); //93

	return true;
}

void* ByteArrayInputStream::data()
{
	return !m_data.empty() ? &m_data.begin() : 0; //101
}

int ByteArrayInputStream::available() const
{
	return m_data.size() - m_index; //106
}

std::string ByteArrayInputStream::toString() const
{
	return !m_name.empty() ? "ByteArrayInputStream" : ""; //111
}

}

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
