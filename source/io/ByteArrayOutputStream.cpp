#include <io/ByteArrayOutputStream.h>

namespace io
{ 


ByteArrayOutputStream::ByteArrayOutputStream( int size ) :
	OutputStream(this),
	m_userDefined( false )
{
	m_buffer->resize( 0 );
}

ByteArrayOutputStream::ByteArrayOutputStream( std::vector<uint8_t>* buffer ) :
	OutputStream(this), //?
	m_buffer( buffer ),
	m_userDefined( true )
{
	assert( 0 != m_buffer ); //Assert on line 23 (matches private KA3D)

	m_buffer->resize( 0 );
}

ByteArrayOutputStream::~ByteArrayOutputStream()
{
	if ( !m_userDefined )
	{
		delete m_buffer;
		m_buffer = 0;
	}
}

void ByteArrayOutputStream::reset()
{
	m_buffer->resize( 0 );
}

void ByteArrayOutputStream::write( const void* data, int size )
{
	int oldsize = m_buffer->size();
	m_buffer->resize( oldsize + size );
	for ( int i = 0 ; i < size ; ++i )
		(*m_buffer)[oldsize+i] = reinterpret_cast<const char*>(data)[i];
}

int ByteArrayOutputStream::size() const
{
	return m_buffer->size();
}

std::string ByteArrayOutputStream::toString() const
{
	return "ByteArrayOutputStream"; //Lol fixed from inputstream
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
