#include <io/FileOutputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

using namespace lang;

namespace io
{ 

class FileOutputStream::Impl : //17
	public Object
{
public:
	Impl(const std::string& filename) : //21
		m_filename(filename)
	{
		m_fh = fopen(filename.c_str(), "wb"); //34
		if (!m_fh)
			throwError(IOException(Format("Failed to open {0} for writing with errno {1} ({2})", filename, errno, strerror(errno)))); //38
	}

	~Impl() //41
	{
		if (m_fh)
			fclose(m_fh);
	}

	void write(const void* data, int size) //47
	{
		int bytes = fwrite(data, 1, size, m_fh); //49
		if (bytes < size && ferror(m_fh))
			throwError(IOException(Format("Failed to write {0} bytes to {1}", size, toString()))); //51
	}

	std::string toString() const //54
	{
		return m_filename;
	}

	std::string path() const //59 | Not on iOS
	{
		const int length = 512; //64
		char cwd[length];
		_getcwd(cwd, sizeof(cwd));

		return PathName(cwd).toString();
	}

private:
	std::string 	m_filename; //80
	FILE* m_fh; //81
};

FileOutputStream::FileOutputStream( const std::string& filename) : //87
	OutputStream(this)
{
	m_impl = new Impl(PathName(filename).toString());
}

FileOutputStream::~FileOutputStream() //92-94
{
}

void FileOutputStream::write( const void* data, int size ) //96-99
{
	return m_impl->write(data, size); //98
}

std::string FileOutputStream::toString() const //101-104
{
	return m_impl->toString(); //103
}

std::string FileOutputStream::path() //Not on iOS
{
	return m_impl->path();
}

} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
