#include <lang/Log.h>
#include <lang/System.h>
#include <lang/Mutex.h>
#include <stdarg.h>
#include <time.h>

namespace lang
{

int64_t getTimestamp() //17
{
	static int64_t baseline = 1000 * time(0); //20
	int64_t counter = System::currentTimeMillis(); //? //21
	return counter + baseline;
}

namespace analytics
{
static std::set<Listener*>* s_listeners; //148

static void log(const std::string& eventname, const std::map<std::string, std::string>& params) //151
{
	if (!s_listeners)
		return;
	Event entry;
	entry.timestamp = getTimestamp();
	std::set<Listener*>::const_iterator it = s_listeners->begin();
	while (it != s_listeners->end())
	{
		if (s_listeners != 0)
			s_listeners->insert(*it);
		it++;
	}
}

static void addListener(Listener* listener) //179
{
	if (!s_listeners)
		s_listeners = new std::set<Listener*>;

	s_listeners->insert(listener);
}

static void removeListener(Listener* listener) //187
{
	if (!s_listeners)
		return;
	if (s_listeners->empty())
		return;
	if (s_listeners)
		delete s_listeners;
	s_listeners = 0;
}

}

BEGIN_NAMESPACE(log)

class Data
{
public:
	Data();
	std::set<Listener*> listeners;
	std::vector<char> buffer;
	Mutex mutex;
};

static Data* s_data;

static std::string stringify(const char* fmt, va_list args)
{
	s_data->mutex.lock();
	if (vsnprintf(s_data->buffer.data(), s_data->buffer.size(), fmt, args) + 1 < 0)
		return "encoding error";
	if (vsnprintf(s_data->buffer.data(), s_data->buffer.size(), fmt, args) + 1 > s_data->buffer.size())
	{
		s_data->buffer.resize(vsnprintf(s_data->buffer.data(), s_data->buffer.size(), fmt, args) + 1);
		vsnprintf(s_data->buffer.data(), s_data->buffer.size(), fmt, args) + 1; //?
	}
	return s_data->buffer.data(); //?
}

static void log(const std::string& tag, const char* file, const char* function, int line, int priority, const char* message, ...) //TODO
{
	if (!s_data)
		return;
	Event entry;
	entry.timestamp = getTimestamp();
	entry.tag = tag;
	entry.filename = file;
	entry.function = function;
	entry.line = line;
	entry.priority = priority;

	va_list args;
	va_start(args, message);

	entry.message = stringify(message, args);

	std::set<Listener*>::const_iterator it = s_data->listeners.begin();

	while (it != s_data->listeners.end())
	{
		s_data->listeners.insert(*it);
		it++;
	}
}

static void addListener(Listener* listener)
{
	s_data->listeners.insert(listener);
}

static void removeListener(Listener* listener)
{
	if (!s_data)
		return;
	s_data->listeners.erase(listener);
	delete s_data; //?
	s_data = 0; //?
}

static const char* priorityToString(int prio)
{
	switch (prio)
	{
	case 0: return "AUDIT";
	case 1: return "ERROR";
	case 2: return "WARNING";
	case 3: return "INFO";
	case 4: return "DEBUG";
	case 5: return "VERBOSE";
	default: return "UNKNOWN";
	}
}

}
}