#include <lang/detail/Event.h>
#include <lang/Mutex.h>

namespace lang
{
namespace event
{

static Event<void(std::function<void()>)> RUN; //Line 10

static Mutex s_mutex;
static size_t nextEvent;
static std::vector<std::pair<float, std::function<void()>>> s_staging;
static std::vector<std::pair<float, std::function<void()>>> s_queue;

BEGIN_NAMESPACE(detail)

//inline P(Link) listen(Event<void(function<void()>, )
//{
//}

void addQueue(float delay, std::function<void()> const& event)
{
	Mutex::Lock lock(s_mutex);
	//s_staging.push_back(std::make_pair<float, std::tr1::function<void>(delay, event));
}

void destructLink(Link* link)
{
	//link->m_status = Link::DESTRUCTED;
}

void process(float dt)
{
	P(Link) link;
	//Mutex::Lock(s_mutex);
	//operator();
}

event_id_t getNextID()
{
	event_id_t id;
	return id;
}

}
}
}