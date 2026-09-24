#include <io/AppDataOutputStream.h>>
#include <io/IOException.h>
#include <io/PathName.h>
#include <lang/Log.h>
#include <io/detail/detail.h>

#ifdef PLATFORM_WIN32
#include <io.h>
#include <winerror.h>
#include <shlobj.h>
#endif

static int fsyncHelper(FILE* file)
{
#ifdef PLATFORM_WIN32
	HANDLE handle = (HANDLE)_get_osfhandle(_fileno(file)); //?
	if (handle == INVALID_HANDLE_VALUE)
	{
		errno = ERROR_INVALID_BLOCK;
		return -1;
	}
	else if (FlushFileBuffers(handle))
	{
		return 0;
	}
	else GetLastError() == ERROR_INVALID_HANDLE ? errno = ERROR_BAD_COMMAND : errno = ERROR_ACCESS_DENIED;
	return -1;
	//return _commit(fileno(file));
#elif PLATFORM_IOS //or apple
	return fsync(fileno(file));
#else
#endif
}

using namespace lang;

namespace io
{

using namespace detail;

static FILE* openFileHelper(const std::string& filename) //RCSSDKLIB
{
	return fopen(filename.c_str(), "wb");
}

static int moveFileHelper(const std::string& oldName, const std::string& newName) //RCSSDKLIB
{
	return rename(oldName.c_str(), newName.c_str());
}

class AppDataOutputStream::Impl :
	public Object
{
public:
	Impl(const std::string& filename)
	{
		m_filename = constructPath(filename);
		m_failure = false;
		m_filename += ".tmp";
		//m_fh = openFileHelper(m_filename); //RCSSDKLIB
		m_fh = fopen(filename.c_str(), "wb"); //On Win, wfopen
		if (!m_fh)
			throwError(IOException(Format("Failed to open {0} for writing, with errno {1} ({2})", m_filename, errno, strerror(errno), errno)));
	}	

	~Impl()
	{
		if (!m_failure)
		{
			if (fflush(m_fh) == -1)
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Failed flushing, not saving %s: %s", m_filename.c_str(), strerror(errno)); //145
				m_failure = true;
			}
			if (fsyncHelper(m_fh) <= -1)
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Failed syncing, not saving %s: %s", m_filename.c_str(), strerror(errno)); //151
				m_failure = true;
			}
			if (fclose(m_fh) <= -1)
			{
				LANG_LOG("AppDataOutputStream", LANG_LOG_PRIORITY_ERROR, "Cannot close file, not saving %s: %s", m_filename.c_str(), strerror(errno)); //157
				m_failure = true;
			}
		}
		else
		{
			m_filename += "tmp";
			moveFileHelper(m_filename, "");
		}
	}

	void write(const void* data, int size) //169
	{
		if (m_failure)
			throwError(IOException(Format("Writing to {0} failed, stream state broken", m_filename)));

		int bytes = fwrite(data, 1, size, m_fh);
		if (bytes < size && ferror(m_fh))
		{
			m_failure = true;
			throwError(IOException(Format("Failed to write {1} bytes to {0}", m_filename, size)));
		}
	}
	std::string toString() const
	{
		return m_filename;
	}
	bool good() const
	{
		return ((m_failure ^ 1) & 1);
	}
	std::string constructPath(const std::string& pathname)
	{
		std::string temp = pathname;
		if ((temp.empty() & 1) == 0 && temp[0] == '/')
			temp.erase(temp.begin());
		return PathName(appdataPath(), temp).toString();
	}
private:
	std::string m_filename;
	bool m_failure;
	FILE* m_fh;
};

AppDataOutputStream::AppDataOutputStream( const std::string& filename ) :
	OutputStream(this)
{
	m_impl = new Impl(filename);
}

AppDataOutputStream::~AppDataOutputStream()
{
}

void AppDataOutputStream::write( const void* data, int size ) //[TODO] Copy of FileOutputStream, why did you make these
{
	m_impl->write(data, size);
}

std::string AppDataOutputStream::toString() const //Copy of *Stream
{
	return m_impl->toString();
}

std::string AppDataOutputStream::path()
{
	return appdataPath();
}

bool AppDataOutputStream::good() const
{
	return m_impl->good();
}

}