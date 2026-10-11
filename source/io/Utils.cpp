#include <io/Utils.h>
#include <lang/SBOBuffer.h>

using namespace lang;

namespace io
{

size_t copy(InputStream& in, OutputStream& out) //8 | Android and 4.1.0 Seasons, this is only used by DiskCache.
{
	const int MAX_BUFFER = 10240; //10
	const int available = in.available(); //11
	const int BUFFER_SIZE = MAX_BUFFER; //12
	SBOBuffer<unsigned char> buffer(MAX_BUFFER); //13

	int read; //15
	size_t bytes; //16
	while (available >= 1)
	{
		read = in.read(&buffer, buffer.bytes()); //19
		bytes += read;
		out.write(&buffer, read); //21
	}

	return bytes;
}

}