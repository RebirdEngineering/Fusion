#ifndef _NET_HTTPRESPONSE_H
#define _NET_HTTPRESPONSE_H

#include <lang/pp.h>

namespace net
{
struct HttpResponse
{
	int status;
	std::string message;
	std::string effectiveUrl;
	std::vector<std::string> headers;
	std::vector<std::string> cookies;
};


} // net


#endif // _NET_HTTPRESPONSE_H
