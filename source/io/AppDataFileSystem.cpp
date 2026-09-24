#include <io/AppDataFileSystem.h>
#include <io/AppDataInputStream.h>
#include <io/AppDataOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/BasicFileSystem.h>
#include <io/PathName.h>
#include <io/detail/detail.h>

namespace io
{

using namespace detail;

P(AppDataInputStream) AppDataFileSystem::createInputStream(const std::string& path)
{
	return new AppDataInputStream(path);
}

P(AppDataOutputStream) AppDataFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories)
{
	if (createMissingDirectories)
	{
		const std::string& dir = PathName(path).parent().toString();
		if (dir.empty() && !isDirectory(dir))
			createDirectory(dir, true); //This is true everywhere, why is there a second check
	}
	return new AppDataOutputStream(path);
}

P(MemoryMappedFile) AppDataFileSystem::openMemoryMappedFile(const std::string& path) //Not defined in Seasons 4.1.0 iOS.
{
	return BasicFileSystem::openMemoryMappedFile(PathName(appdataPath(), path).toString());
}

bool AppDataFileSystem::exists(const std::string& path) //Not defined in Seasons 4.1.0 iOS
{
	return BasicFileSystem::exists(PathName(appdataPath(), path).toString());
}

void AppDataFileSystem::copy(const std::string& path, const std::string&, bool) //Not defined in Seasons 4.1.0 iOS
{
	BasicFileSystem::copy(PathName(appdataPath(), path).toString(), "", false); //TEMP
}

void AppDataFileSystem::move(const std::string& path, const std::string&, bool) //Not defined in Seasons 4.1.0 iOS
{
	BasicFileSystem::move(PathName(appdataPath(), path).toString(), "", false); //TEMP
}

void AppDataFileSystem::rename(const std::string& path, const std::string& newName) //Not defined in Seasons 4.1.0 iOS Name recovered from CFS
{
	BasicFileSystem::rename(PathName(appdataPath(), path).toString(), PathName(appdataPath(), newName).toString());
}

void AppDataFileSystem::remove(const std::string& path)
{
	BasicFileSystem::remove(PathName(appdataPath(), path).toString());
}

bool AppDataFileSystem::isFile(const std::string& path)
{
	return BasicFileSystem::isFile(PathName(appdataPath(), path).toString());
}

bool AppDataFileSystem::isDirectory(const std::string& path)
{
	return BasicFileSystem::isDirectory(PathName(appdataPath(), path).toString());
}

void AppDataFileSystem::createDirectory(const std::string& path, bool createMissingDirectories)
{
	BasicFileSystem::createDirectory(PathName(appdataPath(), path).toString(), createMissingDirectories);
}

std::vector<DirEntry> AppDataFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive)
{
	return BasicFileSystem::enumerate(PathName(appdataPath(), basedir).toString(), filepattern, types, recursive);
}

}