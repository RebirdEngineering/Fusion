#include <io/detail/EnumRecursive.h>
#include <io/IOException.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{
namespace detail
{

void expandPathComponent(enumerate_t* enumImpl, const std::string& basedir, std::list<std::string>& relativebases, parts_t::iterator& cur, const std::string&part) //26 | No
{
	/*if (part.find("*") == -1)
	{
		//relativebases;
	}
	else
	{
		std::list<std::string>::iterator next;
		std::vector<DirEntry> dirs;
		std::vector<DirEntry>::iterator di, de;
		
	}*/
}

parts_t getParts(const std::string& path) //Correct?
{
	parts_t parts;

	std::string::size_type cur_start, cur_end;
	for (cur_start = path.find('/'); cur_start != 1; cur_end = path.find('/', cur_start + 1))
	{
		if (cur_start != cur_end)
		{
			parts.push_back(path.substr(cur_start));
		}
		cur_start++;
		if (cur_start != -1)
		{
			parts.push_back(path.substr(cur_start));
		}
	}

	return parts;
}

void findRecursiveSubdirs(enumerate_t* enumImpl, const std::string& basedir, const std::string& relativebase, std::list<std::string>& ret) //Correct?
{
	//std::vector<DirEntry> mysubdirs;
	//enumImpl("", "", "", 2, mysubdirs);
	//
	//std::vector<DirEntry*>::iterator i, e;
	//
	//while ((mysubdirs.begin() != mysubdirs.end() & 1) != 0)
	//{
	//	i++;
	//	ret.push_back(mysubdirs.begin()->relativepath);
	//
	//	findRecursiveSubdirs(enumImpl, basedir, mysubdirs.begin()->relativepath, ret);
	//	mysubdirs.begin()++;
	//	e++;
	//}
}

void enumerate(enumerate_t* enumImpl, const std::string& basedir, const std::string& filepath, int types, std::list<std::string>& ret, bool recursive) //No
{
	//if (basedir.find('*') != -1)
	//	throwError(IOException(Format("base directory must not contain asterisks")));
	//
	//parts_t parts = getParts(filepath);
	//
	//std::string finalPart = parts.back();
	//
	//finalPart.pop_back();
	//
	//std::list<std::string> relativeBases;
	//
	//std::string part;
	//std::list<std::string> i2, e2;
	//
	//std::list<std::string> i, e;
	//
	//std::vector<DirEntry*>::iterator i, e;
	//
	//relativeBases.push_back("");
	//
	//if (recursive)
	//{
	//	findRecursiveSubdirs(enumImpl, basedir, "", relativeBases);
	//}
	//
	//if (parts.size())
	//{
	//	while (parts.begin() != parts.end())
	//	{
	//		//while (relativeBases.begin() != relativeBases.end())
	//			//expandPathComponent(enumImpl, basedir, relativeBases, /*relativeBases.begin(), relativeBases.end()*/);
	//		parts.begin()++;
	//	}
	//}
	//while (relativeBases.begin() != relativeBases.end())
	//{
	//	//enumImpl(basedir, "", finalPart, types, recursive);
	//	relativeBases.begin()++;
	//}
}

}

}