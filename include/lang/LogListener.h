#ifndef _LANG_LOGLISTENER_H
#define _LANG_LOGLISTENER_H

#include <lang/pp.h>

namespace lang {
namespace log {

struct Event //15 | 32 bytes on iOS
{
	int64_t timestamp; //17
	const char* filename; //18
	const char* function; //19
	int line; //20
	int priority; //21
	std::string message; //22
	std::string tag; //23
};

class Listener
{
public:
	virtual void onLogEvent(const Event&) = 0; //35

	virtual ~Listener(); //37
};

}

namespace analytics {

struct Event 
{
	int64_t timestamp; //67
	std::string event; //68
	std::map<std::string, std::string> params; //69
};

class Listener //75
{
public:
	virtual void onAnalyticsEvent(const Event&) = 0; //81

	virtual void onAnalyticsCommonParameters(const Event&) = 0; //86

	virtual ~Listener(); //88
};

}
}

#endif