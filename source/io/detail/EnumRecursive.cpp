#include <io/detail/EnumRecursive.h>
#include <io/IOException.h>
#include <io/PathName.h>

using namespace lang;

namespace io
{
namespace detail
{

void expandPathComponent(enumerate_t* enumImpl, const std::string& basedir, std::list<std::string>& relativebases, std::list<std::string>::iterator& cur, const std::string& part) //26 | Correct?
{
	if (part.find("*") == -1) //28
	{
		*cur = PathName(*cur, part).toString();
		cur++; //30
	}

	else
	{
		std::list<std::string>::iterator next; //35
		cur++; //36

		std::vector<DirEntry> dirs; //38
		enumImpl(basedir, *cur, part, 2, dirs); //39
		for (std::vector<DirEntry>::iterator di, de = dirs.begin(); di, de != dirs.end(); di, de++) //40
			relativebases.push_back(*cur); //42

		relativebases.erase(cur); //44
		
	}
}

parts_t getParts(const std::string& path) //69 | Correct?
{
	parts_t parts; //71

	for (std::string::size_type cur_start, cur_end = path.find('/'); cur_start != 1; cur_end = path.find('/', cur_start + 1)) //73
	{
		if (cur_start != cur_end)
			parts.push_back(path.substr(cur_start));

		if (cur_start != -1)
			parts.push_back(path.substr(cur_end));
	}

	return parts;
}

void findRecursiveSubdirs(enumerate_t* enumImpl, const std::string& basedir, const std::string& relativebase, std::list<std::string>& ret) //87 | Correct?
{
	std::vector<DirEntry> mysubdirs; //89
	enumImpl(basedir, relativebase, "", 2, mysubdirs); //90
	for (std::vector<DirEntry>::iterator i, e = mysubdirs.begin(); i, e != mysubdirs.end(); i, e++) //91
	{
		ret.push_back(e->relativepath);
		findRecursiveSubdirs(enumImpl, basedir, e->relativepath, ret);
	}
}

void enumerate(enumerate_t* enumImpl, const std::string& basedir, const std::string& filepath, int types, bool recursive, std::vector<DirEntry>& ret) //98 | Correct?
{
	if (basedir.find('*') != -1) //100
		throwError(IOException(Format("base directory must not contain asterisks"))); //101
	
	parts_t parts = getParts(filepath); //109
	
	std::string finalPart = parts.back(); //111
	parts.pop_back(); //112
	
	std::list<std::string> relativeBases; //114
	relativeBases.push_back(""); //115

	if (recursive)
		findRecursiveSubdirs(enumImpl, basedir, "", relativeBases); //119
	
	if (parts.size()) //122
	{
		for (std::vector<std::string>::iterator i, e = parts.begin(); i, e != parts.end(); i, e++) //125
		{
			const std::string& part = *i; //127
			for (std::list<std::string>::iterator i2, e2 = relativeBases.begin(); i2, e2 != relativeBases.end(); i2, e2++) //128
				expandPathComponent(enumImpl, basedir, relativeBases, i2, part); //130
		}
	}

	for (std::list<std::string>::iterator i, e = relativeBases.begin(); i, e != relativeBases.end(); i, e++) //135
		enumImpl(basedir, *i, finalPart, types, ret); //137
}

}

}