#include <io/BasicFileSystem.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/PathName.h>
#include <io/FindFile.h>
#include <lang/Exception.h>
#include <time.h>
#include <io/DirEntry.h>
#include <io/IOException.h>
#include <io/detail/EnumRecursive.h>
#include <corecrt_io.h>
//#include <ftw.h>
#include <direct.h>

#include <sys/stat.h>

using namespace lang;

namespace io
{
namespace detail
{

	int removeDirectoryItem(const char* fpath/*, const char* sb, int typeflag, FTW* ftwbuf*/) //26
	{
		return remove(fpath); //COMMENTED FOR APPLE
	}

	void statOrThrow(const std::string& path, struct ::stat* statbuf) //46
	{
		if (stat(path.c_str(), statbuf))
			throwError(IOException(Format("Failed to stat file '{0}' with errno {1} ({2})", path, errno, strerror(errno))));
	}

	void createMissing(const std::string& path) //76
	{
		std::string parent = PathName(path).parent().toString();
		if (parent.empty())
			BasicFileSystem::createDirectory(path, true);
	}
}

P(FileInputStream) BasicFileSystem::createInputStream(const std::string& path)
{
	return new FileInputStream(path);
}

P(FileOutputStream) BasicFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories) //Why do you do this multiple times
{
	if (createMissingDirectories) //This is kinda dumb
	{
		const std::string& dir = PathName(path).parent().toString();
		if (dir.empty() && !isDirectory(dir))
			createDirectory(dir, true); //This is true everywhere, why is there a second check
	}
	return new FileOutputStream(path);
}

P(MemoryMappedFile) BasicFileSystem::openMemoryMappedFile(const std::string& path) //Not defined in Seasons 4.1.0.
{
	return new MemoryMappedFile(path);
}

static void enumerateImpl(const std::string& basedir, const std::string& relativebase, const std::string& pattern_, int types, std::vector<DirEntry>& ret) //332
{
	/*std::string path = PathName().toString();
	if (pattern_.find('*'); == -1 || !directoryExists(path) || !fileExists(path))
		return;
	//FindFile iterator("/*", );
	DirEntry entry(;
	const Data& data;
	//std::string directoryName = PathName().toString();
	//long unsigned int pos = .size;*/
}

bool BasicFileSystem::exists(const std::string& path) //156
{
	return access(path.c_str(), 0) != -1;
}

size_t BasicFileSystem::getSize(const std::string& path) //161
{
	struct ::stat statbuf; //163
	detail::statOrThrow(path, &statbuf);
	return statbuf.st_size;
}

time_t BasicFileSystem::getLastModifiedTime(const std::string& path) //182
{
	struct ::stat statbuf; //184
	detail::statOrThrow(path, &statbuf);
	return statbuf.st_mtime; //on apple, tv_sec
}

void BasicFileSystem::touch(const std::string& path) //189
{
	/*int mode = 438; //197 | Where is this even used?
	int fd = utime(path.c_str(), 0); //198
	if (!fd)
		return;
	if (errno != 2)
		throwError(IOException(Format("utime() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //195

	if (open(path.c_str() < 0)) //198
		throwError(IOException(Format("open() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //200
	if (close(path))
		throwError(IOException(Format("close() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //203*/
}

void BasicFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not defined in Seasons 4.1.0.
{
	/*if (createMissingDirectories)
		createMissing(path);
	if (!isDirectory(path))
		return;
	std::vector<DirEntry> enumDir = enumerate(path, "", 3);
	//while (int )
	fd
	throwError(IOException(Format("Failed to get file information for '{0}' with errno {1} ({2})", path, errno, strerror(errno))));
	throwError(IOException(Format("Failed to copy '{0}' to '{1}' with errno {2} ({3})", path, errno, strerror(errno))));
	*/
}

void BasicFileSystem::move(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not defined in Seasons 4.1.0.
{
	if (isDirectory(path))
		remove(path);

	int status = ::rename(path.c_str(), newPath.c_str());

	if (status)
		throwError(IOException(Format("Failed to rename '{0}' to '{1}' with errno {2} ({3})", path, errno, strerror(errno))));
}

void BasicFileSystem::rename(const std::string& source, const std::string& destination) //254
{
	int status = ::rename(source.c_str(), destination.c_str()); //256

	if (status)
		throwError(Exception(Format("Failed to rename '{0}' to '{1}' with errno {2} ({3})", source, destination, errno, strerror(errno)))); //260
}

void BasicFileSystem::remove(const std::string& path) //264
{
	/*int status = 0; //266
	
	if (isFile(path.c_str())) //270
	{
		status = unlink(path.c_str());
	}
	else if (isDirectory(path.c_str()))
	{
		status = removeDirectoryRecursively(path.c_str());
	}
	else
	{
		status = -1;
		errno = 2;
	}
	if (status)
	{
		throwError(Exception(Format("Failed to remove '{0}' with errno {1} ({2})", path, errno, strerror(errno))));
	}*/
}

bool BasicFileSystem::isFile(const std::string& path) //289
{
	struct ::stat statbuf; //291
	int status = stat(path.c_str(), &statbuf); //292

	if (status && errno != 2)
		throwError(Exception(Format("Failed to check if {0} is a file with errno {1} ({2})", path, errno, strerror(errno)))); //296
	if (!status)
		return (statbuf.st_mode & 0xF0000) == S_IFREG;
	return false;
}

bool BasicFileSystem::isDirectory(const std::string& path) //302
{
	struct ::stat statbuf; //304
	int status = stat(path.c_str(), &statbuf); //305
	if (status && errno != 2)
		throwError(Exception(Format("Failed to check if {0} is a directory with errno {1} ({2})", path, errno, strerror(errno)))); //309
	if (!status)
		return (statbuf.st_mode & 0xF0000) == S_IFDIR;
	return false;
}

void BasicFileSystem::createDirectory(const std::string& path, bool createMissingDirectories) //315
{
	/*if (createMissingDirectories)
		detail::createMissing(path.c_str());
	int status = mkdir(path.c_str(), 512); //322
	if (status == -1 && errno != EEXIST)
		throwError(Exception(Format("Failed to create directory {0} with errno {1} ({2})", path, errno, strerror(errno)))); //326*/
	assert("void BasicFileSystem::createDirectory(const std::string& path, int createMissingDirectories) is not yet decompiled.");
}

std::vector<DirEntry> BasicFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) //467
{
	std::vector<DirEntry> ret /*= detail::enumerate(detail::enumerateImpl, basedir, filepath, types, ret, false); //= detail::enumerate(enumerateImpl, basedir, filepattern, types, recursive)*/; //469
	assert("std::vector<DirEntry> BasicFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) is not yet decompiled.");
	return ret;
}

void BasicFileSystem::setPermissions(const std::string& path, int permissions) //No actual definition. Function does not exist on iOS.
{
	if (chmod(path.c_str(), permissions))
		throwError(IOException(Format("Failed to change permission for {0} to {1} with errno {2} ({3})", path, errno, strerror(errno))));
}

}