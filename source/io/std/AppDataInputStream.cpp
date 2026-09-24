#include <io/AppDataInputStream.h>
#include <io/FileInputStream.h>
#include <io/detail/detail.h>
#include <io/PathName.h>

USING_NAMESPACE(lang)

BEGIN_NAMESPACE(io)

USING_NAMESPACE(detail)

class AppDataInputStream::Impl :
	public Object
{
public:
	Impl(const std::string& path) :
		m_in(constructPath(path))
	{
	}
	~Impl()
	{
	}
	int read(void* data, int size)
	{
		return m_in.read(data, size);
	}
	int skip(int n)
	{
		return m_in.skip(n);
	}
	bool seek(int offset, SeekMode origin)
	{
		return m_in.seek(offset, origin);
	}
	int available() const
	{
		return m_in.available();
	}
	std::string toString() const
	{
		return m_in.toString();
	}
	std::string constructPath(const std::string& pathname) const //?
	{
		std::string temp = pathname;
		if ((temp.empty() & 1) == 0 && temp[0] == '/')
			temp.erase(temp.begin());
		return PathName(appdataPath(), temp).toString();
	}
private:
	FileInputStream m_in;
};

AppDataInputStream::AppDataInputStream( const std::string& path ) :
	InputStream(this)
{
	m_impl = new Impl(path);
}

AppDataInputStream::~AppDataInputStream()
{
}

int AppDataInputStream::read( void* data, int size )
{
	return m_impl->read(data, size);
}

int AppDataInputStream::skip( int n )
{
	return m_impl->skip(n);
}

bool AppDataInputStream::seek( int offset, SeekMode origin )
{
	return m_impl->seek(offset, origin);
}

int AppDataInputStream::available() const
{
	return m_impl->available();
}

std::string AppDataInputStream::toString() const
{
	return m_impl->toString();
}

std::string AppDataInputStream::path()
{
	return appdataPath();
}

}