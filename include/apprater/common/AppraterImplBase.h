#ifndef _FUSION_APPRATER_APPRATERIMPLBASE_H
#define _FUSION_APPRATER_APPRATERIMPLBASE_H

#include <apprater/Apprater.h>
#include <pf/AlertBox.h>
#include <util/RegistryAccessor.h>

namespace apprater
{

class AppraterAlertBoxListener
{
public:
	virtual void dialogDismissed(Apprater::Result result);
};

class AppraterImplBase :
	public Object
{
public:
	AppraterImplBase();

	void addTry();

	double getCurrentTime();

	bool needToPrompt();

	void dialogDismissed(Apprater::Result);

	void answer(Apprater::Result);

	void prompt(const std::string&, const std::string&, const std::string&, const std::string&, const std::tr1::is_function<void(Apprater::Result)>&);

	void userAnswered(Apprater::Result result, const std::tr1::is_function<void()>& callback);

	void setConfig(const Apprater::Config&);

	static std::tr1::is_function<void()> sm_launchRating;
	static std::tr1::is_function<void(Apprater::Result)> sm_callback;
	static Apprater::Config sm_usedConfig;
	static std::string sm_promptReason;

protected:
	static AppraterAlertBoxListener sm_alertBoxListener;
	static AlertBox sm_alertBox;
	static bool sm_promptActive; //253

private:
	std::string getShortenedVersionString(const std::string&);

	void storeString(const std::string&, const std::string&);

	void storeBool(const std::string&, bool);

	void storeInt(const std::string& keyString, int value)
	{
		RegistryAccessor registryAccessor;
		registryAccessor.registry()["fusion"] = keyString;
		registryAccessor.registry()["Apprater"] = value;
	}

	void storeDouble(const std::string&, double);

	std::string getStoredString(const std::string&, const std::string&);

	bool getStoredBool(const std::string&, bool);

	int getStoredInt(const std::string&, int);

	double getStoredDouble(const std::string&, double);
};

}

#endif