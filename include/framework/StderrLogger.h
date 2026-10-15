#ifndef _FRAMEWORK_STDERRLOGGER_H
#define _FRAMEWORK_STDERRLOGGER_H

#include <lang/Log.h>

namespace framework
{

class StderrLogger : //Only seen in Android and ABTrilogii, given all the loggers tend to be at the root of the framework folder, we're gonna assume all of them are officially there, even this one.
	public lang::log::Listener
{
public:
	StderrLogger();
	~StderrLogger();

	void onLogEvent(const lang::log::Event& e);
};

} // framework

#endif // _FRAMEWORK_STDERRLOGGER_H