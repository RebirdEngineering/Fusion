#ifndef _NET_HTTPREQUEST_H
#define _NET_HTTPREQUEST_H

#include <lang/Object.h>
#include <lang/FastDelegate.h>
#include <net/HttpResponse.h>

namespace net
{

class HttpRequest :
	public lang::Object
{
	typedef lang::FastDelegate4<double, double, double, double, bool> ProgressFunction;
	typedef lang::FastDelegate2<const char*, unsigned long, unsigned long> ReceiveFunction;
	typedef lang::FastDelegate2<char*, unsigned long, unsigned long> SendFunction;
public:
	HttpRequest();

	~HttpRequest();

	HttpResponse get(const std::string& url);

	HttpResponse post(const std::string& url, const std::string& data);

	HttpResponse post(const std::string&, size_t, const SendFunction);

	HttpResponse del(const std::string& url);

	void setConnectionTimeout(int seconds);

	void setHeader(const std::string& header);

	void resetHeaders(const std::string&);

	void addCookie();

	void resetCookies();

	void setProgressFunction(const ProgressFunction& progressFunction); //Recovered from net/ios/HttpRequestHandler.h

	void setReceiveFunction(const ReceiveFunction& function);

	void setWriteHeaderFunction(const ReceiveFunction& writeHeaderFunction); //Recovered from net/ios/HttpRequestHandler.h
private:
	class Impl;
	P(Impl) m_impl;

	HttpRequest(const HttpRequest&);
	HttpRequest& operator=(const HttpRequest&);
};


} // io


#endif // _NET_HTTPREQUEST_H
