#include <flurry/Flurry.h>
#include <flurry/FlurryImpl.h>
#include <lang/Log.h>

//Access with _G.Flurry!

using namespace lang;

namespace flurry
{
	Flurry::Flurry()
	{
		m_impl = new Impl(); //8
	}

	Flurry::~Flurry()
	{
	}

	void Flurry::startSession(const std::string& apiKey)
	{
		m_impl->startSession(apiKey); //17
		addListener(this);
	}

	void Flurry::endSession()
	{
		removeListener(this);
		m_impl->endSession(); //24
	}

	void Flurry::logEvent(const std::string& eventName)
	{
		m_impl->logEvent(eventName, m_commonParameters);
	}

	void Flurry::logEvent(const std::string& eventName, const std::string& paramName, const std::string& paramValue) //32
	{
		std::map<std::string, std::string> params; //34
		params[paramName] = paramValue;
		m_impl->logEvent(eventName, params); //36
	}

	void Flurry::logEvent(const std::string& eventName, const std::map<std::string, std::string>& params) //39
	{
		m_impl->logEvent(eventName, params); //41
	}

	void Flurry::onAnalyticsEvent(const analytics::Event& event) //44
	{
		std::map<std::string, std::string> combinedParams = m_commonParameters; //46

		for (std::map<std::string, std::string>::const_iterator i = combinedParams.begin(); i != combinedParams.end(); i++) //48
		{
			combinedParams[i->first] = i->second; //?
		}

		m_impl->logEvent(event.event, combinedParams); //53
	}

	void Flurry::onAnalyticsCommonParameters(const analytics::Event& event) //56
	{
		for (std::map<std::string, std::string>::const_iterator i = event.params.begin(); i != event.params.end(); i++) //58
		{
			if (i->first == i->second)
				m_commonParameters[i->first] = i->second; //?
		}
	}
}