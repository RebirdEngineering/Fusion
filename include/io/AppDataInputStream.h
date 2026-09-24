#ifndef _IO_APPDATAINPUTSTREAM_H
#define _IO_APPDATAINPUTSTREAM_H


#include <io/InputStream.h>

namespace io
{


class AppDataInputStream : //11
	public InputStream
{
public:
	/** 
	 * 
	 */
	explicit AppDataInputStream( const std::string& filename );

	///
	~AppDataInputStream();

	/**
	 * Tries to read specified number of bytes from the source stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 *
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int		read(void* data, int size);

	/**
	 * 
	 *
	 * @return 
	 * @exception IOException
	 */
	bool	seek(int offset, SeekMode origin);

	/**
	 * Tries to skip over n bytes from the source stream.
	 *
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int		skip(int n);

	/**
	 * Returns the number of bytes that can be read from the source stream without blocking.
	 *
	 * @exception IOException
	 */
	int		available() const;

	/**
	 * Returns string description of the stream.
	 */
	std::string	toString() const;

	/**
	 * Returns string description of the stream.
	 */
	std::string	path();

private:
	class Impl;
	P(Impl) m_impl;

	AppDataInputStream();
	AppDataInputStream( const AppDataInputStream& );
	AppDataInputStream& operator=( const AppDataInputStream& );
};


} // io


#endif // _IO_APPDATAINPUTSTREAM_H
