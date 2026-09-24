#ifndef _IO_INPUTSTREAM_H
#define _IO_INPUTSTREAM_H


#include <lang/Object.h>


namespace io
{ 

/**
 * Base class of all input stream classes.
 *
 * 
 * @ingroup io
 */
class InputStream :
	public NS(lang,Object)
{
public:
	enum SeekMode
	{
		SEEKMODE_SET,
		SEEKMODE_CUR,
		SEEKMODE_END
	};
    
	explicit InputStream(P(InputStream) sourcePtr);
    
    explicit InputStream(InputStream& sourceRef);
    
    ~InputStream();
    
	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	virtual int				read( void* buffer, int size ); //Changed bytes to buffer

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	virtual int				skip( int bytes );
	
	/**
	 * 
	 * @return 
	 * @exception IOException
	 */
	virtual bool			seek( int offset, SeekMode origin );

	/** 
	 * Returns the number of bytes that can be read from the stream without blocking.
	 * @exception IOException
	 */
	virtual int				available() const;

	/**
	 * Returns string description of the stream.
	 */
	virtual std::string	toString() const;
	
protected:
	InputStream& getEmbeddedStream() const;
private:
	P(InputStream) m_ptr; //99
	InputStream& m_ref; //100

	InputStream& operator=(const InputStream&);
};

std::vector<unsigned char> toVector(InputStream& in); //This is used by other apps, it namely comes from CPP
std::string toString(InputStream& in); //This is used by other apps, it namely comes from CPP

} // io


#endif // _IO_INPUTSTREAM_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
