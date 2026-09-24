#include <flurry/FlurryImpl.h>
#include <lang/Log.h>

//Access with _G.Flurry!

using namespace lang;

namespace flurry
{
	Flurry::Flurry()
	{
		m_impl = new Impl();
	}

	Flurry::~Flurry()
	{
	}

	void Flurry::startSession(const std::string& apiKey)
	{
		m_impl->startSession(apiKey);
		addListener(this);
	}

	void Flurry::endSession()
	{
		removeListener(this);
		m_impl->endSession();
	}

	void Flurry::logEvent(const std::string& eventName, const std::string& paramName, const std::string& paramValue)
	{
		std::map<std::string, std::string> params;
		params[paramName] = paramValue;
		m_impl->logEvent(eventName, params);
	}

	void Flurry::onAnalyticsEvent(const lang::analytics::Event& event)
	{
		std::map<std::string, std::string> combinedParams = m_commonParameters;

		for (std::map<std::string, std::string>::const_iterator i = combinedParams.begin(); i != combinedParams.end(); i++)
		{
			combinedParams[i->first] = i->second; //?
		}

		m_impl->logEvent(event.event, combinedParams);
	}

	void Flurry::logEvent(const std::string& eventName, const std::map<std::string, std::string>& params)
	{
		m_impl->logEvent(eventName, params);
	}

	void Flurry::onAnalyticsCommonParameters(const lang::analytics::Event& event)
	{
		for (std::map<std::string, std::string>::const_iterator i = event.params.begin(); i != event.params.end(); i++)
		{
			if (i->first == i->second)
				m_commonParameters[i->first] = i->second; //?
		}
	}
}