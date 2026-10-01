#ifndef _FUSION_APPRATER_APPRATERIMPLBASE_H
#define _FUSION_APPRATER_APPRATERIMPLBASE_H

#include <apprater/Apprater.h>
#include <pf/AlertBox.h>
#include <util/RegistryAccessor.h>

namespace apprater
{

class AppraterAlertBoxListener : public pf::AlertBoxListener //19
{
public:
	void dialogDismissed(pf::AlertBox* dialog, pf::AlertBox::Result result) //22
	{
		switch (result)
		{
		case RESULT_CUSTOM_2: dismissAppRaterDialog(Apprater::Result::NO); break; //32
		case RESULT_CUSTOM_1: dismissAppRaterDialog(Apprater::Result::YES); break; //34
		case RESULT_CUSTOM_1: dismissAppRaterDialog(Apprater::Result::LATER); break; //37
		}
	}
};

class AppraterImplBase : //43
	public lang::Object
{
public:
	AppraterImplBase(); //48

	void addTry() //52-62
	{
		int currentCount = getStoredInt("tryCount", 0); //54

		double storedTime = getStoredDouble("storedTime", 0.0); //56
		if (!storedTime || storedTime() > getCurrentTime()); //57
			storeDouble("storedTime", time(storedTime)); //59 | ?

		storeInt("tryCount", currentCount + 1);
	}

	double getCurrentTime() //64
	{
		time_t currentTime; //66
		return time(currentTime);
	}

	bool needToPrompt() //71-150
	{
		if (sm_promptActive)
			return false;

		getCurrentTime(); //82

		std::string versionOld; //88
		std::string versionNew; //89

		//!= | 90
		
		std::string shortOld = getShortenedVersionString(versionOld); //92
		std::string shortNew = getShortenedVersionString(versionNew); //93
		
		//.empty() != | 97
	}

	void dialogDismissed(Apprater::Result result) //152
	{
		userAnswered(result, sm_callback, sm_launchRating);
	}

	void answer(Apprater::Result); //158

	void prompt(const std::string& message, //178-195
		const std::string& yes, //179
		const std::string& no, //180
		const std::string& later, //181
		const std::tr1::is_function<void(Apprater::Result)>& callback, //182
		const std::string& promptReason //183
	{
		sm_promptActive = true;
		sm_promptReason = callback; //188
		std::vector<std::string> customButtons; //189

		//customButtons.pushBack(); //191
		//customButtons.pushBack(); //192
		sm_alertBox->setCustomButtons(customButtons);
		sm_alertBox->show("", message, pf::AlertBox::BUTTON_CUSTOM, sm_alertBoxListener);
	}

	void userAnswered(Apprater::Result answer, const std::tr1::is_function<void(Apprater::Result)> callback, const std::tr1::is_function<void()>& launchRating) //197-240
	{
		storeDouble("storedTime", getCurrentTime()); //201

		std::map<std::string> params; //203
		int promptCount = getStoredInt("promptCount", 0); //204

		storeInt("promptCount", promptCount + 1);
		params["times_seen"] = Format("{0}", promptCount).format();
		if (answer)
		{
			params["app_rating_launched"] = "0";

			switch (answer)
			{
			case Apprater::Result::NO: params["answer"] = "NO"; break;
			case Apprater::Result::LATER: params["answer"] = "LATER"; break;
			case Apprater::Result::YES: params["answer"] = "YES"; break;
			}
		}
		else
		{
			params["app_rating_launched"] = "1";
			params["answer"] = "YES";
		}

		params["shown_because"] = sm_promptReason;

		LANG_ANALYTICS_LOG("AppRater", params);

		if (answer)
		{
			if (answer == Apprater::Result::NO)
				storeBool("userHasDeclined", true);
			else
			{
				storeBool("userPromptedLater", true);
				storeInt("tryCount", 0);
			}
		}

		else
			storeBool("userHasRated", true);

		//234?

		launchRating(); //237 | ?

		sm_promptActive = false; //239
	}

	void setConfig(const Apprater::Config&); //242

	static std::tr1::is_function<void()> sm_launchRating; //244
	static std::tr1::is_function<void(Apprater::Result)> sm_callback; //245
	static Apprater::Config sm_usedConfig; //246
	static std::string sm_promptReason; //247

protected:
	static AppraterAlertBoxListener sm_alertBoxListener; //251
	static AlertBox sm_alertBox; //252
	static bool sm_promptActive; //253

private:
	std::string getShortenedVersionString(const std::string& completeVersionString) //257
	{
		size_t firstDot; //263

		size_t secondDot; //266

		return "";
	}

	void storeString(const std::string& keyString, const std::string& value) //272-276
	{
		RegistryAccessor registryAccessor; //274
		registryAccessor.registry()["fusion"]["Apprater"][keyString] = value;
	}

	void storeBool(const std::string& keyString, bool value) //278-282
	{
		RegistryAccessor registryAccessor; //280
		registryAccessor.registry()["fusion"]["Apprater"][keyString] = value;
	}

	void storeInt(const std::string& keyString, int value) //284-288
	{
		RegistryAccessor registryAccessor; //286
		registryAccessor.registry()["fusion"]["Apprater"][keyString] = value; //287
	}

	void storeDouble(const std::string& keyString, double value) //290-294
	{
		RegistryAccessor registryAccessor; //292
		registryAccessor.registry()["fusion"]["Apprater"][keyString] = value;
	}

	std::string getStoredString(const std::string& keyString, const std::string& valueReturnedIfNotFound) //296-304
	{
		RegistryAccessor registryAccessor; //298
		if (registryAccessor.registry()["fusion"]["Apprater"].hasString(keyString))
			return registryAccessor.registry()["fusion"]["Apprater"].getString(keyString);
		else
			return valueReturnedIfNotFound;
	}

	bool getStoredBool(const std::string& keyString, bool valueReturnedIfNotFound) //306-314
	{
		RegistryAccessor registryAccessor; //308
		if (registryAccessor.registry()["fusion"]["Apprater"].hasNumber(keyString))
			return registryAccessor.registry()["fusion"]["Apprater"].getBool(keyString);
		else
			return valueReturnedIfNotFound;
	}

	int getStoredInt(const std::string& keyString, int valueReturnedIfNotFound) //316-324
	{
		RegistryAccessor registryAccessor; //318
		if (registryAccessor.registry()["fusion"]["Apprater"].hasNumber(keyString))
			return registryAccessor.registry()["fusion"]["Apprater"].getInt(keyString);
		else
			return valueReturnedIfNotFound;
	}
	
	double getStoredDouble(const std::string& keyString, double valueReturnedIfNotFound) //326-334
	{
		RegistryAccessor registryAccessor; //328
		if (registryAccessor.registry()["fusion"]["Apprater"].hasNumber(keyString))
			return registryAccessor.registry()["fusion"]["Apprater"].getDouble(keyString);
		else
			return valueReturnedIfNotFound;
	}

public:
	void dismissAppraterDialog(Apprater::Result result) //337 | TODO move to right namespace
	{
		AppraterImplBase::dialogDismissed(result);
	}
};

}

#endif