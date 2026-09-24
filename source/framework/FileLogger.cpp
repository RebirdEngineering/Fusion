#include <framework/FileLogger.h> //Only seen in ABTrilogii and Android.

using namespace lang;

namespace framework
{

FileLogger::FileLogger() //UNOFFICIAL
{
	addListener(this);
}

FileLogger::~FileLogger() //UNOFFICIAL
{
	removeListener(this);
}

void FileLogger::onLogEvent(const log::Event& e) //UNOFFICIAL
{
}

}