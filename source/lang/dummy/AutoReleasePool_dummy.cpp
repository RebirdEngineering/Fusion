#include <lang/AutoreleasePool.h>

BEGIN_NAMESPACE(lang)

class AutoreleasePool::Impl : //Win32, Android
	public Object
{
public:
	Impl()
	{
	}

	~Impl()
	{
	}
};

AutoreleasePool::AutoreleasePool()
{
	m_impl = new Impl();
}

AutoreleasePool::~AutoreleasePool()
{
}

END_NAMESPACE()