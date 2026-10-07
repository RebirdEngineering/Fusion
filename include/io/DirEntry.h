#ifndef _IO_DIRENTRY_H
#define _IO_DIRENTRY_H

#include <lang/pp.h>

namespace io
{

struct DirEntry
{
public:
    DirEntry(); //15

    DirEntry(const std::string&, uint32_t); //20

    bool operator==(const DirEntry&) const; //25
    bool operator<(const DirEntry&) const; //30

    std::string relativepath; //43
    uint32_t    flags; //44

    enum Type //46
    {
        TYPE_FILE = 1,
        TYPE_DIR
    };
};

}

#endif // !_IO_DIRENTRY_H