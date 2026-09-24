#include <io/DirEntry.h>

namespace io
{
namespace detail
{

typedef std::vector<std::string> parts_t;
typedef void enumerate_t(const std::string&, const std::string&, const std::string&, int, std::vector<DirEntry>&);

void expandPathComponent(enumerate_t* enumImpl, const std::string& basedir, std::list<std::string>& relativebases, parts_t::iterator& cur, const std::string& part);
parts_t getParts(const std::string& path);
void findRecursiveSubdirs(enumerate_t* enumImpl, const std::string& basedir, const std::string& relativebase, std::list<std::string>& ret);
void enumerate(enumerate_t* enumImpl, const std::string& basedir, const std::string& filepath, int types, std::list<std::string>& ret, bool recursive);

}
}