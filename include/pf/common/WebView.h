WebView::WebView(int x, int y, int height, int width, bool backgroundIsTransparent) //1 (yeah line 1, by that logic there's no ifdef define endif) | Includes and namespaces are redundant since we're including this file in the namespace
{
	m_func_ref = -1;
	m_callback = -1;
	m_impl = new WebViewImpl(x, y, height, width, backgroundIsTransparent);
}

WebView::~WebView() //-10
{
}

void WebView::loadUrl(const std::string& url) //14
{
	m_impl->loadUrl(url); //16
}

void WebView::loadLocalUrl(const std::string& url) //19
{
	m_impl->loadLocalUrl(url); //21
}

void WebView::reload()
{
	m_impl->reload(); //25
}

void WebView::show()
{
	m_impl->show(); //30
}

void WebView::hide()
{
	m_impl->hide(); //35
}

void WebView::setPosition(int x, int y) //38
{
	m_impl->setPosition(x, y); //40
}

void WebView::setSize(int width, int height) //43
{
	m_impl->setSize(width, height);
}

void WebView::setListener(WebViewListener* listener)
{
	//listener->setWebViewInstance(this); //51
	m_impl->setListener(listener); //52
}

WebViewListener* WebView::getListener()
{
	return m_impl->getListener(); //58
}

std::string* WebView::executeJavaScript(std::string javaScript) //61
{
	return m_impl->executeJavaScript(javaScript); //63
}

void WebView::asyncExecuteJavaScript(std::string javaScript) //66
{
	return m_impl->asyncExecuteJavaScript(javaScript); //68
}

bool WebView::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

bool WebView::isWebViewSupported() //Not defined on iOS
{
	return m_impl->isWebViewSupported();
}