#include <io/detail/detail.h>
#include <io/PathName.h>

namespace io
{
namespace detail
{

std::string sm_bundlePath = ".";
std::string sm_appdataPath = ".";
std::string sm_fileCachePath = "";

std::string sm_defaultCacheName = "Fusion-Cache";

const std::string& bundlePath()
{
	return sm_bundlePath;
}

const std::string& appdataPath()
{
	return sm_appdataPath;
}

const std::string& fileCachePath()
{
	if (sm_fileCachePath.empty())
	{
		sm_fileCachePath = PathName(sm_fileCachePath, sm_defaultCacheName).toString();
	}
	return sm_fileCachePath;
}

void setBundlePath(const std::string& path)
{
	sm_bundlePath = path;
}

void setAppdataPath(const std::string& path)
{
	sm_appdataPath = path;
}

void setFileCachePath(const std::string& path)
{
	sm_fileCachePath = path;
}

} // detail
} // io
