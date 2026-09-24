#include <io/BundleInputStream.h>
#include <io/FileInputStream.h>
#include <io/detail/detail.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{

using namespace detail;

class BundleInputStream::Impl :
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

	bool seek(int offset, InputStream::SeekMode origin)
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
	
private:
	FileInputStream			m_in;
	std::string constructPath(const std::string& pathname)
	{
		std::string temp = pathname;
		if ((temp.empty() & 1) == 0 && temp[0] == '/')
			temp.erase(temp.begin());
		return PathName(bundlePath(), temp).toString();
	}
};

BundleInputStream::BundleInputStream( const std::string& path, ReadModeHint hint) :
	InputStream(this)
{
	m_impl = new Impl(path);
}

BundleInputStream::~BundleInputStream()
{
}

int BundleInputStream::read( void* data, int size )
{
	return m_impl->read(data, size);
}

int BundleInputStream::skip( int n )
{
	return m_impl->skip(n);
}

bool BundleInputStream::seek( int offset, SeekMode origin )
{
	return m_impl->seek(offset, origin);
}

int BundleInputStream::available() const
{
	return m_impl->available();
}

std::string BundleInputStream::toString() const
{
	return m_impl->toString();
}

}