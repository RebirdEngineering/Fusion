#ifndef _LANG_AUTORELEASEPOOL_H
#define _LANG_AUTORELEASEPOOL_H

#include <lang/Object.h>

BEGIN_NAMESPACE(lang)

class AutoreleasePool :
    public Object
{
public:
    AutoreleasePool() //20
    {
        m_impl = new Impl();
    }

    ~AutoreleasePool(); //25
private:
    class Impl;
    P(Impl) m_impl; //28

    AutoreleasePool(const AutoreleasePool&); //30
    AutoreleasePool& operator=(const AutoreleasePool&); //31
};

}

#endif