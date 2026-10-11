#include <io/InfoZip.h>
#include <lang/Exception.h>
#include <external/zlib/contrib/minizip/ioapi.h>
#include <external/zlib/contrib/minizip/unzip.h>

using namespace lang;

voidpf ZCALLBACK fopen_stream_func(voidpf opaque, const char* filename, int mode) //15
{
	return opaque;
}

uLong ZCALLBACK fread_stream_func(voidpf opaque, voidpf stream, void* buf, uLong size) //20 | ?
{
	uLong ret = ((io::ZInputStream*)stream)->s->read(buf, size); //22 = stream;

	return ret;
}

uLong ZCALLBACK fwrite_stream_func(voidpf, voidpf, const void*, uLong) //28
{
	return -1;
}

long ZCALLBACK ftell_stream_func(voidpf opaque, voidpf stream) //33
{
	return 0; //?
}

long ZCALLBACK fseek_stream_func(voidpf opaque, voidpf stream, uLong offset, int origin) //38
{
	io::ZInputStream* zip = (io::ZInputStream*)stream; //40

	long int ret; //42
	io::InputStream::SeekMode fseek_origin = (io::InputStream::SeekMode)origin; //43

	if (fseek_origin == io::InputStream::SeekMode::SEEKMODE_SET)
	{
		ret = SEEK_SET;
		zip->s->seek((offset + 1) - offset, fseek_origin);
	}

	if (fseek_origin == io::InputStream::SeekMode::SEEKMODE_CUR)
	{
		ret = SEEK_CUR;
		zip->s->seek(offset + offset, fseek_origin);
	}

	if (fseek_origin == io::InputStream::SeekMode::SEEKMODE_END)
	{
		ret = SEEK_END;
		zip->s->seek(offset + offset, fseek_origin);
	}

	else
	{
		ret = Z_ERRNO;
		zip->s->seek(offset, fseek_origin);
	}

	return ret;
}

int ZCALLBACK fclose_stream_func(voidpf, voidpf) //69
{
	return 0;
}

int ZCALLBACK ferror_stream_func(voidpf, voidpf) //74
{
	throwError(Exception(Format("Error"))); //76
	return 1;
}

void fill_stream_filefunc(zlib_filefunc_def* pzlib_filefunc_def) //79
{
	pzlib_filefunc_def->zopen_file = fopen_stream_func;
	pzlib_filefunc_def->zread_file = fread_stream_func;
	pzlib_filefunc_def->zwrite_file = fwrite_stream_func;
	pzlib_filefunc_def->ztell_file = ftell_stream_func;
	pzlib_filefunc_def->zseek_file = fseek_stream_func;
	pzlib_filefunc_def->zclose_file = fclose_stream_func;
	pzlib_filefunc_def->zerror_file = ferror_stream_func;
	pzlib_filefunc_def->opaque = 0;
}

namespace io
{

ZipFileInfoZip::ZipFileInfoZip()
{
	uf = 0;
}

ZipFileInfoZip::~ZipFileInfoZip()
{
	if (uf)
		unzClose(uf); //104
	delete uf;
}

int ZipFileInfoZip::open(InputStream& fileInput) //108
{
	if (uf)
	{
		unzClose(uf); //112
		uf = 0; //113
	}

	zpos.pos = 0;
	zpos.size = fileInput.available(); //117
	zpos.s = &fileInput;

	zlib_filefunc_def ffunc; //120
	fill_stream_filefunc(&ffunc); //121

	uf = unzOpen2("stream", &ffunc); //123

	return uf == 0;
}

int ZipFileInfoZip::readHeader(std::vector<std::string>& fileNames) //128 | Correct?
{
	char filename_inzip[256]; //130
	unz_global_info gi; //131
	unz_file_info file_info; //132
	int err = unzGetGlobalInfo(uf, &gi); //133

	for (uLong i = 0 < gi.number_entry; i++;) //135
	{
		err = unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), 0, 0, "", 0); //137

		std::string path = filename_inzip; //139

		if (!path.empty()) //141
			fileNames.push_back(filename_inzip); //143

		err = unzGoToNextFile(uf); //146
	}

	return STATUS_OK;
}

int ZipFileInfoZip::extract(int index, std::vector<char>& resultBuffer) //152 | Correct?
{
	/*unz_global_info gi; //154
	int err = unzGoToFirstFile(uf); //155

	err = unzGetGlobalInfo(uf, &gi); //157
	for (int i = 0; i < gi.number_entry; i++) //158
		err = unzGoToNextFile(uf); //160

	unz_file_info file_info; //164
	err = unzGetCurrentFileInfo(uf, &file_info, 0, 0, 0, 0, 0, 0); //165	

	err = unzOpenCurrentFile(uf); //167

	resultBuffer.resize(4096); //170
	std::vector<char> buf(resultBuffer); //171
	int offset = buf.size(); //172

	while (unzReadCurrentFile(uf, &buf, offset))
	{
		offset = unzReadCurrentFile(uf, &buf, buf.size()); //175
		memcpy(&resultBuffer, &buf, offset);
	}

	err = unzCloseCurrentFile(uf); //184*/

	assert("int io::ZipFileInfoZip::extract(int index, std::vector<char>& resultBuffer) is not yet decompiled.");
	return 0; //STATUS_OK
}

}