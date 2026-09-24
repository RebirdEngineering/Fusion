#ifndef _IO_OUTPUTSTREAM_H
#define _IO_OUTPUTSTREAM_H


#include <lang/Object.h>


namespace io
{ 


/**
 * Base class of all classes writing stream of bytes.
 * 
 * @ingroup io
 */
class OutputStream :
	public NS(lang,Object)
{
public:
	explicit OutputStream(P(OutputStream) sourcePtr);
	
	explicit OutputStream(OutputStream& sourceRef); //Recover from InputStream
	
	~OutputStream();
	
	/**
	 * Writes specified number of bytes to the stream.
	 * @exception IOException
	 */
	void 			write( const void* data, int size );

	/** Returns name of the stream. */
	virtual std::string	toString() const;
	
protected:
	/**  */
	OutputStream&			getEmbeddedStream() const;
private:
	P(OutputStream) m_ptr;
	OutputStream& m_ref;
	
	OutputStream& operator=(const OutputStream&);
};


} // io


#endif // _IO_OUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
