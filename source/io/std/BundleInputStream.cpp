#include <io/BundleInputStream.h>
#include <io/FileInputStream.h>
#include <io/detail/detail.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{

class BundleInputStream::Impl : //8
	public Object
{
public:
	Impl(const std::string& path) : //12
		m_in(constructPath(path)) //13
	{
	}

	int read(void* data, int size) //17
	{
		return m_in.read(data, size);
	}

	int skip(int n) //22
	{
		return m_in.skip(n);
	}

	bool seek(int offset, InputStream::SeekMode origin) //27
	{
		return m_in.seek(offset, origin);
	}

	int available() const //32
	{
		return m_in.available();
	}

	std::string toString() const //37
	{
		return m_in.toString();
	}
	
private:
	FileInputStream			m_in; //43

	std::string constructPath(const std::string& pathname) //45
	{
		std::string temp = pathname; //47
		if ((temp.empty() & 1) == 0 && temp[0] == '/') //48
			temp.erase(temp.begin()); //49
		return PathName(detail::bundlePath(), temp).toString(); //50
	}
};

BundleInputStream::BundleInputStream( const std::string& path, ReadModeHint hint ) : InputStream(this) //57-60
{
	m_impl = new Impl(path); //59
}

BundleInputStream::~BundleInputStream() //62-64
{
}

int BundleInputStream::read( void* data, int size ) //66-69
{
	return m_impl->read(data, size); //68
}

int BundleInputStream::skip( int n ) //71-74
{
	return m_impl->skip(n); //73
}

bool BundleInputStream::seek( int offset, SeekMode origin ) //76-79
{
	return m_impl->seek(offset, origin); //78
}

int BundleInputStream::available() const //81-84
{
	return m_impl->available(); //83
}

std::string BundleInputStream::toString() const //86-89
{
	return m_impl->toString(); //88
}

}