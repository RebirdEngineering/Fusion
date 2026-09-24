#include <lang/AutoreleasePool.h>

BEGIN_NAMESPACE(lang)

class AutoreleasePool::Impl :
	public Object
{
public:
	Impl();

	~Impl();
};

END_NAMESPACE()