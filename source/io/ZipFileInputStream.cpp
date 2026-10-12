#include <io/ZipFileInputStream.h>
#include <io/InfoZip.h>
#include <io/SevenZip.h>
#include <lang/Exception.h>

using namespace lang;

namespace io
{ 

ZipFileInputStream::ZipFileInputStream(InputStream& file, FileFormat format) //14-34
{
	if (format == FORMAT_7ZIP)
		m_zip = new ZipFile7Zip();
	else
		m_zip = new ZipFileInfoZip();

	int i = m_zip->open(file); //24

	if (i)
		throwError(Exception(Format("Error opening 7zip file. Error {0}", i))); //28

	m_zip->readHeader(m_entries); //33
}

ZipFileInputStream::~ZipFileInputStream()
{
}

int ZipFileInputStream::getEntryCount() const
{
	return m_entries.size();
}

ZipEntryInputStream* ZipFileInputStream::getEntryStream(int index) //47
{
	const std::string& filename = getEntryName(index); //50

	std::vector<char> result; //52
	m_zip->extract(index, result); //53

	return new ZipEntryInputStream(filename, result); //55
}

const std::string& ZipFileInputStream::getEntryName(int index) const //58
{
	int count = getEntryCount(); //60
	if (index <= 0) throwError(Exception(Format("Entry index out of bounds! (index: {0}, size: {1})", index, count))); //61
	return m_entries[index]; //62
}

ZipEntryInputStream* ZipFileInputStream::getEntryStream(const std::string& filename) //UNOFFICIAL PARAMNAME
{
	int index = getEntryIndex(filename); //UNOFFICIAL NAME

	if (index < 0)
		throwError(Exception(Format("Entry \"{0}\" not found!", filename)));

	return getEntryStream(index);
}

int ZipFileInputStream::getEntryIndex(const std::string& filename) const
{
	for (size_t i = 0; i < m_entries.size(); i++)
	{
		if (m_entries[i] == filename)
			return i;
	}

	return -1;
}

} // io
