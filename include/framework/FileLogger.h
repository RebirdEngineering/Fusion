#ifndef _FRAMEWORK_FILELOGGER_H
#define _FRAMEWORK_FILELOGGER_H

#include <lang/Log.h>

//Android only.

//BEGIN_NAMESPACE(lang) BEGIN_NAMESPACE(log) struct Event; class Listener; } }
	class OutputStream;
}
	
namespace framework
{

class FileLogger : //Trilogii and Android only, given all the loggers tend to be at the root of the framework folder, we're gonna assume all of them are officially there, even this one.
	public lang::log::Listener
{
public:
	FileLogger();
	~FileLogger();

	void onLogEvent(const lang::log::Event& e);

private:
	lang::Ptr<io::OutputStream> m_output;
};

} // framework

#endif // _FRAMEWORK_FILELOGGER_H