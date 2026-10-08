#include <io/AppDataOutputStream.h>
#include <io/IOException.h>
#include <io/PathName.h>
#include <lang/Log.h>
#include <io/detail/detail.h>

#ifdef PLATFORM_WIN32
#include <io.h>
#include <shlobj.h>
#endif

static int fsyncHelper(FILE* file) //88
{
#ifdef PLATFORM_WIN32
	HANDLE handle = (HANDLE)_get_osfhandle(_fileno(file)); //?
	if (handle == INVALID_HANDLE_VALUE)
	{
		errno = ERROR_INVALID_BLOCK;
		return EOF;
	}

	else if (FlushFileBuffers(handle))
	{
		return 0;
	}

	else GetLastError() == ERROR_INVALID_HANDLE ? errno = ERROR_BAD_COMMAND : errno = ERROR_ACCESS_DENIED;

	return EOF;
	//return _commit(fileno(file));
#elif PLATFORM_IOS //or apple
	return fsync(fileno(file)); //90
#else
#endif
}

//static FILE* openFileHelper(const std::string& filename) //RCSSDKLIB
//{
//	return fopen(filename.c_str(), "wb");
//}

static int moveFileHelper(const std::string& oldName, const std::string& newName) //RCSSDKLIB | Not in DWARF?
{
	return rename(oldName.c_str(), newName.c_str()); //96
}

using namespace lang;

namespace io
{

class AppDataOutputStream::Impl :
	public Object
{
public:
	Impl(const std::string& filename) : //127-136
		m_filename(constructPath(filename)), //128
		m_failure(false)
	{
		m_filename += ".tmp";
		m_fh = fopen(filename.c_str(), "wb"); //On Win, wfopen
		if (!m_fh)
			throwError(IOException(Format("Failed to open {0} for writing, with errno {1} ({2})", m_filename, errno, strerror(errno), errno))); //134
	}

	~Impl() //138
	{
		if (!m_failure)
		{
			if (fflush(m_fh) == -1) //143
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Failed flushing, not saving %s: %s", m_filename.c_str(), strerror(errno)); //145
				m_failure = true;
			}

			if (fsyncHelper(m_fh) <= -1) //149
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Failed syncing, not saving %s: %s", m_filename.c_str(), strerror(errno)); //151
				m_failure = true;
			}

			if (fclose(m_fh) == EOF) //155
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Cannot close file, not saving %s: %s", m_filename.c_str(), strerror(errno)); //157
				m_failure = true;
			}
		}

		else
			moveFileHelper(m_filename + ".tmp", m_filename.c_str()); //166 | Inline call? Points to line 96?
	}

	void write(const void* data, int size) //169
	{
		if (m_failure)
			throwError(IOException(Format("Writing to {0} failed, stream state broken", toString()))); //172

		int bytes = fwrite(data, 1, size, m_fh); //174
		if (bytes < size && ferror(m_fh))
		{
			m_failure = true;
			throwError(IOException(Format("Failed to write {1} bytes to {0}", toString(), size))); //178
		}
	}

	std::string toString() const //182
	{
		return m_filename;
	}

	bool good() const //Never seen on iOS.
	{
		return !m_failure;
	}

private:
	std::string m_filename; //193
	bool m_failure; //194
	FILE* m_fh; //195

	std::string constructPath(const std::string& pathname) //197
	{
		std::string temp = pathname; //199
		if ((temp.empty() & 1) == 0 && temp[0] == '/') //200
			temp.erase(temp.begin()); //201
		return PathName(detail::appdataPath(), temp).toString(); //202
	}
};

AppDataOutputStream::AppDataOutputStream( const std::string& filename ) : //209
	OutputStream(this)
{
	m_impl = new Impl(filename); //212
}

AppDataOutputStream::~AppDataOutputStream() //215
{
}

void AppDataOutputStream::write( const void* data, int size ) //218 | [TODO] Copy of FileOutputStream, why did you make these
{
	m_impl->write(data, size); //220
}

std::string AppDataOutputStream::toString() const //225 | Copy of *Stream
{
	return m_impl->toString();
}

std::string AppDataOutputStream::path()
{
	return detail::appdataPath();
}

bool AppDataOutputStream::good() const //Never seen on iOS.
{
	return m_impl->good();
}

}