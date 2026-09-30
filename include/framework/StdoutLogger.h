#ifndef _FRAMEWORK_STDOUTLOGGER_H
#define _FRAMEWORK_STDOUTLOGGER_H

#include <lang/Log.h>
	
namespace framework //5
{
class StdoutLogger : //7 | iOS + Android only.
	public lang::log::Listener
{
public:
	StdoutLogger(); //11
	~StdoutLogger(); //12

	virtual void onLogEvent(const lang::log::Event& Event); //14
};

} // framework

#endif // _FRAMEWORK_STDOUTLOGGER_H