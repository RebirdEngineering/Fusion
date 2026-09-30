#ifndef _PF_ALERTBOX_H
#define _PF_ALERTBOX_H

#include <lang/Object.h>

namespace pf //8
{

class AlertBoxListener;

class AlertBox : //22 | No RTTI on Seasons 4.1.0 Win and WP8! Doesn't exist?
	public lang::Object
{
public:
	enum Button //26
	{
		BUTTON_OK,
		BUTTON_OKCANCEL,
		BUTTON_ABORTRETRYIGNORE,
		BUTTON_YESNO,
		BUTTON_RETRYCANCEL,
		BUTTON_CUSTOM
	};
	enum Result //34
	{
		RESULT_NOTSUPPORTED = -1,
		RESULT_UNKNOWN,
		RESULT_OK,
		RESULT_CANCEL,
		RESULT_ABORT,
		RESULT_RETRY,
		RESULT_IGNORE,
		RESULT_YES,
		RESULT_NO,
		RESULT_CUSTOM_0,
		RESULT_CUSTOM_1,
		RESULT_CUSTOM_2
	};
	AlertBox(); //52

	bool isSupported(); //57

	~AlertBox(); //62

	void setCustomButtons(const std::vector<std::string>& customButtons); //67

	void show(const std::string& title, const std::string& message, int type, AlertBoxListener* listener); //73
private:
	class AlertBoxImpl;
	P(AlertBoxImpl) m_impl; //77 | Impl sizes: [iOS+OSX: 28 bytes {iOS, OSX}, Android: 24 bytes {Android}]
	AlertBox(const AlertBox&); //78
	AlertBox& operator=(const AlertBox&); //79
};

class AlertBoxListener //82
{
public:
	virtual void dialogDismissed(AlertBox* dialog, AlertBox::Result result) = 0; //86 | Recovered param names from apprater::AppraterAlertBoxListener::dialogDismissed
};

}

#endif // !_PF_TEXTINPUT_H