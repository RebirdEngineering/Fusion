#ifndef _FRAMEWORK_FILELOGGER_H
#define _FRAMEWORK_FILELOGGER_H

#include <lang/Log.h>

//Android only.

//BEGIN_NAMESPACE(lang) BEGIN_NAMESPACE(log) struct Event; class Listener; } }
	
BEGIN_NAMESPACE(framework)

class FileLogger :
	public lang::log::Listener
{
public:
	FileLogger();
	~FileLogger();

	virtual void onLogEvent(const NS(lang::log, Event)& Event);
};

} // framework

#endif // _FRAMEWORK_STDOUTLOGGER_H