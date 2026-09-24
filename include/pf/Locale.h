#ifndef _PF_LOCALE_H
#define _PF_LOCALE_H

#include <lang/Object.h>

namespace pf
{

class Locale : public lang::Object //This reeks of identical code
{
public:
	Locale();

	~Locale();

	bool isSupported();

	std::vector<std::string> getPreferedLanguages();
private:
	class LocaleImpl;
	P(LocaleImpl) m_impl;

	Locale(const Locale&);
	Locale& operator=(const Locale&);
};

}

#endif