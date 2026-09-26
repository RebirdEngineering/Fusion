#ifndef FLURRY_FLURRY_H
#define FLURRY_FLURRY_H

#include <lang/LogListener.h>
#include <lang/Object.h>

namespace flurry
{

class Flurry :
	public lang::Object, public lang::analytics::Listener
{
public:
	Flurry();
	~Flurry();

	void startSession(const std::string& apiKey);

	void endSession();

	void logEvent(const std::string&);

	void logEvent(const std::string& eventName, const std::string& paramName, const std::string& paramValue);

	void logEvent(const std::string& eventName, const std::map<std::string, std::string>& params);

	void onAnalyticsEvent(const lang::analytics::Event& event);

	void onAnalyticsCommonParameters(const lang::analytics::Event& event);
private:
	class Impl;
	P(Impl) m_impl;
	std::map<std::string, std::string> m_commonParameters;

	Flurry(const Flurry&);
	Flurry& operator=(const Flurry&);
};

}

#endif // !FLURRY_FLURRY_H