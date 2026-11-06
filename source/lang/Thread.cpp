#include <lang/Thread.h>
#include <lang/Exception.h>
#include <lang/Log.h>
#include <ctime>
#include <time.h>

#ifdef _WIN32
#include <process.h>
//#include <processthreadsapi.h>
#include <windows.h>
#else //UNTESTED
//#include <pthread.h>
//#include <stdio.h>
//#include <sched.h>
#endif

BEGIN_NAMESPACE(lang)

Thread::Thread()
{
    startThread();
    assert(!joinable()); //35 (RCSSDK)
}

Thread::Thread(const Functor& func, bool joinOnDestruct) //37
{
    m_func = new Functor(func);
    m_autoJoin = joinOnDestruct;
    startThread();
    assert(!joinable()); //43 (RCSSDK)
}

bool Thread::joinable() const
{
    return m_threadHandle != 0;
}

Thread::Thread(Thread&& other) : //Correct?
    m_func(other.m_func),
    m_threadHandle(other.m_threadHandle)
{
    m_func = 0;
    m_threadHandle = 0;
    m_autoJoin = false;
}

Thread& Thread::operator=(Thread&& other)
{
    if (!joinable())
    {
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Assigning to joinable lang::Thread, terminating .."); //59 (RCSSDK)
        std::terminate();
    }

    swap(other);
    return *this;
}

void Thread::swap(Thread& other) //Correct?
{
    std::swap(m_func, other.m_func);
    std::swap(m_threadHandle, other.m_threadHandle);
    std::swap(m_autoJoin, other.m_autoJoin);
}

Thread::~Thread() //Win32: 4F43D0
{
    if (joinable()) //68
    {
        m_autoJoin ? join() : closeThread(); //70
    }
}

void Thread::join()
{
    if (joinable())
    {
#ifdef _WIN32
        CloseHandle(m_threadHandle);
#else
        pthread_join(m_threadHandle);
#endif
    }
}

void Thread::closeThread()
{
    if (!joinable())
        return;
#ifdef _WIN32
    CloseHandle(m_threadHandle);
    m_threadHandle = 0; //Why?
#else
    pthread_detach(m_threadHandle);
#endif
    m_threadHandle = 0;
}

int Thread::priority() const //Win32: 4F4380
{
    if (!joinable()) //100
        return 0;

#ifdef _WIN32
    return GetThreadPriority(m_threadHandle);
#else
    /*int policy; //106
    sched_param param = pthread_getschedparam(m_threadHandle); //107
    return param.sched_priority;*/
    return 0;
#endif
}

void Thread::setPriority(int prio) //116 | Win32: 4F43A0
{
    if (!joinable()) //118
        return;

#ifdef _WIN32
    SetThreadPriority(m_threadHandle, prio);
#else
    /*int policy; //124
    sched_param param; //125
    pthread_getschedparam(m_threadHandle, policy, param); //126
    param.sched_priority = prio;
    pthread_setschedparam(m_threadHandle, policy, param); //128
    */
#endif
}

void Thread::sleep(unsigned int ms) //140
{
#ifdef _WIN32
    Sleep(ms);
#else
    /*timespec ts; //146
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = 1000000 * (ms % 1000);
    nanosleep(ts, 0);*/
#endif
}

void Thread::yield() //Never seen on MSFT?
{
    //sched_yield();
}

void Thread::busyYield()
{
    if (hardwareConcurrency() == 1)
        yield();
}

unsigned int getHardwareConcurrency() //158 | TODO
{
    unsigned int result = 1; //162
    //mach_msg_type_number_t infoCount = 12; //177
    //host_basic_info_data_t hostInfo = host_info(; //178
    return result;
}

static const unsigned int s_hardwareConcurrency = getHardwareConcurrency(); //200

void Thread::startThread()
{
#ifdef _WIN32
    m_threadHandle = (ThreadHandle)_beginthreadex(0, 0, 0, m_func, 0, 0);
    if (m_threadHandle)
        return;
#else
    if (!pthread_create(&m_threadHandle, 0, threadFunc, m_func)) //301
        return;
#endif
    delete m_func;
    throwError(Exception(Format("Creating thread failed"))); //304
}

unsigned int Thread::hardwareConcurrency()
{
    return s_hardwareConcurrency;
}

void executeThread(void* data) //228 | TODO
{
    /*Functor* func = ; //230
    AutoreleasePool pool; //234
    //m_func(func); //235
    //ThreadInterruptedException //237
    const exception& e = ;*/ //240
}

void* threadFunc(void* data) //271
{
    executeThread(data); //273
    return 0;
}

}