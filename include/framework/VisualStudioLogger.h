#ifndef _FRAMEWORK_VISUALSTUDIOLOGGER_H
#define _FRAMEWORK_VISUALSTUDIOLOGGER_H

#include <lang/Log.h>

namespace framework
{

class VisualStudioLogger : //Only seen on Win32, given all the loggers tend to be at the root of the framework folder, we're gonna assume all of them are officially there, even this one.
	public lang::log::Listener
{
public:
	VisualStudioLogger();
	~VisualStudioLogger();

	void onLogEvent(const lang::log::Event& Event);
};

}

#endif