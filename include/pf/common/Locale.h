#ifndef _PF_COMMON_LOCALE_H
#define _PF_COMMON_LOCALE_H

#include <pf/Locale.h>

BEGIN_NAMESPACE(pf)

Locale::Locale()
{
	m_impl = new LocaleImpl();
}

Locale::~Locale()
{
}

std::vector<std::string> Locale::getPreferedLanguages()
{
	return m_impl->getPreferedLanguages();
}

}

#endif