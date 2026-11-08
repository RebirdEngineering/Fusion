#include <lang/AutoreleasePool.h>

BEGIN_NAMESPACE(lang)

class AutoreleasePool::Impl : //Win32
	public Object
{
public:
	Impl();

	~Impl();
};

END_NAMESPACE()