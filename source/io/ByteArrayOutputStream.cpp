#include <io/ByteArrayOutputStream.h>
//#include <stdint.h>
//#include <string.h>

namespace io
{ 

ByteArrayOutputStream::ByteArrayOutputStream( int size ) : //8
	OutputStream(this),
	m_userDefined( false )
{
	m_buffer->resize( 0 ); //12
}

ByteArrayOutputStream::ByteArrayOutputStream( std::vector<unsigned char>* buffer ) : //Not seen on iOS.
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

void ByteArrayOutputStream::reset() //Not seen on iOS
{
	m_buffer->resize( 0 );
}

void ByteArrayOutputStream::write( const void* data, int size ) //38
{
	int oldsize = m_buffer->size(); //40
	m_buffer->resize( oldsize + size ); //41
	for ( int i = 0 ; i < size ; ++i ) //42
		(*m_buffer)[oldsize+i] = reinterpret_cast<const char*>(data)[i]; //43
}

int ByteArrayOutputStream::size() const //Not seen on iOS
{
	return m_buffer->size();
}

std::string ByteArrayOutputStream::toString() const
{
	return "ByteArrayOutputStream"; //Lol fixed from inputstream
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
