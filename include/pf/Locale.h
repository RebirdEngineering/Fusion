#ifndef _PF_LOCALE_H
#define _PF_LOCALE_H

#include <lang/Object.h>

namespace pf
{

class Locale : public lang::Object //15 | Win, This reeks of identical code
{
public:
	Locale(); //22

	~Locale(); //27

	bool isSupported(); //32

	std::vector<std::string> getPreferedLanguages(); //37
private:
	class LocaleImpl;
	P(LocaleImpl) m_impl; //42 | Impl sizes: [Win32: 12 bytes {Win32}, Android: 12 bytes {Android}, WP8+OSX: 12 bytes {DUMMY}]
	Locale(const Locale&); //43
	Locale& operator=(const Locale&); //44
};

}

#endif