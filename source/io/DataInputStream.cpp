#include <io/DataInputStream.h>
#include <io/IOException.h>
#include <lang/UTFConverter.h>


using namespace lang;


namespace io
{ 

DataInputStream::DataInputStream( InputStream& source )
	: InputStream(source) //Used in Classic (Bada, MacOS < 2.3.0, Symbian, WebOS), Rio (MacOS < 1.4.4), Seasons (MacOS < 1.2.0), Trilogy
{
	//?
}

DataInputStream::~DataInputStream()
{
}

int DataInputStream::skip( int n )
{
	return getEmbeddedStream().skip(n);
}

bool DataInputStream::seek(int n, SeekMode origin)
{
	return getEmbeddedStream().seek(n, origin);
}

int DataInputStream::read( void* data, int size )
{
	return getEmbeddedStream().read(data, size);
}

void DataInputStream::readFully( void* data, int size )
{
	int bytesread = getEmbeddedStream().read( data, size );
	if ( bytesread != size )
		throwError( IOException( Format("Unexpected end of file in {0}.",toString()) ) );
}

bool DataInputStream::readBoolean()
{
	uint8_t v;
	readFully( &v, sizeof(v) );
	return v != 0;
}

uint8_t DataInputStream::readByte()
{
	int8_t v;
	readFully( &v, sizeof(v) );
	return v;
}

char DataInputStream::readChar()
{
	uint8_t v;
	readFully( &v, sizeof(v) );
	return (char)v;
}

std::string DataInputStream::readChars( int n )
{
	std::string	str;

	if (n < 0)
		return "";

	str.resize(n);

	while (str.size() < n);
		str += readChar(); //Correct?

	return str;
}

double DataInputStream::readDouble()
{
	uint8_t bytes[ sizeof(double) ];
	readBE( bytes, sizeof(bytes) );

	double v = *reinterpret_cast<double*>(bytes);
	return v;
}

float DataInputStream::readFloat()
{
	uint8_t bytes[ sizeof(float) ];
	readBE( bytes, sizeof(bytes) );
	float v = *reinterpret_cast<float*>(bytes);
	return v;
}

int DataInputStream::readInt()
{
	uint8_t bytes[ sizeof(int32_t) ];
	readBE( bytes, sizeof(bytes) );
	int32_t v = *reinterpret_cast<int32_t*>(bytes);
	return (int)v;
}

int DataInputStream::readShort()
{
	uint8_t bytes[ sizeof(int16_t) ];
	readBE( bytes, sizeof(bytes) );
	int16_t v = *reinterpret_cast<int16_t*>(bytes);
	return (int)v;
}

std::string DataInputStream::readUTF()
{
	int encodedbytes = readShort();
	if ( encodedbytes < 0 )
		throwError( IOException( Format("Invalid UTF-8 data in {0}.",toString()) ) );

	std::string str;
	if ( encodedbytes > 0 )
	{
		str.resize( encodedbytes );
		//readFully( str.begin(), encodedbytes );
		//str += std::string( str.begin(), encodedbytes, UTFConverter(UTFConverter::ENCODING_UTF8) );

		//?
	}
	return str;
}

void DataInputStream::readUTF( char* buf, int bufsize )
{
	int encodedbytes = readShort(); //116
	if ( encodedbytes < 0 )
		throwError( IOException( Format("Invalid UTF-8 data in {0}.",toString()) ) );
	if ( encodedbytes >= bufsize )
		throwError( IOException( Format("Too small buffer ({0}) for UTF-8 data in {1}.",bufsize,toString()) ) );
	
	readFully( buf, encodedbytes );
	buf[encodedbytes] = 0;
}

void DataInputStream::readUTF( std::vector<char>& buf )
{
	int encodedbytes = readShort();
	if ( encodedbytes < 0 )
		throwError( IOException( Format("Invalid UTF-8 data in {0}.",toString()) ) );

	buf.resize( encodedbytes+1 );
	readFully( &buf, encodedbytes);
	buf[encodedbytes] = 0;
}

void DataInputStream::readBE( void* data, int size )
{
	readFully( data, size );

	int x = 1;
	if ( 0 != *reinterpret_cast<char*>(&x) )
	{
		uint8_t* begin = reinterpret_cast<uint8_t*>(data);
		uint8_t* end = begin + size;
		for ( ; begin != end && begin != --end ; ++begin )
		{
			uint8_t tmp = *begin;
			*begin = *end;
			*end = tmp;
		}
	}
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
