#ifndef _IO_APPDATAFILESYSTEM_H
#define _IO_APPDATAFILESYSTEM_H

#include <lang/Ptr.h>
#include <io/DirEntry.h>

namespace io
{
	class AppDataInputStream;
	class AppDataOutputStream;
	class MemoryMappedFile;

class AppDataFileSystem //23
{
public:
	P(AppDataInputStream) createInputStream(const std::string& path); //32

	P(AppDataOutputStream) createOutputStream(const std::string& path, bool createMissingDirectories); //41

	P(MemoryMappedFile) openMemoryMappedFile(const std::string& path); //51 | A guess

	bool exists(const std::string& path); //58 | A guess from BFS and CFS

	void copy(const std::string& path, const std::string& newPath, bool createMissingDirectories); //70 | guess

	void move(const std::string& path, const std::string& newPath, bool createMissingDirectories); //82 | guess

	void rename(const std::string& path, const std::string& newName); //91 | Recover param name from CFS (source, destination in BFS? We'll go with CFS since BFS converts stuff)

	void remove(const std::string& path); //99

	bool isFile(const std::string& path); //107

	bool isDirectory(const std::string& path); //115

	void createDirectory(const std::string& path, bool createMissingDirectories); //134

	std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive); //160
};

}

#endif