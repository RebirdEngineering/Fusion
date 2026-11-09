#ifndef _NET_HTTPREQUEST_H
#define _NET_HTTPREQUEST_H

#include <lang/Object.h>
#include <lang/FastDelegate.h>
#include <net/HttpResponse.h>

namespace net
{

class HttpRequest : //40
	public lang::Object
{
public:
	typedef lang::FastDelegate4<double, double, double, double, bool> ProgressFunction; //52

	typedef lang::FastDelegate2<const char*, unsigned long, unsigned long> ReceiveFunction; //61

	typedef lang::FastDelegate2<char*, unsigned long, unsigned long> SendFunction; //70

	HttpRequest(); //76

	~HttpRequest(); //81

	HttpResponse get(const std::string& url); //86

	HttpResponse post(const std::string& url, const std::string& data); //91

	HttpResponse post(const std::string& url, size_t size, const SendFunction sendFunction); //96 | Unknown parameters.

	HttpResponse del(const std::string& url); //101

	void setConnectionTimeout(int seconds); //106

	void setHeader(const std::string& header); //113

	void resetHeaders(); //118

	void addCookie(const std::string& cookie); //124 | Unknown parameter.

	void resetCookies(); //129

	void setProgressFunction(const ProgressFunction& progressFunction); //135 | Recovered from net/ios/HttpRequestHandler.h

	void setReceiveFunction(const ReceiveFunction& function); //142

	void setWriteHeaderFunction(const ReceiveFunction& writeHeaderFunction); //149 | Recovered from net/ios/HttpRequestHandler.h
private:
	class Impl;
	P(Impl) m_impl; //153 | Win32: 0x40 bytes | iOS: 0x64 bytes

	HttpRequest(const HttpRequest&); //155
	HttpRequest& operator=(const HttpRequest&); //156
};


} // io


#endif // _NET_HTTPREQUEST_H
