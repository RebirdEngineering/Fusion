#include <io/CacheFileSystem.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/detail/detail.h>
#include <io/PathName.h>
#include <io/BasicFileSystem.h>

namespace io
{

P(FileInputStream) CacheFileSystem::createInputStream(const std::string& path) //11-14 | Mobile only
{
	return new FileInputStream(PathName(detail::fileCachePath(), path).toString()); //13
}

P(FileOutputStream) CacheFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories) //16-30
{
	createCacheDirectory(); //18

	std::string actualPath = PathName(detail::fileCachePath(), path).toString(); //20
	if (createMissingDirectories)
	{
		const std::string& dir = PathName(actualPath).parent().toString(); //23
		if (!path.empty() && isDirectory(dir)) //24
			createDirectory(dir, true); //25
	}

	return new FileOutputStream(actualPath); //29
}

#ifndef PLATFORM_IOS //Not on iOS.
P(MemoryMappedFile) CacheFileSystem::openMemoryMappedFile(const std::string& path)
{
	createCacheDirectory();

	const std::string& actualPath = PathName(detail::fileCachePath(), path).toString();

	return BasicFileSystem::openMemoryMappedFile(actualPath);
}

bool CacheFileSystem::exists(const std::string& path)
{
	return BasicFileSystem::exists(PathName(detail::fileCachePath(), path).toString());
}
#endif

size_t CacheFileSystem::getSize(const std::string& path) //44-47
{
	return BasicFileSystem::getSize(PathName(detail::fileCachePath(), path).toString()); //46
}

#ifndef PLATFORM_IOS //Not on iOS.
int64_t CacheFileSystem::getCreationTime(const std::string& path)
{
	return BasicFileSystem::getCreationTime(PathName(detail::fileCachePath(), path).toString());
}
#endif

int64_t CacheFileSystem::getLastModifiedTime(const std::string& path) //59-62
{
	return BasicFileSystem::getLastModifiedTime(PathName(detail::fileCachePath(), path).toString()); //61
}

void CacheFileSystem::touch(const std::string& path) //64-67
{
	BasicFileSystem::touch(PathName(detail::fileCachePath(), path).toString()); //66
}

#ifndef PLATFORM_IOS //Not on iOS
void CacheFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories)
{
	BasicFileSystem::copy(PathName(detail::fileCachePath(), path).toString(), PathName(detail::fileCachePath(), newPath).toString(), createMissingDirectories);
}

void CacheFileSystem::move(const std::string& path, const std::string& newPath, bool createMissingDirectories)
{
	BasicFileSystem::move(PathName(detail::fileCachePath(), path).toString(), PathName(detail::fileCachePath(), newPath).toString(), createMissingDirectories);
}
#endif

void CacheFileSystem::rename(const std::string& path, const std::string& newName) //81-84
{
	BasicFileSystem::rename(PathName(detail::fileCachePath(), path).toString(), PathName(detail::fileCachePath(), newName).toString()); //83
}

void CacheFileSystem::remove(const std::string& path) //86-89
{
	BasicFileSystem::remove(PathName(detail::fileCachePath(), path).toString()); //88
}

bool CacheFileSystem::isFile(const std::string& path) //91-94
{
	return BasicFileSystem::isFile(PathName(detail::fileCachePath(), path).toString()); //93
}

bool CacheFileSystem::isDirectory(const std::string& path) //96-99
{
	return BasicFileSystem::isDirectory(PathName(detail::fileCachePath(), path).toString()); //98
}

void CacheFileSystem::createDirectory(const std::string& path, bool createMissingDirectories) //101-106
{
	createCacheDirectory(); //103

	BasicFileSystem::createDirectory(PathName(detail::fileCachePath(), path).toString(), createMissingDirectories); //105
}

std::vector<DirEntry> CacheFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) //108-114
{
	std::string actualBaseDir = PathName(detail::fileCachePath(), basedir).toString(); //110

	return BasicFileSystem::enumerate(actualBaseDir, filepattern, types, recursive); //113
}

void CacheFileSystem::createCacheDirectory()
{
	const std::string& fileCachePath = detail::fileCachePath(); //118

	if (!exists(fileCachePath)) //120
		createDirectory(fileCachePath, true); //122
}

}