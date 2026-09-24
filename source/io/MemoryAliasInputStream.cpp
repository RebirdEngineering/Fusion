#include <io/MemoryAliasInputStream.h>

BEGIN_NAMESPACE(io)

MemoryAliasInputStream::MemoryAliasInputStream(const void* data, int size, const std::string& name):
    InputStream(this)
{
    m_name = name;
    reset(data, size);
}

MemoryAliasInputStream::~MemoryAliasInputStream()
{
}

void MemoryAliasInputStream::reset(const void* data, int size)
{
    m_data = data;
    m_size = size;
    m_index = 0;
}

int MemoryAliasInputStream::read( void* data, int size ) //[TODO]
{
    int left = available(); //30
    int count = size; //31 //left < size ? left : 0; //?
    if (left < count)
        count = left;

    m_data = byteIndex(count);

    m_index += count;
	return count;
}

int MemoryAliasInputStream::skip( int n	) //[ADD] Correct?
{
    assert(n >= 0); //Double check this assert.
    int left = available();
    int count = n; //left < n ? left : 0;

    m_index = n + count;

    return count;
}

bool MemoryAliasInputStream::seek( int offset, SeekMode origin ) //Correct?
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

const void* MemoryAliasInputStream::data() const
{
    return m_size ? m_data : 0;
}

int MemoryAliasInputStream::available() const
{
	return m_size - m_index;
}

std::string MemoryAliasInputStream::toString() const
{
	return !m_name.empty() ? m_name : "MemoryAliasInputStream";
}

END_NAMESPACE()
