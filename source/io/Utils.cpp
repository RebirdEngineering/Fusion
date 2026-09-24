#include <io/Utils.h>
#include <lang/SBOBuffer.h>

using namespace lang;

//typedef for size_t?

namespace io
{

size_t copy(InputStream& in, OutputStream& out) //Android and 4.1.0 Seasons, this is only used by DiskCache.
{
	/*const int MAX_BUFFER = 10240;
	const int available = in.available();
	const int BUFFER_SIZE = MAX_BUFFER;
	SBOBuffer<unsigned char> buffer(MAX_BUFFER);
	int read;
	size_t bytes;

	buffer.bytes();

	//buffer *
	while (available >= 1)
	{
		available = in.
	}

	return bytes;*/

	//in.read(buffer, )

	//out.write(buffer, )

	assert("size_t io::copy(InputStream& in, OutputStream& out) is not decompiled yet.");
	return 0;
}

}