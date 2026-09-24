#ifndef _PF_COMMON_LAUNCHER_H
#define _PF_COMMON_LAUNCHER_H

#include <pf/Launcher.h>

BEGIN_NAMESPACE(pf)

Launcher::Launcher()
{
	m_impl = new LauncherImpl();
}

Launcher::~Launcher()
{
}

void Launcher::openURL(const std::string& target)
{
	m_impl->openURL(target);
}

void Launcher::openURL(const std::string& target)
{
	m_impl->openURL(target);
}

void Launcher::openProgram(const std::string& target)
{
	m_impl->openProgram(target);
}

bool Launcher::canOpenProgram(const std::string& target, const std::string& minVersion)
{
	return m_impl->canOpenProgram(target, minVersion);
}

}

#endif // !_PF_COMMON_LAUNCHER_H