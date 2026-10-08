#ifndef _IO_ENUMRECURSIVE_H
#define _IO_ENUMRECURSIVE_H

#include <io/DirEntry.h>

namespace io
{
namespace detail
{

typedef std::vector<std::string> parts_t;
typedef void enumerate_t(const std::string&, const std::string&, const std::string&, int, std::vector<DirEntry>&);

void expandPathComponent(enumerate_t* enumImpl, const std::string& basedir, std::list<std::string>& relativebases, std::list<std::string>::iterator& cur, const std::string& part);
parts_t getParts(const std::string& path);
void findRecursiveSubdirs(enumerate_t* enumImpl, const std::string& basedir, const std::string& relativebase, std::list<std::string>& ret);
void enumerate(enumerate_t* enumImpl, const std::string& basedir, const std::string& filepath, int types, bool recursive, std::vector<DirEntry>& ret);

}
}

#endif //_IO_ENUMRECURSIVE_H