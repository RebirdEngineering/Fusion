#ifndef _PF_APPSETTINGS_H
#define _PF_APPSETTINGS_H

#include <lang/Object.h>

namespace pf
{

class AppSettings : //14
	public lang::Object
{
public:
	explicit AppSettings(); //21

	~AppSettings(); //26

	bool isSupported(); //31

	bool isBoolean(const std::string& key) const; //36

	bool isString(const std::string& key) const; //41

	bool isNumber(const std::string& key) const; //46

	bool getBoolean(const std::string& key) const; //51

	double getNumber(const std::string& key) const; //56

	std::string getString(const std::string& key) const; //61
private:
	class AppSettingsImpl;
	P(AppSettingsImpl) m_impl; //66
	AppSettings(const AppSettings&); //67
	AppSettings& operator=(const AppSettings&); //68
};

}

#endif // !_PF_APPSETTINGS_H