#ifndef _IO_INFOZIP_H
#define _IO_INFOZIP_H

#include <io/ZipFileInputStream.h>

namespace io
{

typedef void* unzFile; //7

struct ZInputStream //10
{
public:
	long pos; //12
	long size; //13
	InputStream* s; //14
};

class ZipFileInfoZip : public ZipFile //20 | Weird name
{
public:
	ZipFileInfoZip(); //26
	~ZipFileInfoZip(); //27

	int open(InputStream& fileInput); //29
	int readHeader(std::vector<std::string>& fileNames); //30
	int extract(int index, std::vector<char>& resultBuffer); //31

protected:
	unzFile uf; //35
	ZInputStream zpos; //36
};

}

#endif