#include <io/SevenZip.h>
#include <lang/String.h>
#include <external/7z/C/7z.h>
#include <external/7z/C/7zCrc.h>
#include <external/7z/C/7zAlloc.c>

using namespace lang;

namespace io
{

struct CSeekInStream
{
	CSeekInStream();
	ISeekInStream s;
	Int64 position;
	size_t size;
	InputStream* f;
};

static SRes Read_File(void* p, void* buf, size_t* size)
{
	CSeekInStream *ss = ((CSeekInStream*)p);

	size_t num = ss->f->read(buf, *size);
	ss->position += num;
	//assert("SRes Read_File(void* p, void* buf, size_t* size) is not yet decompiled.");
	return 0;
}

static SRes Seek_File(void* p, Int64* pos, ESzSeek origin) //Correct?
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

class ZipFile7Zip::Impl :
	public Object
{
public:
	~Impl()
	{
		if (m_fileWasOpened)
			SzArEx_Free(&m_db, &m_allocImp);
	}
	SRes open(InputStream& fileInput)
	{
		m_allocImp.Alloc = SzAlloc;
		m_allocImp.Free = SzFree;
		m_allocImp.Alloc = SzAllocTemp;
		m_allocImp.Free = SzFreeTemp;
		if (m_fileWasOpened)
		{
			SzArEx_Free(&m_db, &m_allocImp);
			m_fileWasOpened = false;
		}
		m_bufferStream.f = &fileInput;
		m_bufferStream.position = 0;
		m_bufferStream.size = fileInput.available();
		m_bufferStream.s.Seek = Seek_File;
		m_bufferStream.s.Read = Read_File;
		LookToRead_CreateVTable(&m_lookStream, 0);
		LookToRead_Init(&m_lookStream);
		CrcGenerateTable();
		SzArEx_Init(&m_db);
		return SzArEx_Open(&m_db, &m_lookStream.s, &m_allocImp, &m_allocTempImp);
	}
	int extract(int index, std::vector<char>& resultBuffer)
	{
		size_t offset = 0;
		size_t outSizeProcessed = 0;
		Byte* outBuffer = 0;
		size_t outBufferSize = 0;
		if (m_db.db.Files[index].IsDir)
			return -1;
		
		return SzArEx_Extract(&m_db, &m_lookStream.s, index, &m_blockIndex, &outBuffer, &outBufferSize, &offset, &outSizeProcessed, &m_allocImp, &m_allocTempImp);
	}
	int readHeader(std::vector<std::string>& fileNames)
	{	
		/*UInt32 i = 0;

		if (!m_db.db.NumFiles)
			return 0;

		const CSzFileItem* f = m_db.db.Files;

		if (!f)
			return 0;

		while (f[i].IsDir)
		{
			if (i++ >= m_db.db.NumFiles)
				return 0;
		}

		size_t len = SzArEx_GetFileNameUtf16(&m_db, 0, 0);

		if (len <= 0)
		{
			len = SzArEx_GetFileNameUtf16(&m_db, i, 0);
			std::string str = lang::string::toUTF8string(((lang::u16string&)m_db.FileNames.data)); //?
			fileNames.push_back(str);
		}
		if (!m_db.db.NumFiles)
			return 0;
		SzFree(0, 0);

		SzAlloc(0, 2 * len);*/

		assert("int io::ZipFile7Zip::Impl::readHeader(std::vector<std::string>& fileNames) is not yet decompiled.");
		return 0;
	}
private:
	CSeekInStream m_bufferStream;
	CLookToRead m_lookStream;
	CSzArEx m_db;
	ISzAlloc m_allocImp;
	ISzAlloc m_allocTempImp;
	UInt32 m_blockIndex;
	bool m_fileWasOpened;
};

ZipFile7Zip::ZipFile7Zip()
{
	m_impl = new Impl();
}

ZipFile7Zip::~ZipFile7Zip()
{
}


int ZipFile7Zip::open(InputStream& fileInput)
{
	return m_impl->open(fileInput);
}

int ZipFile7Zip::readHeader(std::vector<std::string>& fileNames)
{
	return m_impl->readHeader(fileNames);
}

int ZipFile7Zip::extract(int index, std::vector<char>& resultBuffer)
{
	return m_impl->extract(index, resultBuffer);
}

}