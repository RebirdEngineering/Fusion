#include <io/MemoryAliasInputStream.h>

namespace io
{

MemoryAliasInputStream::MemoryAliasInputStream(const void* data, int size, const std::string& name) : //9
    InputStream(this)
{
    m_name = name;
    reset(data, size);
}

MemoryAliasInputStream::~MemoryAliasInputStream()
{
}

void MemoryAliasInputStream::reset(const void* data, int size) //19
{
    m_data = data;
    m_size = size;
    m_index = 0;
}

int MemoryAliasInputStream::read( void* data, int size ) //26 | [TODO]
{
    //Some assert is probably here...

    int left = available(); //30
    int count = size; //31
    if (left < count)
        count = left;

    if (count >= 1)
        m_data = byteIndex(count); //36

    m_index += count;
	return count;
}

int MemoryAliasInputStream::skip( int n	) //42 | Correct?
{
    assert(n >= 0); //Double check this assert. Likely here according to KA3D InputStream + FilterInputStream.

    int left = available(); //47
    int count = n; //48

    m_index = n + count;

    return count;
}

bool MemoryAliasInputStream::seek( int offset, SeekMode origin ) //56 | Correct?
{
    switch (origin)
    {
    case InputStream::SEEKMODE_SET: m_index = offset; break;
    case InputStream::SEEKMODE_CUR: offset += m_index; break;
    case InputStream::SEEKMODE_END: m_index += m_size; break;
    }
    /*offset = m_index;
    if (offset <= 1)
    {
    	offset = 0;
    	m_index = 0;
    }
    if (offset > m_size)
    	m_index = m_size;*/
    return 1;
}

const void* MemoryAliasInputStream::data() const //Not seen on iOS.
{
    return m_size ? m_data : 0;
}

int MemoryAliasInputStream::available() const //93
{
	return m_size - m_index;
}

std::string MemoryAliasInputStream::toString() const
{
	return !m_name.empty() ? m_name : "MemoryAliasInputStream"; //98
}

}
