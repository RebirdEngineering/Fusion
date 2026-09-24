#ifndef _PF_COMMON_WEBVIEW_H
#define _PF_COMMON_WEBVIEW_H

#include <pf/WebView.h>

BEGIN_NAMESPACE(pf)

WebView::WebView(int x, int y, int height, int width, bool backgroundIsTransparent)
{
	m_impl = new WebViewImpl(x, y, height, width, backgroundIsTransparent);
}

WebView::~WebView()
{
}

void WebView::loadUrl(const std::string& url)
{
	m_impl->loadUrl(url);
}

void WebView::loadLocalUrl(const std::string& url)
{
	m_impl->loadLocalUrl(url);
}

void WebView::reload()
{
	m_impl->reload();
}

void WebView::show()
{
	m_impl->show();
}

void WebView::hide()
{
	m_impl->hide();
}

void WebView::setPosition(int x, int y)
{
	m_impl->setPosition(x, y);
}

void WebView::setSize(int width, int height)
{
	m_impl->setSize(width, height);
}

void WebView::setListener(WebViewListener* listener)
{
	listener->setWebViewInstance(this); //?
	m_impl->setListener(listener);
}

WebViewListener* WebView::getListener()
{
	return m_impl->getListener();
}

std::string* WebView::executeJavaScript(const std::string& javaScript)
{
	return m_impl->executeJavaScript(javaScript);
}

std::string* WebView::asyncExecuteJavaScript(const std::string& javaScript)
{
	return m_impl->asyncExecuteJavaScript(javaScript);
}

bool WebView::isSupported() //Not defined on iOS
{
	return m_impl->isSupported();
}

bool WebView::isWebViewSupported() //Not defined on iOS
{
	return m_impl->isWebViewSupported();
}

}

#endif //! _PF_COMMON_WEBVIEW_H