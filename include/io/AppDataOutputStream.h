#ifndef _IO_APPDATAOUTPUTSTREAM_H
#define _IO_APPDATAOUTPUTSTREAM_H


#include <io/OutputStream.h>
#include <lang/String.h>


namespace io
{ 


/**
 * ByteArrayOutputStream writes bytes to a memory buffer.
 * 
 * @ingroup io
 */
class AppDataOutputStream :
	public OutputStream
{
public:
	/**
	 * 
	 * @exception IOException
	 */
	explicit AppDataOutputStream(const std::string& filename);

	///
	~AppDataOutputStream();

	/**
	 * Writes specified number of bytes to the stream.
	 */
	virtual void			write( const void* data, int size );

	/** Returns name of the stream. */
	virtual std::string	toString() const;

	/*
	* 
	*/
	std::string	path();

	/**  */
	bool good() const;

private:
	class Impl;
	P(Impl)						m_impl;

	AppDataOutputStream();
	AppDataOutputStream( const AppDataOutputStream& );
	AppDataOutputStream& operator=( const AppDataOutputStream& );
};


} // io


#endif // _IO_BYTEARRAYOUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
