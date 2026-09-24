#include <framework/OSInterface.h>

namespace framework
{

OSInterface::~OSInterface() //7
{
	m_arguments.clear();
	m_argv.clear();
}

}