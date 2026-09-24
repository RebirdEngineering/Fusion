#ifndef _IO_SEVENZIP_H
#define _IO_SEVENZIP_H

#include <io/ZipFileInputStream.h>

namespace io
{

class ZipFile7Zip : public ZipFile //Weird name
{
public:
	ZipFile7Zip();
	~ZipFile7Zip();

	int open(InputStream& fileInput);
	int readHeader(std::vector<std::string>& fileNames);
	int extract(int index, std::vector<char>& resultBuffer);
private:
	class Impl;
	P(Impl) m_impl;

	ZipFile7Zip(const ZipFile7Zip&);
	ZipFile7Zip& operator=(const ZipFile7Zip&);
};

}

#endif