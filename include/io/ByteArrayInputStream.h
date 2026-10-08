#ifndef _IO_BYTEARRAYINPUTSTREAM_H
#define _IO_BYTEARRAYINPUTSTREAM_H

#include <io/InputStream.h>

namespace io
{ 

/**
 * ByteArrayInputStream reads bytes from a memory buffer.
 * 
 * @ingroup io
 */
class ByteArrayInputStream : //13
	public InputStream
{
public:
	ByteArrayInputStream(); //20

	/**
	 * Creates an input stream from specified memory buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after ByteArrayInputStream constructor returns.
	 */
	ByteArrayInputStream( const void* data, int size ); //29

	ByteArrayInputStream(InputStream& in); //51

	///
	~ByteArrayInputStream(); //56

	/**
	 * Resets with new input buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after ByteArrayInputStream constructor returns.
	 */
	void	reset( const void* data, int size ); //65

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 */
	int		read( void* data, int size ); //72
	
	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int skip( int n ); //79
	
	bool	seek( int offset, SeekMode origin ); //86
	
	/** 
	 * 
	 */
	void*			data(); //91

	/** 
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int		available() const; //96

	/** Returns byte array identifier. */
	std::string	toString() const; //99

private:
	std::vector<unsigned char>	m_data; //102
	std::string			m_name; //103
	int						m_index; //104

	ByteArrayInputStream( const ByteArrayInputStream& ); //106
	ByteArrayInputStream& operator=( const ByteArrayInputStream& ); //107
};


} // io


#endif // _IO_BYTEARRAYINPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
