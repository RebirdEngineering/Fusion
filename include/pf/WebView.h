#ifndef _PF_WEBVIEW_H
#define _PF_WEBVIEW_H

#include <lang/Object.h> //For now

namespace pf
{

class WebViewImpl; //Should be outside webview
class WebViewListener; //Needed?

class WebView :
	public lang::Object
{
public:
	WebView(int x, int y, int height, int width, bool backgroundIsTransparent); //33
	~WebView(); //34

	void loadUrl(const std::string& url); //36
	void loadLocalUrl(const std::string& url); //37
	void reload(); //38

	void show(); //40
	void hide(); //41

	void setPosition(int, int); //48

	void setSize(int, int); //55

	void setListener(WebViewListener* listener); //57
	WebViewListener* getListener(); //58

	std::string* executeJavaScript(const std::string& javaScript); //61
	void asyncExecuteJavaScript(const std::string& javaScript); //62

	static bool isSupported(); //64
	bool isWebViewSupported(); //65

	int m_func_ref; //68
	int m_callback; //69

private:
	P(WebViewImpl) m_impl; //73

	WebView(const WebView&); //75
	WebView& operator=(const WebView&); //76
};

class WebViewListener
{
public:
	enum LinkClickedResult //91
	{
		DONT_LOAD_PAGE,
		LOAD_PAGE_INTO_WEBVIEW,
		LOAD_PAGE_INTO_EXTERNAL_BROWSER
	};

	WebViewListener(); //101

	virtual ~WebViewListener(); //106

	virtual void onWebViewPageLoaded(bool success, const std::string& pageTitle, WebView& webView) = 0; //114 | Recover from Channel

	virtual LinkClickedResult onWebViewLinkClicked(const std::string& url, WebView& webView) = 0; //123 | Recover from lualistener

	virtual void onWebViewCallFromJavaScript(const std::string& message, WebView& webView) = 0; //130

private:
	WebView* m_instance; //133

	void setWebViewInstance(WebView* instance); //139

public:
	void onWebViewPageLoaded(bool success, const std::string& pageTitle); //147

	LinkClickedResult onWebViewLinkClicked(const std::string& url); //154

	void onWebViewCallFromJavaScript(const std::string& message); //161
};

}

#endif