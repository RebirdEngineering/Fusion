#ifndef IO_CACHEFILESYSTEM_H
#define IO_CACHEFILESYSTEM_H

#include <lang/Ptr.h>
#include <io/DirEntry.h>

namespace io
{
	class FileInputStream;
	class FileOutputStream;
	class MemoryMappedFile;

class CacheFileSystem
{
public:
	P(FileInputStream) createInputStream(const std::string& path); //33

	P(FileOutputStream) createOutputStream(const std::string& path, bool createMissingDirectories); //42

	P(MemoryMappedFile) openMemoryMappedFile(const std::string&); //52

	bool exists(const std::string& path); //59

	size_t getSize(const std::string& path); //67

	int64_t getCreationTime(const std::string& path); //75

	int64_t getLastAccessTime(const std::string& path); //83

	int64_t getLastModifiedTime(const std::string& path); //91

	void touch(const std::string& path); //99

	void copy(const std::string&, const std::string&, bool); //111

	void move(const std::string&, const std::string&, bool); //123

	void rename(const std::string&, const std::string&); //132

	void remove(const std::string&); //140

	bool isFile(const std::string&); //148

	bool isDirectory(const std::string&); //156

	void createDirectory(const std::string&, bool); //175

	std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive); //201

private:
	void createCacheDirectory(); //211
};

}

#endif // !IO_CACHEFILESYSTEM_H