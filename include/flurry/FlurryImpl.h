#ifndef FLURRY_FLURRYIMPL_H
#define FLURRY_FLURRYIMPL_H

#include <lang/Object.h>
#include <flurry/Flurry.h>

namespace flurry
{
	class Flurry::Impl : //18
		public lang::Object
	{
	public:
		Impl();
		~Impl();

		typedef std::map<std::string, std::string> KeyValuePairs; //25

		void startSession(const std::string& apiKey);
		void endSession();
		void logEvent(const std::string& eventName, const KeyValuePairs& paramValue);
	private:
		void logToConsole(const std::string& eventName, const KeyValuePairs& params)
		{
			std::string paramStr;
			for (KeyValuePairs::const_iterator it = params.begin(); it != params.end(); it++)
			{
				//paramStr.append(it->first);
			}
		}
	};
}

#endif // !FLURRY_FLURRYIMPL_H