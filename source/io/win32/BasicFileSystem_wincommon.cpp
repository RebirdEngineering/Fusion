#include <io/BasicFileSystem.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/MemoryMappedFile.h>
#include <io/PathName.h>
#include <io/FindFile.h>
#include <lang/Exception.h>
#include <lang/Log.h>
#include <io/DirEntry.h>
#include <io/IOException.h>
#include <io/detail/EnumRecursive.h>

#include <windows.h>

#include <fileapi.h>

using namespace lang;

int getAttributes(std::string path, WIN32_FILE_ATTRIBUTE_DATA data) //466250 | Recover name from assert in ABC 4.0.0
{
	if (!GetFileAttributesExW(string::towstring(path).c_str(), GetFileExInfoStandard, &data))
		return data.dwFileAttributes;

	int error = GetLastError();

	if (error != ERROR_FILE_NOT_FOUND && error != ERROR_PATH_NOT_FOUND)
	{
		LANG_LOG_DEBUG("BasicFileSystem", LANG_LOG_PRIORITY_WARN, "GetFileAttributesExW: %s", ); //49 (ABC 4.0.0 PC and WP8)
	}

	return -1;
}

namespace io
{
	//P(FileInputStream) BasicFileSystem::createInputStream(const std::string& path) //Never seen.
	//{
	//	return new FileInputStream(path);
	//}

	P(FileOutputStream) BasicFileSystem::createOutputStream(const std::string& path, bool createMissingDirectories)
	{
		/*if (createMissingDirectories)
		{
			const std::string& dir = PathName(path).parent().toString();
			if (dir.empty() && !isDirectory(dir))
				createDirectory(dir, true); //This is true everywhere, why is there a second check
		}*/

		return new FileOutputStream(path);
	}

	/*P(MemoryMappedFile) BasicFileSystem::openMemoryMappedFile(const std::string& path) //Likely doesn't exist.
	{
		return new MemoryMappedFile(path);
	}*/

	bool sub_466250(const std::string& path)
	{
		return false;
	}

	bool BasicFileSystem::exists(const std::string& path) //466310(?) | TODO
	{
		return sub_466250(PathName(path).toString());
	}

	size_t BasicFileSystem::getSize(const std::string& path) //TODO
	{
		return 0;
	}

	time_t BasicFileSystem::getLastModifiedTime(const std::string& path) //TODO
	{
		return 0;
	}

	void BasicFileSystem::touch(const std::string& path) //TODO | 4674E0
	{
		/*HANDLE file = CreateFileW();

		if (file == INVALID_HANDLE_VALUE)
		{
			throwError(IOException(Format("Failed to open file ({0}): {1}", )))
		}*/
	}

	void BasicFileSystem::copy(const std::string& path, const std::string& newPath, bool createMissingDirectories) //TODO
	{
	}

	void BasicFileSystem::move(const std::string& path, const std::string& newPath, bool createMissingDirectories) //TODO
	{
		
	}

	void BasicFileSystem::rename(const std::string& source, const std::string& destination) //TODO
	{
		
	}

	void BasicFileSystem::remove(const std::string& path) //467930
	{
		//std::string r;
		//4676F0

		//u16string conv = string::toUTF16string(path);

		//if (!)
			//throwError(IOException(Format("Deleting {0} failed", conv)));

		//LANG_LOG_DEBUG("BasicFileSystem", "BasicFileSystem::remove failed : {0} (errno{1})", );

		assert("void io::BasicFileSystem::remove(const std::string& path) for MSFT is not yet decompiled.");
	}

	bool BasicFileSystem::isFile(const std::string& path) //TODO | 466360
	{
		return false; //sub_466250(;
	}

	bool BasicFileSystem::isDirectory(const std::string& path) //TODO | 4663C0
	{
		return false; //466250(
	}

	void BasicFileSystem::createDirectory(const std::string& path, bool createMissingDirectories) //TODO | 466420
	{
		//if ()

		//
	}

	void enumerateImpl(const std::string& basedir, const std::string& relativebase, const std::string& pattern_, int types, std::vector<DirEntry>& ret) //4668C0
	{
		//Looks like FindFile

		//std::string path = PathName(basedir, relativebase).toString(); //335
		//if (!BasicFileSystem::isDirectory(path) || !BasicFileSystem::isFile(path))
		//	return;

		assert("void io::enumerateImpl(const std::string& basedir, const std::string& relativebase, const std::string& pattern_, int types, std::vector<DirEntry>& ret) for MSFT is not yet decompiled.");
	}

	std::vector<DirEntry> BasicFileSystem::enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive) //466EB0
	{
		std::vector<DirEntry> ret;
		detail::enumerate(enumerateImpl, basedir, filepattern, types, false, ret);
		return ret;
	}

	void BasicFileSystem::setPermissions(const std::string& path, int permissions) //TODO
	{
	}
}