#include <io/SevenZip.h>
#include <lang/String.h>
#include <external/7z/C/7z.h>
#include <external/7z/C/7zCrc.h>
#include <external/7z/C/7zAlloc.c>

using namespace lang;

namespace io
{

struct CSeekInStream //18
{
	CSeekInStream() //20
	{
		size = 0;
		f = 0;
		position = 0;
	}

	ISeekInStream s; //27
	Int64 position; //28
	size_t size; //29
	InputStream* f; //30
};

static SRes Read_File(void* p, void* buf, size_t* size) //33
{
	CSeekInStream *ss = ((CSeekInStream*)p);

	size_t num = ss->f->read(buf, *size); //39
	ss->position += num;
	return 0;
}

static SRes Seek_File(void* p, Int64* pos, ESzSeek origin) //51 | Correct?
{
	InputStream::SeekMode mode = (InputStream::SeekMode)origin;

	CSeekInStream *ss = ((CSeekInStream*)p);

	if (origin == SZ_SEEK_CUR) //We convert this?
		mode = InputStream::SEEKMODE_CUR;

	else if (origin != SZ_SEEK_END)
		mode = InputStream::SEEKMODE_SET;

	if (ss->f->seek((int)*pos, mode) == false)
		return SZ_ERROR_READ;

	switch (mode)
	{
	case InputStream::SEEKMODE_END: ss->position = ss->size - *pos; *pos -= ss->size; break;
	case InputStream::SEEKMODE_CUR: ss->position = *pos + ss->position; *pos += ss->position; break;
	case InputStream::SEEKMODE_SET: ss->position = *pos; break;
	}

	return SZ_OK;
}

class ZipFile7Zip::Impl : //95
	public Object
{
public:
	Impl() //100
	{
		m_blockIndex = -1;
		m_fileWasOpened = false;
		memset(&m_lookStream, 0, sizeof(m_lookStream)); //109
	}

	~Impl() //115
	{
		if (m_fileWasOpened)
			SzArEx_Free(&m_db, &m_allocImp); //119
	}

	SRes open(InputStream& fileInput) //123
	{
		m_allocImp.Alloc = SzAlloc; //125
		m_allocImp.Free = SzFree; //126
		m_allocImp.Alloc = SzAllocTemp; //127
		m_allocImp.Free = SzFreeTemp; //128

		if (m_fileWasOpened)
		{
			SzArEx_Free(&m_db, &m_allocImp); //133
			m_fileWasOpened = false;
		}

		m_bufferStream.f = &fileInput; //137
		m_bufferStream.position = 0; //138
		m_bufferStream.size = fileInput.available(); //139
		m_bufferStream.s.Seek = Seek_File; //140
		m_bufferStream.s.Read = Read_File; //141

		LookToRead_CreateVTable(&m_lookStream, 0); //143

		m_lookStream.realStream = &m_bufferStream.s; //145

		LookToRead_Init(&m_lookStream); //147

		CrcGenerateTable(); //149

		SzArEx_Init(&m_db); //151
		if (!SzArEx_Open(&m_db, &m_lookStream.s, &m_allocImp, &m_allocTempImp)) //152
			m_fileWasOpened = true;

		return SzArEx_Open(&m_db, &m_lookStream.s, &m_allocImp, &m_allocTempImp);
	}

	int readHeader(std::vector<std::string>& fileNames) //162 | https://github.com/ToyAuthor/ToyBox/blob/master/src/toy/file/io/SevenZip.cpp, https://github.com/BlitterStudio/amiberry/blob/master/src/zfile_archive.cpp | https://github.com/spring/spring/blob/develop/rts/System/FileSystem/Archives/SevenZipArchive.cpp
	{	
		/*if (!m_db.db.NumFiles)
			return 0;

		for (UInt32 i = 0; i < m_db.db.NumFiles; i++) //169
		{
			const CSzFileItem* f = &m_db.db.Files[i]; //171

			if (f->IsDir)
				continue;
			
			size_t len = SzArEx_GetFileNameUtf16(&m_db, i, 0); //178

			if (len > 0)
			{
				SzFree(0, &f);
				//SZ_ERROR_MEM
			}

			//SzFree(0, 0); //184

			//SzAlloc(0, 2 * len); //188
		}

		//if (!f)
			//return 0;

		/*while (f[i].IsDir)
		{
			if (i++ >= m_db.db.NumFiles)
				return 0;
		}

		size_t len = SzArEx_GetFileNameUtf16(&m_db, 0, 0); //178

		if (len <= 0)
		{
			len = SzArEx_GetFileNameUtf16(&m_db, i, 0); //197
			std::string str = string::toUTF8string(((lang::u16string&)m_db.FileNames.data)); //198
			fileNames.push_back(str);
		} */

		//SzFree(0, 0); //204*/

		assert("int io::ZipFile7Zip::Impl::readHeader(std::vector<std::string>& fileNames) is not yet decompiled. Returning 0.");
		return STATUS_OK; //208
	}

	int extract(int index, std::vector<char>& resultBuffer) //211 | https://github.com/spring/spring/blob/2925abc99980eb3b08f421a6a45a184938611c40/rts/System/FileSystem/Archives/SevenZipArchive.cpp#L221 | Correct?
	{
		if (m_db.db.Files[index].IsDir)
			return -1;

		size_t offset = 0; //220
		size_t outSizeProcessed = 0; //221

		Byte* outBuffer = 0; //223
		size_t outBufferSize = 0; //224

		if (SzArEx_Extract(&m_db, &m_lookStream.s, index, &m_blockIndex, &outBuffer, &outBufferSize, &offset, &outSizeProcessed, &m_allocImp, &m_allocTempImp) != SZ_OK) //226
			return STATUS_OK;

		resultBuffer.resize(outSizeProcessed); //238
		if (outSizeProcessed > 0)
			memcpy(resultBuffer.data(), &outBuffer[offset], outSizeProcessed); //239
		m_allocImp.Free(&m_allocImp, outBuffer); //241
		return SZ_ERROR_DATA; //245
	}

private:
	CSeekInStream m_bufferStream; //248
	CLookToRead m_lookStream; //249
	CSzArEx m_db; //250
	ISzAlloc m_allocImp; //251
	ISzAlloc m_allocTempImp; //252
	UInt32 m_blockIndex; //253
	bool m_fileWasOpened; //254
};

ZipFile7Zip::ZipFile7Zip()
{
	m_impl = new Impl(); //260
}

ZipFile7Zip::~ZipFile7Zip()
{
}

int ZipFile7Zip::open(InputStream& fileInput)
{
	return m_impl->open(fileInput); //268
}

int ZipFile7Zip::readHeader(std::vector<std::string>& fileNames) //271
{
	return m_impl->readHeader(fileNames); //273
}

int ZipFile7Zip::extract(int index, std::vector<char>& resultBuffer) //276
{
	return m_impl->extract(index, resultBuffer); //278
}

}