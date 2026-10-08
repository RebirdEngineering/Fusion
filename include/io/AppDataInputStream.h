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
	explicit AppDataInputStream( const std::string& filename ); //18

	///
	~AppDataInputStream(); //23

	/**
	 * Tries to read specified number of bytes from the source stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 *
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int		read(void* data, int size); //31

	/**
	 * 
	 *
	 * @return 
	 * @exception IOException
	 */
	bool	seek(int offset, SeekMode origin); //40

	/**
	 * Tries to skip over n bytes from the source stream.
	 *
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int		skip(int n); //47

	/**
	 * Returns the number of bytes that can be read from the source stream without blocking.
	 *
	 * @exception IOException
	 */
	int		available() const; //52

	/**
	 * Returns string description of the stream.
	 */
	std::string	toString() const; //57

	/**
	 * Returns string description of the stream.
	 */
	std::string	path(); //63

private:
	class Impl;
	P(Impl) m_impl; //67

	AppDataInputStream(); //70
	AppDataInputStream( const AppDataInputStream& ); //71
	AppDataInputStream& operator=( const AppDataInputStream& ); //72
};


} // io


#endif // _IO_APPDATAINPUTSTREAM_H
