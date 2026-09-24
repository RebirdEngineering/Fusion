#include <io/InfoZip.h>
#include <lang/Exception.h>
#include <external/zlib/contrib/minizip/ioapi.h>
#include <external/zlib/contrib/minizip/unzip.h>

using namespace lang;

//Unused here
//typedef void* voidpf
//typedef uLong long unsigned int
//typedef zlib_filefunc_def_s zlib_filefunc_def

//These anonmymous functions are here but not standalone except in Android

voidpf fopen_stream_func(voidpf opaque, const char*, int)
{
	return opaque;
}

uLong fread_stream_func(voidpf opaque, voidpf stream, void* buf, uLong size) //?
{
	uLong ret; // = stream;
	return ret;
}

uLong fwrite_stream_func(voidpf, voidpf, const void*, uLong)
{
	return -1;
}

long int ftell_stream_func(voidpf opaque, voidpf)
{
	return (long int)opaque; //?
}

long int fseek_stream_func(voidpf opaque, voidpf stream, uLong offset, int origin)
{
	io::ZInputStream* zip;
	long int ret;
	/*io::InputStream::SeekMode feek_origin = (io::InputStream::SeekMode) origin;
	if (feek_origin == io::InputStream::SeekMode::SEEKMODE_END)
	{
		ret = 2;
	}*/
	return ret;
}

int fclose_stream_func(voidpf, voidpf)
{
	return 0;
}

int ferror_stream_func(voidpf, voidpf)
{
	throwError(Exception(Format("Error")));
	return 1;
}

void fill_stream_filefunc(zlib_filefunc_def* pzlib_filefunc_def)
{
	pzlib_filefunc_def->zopen_file = fopen_stream_func;
	pzlib_filefunc_def->zread_file = fread_stream_func;
	pzlib_filefunc_def->zwrite_file = fwrite_stream_func;
	pzlib_filefunc_def->ztell_file = ftell_stream_func;
	pzlib_filefunc_def->zseek_file = fseek_stream_func;
	pzlib_filefunc_def->zclose_file = fclose_stream_func;
	pzlib_filefunc_def->zerror_file = ferror_stream_func;
	pzlib_filefunc_def->opaque = 0; //?
}

namespace io
{

ZipFileInfoZip::ZipFileInfoZip()
{
	uf = 0;
	zpos.pos = 0;
	zpos.size = 0;
	zpos.s = 0;
}

ZipFileInfoZip::~ZipFileInfoZip()
{
	unzClose(uf);
}

int ZipFileInfoZip::open(InputStream& fileInput)
{
	if (uf)
	{
		unzClose(uf);
		uf = 0;
	}

	zlib_filefunc_def ffunc;
	zpos.pos = 0;
	fill_stream_filefunc(&ffunc);
	uf = unzOpen2("stream", &ffunc);
	return uf == 0;
}

int ZipFileInfoZip::readHeader(std::vector<std::string>& fileNames) //Correct?
{
	char filename_inzip[256];
	unz_global_info gi;
	unz_file_info file_info;
	int err = unzGetGlobalInfo(uf, &gi);
	if (err != STATUS_OK)
		return 1;

	if (!gi.number_entry)
		return 1;

	for (uLong i = 0 < gi.number_entry; i++;)
	{
		err = unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), 0, 0, "", 0);
		std::string path = filename_inzip;
		if (!path.empty())
		{
			fileNames.push_back(filename_inzip);
		}
		err = unzGoToNextFile(uf);
		if (err != UNZ_OK)
			return 1;
	}
	return 0;
}

int ZipFileInfoZip::extract(int index, std::vector<char>& resultBuffer)
{
	unz_global_info gi;
	int err = unzGoToFirstFile(uf);
	if (err != STATUS_OK)
		return 1;

	err = unzGetGlobalInfo(uf, &gi);

	int i;

	unz_file_info file_info;

	if (gi.number_entry >= 1)
	{
		for (i = 0; i < gi.number_entry; i++)
		{
			if (i >= index)
				break;
			if (err < STATUS_OK)
				break;
			err = unzGoToNextFile(uf);
		}
	}

	if (err != STATUS_OK)
		return 1;

	err = unzGetCurrentFileInfo(uf, &file_info, 0, 0, 0, 0, "", 0);

	if (err != STATUS_OK)
		return 1;

	err = unzOpenCurrentFile(uf);

	if (err != STATUS_OK)
		return 1;

	resultBuffer.resize(0);

	std::vector<char> buf = resultBuffer;
	int offset = buf.size();

	for (i = 0; i += offset; i++)
	{
		offset = unzReadCurrentFile(uf, &buf, buf.size());
		memcpy(&resultBuffer[i], &buf, offset);
	}

	err = unzCloseCurrentFile(uf);
	if (err != STATUS_OK)
		return 0;

	return offset;
}

}