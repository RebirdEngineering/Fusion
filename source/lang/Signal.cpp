#include <lang/Signal.h>
#include <lang/Exception.h>
#include <time.h>
#include <lang/Log.h>

const int64_t NSEC_BY_MSEC = 1000000;

const int64_t NSEC_BY_SEC = 1000000000;

auto from_msec = [](uint32_t msec)
{
	timespec ret;
	int64_t nsec_total;
	int64_t nsec_rem;
	uint32_t set_total;
	return ((NSEC_BY_MSEC * msec - NSEC_BY_MSEC * msec % NSEC_BY_SEC) / NSEC_BY_MSEC);
};

BEGIN_NAMESPACE(lang)

class Signal::Impl
{
public:
	Impl(bool set)
	{
		/*m_set.value.value = set;
		//if ()

		throwError(Exception(Format("lang::Signal: pthread_mutex_init: {0}", )));
		throwError(Exception(Format("lang::Signal: pthread_condattr_init: {0}", )));
		throwError(Exception(Format("lang::Signal: pthread_cond_init: {0}", )));*/

		//pthread_condattr_destroy();
	}

	~Impl()
	{
	}

	class Lock
	{
	public:
		Impl* i;
		const char* fn;
		Lock(Impl* i, const char* fn)
		{
			/*int res;
			const int64_t currentMsec = from_msec(;
			const uint32_t elapsed;
			if (m_mutex->pthread_mutex_lock())
			{
				LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "%s: pthread_mutex_lock: %d"); //190?
				abort();
			}*/
		};

		~Lock()
		{
			//pthread_mutex_unlock();
		}
	};

	void set()
	{
		LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "%s: pthread_mutex_lock: %d", ); //226
		Lock l(this, "set");
		//int res =
		//m_set(1);
		//pthread_condattr_t attr = m_cond;
		//pthread_cond_broadcast(m_cond)
	}

	void reset()
	{
		Lock l(this, "reset");
		//pthread_mutex_unlock()
	}

	void wait()
	{
	}

	bool wait(uint32_t timeout_msec)
	{
		/*timespec ts;

		const int64_t startMsec = from_msec(timeout_msec);

		ts.tv_sec = startMsec;
		ts.tv_nsec = from_msec(startMsec); //?

		Lock l(this, "wait(timeout)");*/

		//LANG_LOG("lang::Signal", LANG_LOG_PRIORITY_ERROR, "wait(timeout): pthread_cond_wait: %d");
		return false;
	}
};

Signal::Signal(bool set)
{
	m_impl = new Impl(set);
}

Signal::~Signal()
{
}

void Signal::set()
{
	m_impl->set();
}

void Signal::reset()
{
	m_impl->reset();
}

void Signal::wait()
{
	m_impl->wait();
}

bool Signal::wait(uint32_t timeout_msec)
{
	return m_impl->wait(timeout_msec);
}

}