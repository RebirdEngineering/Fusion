#ifndef _NET_COMMON_HTTPREQUEST_H
#define _NET_COMMON_HTTPREQUEST_H

HttpRequest::HttpRequest()
{
	m_impl = new Impl();
}

HttpRequest::~HttpRequest()
{
}

HttpResponse HttpRequest::get(const std::string& url)
{
	return m_impl->get(url);
}

HttpResponse HttpRequest::post(const std::string& url, const std::string& data)
{
	return m_impl->post(url, data);
}

HttpResponse HttpRequest::post(const std::string& url, size_t size, const SendFunction sendfunction)
{
	return m_impl->post(url, size, sendfunction);
}

HttpResponse HttpRequest::del(const std::string& url)
{
	return m_impl->del(url);
}

void HttpRequest::setConnectionTimeout(int seconds)
{
	return m_impl->setConnectionTimeout(seconds);
}

void HttpRequest::setHeader(const std::string& header)
{
	return m_impl->setHeader(header);
}

void HttpRequest::resetHeaders()
{
	return m_impl->resetHeaders();
}

void HttpRequest::addCookie(const std::string& cookie)
{
	return m_impl->addCookie(cookie);
}

void HttpRequest::resetCookies()
{
	return m_impl->resetCookies();
}

void HttpRequest::setProgressFunction(const ProgressFunction& progressFunction)
{
	return m_impl->setProgressFunction(progressFunction);
}

void HttpRequest::setReceiveFunction(const ReceiveFunction& function)
{
	return m_impl->setReceiveFunction(function);
}

void HttpRequest::setWriteHeaderFunction(const ReceiveFunction& writeHeaderFunction)
{
	return m_impl->setWriteHeaderFunction(writeHeaderFunction);
}

#endif // _NET_COMMON_HTTPREQUEST_H
