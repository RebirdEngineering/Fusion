#ifndef _LANG_FUNCTOR_H
#define _LANG_FUNCTOR_H

#include <lang/Object.h>

BEGIN_NAMESPACE(lang)

class FuncBase
{
public:
    virtual void operator()();
    virtual FuncBase* clone();
    ~FuncBase();
};

class Functor
{
public:
    Functor();

    ~Functor();

    void operator()();

    Functor(const Functor&);

    Functor& operator=(const Functor&);
private:
    FuncBase* m_func;
};

}

#endif