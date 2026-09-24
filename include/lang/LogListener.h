#ifndef _LANG_LOGLISTENER_H
#define _LANG_LOGLISTENER_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)
BEGIN_NAMESPACE(log)

struct Event
{
public:
	int64_t timestamp;
	const char* filename;
	const char* function;
	int line;
	int priority;
	std::string message;
	std::string tag;
};

class Listener
{
public:
	virtual void onLogEvent(const Event&) = 0;
	virtual ~Listener();
};

}
BEGIN_NAMESPACE(analytics)

class Event
{
public:
	int64_t timestamp;
	std::string event;
	std::map<std::string, std::string> params;
};

class Listener
{
public:
	virtual void onAnalyticsEvent(const Event&) = 0;

	virtual void onAnalyticsCommonParameters(const Event&) = 0;

	virtual ~Listener();
};

}
}

#endif