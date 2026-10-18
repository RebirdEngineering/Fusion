#include <pf/WebView.h>

using namespace lang;

namespace pf
{
	class WebViewImpl : public Object //Win32, OSX
	{
	public:
		WebViewImpl(int x, int y, int height, int width, bool backgroundIsTransparent)
		{
			m_listener = 0;
		}

		~WebViewImpl()
		{
		}

		void loadUrl(const std::string& url)
		{
			if (m_listener)
				m_listener->onWebViewPageLoaded(false, "");
		}

		void loadLocalUrl(const std::string& url)
		{
			if (m_listener)
				m_listener->onWebViewPageLoaded(false, "");
		}

		void reload()
		{
			m_listener->onWebViewPageLoaded(false, "");
		}

		void show()
		{
		}

		void hide()
		{
		}

		void setPosition(int x, int y)
		{
		}

		void setSize(int width, int height)
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

	private:
		WebViewListener* m_listener; //unknown
	};

#include <pf/common/WebView.h>

}