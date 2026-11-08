#include <net/HttpRequest.h>

using namespace lang;

namespace net
{

class HttpRequest::Impl : public Object //Win32, Android, OSX
{
public:
	Impl();

	~Impl();

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
};

#include <net/common/HttpRequest.h>

}