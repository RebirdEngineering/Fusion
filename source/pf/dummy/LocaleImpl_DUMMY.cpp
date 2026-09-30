#include <pf/Locale.h>

using namespace lang;

namespace pf
{
	class Locale::LocaleImpl : public Object //WP8+OSX
	{
	public:
		LocaleImpl()
		{
		}

		~LocaleImpl()
		{
		}

		bool isSupported()
		{
			return false;
		}

		std::vector<std::string> getPreferedLanguages()
		{
			std::vector<std::string> langs;
			langs.push_back("en_EN");

			return langs;
		}
	};

#include <pf/common/Locale.h>

}