#ifndef _FUSION_APPRATER_APPRATER_H
#define _FUSION_APPRATER_APPRATER_H

#include <lang/pp.h>

namespace apprater
{
	class Apprater :
		public lang::Object
	{
	public:
		bool isSupported();
		enum Result
		{
			YES,
			NO,
			LATER,
		};
		struct Config
		{
#ifdef PLATFORM_IOS
			std::string iTunesAppId; //Only on iOS.
#endif
			double daysUntilPromptFirst;
			double daysUntilPromptLater;
			int triesUntilPromptFirst;
			int triesUntilPromptLater;

			Config();
		};
		bool check(const Config& config);

		void prompt(const std::string& message, const std::string& yes, const std::string& no, const std::string& later, std::tr1::is_function<void(Result)>& callback, const std::string& promptReason);

		void answer(Result);
	};
}

#endif