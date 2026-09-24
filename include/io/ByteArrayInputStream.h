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
class ByteArrayInputStream :
	public InputStream
{
public:
	ByteArrayInputStream();
	/** 
	 * Creates an input stream from specified memory buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after ByteArrayInputStream constructor returns.
	 */
	ByteArrayInputStream( const void* data, int size );

	/**
	 * 
	 * 
	 * 
	 */
	ByteArrayInputStream(InputStream& in);

	///
	~ByteArrayInputStream();

	/**
	 * Resets with new input buffer.
	 * Note that the contents of the buffer is duplicated so the buffer
	 * can be freed immediately after ByteArrayInputStream constructor returns.
	 */
	void	reset( const void* data, int size );

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 */
	int		read( void* data, int size );
	
	/**
	 * Tries to skip over n bytes from the stream.
	 *
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int skip( int n );
	
	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 */
	bool	seek( int offset, SeekMode origin );
	
	/** 
	 * 
	 */
	void*			data();

	/** 
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int		available() const;

	/** Returns byte array identifier. */
	std::string	toString() const;

private:
	std::vector<unsigned char>	m_data;
	std::string			m_name;
	int						m_index;

	ByteArrayInputStream( const ByteArrayInputStream& );
	ByteArrayInputStream& operator=( const ByteArrayInputStream& );
};


} // io


#endif // _IO_BYTEARRAYINPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
