#ifndef _IO_SEVENZIP_H
#define _IO_SEVENZIP_H

#include <io/ZipFileInputStream.h>

namespace io
{

class ZipFile7Zip : //10 | Weird name
	public ZipFile
{
public:
	ZipFile7Zip(); //14
	~ZipFile7Zip(); //15

	int open(InputStream& fileInput); //17
	int readHeader(std::vector<std::string>& fileNames); //18
	int extract(int index, std::vector<char>& resultBuffer); //19

private:
	class Impl;
	P(Impl) m_impl; //23

	ZipFile7Zip(const ZipFile7Zip&); //25
	ZipFile7Zip& operator=(const ZipFile7Zip&); //26
};

}

#endif