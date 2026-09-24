#ifndef _IO_FILEOUTPUTSTREAM_H
#define _IO_FILEOUTPUTSTREAM_H


#include <io/OutputStream.h>

namespace io
{


/**
 * FileOutputStream writes bytes to a file in a file system.
 *
 * @ingroup io
 */
	class FileOutputStream :
	public OutputStream
{
public:
	/**
	 * Opens a file output stream.
	 * @exception IOException
	 */
	explicit FileOutputStream(const std::string& filename);

	///
	~FileOutputStream();

	/**
	 * Writes specified number of bytes to the stream.
	 * @exception IOException
	 */
	void			write(const void* data, int size);

	/** Returns name of the file. */
	std::string	toString() const;

	/**  */
	std::string	path();

private:
	class Impl;
	P(Impl) m_impl;

	FileOutputStream();
	FileOutputStream(const FileOutputStream&);
	FileOutputStream& operator=(const FileOutputStream&);
};

} // io


#endif // _IO_FILEOUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
