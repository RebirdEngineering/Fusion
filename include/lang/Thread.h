#ifndef _LANG_THREAD_H
#define _LANG_THREAD_H

#include <lang/Object.h>
#include <lang/Functor.h>
#include <external/webp/utils/thread.h>

typedef HANDLE ThreadHandle; //Multiplatform handle
//typedef __darwin_pthread_t pthread_t;
//typedef _opaque_pthread_t* __darwin_pthread_t;

BEGIN_NAMESPACE(lang)

class Thread :
    public Object
{
public:
    Thread();

    Thread(const Functor& func, bool joinOnDestruct);

    Thread(Thread&&);

    Thread& operator=(Thread&);

    ~Thread();

    bool joinable() const;

    void join();

    int priority() const;

    void setPriority(int);

    void swap(Thread&);

    void sleep(unsigned int);

    unsigned int hardwareConcurrency();

    void yield();

    void busyYield();
private:
    void startThread();

    void closeThread();

    Functor* m_func;

    ThreadHandle m_threadHandle;
    bool m_autoJoin;
};

}

#endif