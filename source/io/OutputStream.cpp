#include <io/OutputStream.h>

namespace io
{ 

OutputStream::OutputStream(P(OutputStream) sourcePtr) : //16
	m_ptr(sourcePtr),
	m_ref(*this)
{
}

OutputStream::~OutputStream() //22-24
{
}

void OutputStream::write(const void* data, int size) //26
{
	getEmbeddedStream().write(data, size); //28
}

OutputStream& OutputStream::getEmbeddedStream() const
{
	return &m_ref == this ? m_ref : *m_ptr; //33
}

std::string OutputStream::toString() const
{
	return getEmbeddedStream().toString(); //38
}

} // io