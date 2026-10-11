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
class OutputStream : //17
	public lang::Object
{
public:
	explicit OutputStream(P(OutputStream) sourcePtr); //27
	
	explicit OutputStream(OutputStream& sourceRef); //33 | Recover from InputStream
	
	~OutputStream(); //38
	
	/**
	 * Writes specified number of bytes to the stream.
	 * @exception IOException
	 */
	virtual void 			write( const void* data, int size ); //46

	/** Returns name of the stream. */
	virtual std::string	toString() const; //55
	
protected:
	OutputStream&			getEmbeddedStream() const; //63

private:
	P(OutputStream) m_ptr; //66
	OutputStream& m_ref; //67
	
	OutputStream& operator=(const OutputStream&); //70
};


} // io


#endif // _IO_OUTPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
