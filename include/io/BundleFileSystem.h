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
	P(BundleInputStream) createInputStream(const std::string& path);

	bool exists(const std::string& path);

	bool isFile(const std::string&);

	bool isDirectory(const std::string& path);

	std::vector<DirEntry> enumerate(const std::string& basedir, const std::string& filepattern, int types, bool recursive = false);
};

}

#endif // !IO_BUNDLEFILESYSTEM_H