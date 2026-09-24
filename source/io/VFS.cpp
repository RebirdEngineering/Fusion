#include <io/VFS.h>
#include <io/AppDataInputStream.h>
#include <io/AppDataOutputStream.h>
#include <io/BundleInputStream.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <lang/Mutex.h>
#include <lang/Throwable.h>
#include <io/IOException.h>

using namespace lang;

namespace io
{

static std::map<std::string, VFS::ReadHandler> s_readHandlers;
static std::map<std::string, VFS::WriteHandler> s_writeHandlers;
static std::map<std::string, URI> s_links;
static std::string s_bundlePath;
static Mutex s_mutex;

static InputStream* openFileInputStream(const URI& uri)
{
	return new FileInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static OutputStream* openFileOutputStream(const URI& uri)
{
	return new FileOutputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static InputStream* openBundleInputStream(const URI& uri)
{
	return new BundleInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static InputStream* openAppDataInputStream(const URI& uri)
{
	return new AppDataInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static OutputStream* openAppDataOutputStream(const URI& uri)
{
	return new AppDataOutputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static void init()
{
	static bool s_initialized = false;
	if (!s_initialized)
	{
		s_initialized = true;
		VFS::addSchemeReadHandler("file", (VFS::ReadHandler)openFileInputStream);
		VFS::addSchemeReadHandler("bundle", (VFS::ReadHandler)openBundleInputStream);
		VFS::addSchemeReadHandler("appdata", (VFS::ReadHandler)openAppDataInputStream);
		VFS::addSchemeWriteHandler("file", (VFS::WriteHandler)openFileOutputStream);
		VFS::addSchemeWriteHandler("appdata", (VFS::WriteHandler)openAppDataOutputStream);
	}
}

URI resolve(const URI& uri)
{
	if (uri.isAbsolute() || uri.isOpaque())
	{
		return uri;
	}
	/*std::string path = uri.path();
	std::string newpath = uri.path();
	std::string newpart;
	iterator it;
	size_t offset;*/
}

InputStream* createReadStream(URI const& uri) //99
{
	//_ZNSt3mapISsPFPN2io11InputStreamERKNS0_3URIEESt4lessISsESaISt4pairIKSsS7_EEE4findERSB_
	//std::map <std::string, InputStream* (*)(const URI const&)>::iterator it;
	//if (uri.)
	//throwError(IOException(Format("Unsupported read scheme: \"{0}\" while trying to open: \"{1}\"", uri.scheme(), uri.toString())));
	assert("io::InputStream* io::createReadStream(URI const& uri) was not yet decompiled. Returning 0.");
	return 0;
	//return InputStream(uri);
}

void VFS::link(const URI& destination, const std::string& alias)
{
	Mutex::Lock lock(s_mutex);
	init();
	s_links[alias] = destination; //So this uses RCS, why?
}

void VFS::addSchemeReadHandler(const std::string& scheme, ReadHandler handler)
{
	Mutex::Lock lock(s_mutex);
	init();
	s_readHandlers[string::tolower(scheme)] = handler;
}

void VFS::addSchemeWriteHandler(const std::string& scheme, WriteHandler handler)
{
	Mutex::Lock lock(s_mutex);
	init();
	s_writeHandlers[string::tolower(scheme)] = handler;
}

P(InputStream) VFS::openRead(const URI& uri)
{
	Mutex::Lock lock(s_mutex);
	init();
	URI resolved = resolve(uri);
	return createReadStream(uri);
}

P(OutputStream) VFS::openWrite(const URI& uri)
{
	/*Mutex::Lock lock(s_mutex);
	init();
	URI resolved = resolve(uri);*/

	assert("P(OutputStream) VFS::openWrite(const URI& uri) was not yet decompiled. Returning 0.");

	return 0;
}

} // io
