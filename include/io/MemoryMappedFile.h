#ifndef IO_MEMORYMAPPEDFILE_H
#define IO_MEMORYMAPPEDFILE_H

#include <lang/Object.h>

namespace io
{

class MemoryMappedFile : public lang::Object
{
public:
	MemoryMappedFile(const std::string& name); //Guess from MAIS

	~MemoryMappedFile();

	size_t size() const;
	const char* data(size_t offset) const; //Recover from assert
private:
	class Impl;
	P(Impl) m_impl;
	MemoryMappedFile(const MemoryMappedFile&);
	MemoryMappedFile& operator=(const MemoryMappedFile&);
};

}

#endif // !IO_MEMORYMAPPEDFILE_H