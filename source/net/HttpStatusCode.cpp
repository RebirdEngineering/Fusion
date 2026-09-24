#include <net/HttpStatusCode.h>

namespace net
{

const char* toString(HttpStatusCode code)
{
	switch (code)
	{
	case HTTP_CONTINUE: return "100 Continue";
	case HTTP_SWITCHING_PROTOCOLS: return "101 Switching Protocols";
	case HTTP_OK: return "200 OK";
	case HTTP_CREATED: return "201 Created";
	case HTTP_ACCEPTED: return "202 Accepted";
	case HTTP_NON_AUTHORITATIVE_INFORMATION: return "203 Non-Authoritative Information";
	case HTTP_NO_CONTENT: return "204 No Content";
	case HTTP_RESET_CONTENT: return "205 Reset Content";
	case HTTP_PARTIAL_CONTENT: return "206 Partial Content";
	case HTTP_MULTIPLE_CHOICES: return "300 Multiple Choices";
	case HTTP_MOVED_PERMANENTLY: return "301 Moved Permanently";
	case HTTP_FOUND: return "302 Found";
	case HTTP_SEE_OTHER: return "303 See Other";
	case HTTP_NOT_MODIFIED: return "304 Not Modified";
	case HTTP_USE_PROXY: return "305 Use Proxy";
	case HTTP_TEMPORARY_REDIRECT: return "307 Temporary Redirect";
	case HTTP_BAD_REQUEST: return "400 Bad Request";
	case HTTP_UNAUTHORIZED: return "401 Unauthorized";
	case HTTP_PAYMENT_REQUIRED: return "402 Payment Required";
	case HTTP_FORBIDDEN: return "403 Forbidden";
	case HTTP_NOT_FOUND: return "404 Not Found";
	case HTTP_METHOD_NOT_ALLOWED: return "405 Method Not Allowed";
	case HTTP_NOT_ACCEPTABLE: return "406 Not Acceptable";
	case HTTP_PROXY_AUTHENTICATION_REQUIRED: return "407 Proxy Authentication Required";
	case HTTP_REQUEST_TIMEOUT: return "408 Request Timeout";
	case HTTP_CONFLICT: return "409 Conflict";
	case HTTP_GONE: return "410 Gone";
	case HTTP_LENGTH_REQUIRED: return "411 Length Required";
	case HTTP_PRECONDITION_FAILED: return "412 Precondition Failed";
	case HTTP_REQUEST_ENTITY_TOO_LARGE: return "413 Request Entity Too Large";
	case HTTP_REQUEST_URI_TOO_LONG: return "414 Request-URI Too Long";
	case HTTP_UNSUPPORTED_MEDIA_TYPE: return "415 Unsupported Media Type";
	case HTTP_REQUESTED_RANGE_NOT_SATISFIABLE: return "416 Requested Range Not Satisfiable";
	case HTTP_EXPECTATION_FAILED: return "417 Expectation Failed";
	case HTTP_INTERNAL_SERVER_ERROR: return "500 Internal Server Error";
	case HTTP_NOT_IMPLEMENTED: return "501 Not Implemented";
	case HTTP_BAD_GATEWAY: return "502 Bad Gateway";
	case HTTP_SERVICE_UNAVAILABLE: return "503 Service Unavailable";
	case HTTP_GATEWAY_TIMEOUT: return "504 Gateway Timeout";
	case HTTP_HTTP_VERSION_NOT_SUPPORTED: return "505 HTTP Version Not Supported";
	default: return "Unidentified HttpStatusCode";
	}
}

}