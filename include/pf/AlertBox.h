#ifndef _PF_ALERTBOX_H
#define _PF_ALERTBOX_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class AlertBox :
	public Object
{
public:
	enum Button
	{
		BUTTON_OK,
		BUTTON_OKCANCEL,
		BUTTON_ABORTRETRYIGNORE,
		BUTTON_YESNO,
		BUTTON_RETRYCANCEL,
		BUTTON_CUSTOM
	};
	enum Result
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
	AlertBox();

	bool isSupported();

	~AlertBox();

	void setCustomButtons(const std::vector<std::string>& customButtons);

	void show(const std::string&, const std::string&, int, AlertBoxListener*);
private:
	class AlertBoxImpl;
	P(AlertBoxImpl) m_impl;

	AlertBox(const AlertBox&);
	AlertBox& operator=(const AlertBox&);
};

class AlertBoxListener
{
public:
	virtual void dialogDismissed(AlertBox*, AlertBox::Result) = 0;
};

}

#endif // !_PF_TEXTINPUT_H