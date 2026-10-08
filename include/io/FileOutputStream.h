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
class FileOutputStream : //12
	public OutputStream
{
public:
	/**
	 * Opens a file output stream.
	 * @exception IOException
	 */
	explicit FileOutputStream(const std::string& filename); //20

	///
	~FileOutputStream(); //25

	/**
	 * Writes specified number of bytes to the stream.
	 * @exception IOException
	 */
	void			write(const void* data, int size); //31

	/** Returns name of the file. */
	std::string	toString() const; //36

	/**  */
	std::string	path(); //41

private:
	class Impl;
	P(Impl) m_impl; //45

	FileOutputStream(); //47
	FileOutputStream(const FileOutputStream&); //48
	FileOutputStream& operator=(const FileOutputStream&); //49
};

} // io


#endif // _IO_FILEOUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
