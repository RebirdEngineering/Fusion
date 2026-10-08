#include <io/AppDataInputStream.h>
#include <io/FileInputStream.h>
#include <io/detail/detail.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{

class AppDataInputStream::Impl : //8
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

	bool seek(int offset, SeekMode origin) //27
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
	FileInputStream m_in; //43

	std::string constructPath(const std::string& pathname) const //45 | ?
	{
		std::string temp = pathname; //47
		if ((temp.empty() & 1) == 0 && temp[0] == '/') //48
			temp.erase(temp.begin()); //49
		return PathName(detail::appdataPath(), temp).toString(); //50
	}
};

AppDataInputStream::AppDataInputStream( const std::string& path ) : //57
	InputStream(this)
{
	m_impl = new Impl(path); //59
}

AppDataInputStream::~AppDataInputStream() //62-64
{
}

int AppDataInputStream::read( void* data, int size ) //66
{
	return m_impl->read(data, size); //68
}

int AppDataInputStream::skip( int n ) //71
{
	return m_impl->skip(n); //73
}

bool AppDataInputStream::seek( int offset, SeekMode origin ) //76
{
	return m_impl->seek(offset, origin); //78
}

int AppDataInputStream::available() const //81
{
	return m_impl->available(); //83
}

std::string AppDataInputStream::toString() const //88
{
	return m_impl->toString(); //90
}

std::string AppDataInputStream::path() //Not on iOS.
{
	return detail::appdataPath();
}

}