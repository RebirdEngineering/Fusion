#ifndef _UTIL_STREAMUTIL_H
#define _UTIL_STREAMUTIL_H

#include <lang/Optional.h>
#include <io/InputStream.h>

namespace util
{

std::vector<unsigned char> decryptAndDecompress(io::InputStream& input, lang::optional<std::vector<unsigned char>>& encryptionKey, bool zipped);

}

#endif