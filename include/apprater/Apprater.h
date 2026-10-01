#ifndef _FUSION_APPRATER_APPRATER_H
#define _FUSION_APPRATER_APPRATER_H

#include <lang/Object.h>

namespace apprater
{
	class Apprater : //20 | Apple only.
		public lang::Object
	{
	public:
		bool isSupported(); //28

		enum Result //30
		{
			YES,
			NO,
			LATER,
		};
        
		struct Config //35
		{
			std::string iTunesAppId; //37
			double daysUntilPromptFirst; //38
			double daysUntilPromptLater; //39
			int triesUntilPromptFirst; //40
			int triesUntilPromptLater; //41

			Config(); //43
		};
		bool check(const Config& config); //60

		void prompt(const std::string& message, const std::string& yes, const std::string& no, const std::string& later, std::tr1::is_function<void(Result)>& callback, const std::string& promptReason); //69

		void answer(Result); //85
	};
}

#endif