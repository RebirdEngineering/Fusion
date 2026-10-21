#include <lang/Signal.h>
//#include <lang/Atomic.h>
#include <lang/Exception.h>
#include <time.h>
#include <lang/Log.h>

const int64_t NSEC_BY_SEC = 1000000000; //143

const int64_t NSEC_BY_MSEC = 1000000; //145

auto from_msec = [](uint32_t msec) //157
{
	timespec ret; //159
	int64_t nsec_total; //160
	int64_t nsec_rem; //161
	uint32_t set_total; //162
	return ((NSEC_BY_MSEC * msec - NSEC_BY_MSEC * msec % NSEC_BY_SEC) / NSEC_BY_MSEC);
};

BEGIN_NAMESPACE(lang)

class Signal::Impl //172
{
public:
	Impl(bool set) //174
	{
		/*m_set.value.value = set;
		//if ()

		throwError(Exception(Format("lang::Signal: pthread_mutex_init: {0}", )));
		throwError(Exception(Format("lang::Signal: pthread_condattr_init: {0}", )));
		throwError(Exception(Format("lang::Signal: pthread_cond_init: {0}", )));*/

		//pthread_condattr_destroy();
	}

	~Impl() //210
	{
	}

	struct Lock //216
	{
		Impl& i; //218
		const char* fn; //219

		Lock(Impl* i, const char* fn) : i(this->i), fn(this->fn) //221
		{
			/*int res; //224
			const int64_t currentMsec = from_msec(;
			const uint32_t elapsed;
			if (m_mutex->pthread_mutex_lock())
			{
				//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "%s: pthread_mutex_lock: %d"); //190?
				abort();
			}*/

			//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "%s: pthread_mutex_lock: %d", ); //226
		};

		~Lock() //231
		{
			//pthread_mutex_unlock();
		}
	};

	void set() //237
	{
		Lock l(this, "set"); //239
		m_set = true;
		//int res =
		//m_set(1);
		//pthread_condattr_t attr = m_cond;
		//pthread_cond_broadcast(m_cond)
	}

	void reset() //244
	{
		Lock l(this, "reset"); //246
		//pthread_mutex_unlock(m_mutex);
	}

	void wait() //250
	{
	}

	bool wait(uint32_t timeout_msec) //265
	{
		/*timespec ts; //270
		
		const int64_t startMsec = from_msec(timeout_msec); //274

		Lock l(this, "wait(timeout)"); //282

		int res; //287
		const int64_t currentMsec; //288
		const int64_t elapsed; //289

		ts.tv_sec = startMsec;
		ts.tv_nsec = from_msec(startMsec); //?

		*/

		//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "wait(timeout): pthread_cond_wait: %d");
		return false;
	}

#ifdef _WIN32
	
#else
	p_thread_mutex_t m_mutex; //310
	pthread_cond_t m_cond; //311
#endif
	/*atomic<*/bool/*>*/ m_set; //312 | TODO
};

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