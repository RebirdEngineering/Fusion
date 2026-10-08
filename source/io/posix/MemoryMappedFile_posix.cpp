#include <io/MemoryMappedFile.h>
#include <io/IOException.h>

//#include <sys/mman.h> //Dummied for now

using namespace lang;

namespace io
{

class MemoryMappedFile::Impl : public Object //20 bytes. Used by Android[+RCS/SkyNest/Beacon] and MacOS | UNTESTED
{
public:
	Impl(const std::string& name)
	{
		/*FILE* f = fopen(name.c_str(), "rb");
		if (!f)
			throwError(IOException(Format("Failed to open {0} with errno {1} ({2})", name, errno, strerror(errno)));
		
		//Similar to FileInputStream::available
		fseek(f, 0, SEEK_END);
		m_size = ftell(f);
		fseek(f, 0, SEEK_SET);

		if (m_size)
			m_memmap = mmap(0, m_size, 1, PROT_READ, MAP_PRIVATE, fileno(f), 0);

		fclose(f);*/
	}

	~Impl()
	{
		/*if (m_memmap)
			munmap(m_memmap, m_size);*/
	}

	size_t size()
	{
		return m_size;
	}

	const char* data(size_t offset) const
	{
		assert(offset <= m_size); //RCSSDKDBG line 50
		return (char*)m_memmap + offset; //?
	}

private:
	size_t m_size;
	void* m_memmap; //Correct?
};

MemoryMappedFile::MemoryMappedFile(const std::string& name) //Not on legacy iOS
{
	m_impl = new Impl(name);
}

size_t MemoryMappedFile::size() const
{
	return m_impl->size();
}

const char* MemoryMappedFile::data(size_t offset) const
{
	return m_impl->data(offset);
}

}