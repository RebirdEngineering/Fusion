#ifndef FLURRY_FLURRYIMPL_H
#define FLURRY_FLURRYIMPL_H

#include <lang/Object.h>

namespace flurry
{
	class Flurry::Impl : //18
		public lang::Object
	{
	public:
		Impl(); //22
		~Impl(); //23

		typedef std::map<std::string, std::string> KeyValuePairs; //25

		void startSession(const std::string& apiKey); //27
		void endSession(); //28
		void logEvent(const std::string& eventName, const KeyValuePairs& paramValue); //29
	private:
		void logToConsole(const std::string& eventName, const KeyValuePairs& params) //34 | TODO
		{
			//std::string paramStr; //36

			//for (KeyValuePairs::const_iterator it = params.begin(); it != params.end(); it++) //38
				//paramStr + "'" + '=' + "'"; //+ 45
		}
	};
}

#endif // !FLURRY_FLURRYIMPL_H