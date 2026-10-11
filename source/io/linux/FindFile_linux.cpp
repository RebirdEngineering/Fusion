#include <io/FindFile.h>
#include <lang/Throwable.h>
#include <io/IOException.h>
#include <lang/Log.h>

#include <glob>

using namespace lang;

namespace io
{

int error_func(const char* msg, int errorNum) //23
{
	LANG_LOG("FindFile", LANG_LOG_PRIORITY_ERROR, "error_func(% d) : % s", errorNum, msg); //25
	return 0;
}

class FindFile::Impl : //29
	public Object
{
public:
	Impl(const std::string& filter, int flags) : //33
		m_filter(PathName(filter).basename() + PathName(filter).suffix()), //34
		m_path(PathName(filter).parent().toString()), //35
		m_flags(flags),
		m_subdirs(),
		m_data(),
		m_current(0)//,
		//m_glob()
	{
		/*if (flags & FIND_RECURSE)
			listSubDirs(m_path);

		m_subdirs.push_back(m_path); //49
		next();*/
	}
	
	~Impl() //53
	{
		//globfree(m_glob);
	}
	
	void next() //58
	{
		/*
		//.empty() //73
		
		//= //75
		
		if (m_fh != -1 && 0 == _findnext(m_fh, &m_fd))
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
	
	bool more() const //86
	{
		//return ! m_glob.gl_pathc.size()
		//return m_glob && m_glob.gl_pathc >= m_current || m_subdirs.empty() > 0;
		//return m_fh != -1 || m_subdirs.empty() > 0;
		//return false; // ? m_fh != -1 || m_subdirs.empty() > 0;
		return false;
	}
	
	const Data& data() const //91
	{
		return m_data;
	}
	
private:
	std::string			m_filter; //97
	std::string			m_path; //98
	int				m_flags; //99
	std::vector<std::string>	m_subdirs; //100
	Data			m_data; //101
	unsigned int m_current; //102
	//glob_t m_glob; //103 | TODO

	void glob(const std::string& pattern, int flags) //105 | TODO
	{
		/*if (glob(pattern.c_str(), flags & 0xFFFFFEFF, error_func, m_glob) != -3) //109
			throwError(IOException(Format("Error globbing '{0}' with error {1} (errno:{2})", pattern, errno, strerror(errno)))); //111*/
	}

	void updateData() //114 | TODO
	{
		/*if (!m_glob.gl_pathc)
			return;

		struct stat stats; //119
		int error = stat(m_glob.gl_pathv[m_current], &stats); //120, recover from assert
		assert(error == 0 && "Stat failed!"); //Add assert on line 121 (RCSSDKDBG) or 132

		m_data.attrib = ATTRIB_NORMAL;

		if ((stats.st_mode & 2) != 0)
			m_data.attrib |= ATTRIB_READONLY;

		if ((stats.st_mode & S_IFMT) == S_IFDIR)
			m_data.attrib |= ATTRIB_SUBDIR; //134
		else if ((stats.st_mode & S_IFMT) == S_IFREG)
			m_data.attrib |= ATTRIB_ARCHIVE; //136

		m_data.writeTime = stats.st_mtimespec.tv_sec;
		m_data.size = stats.st_size;
		m_data.path = PathName(m_glob.gl_pathv[m_current]); //140*/
	}

	void listSubDirs(std::string path) //143 | TODO
	{
		/*glob(PathName(path, "*").toString(), m_glob.gl_flags); //145
		
		struct stat stats; //147

		//m_subdirs.size(); //149 | ?
		for (unsigned int i = 0; i < m_glob.gl_pathc; i++) //150
		{
			int error = errno; //152
			if (stat(m_glob.gl_pathv[i], &stats))
				LANG_LOG("FindFile", LANG_LOG_PRIORITY_ERROR, "stat(\"%s\") failed with %s", m_glob.gl_pathv[i], strerror(error)); //154
			else if ((stats.st_mode & 0xF000) == S_IFDIR)
				m_subdirs.push_back(PathName(m_glob.gl_pathv[i]).toString()); //156
		}
		
		globfree(m_glob); //158

		m_subdirs.size(); //160 | ?
		for (int i = 0; i < m_subdirs.size(); i++) //161
			listSubDirs(m_subdirs[i]); //162
		
		m_glob.gl_pathc = 0;
		m_glob.gl_pathv = 0;
		m_glob.gl_offs = 0;
		memset(m_glob, 0, sizeof(m_glob));*/
	}
};

FindFile::FindFile(const std::string& filter, int flags) //171
{
	m_impl = new Impl(filter, flags); //173
}

FindFile::~FindFile()
{
}

void FindFile::next() //180-183
{
	m_impl->next(); //182
}

bool FindFile::more() const //185-188
{
	return m_impl->more(); //187
}

const FindFile::Data& FindFile::data() const //190-193
{
	return m_impl->data(); //192
}

bool FindFile::isFileExist(const std::string& filter, int flags)
{
	FindFile ff(filter, flags);
	return ff.more();
}

}