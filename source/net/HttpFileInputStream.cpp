#include <net/HttpFileInputStream.h>
#include <net/HttpStatusCode.h>
#include <net/HttpRequestException.h>

using namespace lang;

namespace net
{

HttpFileInputStream::HttpFileInputStream(const std::string& url) : //8
	InputStream(this)
{
	HttpRequest request; //11
	HttpResponse response = request.get(url); //12
	if (response.status != HTTP_CONTINUE)
		throwError(HttpRequestException(Format("Creating HttpFileInputStream failed with status: {0} URL: {1}", response.status, url))); //14
	m_message.reset(response.message.data(), response.message.size()); //15
}

int HttpFileInputStream::read(void* data, int size) //27
{
	return m_message.read(data, size);
}

int HttpFileInputStream::skip(int n) //32
{
	return m_message.skip(n);
}

bool HttpFileInputStream::seek(int offset, SeekMode origin) //37
{
	return m_message.seek(offset, origin);
}

int HttpFileInputStream::available() const
{
	return m_message.available(); //44
}

std::string HttpFileInputStream::toString() const
{
	return m_message.toString(); //49
}

}
