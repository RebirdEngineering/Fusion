#ifndef _IO_APPDATAFILESYSTEM_H
#define _IO_APPDATAFILESYSTEM_H

#include <lang/Ptr.h>
#include <io/DirEntry.h>

namespace io
{
	class AppDataInputStream;
	class AppDataOutputStream;
	class MemoryMappedFile;

class AppDataFileSystem
{
public:
	P(AppDataInputStream) createInputStream(const std::string& path);

	P(AppDataOutputStream) createOutputStream(const std::string& path, bool createMissingDirectories);

	P(MemoryMappedFile) openMemoryMappedFile(const std::string& path); //A guess

	bool exists(const std::string& path); //A guess

	void copy(const std::string&, const std::string&, bool);

	void move(const std::string&, const std::string&, bool);

	void rename(const std::string&, const std::string&);

	void remove(const std::string&);

	bool isFile(const std::string&);

	bool isDirectory(const std::string& path);

	void createDirectory(const std::string& path, bool createMissingDirectories);

	std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive = false);
};

}

#endif