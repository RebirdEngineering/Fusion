#include <lang/Signal.h>
#include <lang/System.h>
#include <lang/Exception.h>
#include <lang/Log.h>

#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
//#include <lang/Atomic.h> //UNTESTED!
#endif

namespace lang
{

#ifdef _WIN32 //Given by heavily disconnected log line numbers, we're gonna assume the Posix impl is underneath.
class Signal::Impl //0x4 bytes. Win32 impl.
{
public:
	Impl(BOOL set) //53C320
	{
		m_mutex = CreateEventW(0, TRUE, set, 0);
		if (!m_mutex)
			throw Exception(Format("lang::Signal: CreateEventExW: {0}", GetLastError()));
	}

	~Impl() //53C300
	{
		if (m_mutex)
			CloseHandle(m_mutex);
	}

	void set() //53C420
	{
		if (!SetEvent(m_mutex))
		{
			LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "SetEvent: %s", GetLastError()); //46
			abort();
		}
	}

	void reset() //53C510
	{
		if (!ResetEvent(m_mutex))
		{
			LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "ResetEvent: %s", GetLastError()); //57
			abort();
		}
	}

	void wait() //Not found?
	{
	}

	bool wait(DWORD timeout_msec) //53C600
	{
		if (timeout_msec == -1)
			timeout_msec = -1;

		DWORD res = WaitForSingleObjectEx(m_mutex, timeout_msec, FALSE);

		if (!res)
			return true;

		if (res != WAIT_TIMEOUT)
		{
			if (res == WAIT_FAILED)
			{
				LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "WaitForSingleObjectEx: %s", GetLastError()); //113
				abort();
			}

			LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "Unexpected %d from WaitForSingleObjectEx.", res); //121
			abort();
		}

		return false;
	}

	HANDLE m_mutex;
};

#else //UNTESTED!
const int64_t NSEC_BY_SEC = 1000000000; //143

const int64_t NSEC_BY_MSEC = 1000000; //145

timespec from_msec(uint32_t msec) //157
{
	timespec ret; //159
	int64_t nsec_total; //160
	int64_t nsec_rem; //161
	uint32_t set_total; //162
	return ret;
	//return ((NSEC_BY_MSEC * msec - NSEC_BY_MSEC * msec % NSEC_BY_SEC) / NSEC_BY_MSEC);
}

class Signal::Impl //172 | //POSIX (TODO), 0x4C bytes. //TODO Separate class for MSFT b4 Posix? Line numbers suggest so.
{
public:
	Impl(bool set) //174
	{
		/*m_set.value.value = set; //176
		int res = pthread_mutex_init(&m_mutex, 0); //177
		if (res)
			throwError(Exception(Format("lang::Signal: pthread_mutex_init: {0}", res))); //179

		pthread_condattr_t attr; //182
		if (pthread_condattr_init(attr)) //183
		{
			pthread_mutex_destroy(&m_mutex); //185

			throwError(Exception(Format("lang::Signal: pthread_condattr_init: {0}", ))); //187
		}

		if (pthread_cond_init(&m_cond, attr)) //197
		{
			pthread_condattr_destroy(attr); //200
			pthread_mutex_destroy(&m_mutex); //201

			throwError(Exception(Format("lang::Signal: pthread_cond_init: {0}", ))); //203
		}*/
	}

	~Impl() //210
	{
		//pthread_cond_destroy(m_cond); //212
		//pthread_mutex_destroy(m_mutex); //213
	}

	struct Lock //216
	{
		Impl& i; //218
		const char* fn; //219

		Lock(Impl* i, const char* fn) : //221
			i(this->i), fn(this->fn)
		{
			/*int res; //224
			const int64_t currentMsec = from_msec(;
			const uint32_t elapsed;
			if (m_mutex->pthread_mutex_lock())
			{
				//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "%s: pthread_mutex_lock: %d"); //226
				abort();
			}*/
		};

		~Lock() //231
		{
			//pthread_mutex_unlock(i.m_mutex); //233
		}
	};

	void set() //237-242
	{
		Lock l(this, "set"); //239
		m_set = true; //240
		//pthread_cond_broadcast(m_cond); //241
	}

	void reset() //244-248
	{
		Lock l(this, "reset"); //246
		m_set = false; //247
	}

	void wait() //Not on iOS | Correct?
	{
		/*if (m_set)
			return;

		Lock l(this, "wait"); //assuming l;
		while (!m_set)
		{
			int res = pthread_cond_wait(m_cond, m_mutex);
			if (res)
			{
				LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "wait: pthread_cond_wait: %d", res); //259
				abort();
			}
		}*/
	}

	bool wait(uint32_t timeout_msec) //265-308 | TODO
	{
		return false;
		/*if (!m_set) //267
			return true;

		timespec ts; //270
		
		ts = from_msec(timeout_msec); //273
		const int64_t startMsec = System::currentTimeMillis(); //274

		Lock l(this, "wait(timeout)"); //282
		while (m_set) //283
		{
		}*/

		//int res; //287
		//const int64_t currentMsec; //288
		//const uint32_t elapsed; //289

		//from_msec(); //293
		
		//POSIX
		//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "wait(timeout): pthread_cond_wait: %d"); //302
		//abort(); //303

		return false;
	}

	p_thread_mutex_t m_mutex; //310
	pthread_cond_t m_cond; //311
	atomic<bool> m_set; //312 | TODO
};
#endif

Signal::Signal(bool set) //322
{
	m_impl = new Impl(set);
}

Signal::~Signal()
{
}

void Signal::set()
{
	m_impl->set(); //334
}

void Signal::reset()
{
	m_impl->reset(); //339
}

void Signal::wait()
{
	m_impl->wait();
}

bool Signal::wait(uint32_t timeout_msec) //347
{
	return m_impl->wait(timeout_msec);
}

}