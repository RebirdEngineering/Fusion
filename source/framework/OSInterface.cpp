#include <framework/OSInterface.h>

namespace framework
{

OSInterface::~OSInterface()
{
	m_arguments.clear(); //7
	m_argv.clear(); //8
}

}