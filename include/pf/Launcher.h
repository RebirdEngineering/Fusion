#ifndef _PF_LAUNCHER_H
#define _PF_LAUNCHER_H

#include <lang/Object.h>

namespace pf
{

class LauncherDelegate //12
{
public:
	enum ResultValue { FAILED, SUCCEEDED, CANCELLED, UNKNOWN }; //15
	virtual void LauncherCompleted(ResultValue) = 0; //16
};

class Launcher : //24
	public lang::Object
{
public:
	Launcher(); //28

	~Launcher(); //30

	bool isSupported(); //35

	bool open(); //40

	bool openURL(const std::string& target); //47

	bool openProgram(const std::string& target); //53

	bool canOpenProgram(const std::string& target, const std::string& minVersion); //62

	bool openSMS(const std::string&, const std::string&, const std::string&, const std::string&); //67, unknown params.

	bool openEmail(const std::string&, const std::string&, const std::string&); //72, unknown params.

	bool canOpenEmail(); //77

	void setDelegate(LauncherDelegate*); //83, unknown param.
private:
	class LauncherImpl;
	P(LauncherImpl) m_impl; //88 | Impl sizes: [Win32+WP8: 16 bytes, iOS: 32 bytes, Android: 16 bytes]
	Launcher(const Launcher&); //89
	Launcher& operator=(const Launcher&); //90
};

}

#endif // !_PF_LAUNCHER_H