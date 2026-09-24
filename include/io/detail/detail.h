#ifndef _IO_DETAIL_DETAIL_H
#define _IO_DETAIL_DETAIL_H

#include <lang/pp.h>

namespace io
{
namespace detail
{

const std::string& bundlePath();

const std::string& appdataPath();

const std::string& fileCachePath();

void setBundlePath(const std::string& path);

void setAppdataPath(const std::string& path);

void setFileCachePath(const std::string& path);

}
}

#endif