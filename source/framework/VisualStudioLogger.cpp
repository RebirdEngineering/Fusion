#include <framework/VisualStudioLogger.h>
#include <lang/Format.h>
#include <windows.h>

using namespace lang;

namespace framework
{

VisualStudioLogger::VisualStudioLogger()
{
	addListener(this);
}

VisualStudioLogger::~VisualStudioLogger()
{
	removeListener(this);
}

void VisualStudioLogger::onLogEvent(const log::Event& e)
{
	if (e.filename)
	{
		if (!e.tag.empty())
			OutputDebugStringA(Format("{0}({1}): [{2}] ({3}): {4}\n", e.filename, e.line, log::priorityToString(e.priority), e.tag, e.message).format().c_str());
		else
			OutputDebugStringA(Format("{0}({1}): [{2}]: {3}\n", e.filename, e.line, log::priorityToString(e.priority), e.message).format().c_str());
	}

	else if (!e.message.empty())
		OutputDebugStringA(e.message.c_str());
}

}