#ifndef _FRAMEWORK_ANDROIDLOGGER_H
#define _FRAMEWORK_ANDROIDLOGGER_H

#include <lang/Log.h>

namespace framework
{
	class AndroidLogger : //Given all the loggers tend to be at the root of the framework folder, we're gonna assume all of them are officially there, even this one.
		public lang::log::Listener
	{
	public:
		AndroidLogger();
		~AndroidLogger();

		void onLogEvent(const lang::log::Event& Event);
	};

}

#endif