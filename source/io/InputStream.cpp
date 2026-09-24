#include <io/InputStream.h>

namespace io
{

InputStream::InputStream(InputStream& sourceRef) : //13
	m_ref(sourceRef)
{
	m_ptr->m_ptr = 0;
}

InputStream::InputStream(P(InputStream) sourcePtr) : //19
	m_ptr(sourcePtr), m_ref(*sourcePtr)
{
}

InputStream::~InputStream() //25
{
}

int InputStream::read(void* buffer, int bytes) //29
{
	return getEmbeddedStream().m_ptr->read(buffer, bytes);
}

int InputStream::skip(int bytes) //34
{
	return getEmbeddedStream().m_ptr->skip(bytes);
}

bool InputStream::seek(int offset, SeekMode origin) //39
{
	return getEmbeddedStream().m_ptr->seek(offset, origin);
}

int InputStream::available() const
{
	return getEmbeddedStream().m_ptr->available();
}

InputStream& InputStream::getEmbeddedStream() const //46
{
	if (m_ptr == this)
		return m_ptr.operator*();
	return m_ref; //Correct?
}

std::string InputStream::toString() const //51
{
	return getEmbeddedStream().toString();
}

std::string toString(InputStream& in) //59
{
	const std::vector<unsigned char>& data = toVector(in);

	//data.begin();
	//data.end();

	assert("io::toString(InputStream& in) is not decompiled yet.");
	return in.toString();
}

static std::vector<unsigned char> toVector(InputStream& in) //65
{
	std::vector<unsigned char> result;

	int bytes = in.available();

	const int CHUNK_SIZE = 1024;
	int read;

	int size = result.size();

	if (bytes >= 0)
	{
		if (bytes > 0)
		{
			result.resize(bytes, 0);
			read = in.read(result.data(), bytes);
		}
	}

	else
	{
		while (read == CHUNK_SIZE)
		{
			result.resize(size + CHUNK_SIZE, 0);
			read = in.read(size + result.data(), CHUNK_SIZE);
		}
		result.resize(result.size() + bytes - CHUNK_SIZE, 0);
	}

	return result;
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
