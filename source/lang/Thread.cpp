#include <lang/Thread.h>
#include <lang/Exception.h>
#include <ctime>
#include <time.h>
//#include <pthread.h>
//#include <stdio.h>
//#include <sched.h>

BEGIN_NAMESPACE(lang)

unsigned int getHardwareConcurrency()
{
    unsigned int result = 1;
    //mach_msg_type_number_t infoCount = 12;
    //host_basic_info_data_t hostInfo = host_info(;
    return result;
}

static const unsigned int s_hardwareConcurrency;

Thread::Thread()
{
    startThread();
    assert(!joinable()); //35
}

Thread::Thread(const Functor& func, bool joinOnDestruct)
{
    m_func = new Functor(func);
    m_autoJoin = joinOnDestruct;
    startThread();
    assert(!joinable()); //35 (RCSSDK) or 43
}

Thread::~Thread()
{
    /*if (!m_threadHandle)
        return;
    m_autoJoin ? join : pthread_detach(m_threadHandle);
    m_threadHandle = 0;*/
}

void Thread::join()
{
    /*if (m_threadHandle)
        pthread_join(m_threadHandle, 0);*/
}

int Thread::priority() const
{
    /*int policy = joinable();
    int param = pthread_getschedparam(m_threadHandle);
    if (!m_threadHandle)
        return 0;
    return policy ? param : 0;*/
    return 0;
}

bool Thread::joinable() const
{
    return m_autoJoin != false;
}

void Thread::setPriority(int prio)
{
    /*int policy = joinable();
    int param = m_threadHandle.pthread_getschedparam();
    if (!m_threadHandle)
        return;
    m_threadHandle.sched_priority = prio;
    m_thread.pthread_setschedparam(policy, param);*/
    
}

void Thread::sleep(unsigned int ms)
{
    /*timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = 1000000 * (ms % 1000);
    nanosleep(ts, 0);*/
}

void Thread::yield()
{
    //sched_yield();
}

void Thread::startThread()
{
    //if (!pthread_create(&m_threadHandle, 0, threadFunc, m_func))
        //return;

    throwError(Exception(Format("Creating thread failed")));
}

void executeThread(void* data)
{
    /*Functor* func = ;
    AutoreleasePool pool;
    //ThreadInterruptedException
    const exception& e = ;*/
}

void* threadFunc(void* data)
{
    executeThread(data);
    return 0;
}

}