#include <io/CacheFileSystem.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/detail/detail.h>
#include <io/PathName.h>
#include <io/BasicFileSystem.h>

using namespace lang;

namespace io
{

using namespace detail;

P(FileInputStream) CacheFileSystem::createInputStream(const std::string& path) //Mobile only
{
	return new FileInputStream(PathName(fileCachePath(), path).toString());
}

P(FileOutputStream) CacheFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories)
{
	createCacheDirectory();

	const std::string& dir = PathName(fileCachePath(), path).toString();

	if (createMissingDirectories)
	{
		if (dir.size() && !isDirectory(dir))
		{
			createDirectory(dir, createMissingDirectories);
		}
	}
	return new FileOutputStream(dir);
}

P(MemoryMappedFile) CacheFileSystem::openMemoryMappedFile(const std::string& path) //Not seen in 4.1.0 iOS.
{
	createCacheDirectory();

	const std::string& dir = PathName(fileCachePath(), path).toString();

	return BasicFileSystem::openMemoryMappedFile(dir);
}

size_t CacheFileSystem::getSize(const std::string& path)
{
	return BasicFileSystem::getSize(PathName(fileCachePath(), path).toString());
}

int64_t CacheFileSystem::getCreationTime(const std::string& path)
{
	return BasicFileSystem::getCreationTime(PathName(fileCachePath(), path).toString());
}

int64_t CacheFileSystem::getLastModifiedTime(const std::string& path)
{
	return BasicFileSystem::getLastModifiedTime(PathName(fileCachePath(), path).toString());
}

void CacheFileSystem::touch(const std::string& path)
{
	return BasicFileSystem::touch(PathName(fileCachePath(), path).toString());
}

void CacheFileSystem::rename(const std::string& path, const std::string& newName)
{
	BasicFileSystem::rename(PathName(fileCachePath(), path).toString(), PathName(fileCachePath(), newName).toString());
}

void CacheFileSystem::remove(const std::string& path)
{
	BasicFileSystem::remove(PathName(fileCachePath(), path).toString());
}

bool CacheFileSystem::isFile(const std::string& path)
{
	return BasicFileSystem::isFile(PathName(fileCachePath(), path).toString());
}

bool CacheFileSystem::isDirectory(const std::string& path)
{
	return BasicFileSystem::isDirectory(PathName(fileCachePath(), path).toString());
}

void CacheFileSystem::createDirectory(const std::string& path, bool createMissingDirectories)
{
	createCacheDirectory();
	return BasicFileSystem::createDirectory(PathName(fileCachePath(), path).toString(), createMissingDirectories);
}

std::vector<DirEntry> CacheFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive)
{
	std::string actualBaseDir = PathName(fileCachePath(), basedir).toString();
	return BasicFileSystem::enumerate(actualBaseDir, filepattern, types, recursive);
}

void CacheFileSystem::createCacheDirectory()
{
	const std::string& fileCachePath = detail::fileCachePath();
	if (!exists(fileCachePath))
		createDirectory(fileCachePath, true);
}

}