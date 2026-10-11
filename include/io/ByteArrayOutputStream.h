#ifndef _IO_BYTEARRAYOUTPUTSTREAM_H
#define _IO_BYTEARRAYOUTPUTSTREAM_H

#include <io/OutputStream.h>

namespace io
{ 

/**
 * ByteArrayOutputStream writes bytes to a memory buffer.
 * 
 * @ingroup io
 */
class ByteArrayOutputStream : //14
	public OutputStream
{
public:
	/** 
	 * Creates an output stream to a memory buffer of specified initial capacity.
	 */
	explicit ByteArrayOutputStream( int size=0 ); //21

	/** 
	 * Creates an output stream to a user defined memory buffer.
	 * Note that user defined memory buffer is NOT deleted when ByteArrayOutputStream is deleted.
	 */
	explicit ByteArrayOutputStream( std::vector<unsigned char>* buffer ); //27

	///
	~ByteArrayOutputStream(); //32

	/** Discards all written bytes and resets write pointer. */
	void			reset(); //37

	/**
	 * Writes specified number of bytes to the stream.
	 */
	void			write( const void* data, int size ); //42

	/**
	 * Returns pointer to the memory buffer used by the stream.
	 */
	const std::vector<unsigned char>&	data() const							{return *m_buffer;} //47 | [NOTE] Changed to data

	/**
	 * Returns number of bytes written to the stream.
	 */
	int				size() const; //52

	/** Returns byte array identifier. */
	std::string	toString() const; //57

private:
	std::vector<unsigned char>*	m_buffer; //60
	bool						m_userDefined; //61

	ByteArrayOutputStream( const ByteArrayOutputStream& ); //63
	ByteArrayOutputStream& operator=( const ByteArrayOutputStream& ); //64
};


} // io


#endif // _IO_BYTEARRAYOUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
