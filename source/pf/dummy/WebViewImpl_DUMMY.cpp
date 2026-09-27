#include <pf/WebView.h>

using namespace lang;

namespace pf
{
	class WebViewImpl : public Object //OSX, likely Windows too
	{
	public:
		WebViewImpl(int x, int y, int height, int width, bool backgroundIsTransparent)
		{
		}

		~WebViewImpl()
		{
		}

		void loadUrl(const std::string& url)
		{
			//if (url.size() > 0)
		}

		void loadLocalUrl(const std::string& url)
		{
			//if (url.size() > 0)
		}

		void reload()
		{
		}

		void show()
		{
		}

		void hide()
		{
		}

		void setPosition(int, int)
		{
		}

		void setSize(int, int)
		{
		}

		void setListener(WebViewListener* listener)
		{
			m_listener = listener;
		}

		WebViewListener* getListener()
		{
			return m_listener;
		}

		std::string* executeJavaScript(std::string javaScript) //TODO
		{
			std::string* result;
			return result;
		}

		void asyncExecuteJavaScript(std::string javaScript)
		{
		}

		bool isSupported()
		{
			return false;
		}

		bool isWebViewSupported()
		{
			return false;
		}

		WebViewListener* m_listener; //unknown
	};

#include <pf/common/WebView.h>

}