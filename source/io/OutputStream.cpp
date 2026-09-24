#include <io/OutputStream.h>

namespace io
{ 

OutputStream::OutputStream(P(OutputStream) sourcePtr)
	: m_ptr(sourcePtr), m_ref(*this)
{
	//This increases by 1?
}

OutputStream::~OutputStream()
{
}

void OutputStream::write(const void* data, int size)
{
	getEmbeddedStream().write(data, size);
}

OutputStream& OutputStream::getEmbeddedStream() const
{
	if (m_ptr == this)
		return m_ptr.operator*();
	return m_ref;
}

std::string OutputStream::toString() const
{
	return getEmbeddedStream().toString();
}

} // io