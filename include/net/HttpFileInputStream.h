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
class HttpFileInputStream :
	public io::InputStream
{
public:
	/**
	 *
	 */
	HttpFileInputStream(const std::string& name);


	HttpFileInputStream(const std::string& name, HttpRequest&);

	/**
	 * Tries to read specified number of bytes from the stream.
	 * Doesn't block the caller if specified number of bytes isn't available.
	 * @return Number of bytes actually read.
	 * @exception IOException
	 */
	virtual int				read(void* data, int size);

	/**
	 * Tries to skip over n bytes from the stream.
	 * @return Number of bytes actually skipped.
	 * @exception IOException
	 */
	virtual int				skip(int n);

	/**
	 *
	 * @return
	 * @exception IOException
	 */
	virtual bool				seek(int offset, SeekMode origin);

	const void* data() const;

	/**
	 * Returns the number of bytes that can be read from the stream without blocking.
	 */
	virtual int available() const;

	virtual std::string toString() const;
private:
	io::ByteArrayInputStream m_message;
	std::string m_url;

	HttpFileInputStream();
	HttpFileInputStream(const HttpFileInputStream&);
	HttpFileInputStream& operator=(const HttpFileInputStream&);
};


} // net


#endif // _NET_HTTPFILEINPUTSTREAM_H
