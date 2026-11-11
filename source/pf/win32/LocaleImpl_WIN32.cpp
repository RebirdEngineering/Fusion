#include <pf/Locale.h>

#include <windows.h>

using namespace lang;

namespace pf
{
	class Locale::LocaleImpl : public Object //Win32
	{
	public:
		LocaleImpl()
		{
		}

		bool isSupported()
		{
			return true;
		}

		std::vector<std::string> getPreferedLanguages() //4CBBE0 | Correct?
		{
			std::vector<std::string> langs;
			char localeData[20];

			int langName = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO639LANGNAME, localeData, 9);
			if (langName)
			{
				localeData[langName - 1] = '_';
				
				int countryName = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, &localeData[langName - 1], 9);
				if (countryName)
				{
					langs.push_back(localeData);
				}
			}

			if (!langs.size())
				langs.push_back("en_EN");

			return langs;
		}
	};

#include <pf/common/Locale.h>

}