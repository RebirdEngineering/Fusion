#include <io/BasicFileSystem.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/PathName.h>
#include <io/FindFile.h>
#include <lang/Exception.h>
#include <io/DirEntry.h>
#include <io/IOException.h>
#include <io/detail/EnumRecursive.h>

#include <corecrt_io.h> //Windows hotfix, to remove later, just so we can compile it on Win for testing
#include <sys/stat.h>
//#include <utime.h>

//#include <ftw.h>

using namespace lang;

int removeDirectoryItem(const char* fpath, const struct stat* sb, int typeflag/* FTW* ftwbuf*/) //26, TODO MATCH THIS SYMBOL
{
	return remove(fpath); //COMMENTED FOR APPLE
}

void statOrThrow(const std::string& path, struct stat* statbuf) //46
{
	if (stat(path.c_str(), statbuf)) //48
		throwError(io::IOException(Format("Failed to stat file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //49
}

void createMissing(const std::string& path) //76
{
	std::string parent = io::PathName(path).parent().toString(); //78

	if (parent.empty()) //80
		io::BasicFileSystem::createDirectory(path, true);
}

namespace io
{

P(FileInputStream) BasicFileSystem::createInputStream(const std::string& path) //Not on iOS.
{
	return new FileInputStream(path);
}

P(FileOutputStream) BasicFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories) //Not on iOS.
{
	if (createMissingDirectories)
	{
		const std::string& dir = PathName(path).parent().toString();
		if (dir.empty() && !isDirectory(dir))
			createDirectory(dir, true); //This is true everywhere, why is there a second check
	}

	return new FileOutputStream(path);
}

P(MemoryMappedFile) BasicFileSystem::openMemoryMappedFile(const std::string& path) //Not on iOS.
{
	return new MemoryMappedFile(path);
}

bool BasicFileSystem::exists(const std::string& path) //156
{
	return access(path.c_str(), 0) != -1;
}

size_t BasicFileSystem::getSize(const std::string& path) //161
{
	struct ::stat statbuf; //163
	statOrThrow(path, &statbuf);
	return statbuf.st_size;
}

time_t BasicFileSystem::getLastModifiedTime(const std::string& path) //182
{
	struct ::stat statbuf; //184
	statOrThrow(path, &statbuf);
	return statbuf.st_mtime; //on apple, tv_sec
}

void BasicFileSystem::touch(const std::string& path) //189
{
	/*if (!utime(path.c_str())) //191
		return;

	if (errno != 2) //194
		throwError(IOException(Format("utime() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //195

	int mode = 438; //197 | Where is this even used?
	int fd = utime(path.c_str(), 0); //198
	if (open(path.c_str() < 0, 513, mode)) //199
		throwError(IOException(Format("open() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //200

	if (close(path)) //202
		throwError(IOException(Format("close() failed for file '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //203*/

	assert("void BasicFileSystem::touch(const std::string& path) was not yet decompiled.");
}

void BasicFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not on iOS.
{
	/*if (createMissingDirectories)
		createMissing(path);

	if (isDirectory(path))
	{
		std::vector<DirEntry> ret = enumerate(path, "", 3);
		for (int i = 0; i < ret.size(); i++)
		{
			if (!ret[i].relativepath.empty()) //No pointer?
			{
				if (PathName(ret[i].relativepath).filename() != ".")
				{
					if (PathName(ret[i].relativepath).filename() != "..")
						copy(ret[i].relativepath + "/", newPath + "/", createMissingDirectories);
				}
			}
		}
	}
	
	else if 
	{
	}

	throwError(IOException(Format("Failed to get file information for '{0}' with errno {1} ({2})", path, errno, strerror(errno))));
	throwError(IOException(Format("Failed to copy '{0}' to '{1}' with errno {2} ({3})", path, errno, strerror(errno))));*/
	
	assert("void io::BasicFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories) was not yet decompiled.");
}

void BasicFileSystem::move(const std::string& path, const std::string& newPath, bool createMissingDirectories) //Not on iOS.
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
		throwError(Exception(Format("Failed to rename '{0}' to '{1}' with errno {2} ({3})", source, destination, errno, strerror(errno)))); //260 | Did you meant move?
}

void BasicFileSystem::remove(const std::string& path) //264
{
	/*int status = 0; //266
	
	if (isFile(path.c_str())) //270
		status = unlink(path.c_str());

	else if (isDirectory(path.c_str()))
		status = removeDirectoryItem(path.c_str(), 64, 5);

	else
	{
		status = -1;
		errno = 2;
	}

	if (status)
		throwError(Exception(Format("Failed to remove '{0}' with errno {1} ({2})", path, errno, strerror(errno)))); //285*/
	assert("void io::BasicFileSystem::remove(const std::string& path) is not yet decompiled.");
}

bool BasicFileSystem::isFile(const std::string& path) //289
{
	struct ::stat statbuf; //291
	int status = stat(path.c_str(), &statbuf); //292
	if (status)
		return false;
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
	if (status)
		return false;
	if (status && errno != ENOENT)
		throwError(Exception(Format("Failed to check if {0} is a directory with errno {1} ({2})", path, errno, strerror(errno)))); //309

	if (!status)
		return (statbuf.st_mode & 0xF0000) == S_IFDIR; //312
}

void BasicFileSystem::createDirectory(const std::string& path, bool createMissingDirectories) //315
{
	/*if (createMissingDirectories)
		createMissing(path.c_str());
	int status = mkdir(path.c_str(), 512); //322
	if (status == -1 && errno != EEXIST)
		throwError(Exception(Format("Failed to create directory {0} with errno {1} ({2})", path, errno, strerror(errno)))); //326*/
	assert("void io::BasicFileSystem::createDirectory(const std::string& path, int createMissingDirectories) is not yet decompiled.");
}

void enumerateImpl(const std::string& basedir, const std::string& relativebase, const std::string& pattern_, int types, std::vector<DirEntry>& ret) //332-464
{
	/*//if (pattern_.find('*') != -1) return; //334 | Ok how does this even work? Is there supposed to be a var here? It's not in DWARF?
	std::string path = PathName(basedir, relativebase).toString(); //335
	if (!BasicFileSystem::isDirectory(path) || !BasicFileSystem::isFile(path))
		return;

	if (!pattern_.find('*') && BasicFileSystem::isFile(path)) //Redundant?
		path += "/*"; //419

	FindFile iterator(path, FindFile::FIND_DIRECTORIESONLY); //424 | How are the find flags set?

	while (iterator.more()) //426
	{
		const FindFile::Data& data = iterator.data(); //428
		DirEntry entry; //430

		if ((data.attrib & FindFile::ATTRIB_SUBDIR) != 0)
		{
			if ((types & DirEntry::TYPE_DIR) != 0)
			{
				entry.flags = DirEntry::TYPE_DIR;
				std::string directoryName = PathName(data.path).toString(); //438
				if (directoryName[0] == '/')
					directoryName.erase(directoryName.size() - 1); //440

				entry.relativepath = PathName(relativebase, entry.relativepath).toString();

				ret.push_back(entry); //448
			}
		}

		//if (?.size() > 0) //440
		//{
			//.size() //442
		//}

		//long unsigned int pos = .size; //445
		//.substr(); //446

		//ret.push_back(entry); //448


		entry.relativepath = PathName(relativebase).toString(); //456
		ret.push_back(entry); //457

		iterator.next(); //461
	}*/
	assert("void io::enumerateImpl(const std::string& basedir, const std::string& relativebase, const std::string& pattern_, int types, std::vector<DirEntry>& ret) is not yet decompiled.");
}

std::vector<DirEntry> BasicFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) //467-472
{
	std::vector<DirEntry> ret; //469
	detail::enumerate(enumerateImpl, basedir, filepattern, types, false, ret); //470
	return ret;
}

void BasicFileSystem::setPermissions(const std::string& path, int permissions) //Not on iOS.
{
	int status = chmod(path.c_str(), permissions);
	if (status)
		throwError(IOException(Format("Failed to change permission for {0} to {1} with errno {2} ({3})", path, permissions, errno, strerror(errno))));
}

}