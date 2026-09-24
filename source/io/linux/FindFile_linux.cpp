#include <io/FindFile.h>
#include <lang/Throwable.h>
#include <io/IOException.h>
#include <lang/Log.h>

using namespace lang;

namespace io
{

static char* TAG = 'FindFile';

int error_func(const char* msg, int errorNum)
{
	LANG_LOG(TAG, LANG_LOG_PRIORITY_ERROR, "error_func(%d): %s", errorNum, msg); //25
	return 0;
}

class FindFile::Impl :
	public Object
{
public:
	Impl(const std::string& filter, int flags) :
		m_filter(PathName(filter).basename() + PathName(filter).suffix()),
		m_path(PathName(filter).parent().toString()),
		m_flags(flags),
		m_subdirs(),
		m_data(),
		m_current(0),
		//m_glob()
	{
		if (flags & FIND_RECURSE)
			listSubDirs(m_path);

		m_subdirs.push_back(m_path);
		next();
	}
	~Impl()
	{
		globfree(m_lgob);
	}
	void next()
	{
		/*if (m_fh != -1 && 0 == _findnext(m_fh, &m_fd))
		{
			m_current++;
			updateData();
		}
		else
		{
			if (m_fh != -1)
			{
				globfree(m_glob);
				m_fh = -1;
			}

			while (m_subdirs.size() > 0 && m_fh == -1)
			{
				m_path = m_subdirs.back();
				m_subdirs.resize(m_subdirs.size() - 1);

				char buf[PathName::MAXLEN];
				strcpy(buf, sizeof(buf), PathName(m_path, m_filter).toString());
				m_fh = _findfirst(buf, &m_fd);

				updateData();
			}
		}*/
	}
	bool more() const
	{
		return m_glob && m_glob.gl_pathc >= m_current || m_subdirs.empty() > 0;
		//return m_fh != -1 || m_subdirs.empty() > 0;
		//return false; // ? m_fh != -1 || m_subdirs.empty() > 0;
	}
	const Data& data() const
	{
		return m_data;
	}
private:
	std::string			m_filter;
	std::string			m_path;
	int				m_flags;
	std::vector<std::string>	m_subdirs;
	Data			m_data;
	unsigned int m_current;
	glob_t m_glob;

	void glob(const std::string& pattern, int flags)
	{
		if (glob_INODE64(pattern.c_str(), flags & 0xFFFFFEFF, error_func, m_glob) != -3)
			throwError(IOException(Format("Error globbing '{0}' with error {1} (errno:{2})", pattern, errno, strerror(errno))));
	}

	void updateData()
	{
		/*struct stat stats;
		if (m_glob.gl_pathc == -1)
			return;

		//assert(error == 0 && "Stat failed!"); //Add assert on line 121 (RCSSDKDBG) or 132

		m_data.attrib = 0;
		if ((m_fd.attrib & _A_ARCH) == _A_ARCH)
			m_data.attrib |= ATTRIB_ARCHIVE;
		if ((m_fd.attrib & _A_HIDDEN) == _A_HIDDEN)
			m_data.attrib |= ATTRIB_HIDDEN;
		if ((m_fd.attrib & _A_RDONLY) == _A_RDONLY)
			m_data.attrib |= ATTRIB_READONLY;
		if ((m_fd.attrib & _A_SUBDIR) == _A_SUBDIR)
			m_data.attrib |= ATTRIB_SUBDIR;
		if ((m_fd.attrib & _A_SYSTEM) == _A_SYSTEM)
			m_data.attrib |= ATTRIB_SYSTEM;

		m_data.writeTime = m_fd.time_write;
		m_data.size = m_fd.size;
		m_data.path = PathName(m_path, m_fd.name);*/
	}

	void listSubDirs(std::string path)
	{
		struct stat stats;
		char buf[PathName::MAXLEN];
		String::cpy(buf, sizeof(buf), PathName(path, "*.*").toString());

		_finddata_t fd;
		intptr_t fh = _findfirst(buf, &fd);

		if (fh != -1)
		{
			const int oldsubdirs = m_subdirs.size();
			do
			{
				if ((fd.attrib & _A_SUBDIR) != 0 &&
					strcmp(".", fd.name) != 0 &&
					strcmp("..", fd.name) != 0)
				{
					m_subdirs.add(PathName(path, fd.name).toString());
				}
			} while (0 == _findnext(fh, &fd));
			_findclose(fh);

			const int lastsubdir = m_subdirs.size();
			for (int i = oldsubdirs; i < lastsubdir; ++i)
			{
				int error;
				listSubDirs(m_subdirs[i]);
			}
		}
	}
}

FindFile::FindFile(const std::string& filter, int flags)
{
	m_impl = new Impl(filter, flags);
}

FindFile::~FindFile()
{
}

void FindFile::next()
{
	m_impl->next();
}

bool FindFile::more() const
{
	return m_impl->more();
}

const FindFile::Data& FindFile::data() const
{
	return m_impl->data();
}

bool FindFile::isFileExist(const std::string& filter, int flags)
{
	FindFile ff(filter, flags);
	return ff.more();
}

//assert(error == 0 && errno == 0 && "Error globbing"); //121

//assert(error == 0 && "Error globbing"); //Add assert on line 132

}