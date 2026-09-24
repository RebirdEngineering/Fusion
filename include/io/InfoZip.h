#ifndef _IO_INFOZIP_H
#define _IO_INFOZIP_H

#include <io/ZipFileInputStream.h>

namespace io
{

typedef void* unzFile; //

struct ZInputStream
{
public:
	long int pos;
	long int size;
	InputStream* s;
};

class ZipFileInfoZip : public ZipFile //Weird name
{
public:
	ZipFileInfoZip();
	~ZipFileInfoZip();

	virtual int open(InputStream& fileInput);
	virtual int readHeader(std::vector<std::string>& fileNames);
	virtual int extract(int index, std::vector<char>& resultBuffer);
protected:
	unzFile uf;
	ZInputStream zpos;
};

}

#endif