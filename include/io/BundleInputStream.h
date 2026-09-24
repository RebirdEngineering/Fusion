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
class BundleInputStream :
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
	explicit BundleInputStream( const std::string& filename, ReadModeHint hint = READ_BULK ); //Not initialized but I did

	///
	~BundleInputStream();

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
	 * 
	 */
	std::string	toString() const;
	
	/**
	 * 
	 */
	std::string	path();

private:
	class Impl;
	P(Impl) m_impl;

	BundleInputStream();
	BundleInputStream( const BundleInputStream& );
	BundleInputStream& operator=( const BundleInputStream& );
};


} // io


#endif // _IO_BUNDLEINPUTSTREAM_H


