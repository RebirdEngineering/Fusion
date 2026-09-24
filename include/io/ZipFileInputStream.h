#ifndef _IO_ZIPFILEINPUTSTREAM_H
#define _IO_ZIPFILEINPUTSTREAM_H

#include <io/ZipEntryInputStream.h>

namespace io
{

class ZipFile
{
public:
	const int STATUS_OK = 0;
	~ZipFile();
	virtual int open(InputStream& fileInput) = 0;
	virtual int readHeader(std::vector<std::string>& fileNames) = 0;
	virtual int extract(int index, std::vector<char>& resultBuffer) = 0;
};

/**
 *
 *
 * @ingroup io
 */
class ZipFileInputStream :
	public NS(lang,Object)
{
public:
	enum FileFormat
	{
		FORMAT_7ZIP,
		FORMAT_INFOZIP,
	};

	/**
	 *
	 */
	ZipFileInputStream(InputStream& file, FileFormat format);

	///
	~ZipFileInputStream();

	int getEntryCount() const;

	ZipEntryInputStream* getEntryStream(int index = 0);

	const std::string& getEntryName(int index) const;

	ZipEntryInputStream* getEntryStream(const std::string& filename); //UNOFFICIAL NAME

	int getEntryIndex(const std::string& path) const;
private:
	ZipFile* m_zip;
	std::vector<std::string> m_entries;

	ZipFileInputStream();
	ZipFileInputStream(const ZipFileInputStream&);
	ZipFileInputStream& operator=(const ZipFileInputStream&);
};


} // io


#endif // _IO_ZIPFILEINPUTSTREAM_H
