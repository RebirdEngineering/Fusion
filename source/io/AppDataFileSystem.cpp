#include <io/AppDataFileSystem.h>
#include <io/AppDataInputStream.h>
#include <io/AppDataOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/BasicFileSystem.h>
#include <io/PathName.h>
#include <io/detail/detail.h>

namespace io
{

P(AppDataInputStream) AppDataFileSystem::createInputStream(const std::string& path) //11
{
	return new AppDataInputStream(path); //13
}

P(AppDataOutputStream) AppDataFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories) //16
{
	if (createMissingDirectories)
	{
		const std::string& dir = PathName(path).parent().toString(); //20
		if (dir.empty() && !isDirectory(dir)) //21
			createDirectory(dir, true); //23 | This is true everywhere, why is there a second check
	}

	return new AppDataOutputStream(path); //27
}

P(MemoryMappedFile) AppDataFileSystem::openMemoryMappedFile(const std::string& path) //Not on iOS.
{
	return BasicFileSystem::openMemoryMappedFile(PathName(detail::appdataPath(), path).toString());
}

bool AppDataFileSystem::exists(const std::string& path) //Not on iOS.
{
	return BasicFileSystem::exists(PathName(detail::appdataPath(), path).toString()); //Not on iOS.
}

void AppDataFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not on iOS.
{
	BasicFileSystem::copy(PathName(detail::appdataPath(), path).toString(), newPath, createMissingDirectories);
}

void AppDataFileSystem::move(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not on iOS.
{
	BasicFileSystem::move(PathName(detail::appdataPath(), path).toString(), newPath, createMissingDirectories);
}

void AppDataFileSystem::rename(const std::string& path, const std::string& newName) //Not on iOS.
{
	BasicFileSystem::rename(PathName(detail::appdataPath(), path).toString(), PathName(detail::appdataPath(), newName).toString());
}

void AppDataFileSystem::remove(const std::string& path) //57-60
{
	BasicFileSystem::remove(PathName(detail::appdataPath(), path).toString()); //59
}

bool AppDataFileSystem::isFile(const std::string& path) //Not on iOS.
{
	return BasicFileSystem::isFile(PathName(detail::appdataPath(), path).toString());
}

bool AppDataFileSystem::isDirectory(const std::string& path) //67-70
{
	return BasicFileSystem::isDirectory(PathName(detail::appdataPath(), path).toString()); //69
}

void AppDataFileSystem::createDirectory(const std::string& path, bool createMissingDirectories) //72-75
{
	BasicFileSystem::createDirectory(PathName(detail::appdataPath(), path).toString(), createMissingDirectories); //74
}

std::vector<DirEntry> AppDataFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) //77-80
{
	return BasicFileSystem::enumerate(PathName(detail::appdataPath(), basedir).toString(), filepattern, types, recursive); //79
}

}