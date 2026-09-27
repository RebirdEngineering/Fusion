#ifndef _PF_COMMON_LAUNCHER_H
#define _PF_COMMON_LAUNCHER_H

Launcher::Launcher()
{
	m_impl = new LauncherImpl(); //8
}

Launcher::~Launcher()
{
}

bool Launcher::isSupported()
{
	return m_impl->isSupported();
}

bool Launcher::open()
{
	return m_impl->isSupported();
}

bool Launcher::openURL(const std::string& target) //25
{
	return m_impl->openURL(target); //27
}

bool Launcher::openProgram(const std::string& target) //30
{
	return m_impl->openProgram(target); //32
}

bool Launcher::canOpenProgram(const std::string& target, const std::string& minVersion) //35
{
	return m_impl->canOpenProgram(target, minVersion);
}

bool Launcher::openSMS(const std::string&, const std::string&, const std::string&, const std::string&)
{
	return false; //m_impl->openSMS(?, ?, ?, ?);
}

bool Launcher::openEmail(const std::string&, const std::string&, const std::string&)
{
	return false; //m_impl->openEmail(?, ?, ?, ?);
}

bool Launcher::canOpenEmail()
{
	return m_impl->canOpenEmail();
}

void Launcher::setDelegate(LauncherDelegate*)
{
	//m_impl->setDelegate();
}

#endif // !_PF_COMMON_LAUNCHER_H