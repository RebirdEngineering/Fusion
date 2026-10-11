#ifndef _IO_DIRENTRY_H
#define _IO_DIRENTRY_H

#include <lang/pp.h>

namespace io
{

struct DirEntry
{
public:
    DirEntry() //15
    {
        flags = !relativepath.empty() ? TYPE_DIR : TYPE_FILE; //?
    }

    DirEntry(const std::string& relativepath, uint32_t flags = 0) //20
    {
        this->relativepath = relativepath, this->flags = flags; //?
    }

    bool operator==(const DirEntry& other) const //25
    {
        return this == &other;
    }

    bool operator<(const DirEntry& other) const //30
    {
        return this < &other;
    }

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