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

static InputStream* openFileInputStream(const URI& uri) //16
{
	return new FileInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static OutputStream* openFileOutputStream(const URI& uri) //21
{
	return new FileOutputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static InputStream* openBundleInputStream(const URI& uri) //26
{
	return new BundleInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static InputStream* openAppDataInputStream(const URI& uri) //31
{
	return new AppDataInputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static OutputStream* openAppDataOutputStream(const URI& uri) //36
{
	return new AppDataOutputStream(uri.isOpaque() ? uri.schemeSpecificPart() : uri.path());
}

static std::map<std::string, VFS::ReadHandler> s_readHandlers; //41
static std::map<std::string, VFS::WriteHandler> s_writeHandlers; //42
static std::map<std::string, URI> s_links; //43
static std::string s_bundlePath; //44
static Mutex s_mutex; //45

static void init() //48
{
	static bool s_initialized = false;
	if (!s_initialized)
	{
		s_initialized = true;
		VFS::addSchemeReadHandler("file", (VFS::ReadHandler)openFileInputStream); //53
		VFS::addSchemeReadHandler("bundle", (VFS::ReadHandler)openBundleInputStream); //54
		VFS::addSchemeReadHandler("appdata", (VFS::ReadHandler)openAppDataInputStream); //55
		VFS::addSchemeWriteHandler("file", (VFS::WriteHandler)openFileOutputStream); //56
		VFS::addSchemeWriteHandler("appdata", (VFS::WriteHandler)openAppDataOutputStream); //57
	}
}

URI resolve(const URI& uri) //61-96
{
	/*if (uri.scheme().empty() || uri.scheme() == "vfs") //64
	{
		std::string path = uri.path(); //66

		if (path.empty()) //68
		{
			std::map<std::string, URI>::iterator it = s_links.find(path); //70

			std::string newpath = uri.path(); ///73
			std::string newpart = uri.toString(); //74
			//if (it == s_links.begin()) //75 | ?
				//return resolve(uri); //76

			//if (path.find_first_of('/')) //82
			//.find_first_of()
		}

		else
			throwError(IOException(Format("Unable to resolve vfs path \"{0}\"", uri.toString()))); //92
	}

	//.begin() //75
	//size_t offset; //85

	//.begin(); //88
	//}*/
	assert("io::URI io::resolve(URI const& uri) was not yet decompiled. Returning 0.");
	return 0;
}

InputStream* createReadStream(URI const& uri) //99
{
	//std::map <std::string, InputStream* (*)(const URI const&)>::iterator it = s_readHandlers.find(uri.scheme()); //101
	//if (uri.)
	//throwError(IOException(Format("Unsupported read scheme: \"{0}\" while trying to open: \"{1}\"", uri.scheme(), uri.toString()))); //103
	assert("io::InputStream* io::createReadStream(URI const& uri) was not yet decompiled. Returning 0.");
	return 0; //105
	//return InputStream(uri);
}

OutputStream* createWriteStream(URI const& uri) //Function name only exists in Trilogii and Android but given there's a line jump it's prob here.
{
	//std::map <std::string, OutputStream* (*)(const URI const&)>::iterator it = s_writeHandlers.find(uri.scheme());
	assert("io::OutputStream* io::createWriteStream(URI const& uri) was not yet decompiled. Returning 0.");
	return 0;
	//return OutputStream(uri);
}

P(InputStream) VFS::openRead(const URI& uri) //115
{
	Mutex::Lock lock(s_mutex); //117
	init();
	URI resolved = resolve(uri); //119
	return createReadStream(resolved); //120
}

P(OutputStream) VFS::openWrite(const URI& uri)
{
	Mutex::Lock lock(s_mutex);
	init();
	URI resolved = resolve(uri);
	return createWriteStream(resolved);
}

void VFS::link(const URI& destination, const std::string& alias) //131-136
{
	Mutex::Lock lock(s_mutex); //133
	init();
	s_links[alias] = destination; //135 | So this uses RCS, why?
}

void VFS::addSchemeReadHandler(const std::string& scheme, ReadHandler handler) //138-143
{
	Mutex::Lock lock(s_mutex); //140
	init();
	s_readHandlers[string::tolower(scheme)] = handler;
}

void VFS::addSchemeWriteHandler(const std::string& scheme, WriteHandler handler) //145-150
{
	Mutex::Lock lock(s_mutex); //147
	init();
	s_writeHandlers[string::tolower(scheme)] = handler;
}

} // io
