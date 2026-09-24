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
	P(FileInputStream) createInputStream(const std::string& path);

	P(FileOutputStream) createOutputStream(const std::string& path, bool);

	P(MemoryMappedFile) openMemoryMappedFile(const std::string&);

	bool exists(const std::string& path);

	size_t getSize(const std::string& path);

	int64_t getCreationTime(const std::string& path);

	int64_t getLastAccessTime(const std::string& path);

	int64_t getLastModifiedTime(const std::string& path);

	void touch(const std::string& path);

	void copy(const std::string&, const std::string&, bool);

	void move(const std::string&, const std::string&);

	void rename(const std::string&, const std::string&);

	void remove(const std::string&);

	bool isFile(const std::string&);

	bool isDirectory(const std::string&);

	void createDirectory(const std::string&, bool);

	std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive);
private:
	void createCacheDirectory();
};

}

#endif // !IO_CACHEFILESYSTEM_H