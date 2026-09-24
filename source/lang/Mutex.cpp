#include <lang/Mutex.h>
#include <lang/Object.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h> //UNTESTED!
#endif

namespace lang
{

Mutex::Lock::Lock(Mutex& mutex) :
    m_mutex(mutex)
{
    mutex.lock();
}

Mutex::Lock::~Lock()
{
    m_mutex.unlock();
}

class Mutex::MutexImpl : //24
    public Object
{
public:
    MutexImpl()
    {
#ifdef _WIN32
        m_mutex = CreateMutexW(0, 0, 0);
#else
        pthread_mutexattr_t attr; //33
        pthread_mutexattr_init(attr);
        pthread_mutexattr_settype(attr, 2);

        pthread_mutex_init(m_mutex);
        pthread_mutexattr_destroy();
#endif
    }
    ~MutexImpl() //41
    {
#ifdef _WIN32
        CloseHandle(m_mutex);
#else
        pthread_mutex_destroy(&m_mutex);
#endif
    }

    void lock() //52
    {
#ifdef _WIN32
        WaitForSingleObject(m_mutex, -1);
#else
        pthread_mutex_lock(&m_mutex);
#endif
    }

    bool tryLock() //64
    {
#ifdef _WIN32
        //assert("bool Mutex::MutexImpl::tryLock for Win32 is not yet decompiled. Returning false.");
        return WaitForSingleObject(m_mutex, 0);
#else
        return pthread_mutex_trylock(&m_mutex) == 0;
#endif
    }

    void unlock() //77
    {
#ifdef _WIN32
        ReleaseMutex(m_mutex);
#else
        pthread_mutex_unlock(&m_mutex);
#endif
    }
private:

#ifdef _WIN32
    HANDLE m_mutex;
#else
    pthread_mutex_t m_mutex; //Multplatform (OSX, Meego)
#endif
};

Mutex::Mutex()
{
    m_impl = new MutexImpl(); //102
}

Mutex::~Mutex() //106
{
}

void Mutex::lock()
{
    m_impl->lock(); //111
}

bool Mutex::tryLock()
{
    return m_impl->tryLock(); //116
}

void Mutex::unlock()
{
    m_impl->unlock(); //121
}

}