#ifndef FLURRY_FLURRY_H
#define FLURRY_FLURRY_H

#include <lang/LogListener.h>
#include <lang/Object.h>

namespace flurry
{

class Flurry : //26
	public lang::Object, public lang::analytics::Listener
{
public:
	Flurry(); //30
	~Flurry(); //31

	void startSession(const std::string& apiKey); //37

	void endSession(); //42

	void logEvent(const std::string& eventName); //48

	void logEvent(const std::string& eventName, const std::string& paramName, const std::string& paramValue); //56

	void logEvent(const std::string& eventName, const std::map<std::string, std::string>& params); //63

	void onAnalyticsEvent(const lang::analytics::Event& event); //69

	void onAnalyticsCommonParameters(const lang::analytics::Event& event); //75
private:
	class Impl;
	P(Impl) m_impl; //80
	std::map<std::string, std::string> m_commonParameters; //81

	Flurry(const Flurry&); //83
	Flurry& operator=(const Flurry&); //84
};

}

#endif // !FLURRY_FLURRY_H