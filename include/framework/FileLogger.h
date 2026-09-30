#ifndef _FRAMEWORK_FILELOGGER_H
#define _FRAMEWORK_FILELOGGER_H

#include <lang/Log.h>

//Android only.

//BEGIN_NAMESPACE(lang) BEGIN_NAMESPACE(log) struct Event; class Listener; } }
	
namespace framework
{

class FileLogger :
	public lang::log::Listener
{
public:
	FileLogger();
	~FileLogger();

	virtual void onLogEvent(const NS(lang::log, Event)& Event);
};

END_NAMESPACE() // framework

#endif // _FRAMEWORK_FILELOGGER_H