#include <framework/StdoutLogger.h>

using namespace lang;

namespace framework
{

StdoutLogger::StdoutLogger() //33
{
	addListener(this);
}

StdoutLogger::~StdoutLogger()
{
	removeListener(this);
}

void StdoutLogger::onLogEvent(const log::Event& e) //40
{
	const char* color; //42, color to apply to printf call
	const char* reset; //43, this likely sets the color back?

#ifdef _DEBUG //Only exists in ABC 3.3.0-5.0.2 ads well as ABStella 1.0.3 on WinPhone8, console Trilogy and RCS plugins, maybe it's not debug only?
	auto supports_color = []()
	{
		return false; //Always? So this is just never used?
	};
	if ((supports_color() & 1) != 0)
	{
		color = "\x1B[0m";
		if (e.priority == LANG_LOG_PRIORITY_WARN)
		{
			reset = "\x1B[1m\x1B[33m";
		}
		else if (e.priority == LANG_LOG_PRIORITY_ERROR)
		{
			reset = "\x1B[1m\x1B[31m";
		}
	}
#endif

	if (e.filename) //59
	{
		if (!e.tag.empty()) //61
			printf("%s[%s] (%s): %s\n%s", color, log::priorityToString(e.priority), e.tag, e.message, reset); //64
		else
			printf("%s[%s]: %s\n%s", color, log::priorityToString(e.priority), e.message, reset); //69
	}

	else
		printf("%s%s%s", color, e.message, reset);

}

}