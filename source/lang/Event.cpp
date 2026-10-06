#include <lang/detail/Event.h>
#include <lang/Mutex.h>

namespace lang
{
namespace event
{

static Event<void(std::function<void()>)> RUN; //10

Link::Link(const std::function<Status(Link*, Status)>& func) //12
{
	//m_changeStatus.assign(func, 2);
	m_status = DISCONNECTED;
}

Link::~Link()
{
	disconnect();
	//m_status = DESTRUCTED;
	//if (m_changeStatus)
		//m_changeStatus.assign(m_status, DISCONNECTED + DESTRUCTED);
}

void Link::connect()
{
	//if (!m_changeStatus) //?
		//throw();

	//m_changeStatus.assign(m_status, CONNECTED);
}

void Link::disconnect()
{
	//if (!m_changeStatus) //?
		//throw();

	//m_changeStatus.assign(m_status, DISCONNECTED);
}

static Mutex s_mutex; //40
static size_t nextEvent; //41
static std::vector<std::pair<float, std::function<void()>>> s_staging; //42
static std::vector<std::pair<float, std::function<void()>>> s_queue; //43

namespace detail
{
	event_id_t getNextID() //48
	{
		static event_id_t id; //50
		return id++;
	}

	void addQueue(float delay, std::function<void()> const& event) //54
	{
		Mutex::Lock lock(s_mutex); //56
		s_staging.push_back(std::make_pair(delay, event));
	}

	void destructLink(Link* link) //60
	{
		delete link;
	}
}

void process(float dt) //66
{
	//P(Link)(RUN); //68 operator()
	// 
	//Mutex::Lock(s_mutex);
	//operator(); //90
}

}
}
//}