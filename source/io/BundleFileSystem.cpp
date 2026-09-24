#include <io/BundleFileSystem.h>
#include <io/BasicFileSystem.h>
#include <io/BundleInputStream.h>
#include <io/detail/detail.h>
#include <io/PathName.h>
#include <lang/Exception.h>

namespace io
{
using namespace detail;

#ifdef PLATFORM_ANDROID //This class only exists on Android as it reads the APK using Java classes.
#include <java/jni.h>

USING_NAMESPACE(java)

P(BundleInputStream) BundleFileSystem::createInputStream(const std::string& path)
{
	return new BundleInputStream(PathName(bundlePath(), path).toString());
}

bool BundleFileSystem::isFile(const std::string& path)
{
	
}

bool BundleFileSystem::isDirectory(const std::string& path)
{
	
}

std::vector<DirEntry> BundleFileSystem::enumerate(const std::string& basedir, const string& filepattern, int types, bool recursive);
{
	std::string jniClass = jni::FindClass("com/rovio/fusion/FileReader");
	throwError(JavaException(Format("Class \"{0}\" not found", jniClass)));
	throwError(JavaException(Format("{0} \"{1}\" with signature \"{2}\" not found", "StaticMethod" , "enumerate", "(Ljava/lang/String;)[Ljava/lang/String;")));
}

bool BundleFileSystem::exists(const std::string& path)
{
	jni::FindClass("com/rovio/fusion/FileReader");
	throwError(JavaException(Format("Java method threw an exception")));
	throwError(JavaException(Format("{0}: out of memory", "NewStringUTF")));
}

#else
bool BundleFileSystem::exists(const std::string& path) //iOS and Android, it's really just here for AB's LuaManager::findScriptPath. | 14
{
	return BasicFileSystem::exists(PathName(bundlePath(), path).toString());
}
#endif

}