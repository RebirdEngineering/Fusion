#ifndef _PF_LOCALE_H
#define _PF_LOCALE_H

#include <lang/Object.h>

namespace pf
{

class Locale : public lang::Object //15 | This reeks of identical code
{
public:
	Locale(); //22

	~Locale(); //27

	bool isSupported(); //32

	std::vector<std::string> getPreferedLanguages(); //37
private:
	class LocaleImpl;
	P(LocaleImpl) m_impl; //42
	Locale(const Locale&); //43
	Locale& operator=(const Locale&); //44
};

}

#endif