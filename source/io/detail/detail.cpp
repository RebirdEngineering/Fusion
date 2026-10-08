#include <io/detail/detail.h>
#include <io/PathName.h>

namespace io
{
namespace detail
{

static std::string sm_bundlePath = "."; //11
static std::string sm_appdataPath = "."; //12
static std::string sm_fileCachePath = ""; //13

static std::string sm_defaultCacheName = "Fusion-Cache"; //15

const std::string& bundlePath() //18
{
	return sm_bundlePath;
}

const std::string& appdataPath() //23
{
	return sm_appdataPath;
}

const std::string& fileCachePath() //28
{
	if (sm_fileCachePath.empty()) //30
		sm_fileCachePath = PathName(sm_fileCachePath, sm_defaultCacheName).toString(); //32

	return sm_fileCachePath;
}

void setBundlePath(const std::string& path) //38
{
	sm_bundlePath = path; //40
}

void setAppdataPath(const std::string& path) //43
{
	sm_appdataPath = path; //45
}

void setFileCachePath(const std::string& path) //48
{
	sm_fileCachePath = path; //50
}

} // detail
} // io
