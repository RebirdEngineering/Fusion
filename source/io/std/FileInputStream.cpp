#include <io/FileInputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{ 

//const int length = 512; //94

class FileInputStream::Impl : //18
	public Object
{
public:
	Impl(const std::string& filename) : //22-45
		m_filename(filename)
	{
		if (filename.empty() && filename[filename.size() - 1] == '/' || filename[filename.size() - 1] == '\\') //26
			throwError(IOException(Format("Failed to open {0} with errno {1}", m_filename, EINVAL))); //27 | Why is this officially a formatted float?

		m_fh = fopen(filename.c_str(), "rb"); //39
		if (!m_fh)
			throwError(IOException(Format("Failed to open {0} with errno {1} ({2})", m_filename, errno, strerror(errno)))); //43
	}

	~Impl() //47-50
	{
		fclose(m_fh);
	}

	int read(void* data, int size) //52-58
	{
		int bytes = fread(data, 1, size, m_fh); //54
		if (bytes < size && ferror(m_fh))
			throwError(IOException(Format("Failed to read {1} bytes from {0}", toString(), size))); //56
		return bytes;
	}

	int skip(int n) const //60-66
	{
		int ret = n; //62 | Previously cur
		if (fseek(m_fh, n, SEEK_CUR))
			throwError(IOException(Format("Failed to skip {0} bytes from {1}", toString(), n))); //64 | Previously "Failed to skip {1} bytes from {0}"
		return n;
	}

	int seek(int offset, SeekMode origin) const //68
	{
		return fseek(m_fh, offset, origin);
	}

	int available() const //73-82
	{
		int cur = ftell(m_fh); //75
		fseek(m_fh, 0, SEEK_END);
		int end = ftell(m_fh); //77
		fseek(m_fh, cur, SEEK_SET);
		if (ferror(m_fh))
			throwError(IOException(Format("Failed to seek {0}", toString()))); //80
		return end - cur;
	}

	std::string toString() const //84
	{
		return m_filename;
	}

	std::string path() //89
	{
		return PathName(m_filename).toString();
	}

private:
	std::string 	m_filename; //110
	FILE* m_fh; //111
};
	
FileInputStream::FileInputStream( const std::string& filename ) : InputStream(this) //117
{ //118?
	m_impl = new Impl(PathName(filename).toString()); //119
}

FileInputStream::~FileInputStream() //122-124
{
}

int FileInputStream::read( void* data, int size ) //126
{
	return m_impl->read(data, size); //128
}

int FileInputStream::skip(int n)
{
	return m_impl->skip(n); //133
}

bool FileInputStream::seek(int offset, SeekMode origin) //136
{
	return m_impl->seek(offset, origin); //138
}

int FileInputStream::available() const //141-144
{
	return m_impl->available(); //143
}

std::string FileInputStream::toString() const //145-149
{
	return m_impl->toString(); //148
}

std::string FileInputStream::path()
{
	return m_impl->path();
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
