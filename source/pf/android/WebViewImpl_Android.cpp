#include <pf/WebView.h>

//TODO

using namespace lang;

namespace pf
{
	class WebViewImpl : public Object //Android, 0x44 bytes.
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

		void loadLocalUrl(const std::string& url) //Blank!
		{
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
			return true;
		}

		bool isWebViewSupported()
		{
			return isSupported();
		}

	private:
		java::GlobalRef baseGlobalRefC;
		WebViewListener* m_listener; //0x10 | unknown name
		java::GlobalRef subClass14;
		jobject jobject18;
		jmethodID* init_jmethodID1C;
		jmethodID* destroy_jmethodID20;
		jmethodID* loadUrl_jmethodID24;
		jmethodID* reload_jmethodID28;
		jmethodID* show_jmethodID2C;
		jmethodID* hide_jmethodID30;
		jmethodID* setPosition_jmethodID34;
		jmethodID* setSize_jmethodID38;
		jmethodID* executeJavaScript_jmethodID3C;
		jmethodID* asyncExecuteJavaScript_jmethodID40;
	};

#include <pf/common/WebView.h>

}