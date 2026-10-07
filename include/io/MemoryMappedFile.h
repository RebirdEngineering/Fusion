#ifndef IO_MEMORYMAPPEDFILE_H
#define IO_MEMORYMAPPEDFILE_H

#include <lang/Object.h>

namespace io
{

class MemoryMappedFile : public lang::Object //9
{
public:
	MemoryMappedFile(const std::string& name); //19 | Guess from MAIS

	~MemoryMappedFile(); //26

	size_t size() const; //31

	const char* data(size_t offset) const; //38 | Recover from assert
private:
	class Impl;
	P(Impl) m_impl; //42

	MemoryMappedFile(const MemoryMappedFile&); //44
	MemoryMappedFile& operator=(const MemoryMappedFile&); //45
};

}

#endif // !IO_MEMORYMAPPEDFILE_H