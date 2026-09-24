#ifndef _LANG_MUTEX_H
#define _LANG_MUTEX_H

#include <lang/Ptr.h>

namespace lang
{

class Mutex //12
{
public:
    class Lock //16
    {
    public:
        Lock(Mutex& mutex); //19
        ~Lock(); //20
    private:
        Mutex& m_mutex; //22
        Lock(const Lock&); //23
        Lock& operator=(const Lock&); //24
    };

    Mutex(); //27
    ~Mutex(); //28

    void lock(); //30
    bool tryLock(); //31
    void unlock(); //32
private:
    class MutexImpl;
    P(MutexImpl) m_impl; //36

    Mutex(const Mutex&); //38
    Mutex& operator=(const Mutex&); //39
};

}

#endif