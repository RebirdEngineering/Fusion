#ifndef IO_BUNDLEFILESYSTEM_H
#define IO_BUNDLEFILESYSTEM_H

#include <io/DirEntry.h>
#include <lang/Ptr.h>

namespace io
{
	class BundleInputStream;

class BundleFileSystem
{
public:
	static P(BundleInputStream) createInputStream(const std::string& path);

	static bool exists(const std::string& path);

	static bool isFile(const std::string&);

	static bool isDirectory(const std::string& path);

	static std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive = false);
};

}

#endif // !IO_BUNDLEFILESYSTEM_H