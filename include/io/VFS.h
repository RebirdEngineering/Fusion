#ifndef _IO_VFS_H
#define _IO_VFS_H

#include <lang/Ptr.h>
#include <io/URI.h>

namespace io
{
    class InputStream;
    class OutputStream;
class VFS
{
public:
    class URIIterator;

    //typedef InputStream** ReadHandler(const URI*);
    //typedef InputStream* (*)(const URI&);
    typedef InputStream *(*ReadHandler)(const URI&);

    //typedef OutputStream** WriteHandler(const URI*);
    typedef OutputStream *(*WriteHandler)(const URI&);

    static P(InputStream) openRead(const URI&);

    static P(OutputStream) openWrite(const URI&);

    static void link(const URI& destination, const std::string& alias);

    static void addSchemeReadHandler(const std::string& scheme, ReadHandler handler);

    static void addSchemeWriteHandler(const std::string& scheme, WriteHandler handler);

    static void copy(const URI&, const URI&);

    static void move(const URI&, const URI&);

    static void rename(const URI&, const std::string&);

    static void remove(const URI&);

    static void mkdir(const URI&);

    static void setMappings(const std::map<char, char>&);

    static std::map<char, char>& getMappings();

    static URIIterator enumerate(const URI&);
};

}

#endif // !_IO_VFS_H
