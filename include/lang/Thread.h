#ifndef _LANG_THREAD_H
#define _LANG_THREAD_H

#include <lang/Object.h>
#include <lang/Functor.h>
#include <external/webp/utils/thread.h>

typedef HANDLE ThreadHandle; //Multiplatform handle
//typedef __darwin_pthread_t pthread_t;
//typedef _opaque_pthread_t* __darwin_pthread_t;

BEGIN_NAMESPACE(lang)

class Thread : //31 | 0x18 bytes on Win32
    public Object
{
public:
    Thread(); //39

    Thread(const Functor& func, bool joinOnDestruct); //47

    Thread(Thread&& other); //53 | Unknown param.

    Thread& operator=(Thread&& other); //61 | Unknown param.

    ~Thread(); //67

    bool joinable() const; //72

    void join(); //78

    int priority() const; //83

    void setPriority(int prio); //88

    void swap(Thread& other); //93 | Unknown param.

    void sleep(unsigned int ms); //93

    unsigned int hardwareConcurrency(); //110

    void yield(); //115

    void busyYield(); //123

private:
    void startThread(); //127

    void closeThread(); //130

    Functor* m_func; //133

    ThreadHandle m_threadHandle; //135
    bool m_autoJoin; //136
};

}

#endif