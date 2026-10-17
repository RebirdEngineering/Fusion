#ifndef _LANG_FUNCTOR_H
#define _LANG_FUNCTOR_H

#include <lang/Object.h>

BEGIN_NAMESPACE(lang)

class FuncBase //6
{
public:
    virtual void operator()() = 0; //9
    virtual FuncBase* clone() = 0; //10
    virtual ~FuncBase(); //11
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