#include <io/FileOutputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>
#include <direct.h>

const int length = 512; //?

using namespace lang;


namespace io
{ 

class FileOutputStream::Impl :
	public Object
{
public:
	Impl(const std::string& filename) :
		m_filename(filename)
	{
		m_fh = fopen(filename.c_str(), "wb");
		if (!m_fh)
			throwError(IOException(Format("Failed to open {0} for writing with errno {1} ({2})", filename, errno, strerror(errno))));
	}

	~Impl()
	{
		if (m_fh)
			fclose(m_fh);
	}

	void write(const void* data, int size)
	{
		int bytes = fwrite(data, 1, size, m_fh);
		if (bytes < size && ferror(m_fh))
			throwError(IOException(Format("Failed to write {0} bytes to {1}", size, toString())));
	}

	std::string toString() const
	{
		return m_filename;
	}

	std::string path() const //Code not in 4.1.0
	{
		char cwd[length];
		_getcwd(cwd, sizeof(cwd));
		return PathName(cwd).toString();
	}
private:
	std::string 	m_filename;
	FILE* m_fh;
};


FileOutputStream::FileOutputStream( const std::string& filename) :
	OutputStream(this)
{
	m_impl = new Impl(PathName(filename).toString());
}

FileOutputStream::~FileOutputStream()
{
}

void FileOutputStream::write( const void* data, int size )
{
	return m_impl->write(data, size);
}

std::string FileOutputStream::toString() const
{
	return m_impl->toString();
}

std::string FileOutputStream::path()
{
	return m_impl->path();
}

} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
