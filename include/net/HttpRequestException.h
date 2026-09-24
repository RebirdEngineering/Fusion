#ifndef _NET_HTTPREQUESTEXCEPTION_H
#define _NET_HTTPREQUESTEXCEPTION_H

#include <lang/Exception.h>

BEGIN_NAMESPACE(net)

/**
 * 
 * @ingroup net
 */
class HttpRequestException : //12
	public NS(lang, Exception)
{
public:
	HttpRequestException(const NS(lang, Format)& msg) : Exception(msg) {}
};


END_NAMESPACE() // net


#endif // _NET_HTTPREQUESTEXCEPTION_H