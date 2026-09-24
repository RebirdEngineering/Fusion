#ifndef _IO_FILEINPUTSTREAM_H
#define _IO_FILEINPUTSTREAM_H


#include <io/InputStream.h>

namespace io
{ 


/**
 * FileInputStream reads bytes from a standard file.
 * 
 * @ingroup io
 */
class FileInputStream :
	public InputStream
{
public:
	/** 
	 * Opens a file input stream. 
	 */
	explicit FileInputStream( const std::string& filename );

	///
	~FileInputStream();

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 *
	 * @return Number of bytes actually read.
	 */
	int				read( void* data, int size );

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int				skip(int n);
	
	/** 
	 * 
	 */
	bool			seek(int offset, SeekMode origin);

	/** 
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int				available() const;

	/**
	 * Returns name and seek position of the file.
	 */
	std::string	toString() const;
	
	/**
	 * 
	 */
	std::string			path();

private:
	class Impl;
	P(Impl) m_impl;

	FileInputStream();
	FileInputStream( const FileInputStream& );
	FileInputStream& operator=( const FileInputStream& );
};


} // io


#endif // _IO_FILEINPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
