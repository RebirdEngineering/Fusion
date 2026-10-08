#ifndef _IO_BASICFILESYSTEM_H
#define _IO_BASICFILESYSTEM_H

#include <lang/Ptr.h>
#include <io/DirEntry.h>

namespace io
{
	class FileInputStream;
	class FileOutputStream;
	class MemoryMappedFile;

class BasicFileSystem //Used in mobile, RCS client and Seasons 4.0.1 for PC
{
public:
	P(FileInputStream) createInputStream(const std::string& path); //33

	P(FileOutputStream) createOutputStream(const std::string& path, bool createMissingDirectories); //42

	static P(MemoryMappedFile) openMemoryMappedFile(const std::string& path); //52

	static bool exists(const std::string& path); //59

	static size_t getSize(const std::string& path); //67

	static int64_t getCreationTime(const std::string& path); //75

	static int64_t getLastAccessTime(const std::string& path); //83

	static int64_t getLastModifiedTime(const std::string& path); //91

	static void touch(const std::string& path); //99

	static void copy(const std::string& path, const std::string& newPath, bool createMissingDirectories); //111 | guess

	static void move(const std::string& path, const std::string& newPath, bool createMissingDirectories); //123 | guess

	static void rename(const std::string& path, const std::string& newPath); //132 | guess

	static void remove(const std::string& path); //140

	static bool isFile(const std::string& path); //148

	static bool isDirectory(const std::string& path); //156

	static void createDirectory(const std::string& path, bool createMissingDirectories); //175

	static std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive = false); //201 | Called by GameLua::removeTemporaryLevels

	void setPermissions(const std::string& path, int permissions); //214, unknown parameters.
};

}

#endif