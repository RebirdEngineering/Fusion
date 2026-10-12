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
class ZipEntryInputStream : //13
	public ByteArrayInputStream
{
public:
	/**
	 *
	 */
	ZipEntryInputStream(const std::string& filename, const std::vector<char> buffer); //20

	///
	~ZipEntryInputStream(); //23

	const std::string& getFilename() const; //28

	std::string toString() const; //33

private:
	std::string m_filename; //36
	std::vector <char> m_buffer; //37

	ZipEntryInputStream(const ZipEntryInputStream&); //39
	ZipEntryInputStream& operator=(const ZipEntryInputStream&); //40
};


} // io


#endif // _IO_ZipEntryInputStream_H
