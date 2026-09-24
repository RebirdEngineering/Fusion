#ifndef _IO_DIRENTRY_H
#define _IO_DIRENTRY_H

#include <lang/pp.h>

namespace io
{

class DirEntry
{
public:
    DirEntry();

    DirEntry(const std::string&, uint32_t);

    enum Type
    {
        TYPE_FILE = 1,
        TYPE_DIR
    };

    std::string& relativepath;
    uint32_t    flags;
private:
    bool operator==(const DirEntry&) const;
    bool operator<(const DirEntry&) const;
};

}

#endif // !_IO_DIRENTRY_H