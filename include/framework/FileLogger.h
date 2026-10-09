#ifndef _FRAMEWORK_FILELOGGER_H
#define _FRAMEWORK_FILELOGGER_H

#include <lang/Log.h>
#include <io/OutputStream.h>

//Android only.

//BEGIN_NAMESPACE(lang) BEGIN_NAMESPACE(log) struct Event; class Listener; } }
	
namespace framework
{

class FileLogger : //Trilogii and Android only, given all the loggers tend to be at the root of the framework folder, we're gonna assume all of them are officially there, even this one.
	public lang::log::Listener
{
public:
	FileLogger();
	~FileLogger();

	void onLogEvent(const NS(lang::log, Event)& Event);

private:
	P(io::OutputStream) m_output;
};

} // framework

#endif // _FRAMEWORK_FILELOGGER_H