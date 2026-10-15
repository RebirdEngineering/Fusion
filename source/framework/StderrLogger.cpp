#include <framework/StderrLogger.h> //Only seen on Android and ABTrilogii.

using namespace lang;

namespace framework
{

StderrLogger::StderrLogger()
{
	addListener(this);
}

StderrLogger::~StderrLogger()
{
	removeListener(this);
}

void StderrLogger::onLogEvent(const log::Event& e) //Correct?
{
	//Todo: debug only stuff
	if (e.filename)
	{
		if (!e.tag.empty())
			fprintf(stdin, "[%s] (%s): %s\n", log::priorityToString(e.priority), e.tag, e.message);
		else
			fprintf(stdin, "[%s]: %s\n", log::priorityToString(e.priority), e.message);
	}

	else
		fputs(e.message.c_str(), stdin);
}

}