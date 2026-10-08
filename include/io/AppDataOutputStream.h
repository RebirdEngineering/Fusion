#ifndef _IO_APPDATAOUTPUTSTREAM_H
#define _IO_APPDATAOUTPUTSTREAM_H

#include <io/OutputStream.h>

namespace io
{ 

/**
 * 
 * 
 * @ingroup io
 */
class AppDataOutputStream : //12
	public OutputStream
{
public:
	/**
	 * 
	 * @exception IOException
	 */
	explicit AppDataOutputStream(const std::string& filename); //20

	///
	~AppDataOutputStream(); //25

	/**
	 * Writes specified number of bytes to the stream.
	 * @exception IOException
	 */
	void			write( const void* data, int size ); //31

	/** Returns name of the stream. */
	std::string	toString() const; //36

	/*
	* 
	*/
	std::string	path(); //42

	/**  */
	bool good() const; //47

private:
	class Impl;
	P(Impl)						m_impl; //51

	AppDataOutputStream(); //53
	AppDataOutputStream( const AppDataOutputStream& ); //54
	AppDataOutputStream& operator=( const AppDataOutputStream& ); //55
};


} // io


#endif // _IO_APPDATAOUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
