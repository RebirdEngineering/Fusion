#include <net/HttpFileInputStream.h>
#include <net/HttpStatusCode.h>
#include <net/HttpRequestException.h>

using namespace lang;

namespace net
{

HttpFileInputStream::HttpFileInputStream(const std::string& url) :
	InputStream(this)
{
	HttpRequest request;
	HttpResponse response = request.get(url);
	if (response.status != HTTP_CONTINUE)
		throwError(HttpRequestException(Format("Creating HttpFileInputStream failed with status: {0} URL: {1}", response.status, url)));
	m_message.reset(response.message.data(), response.message.size());
}

int HttpFileInputStream::read(void* data, int size)
{
	return m_message.read(data, size);
}

int HttpFileInputStream::skip(int n)
{
	return m_message.skip(n);
}

bool HttpFileInputStream::seek(int offset, SeekMode origin)
{
	return m_message.seek(offset, origin);
}

int HttpFileInputStream::available() const
{
	return m_message.available();
}

std::string HttpFileInputStream::toString() const
{
	return m_message.toString();
}

}
