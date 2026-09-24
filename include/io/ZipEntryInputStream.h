#ifndef _IO_ZIPENTRYINPUTSTREAM_H
#define _IO_ZIPENTRYINPUTSTREAM_H


#include <io/ByteArrayInputStream.h>

namespace io
{


/**
 *
 *
 * @ingroup io
 */
	class ZipEntryInputStream :
	public ByteArrayInputStream
{
public:
	/**
	 *
	 */
	ZipEntryInputStream(const std::string& filename, const std::vector<char> buffer);

	///
	~ZipEntryInputStream();

	const std::string& getFilename() const;

	std::string toString() const;

private:
	std::string m_filename;
	std::vector <char> m_buffer;

	ZipEntryInputStream(const ZipEntryInputStream&);
	ZipEntryInputStream& operator=(const ZipEntryInputStream&);
};


} // io


#endif // _IO_ZipEntryInputStream_H
