#ifndef _IO_BUNDLEINPUTSTREAM_H
#define _IO_BUNDLEINPUTSTREAM_H

#include <io/InputStream.h>

namespace io
{ 

/**
 * 
 * 
 * @ingroup io
 */
class BundleInputStream : //14
	public InputStream
{
public:
	enum ReadModeHint
	{
		READ_BULK,
		READ_STREAM //Seems this is never used. Maybe it's used when they introduced .stream and .zstream
	};

	/** 
	 * Opens a file input stream. 
	 */
	explicit BundleInputStream( const std::string& filename, ReadModeHint hint = READ_BULK ); //34 | Not initialized but I did

	///
	~BundleInputStream(); //39

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 *
	 * @return Number of bytes actually read.
	 */
	int				read( void* data, int size ); //47

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int				skip(int n); //54
	
	/** 
	 * 
	 */
	bool			seek(int offset, SeekMode origin); //61

	/** 
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int				available() const; //66

	/**
	 * 
	 */
	std::string	toString() const; //71
	
	/**
	 * 
	 */
	std::string	path(); //77

private:
	class Impl;
	P(Impl) m_impl; //81

	BundleInputStream(); //83
	BundleInputStream( const BundleInputStream& ); //84
	BundleInputStream& operator=( const BundleInputStream& ); //85
};


} // io


#endif // _IO_BUNDLEINPUTSTREAM_H


