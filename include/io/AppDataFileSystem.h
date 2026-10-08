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
	static P(AppDataInputStream) createInputStream(const std::string& path); //32

	static P(AppDataOutputStream) createOutputStream(const std::string& path, bool createMissingDirectories); //41

	static P(MemoryMappedFile) openMemoryMappedFile(const std::string& path); //51 | A guess

	static bool exists(const std::string& path); //58 | A guess from BFS and CFS

	static void copy(const std::string& path, const std::string& newPath, bool createMissingDirectories); //70 | guess

	static void move(const std::string& path, const std::string& newPath, bool createMissingDirectories); //82 | guess

	static void rename(const std::string& path, const std::string& newName); //91 | Recover param name from CFS (source, destination in BFS? We'll go with CFS since BFS converts stuff)

	static void remove(const std::string& path); //99

	static bool isFile(const std::string& path); //107

	static bool isDirectory(const std::string& path); //115

	static void createDirectory(const std::string& path, bool createMissingDirectories); //134

	static std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive); //160
};

}

#endif