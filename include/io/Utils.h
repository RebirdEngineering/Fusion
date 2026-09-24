#ifndef _IO_UTILS_H
#define _IO_UTILS_H

#include <io/InputStream.h>
#include <io/OutputStream.h>

namespace io
{

size_t copy(InputStream& in, OutputStream& out);

}

#endif