#ifndef _NET_HTTPFILEINPUTSTREAM_H
#define _NET_HTTPFILEINPUTSTREAM_H

#include <net/HttpRequest.h>
#include <io/ByteArrayInputStream.h>

namespace net
{

/**
 *
 *
 * @ingroup net
 */
class HttpFileInputStream : //19
	public io::InputStream
{
public:
	/**
	 *
	 */
	HttpFileInputStream(const std::string& name); //27


	HttpFileInputStream(const std::string& name, HttpRequest&); //33

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	int				read(void* data, int size); //41

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	int				skip(int n); //50

	/**
	 *
	 * @return
	 * @exception IOException
	 */
	bool				seek(int offset, SeekMode origin); //55

	/**
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	int available() const; //61

	/**
	 * Returns string description of the stream.
	 */
	std::string toString() const; //66

private:
	io::ByteArrayInputStream m_message; //69
	std::string m_url; //70

	HttpFileInputStream();
	HttpFileInputStream(const HttpFileInputStream&);
	HttpFileInputStream& operator=(const HttpFileInputStream&);
};


} // net


#endif // _NET_HTTPFILEINPUTSTREAM_H
