#include <io/ZipFileInputStream.h>
#include <io/InfoZip.h>
#include <io/SevenZip.h>
#include <lang/Exception.h>

using namespace lang;

namespace io
{ 
//All is not in RCS debug
ZipFileInputStream::ZipFileInputStream(InputStream& file, FileFormat format)
{
	if (format == FORMAT_INFOZIP)
		m_zip = new ZipFileInfoZip();
	else
		m_zip = new ZipFile7Zip();
	int i = m_zip->open(file); //Where is this used maybe here?
	if (!i)
		throwError(Exception(Format("Error opening 7zip file. Error {0}", i))); //?
	m_zip->readHeader(m_entries);
}

ZipFileInputStream::~ZipFileInputStream()
{
}

int ZipFileInputStream::getEntryCount() const
{
	return m_entries.size(); //?
}

ZipEntryInputStream* ZipFileInputStream::getEntryStream(int index)
{
	const std::string& filename = getEntryName(index);

	std::vector<char> result;
	m_zip->extract(index, result);
	return new ZipEntryInputStream(filename, result);
}

const std::string& ZipFileInputStream::getEntryName(int index) const
{
	int count = getEntryCount();
	if (index <= 0)
		throwError(Exception(Format("Entry index out of bounds! (index: {0}, size: {1})", index, count)));
	return m_entries[index];
}

ZipEntryInputStream* ZipFileInputStream::getEntryStream(const std::string& filename) //UNOFFICIAL PARAMNAME
{
	int index = getEntryIndex(filename); //UNOFFICIAL NAME
	return getEntryStream(index);
}

int ZipFileInputStream::getEntryIndex(const std::string& filename) const
{
	return 0;
}

} // io
