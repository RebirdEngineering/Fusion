#ifndef _NET_COMMON_HTTPREQUEST_H
#define _NET_COMMON_HTTPREQUEST_H

#include <net/HttpRequest.h>

BEGIN_NAMESPACE(net)

//ObjC?

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
	return m_impl->post(url);
}

/*HttpResponse HttpRequest::post(const std::string&, size_t, const SendFunction)
{
	//return m_impl->post(url);
}*/

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

void HttpRequest::setReceiveFunction(const ReceiveFunction& function)
{
	return m_impl->setReceiveFunction(function);
}

} // net

#endif // _NET_COMMON_HTTPREQUEST_H
