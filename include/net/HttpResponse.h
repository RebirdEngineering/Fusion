#ifndef _NET_HTTPRESPONSE_H
#define _NET_HTTPRESPONSE_H

#include <lang/pp.h>

namespace net
{
struct HttpResponse
{
	int status; //15

	std::string message; //18

	std::string effectiveUrl; //21

	std::vector<std::string> headers; //24

	std::vector<std::string> cookies; //27
};


} // net


#endif // _NET_HTTPRESPONSE_H
