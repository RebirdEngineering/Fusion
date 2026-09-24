#ifndef _PF_LAUNCHER_H
#define _PF_LAUNCHER_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class LauncherDelegate
{
public:
	enum ResultValue { FAILED, SUCCEEDED, CANCELLED, UNKNOWN };
	virtual void LauncherCompleted(ResultValue) = 0;
};

class Launcher :
	public lang::Object
{
public:
	Launcher();

	~Launcher();

	bool isSupported();

	bool open();

	bool openURL(const std::string& target);

	bool openProgram(const std::string& target);

	bool canOpenProgram(const std::string& target, const std::string& minVersion);

	bool openSMS(const std::string&, const std::string&, const std::string&, const std::string&);

	bool openEmail(const std::string&, const std::string&, const std::string&);

	bool canOpenEmail();

	void setDelegate(LauncherDelegate*);
private:
	class LauncherImpl;
	P(LauncherImpl) m_impl;

	Launcher(const Launcher&);
	Launcher& operator=(const Launcher&);
};

}

#endif // !_PF_LAUNCHER_H