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
    //typedef OutputStream** WriteHandler(const URI*);

    typedef InputStream *(*ReadHandler)(const URI&); //37
    typedef OutputStream *(*WriteHandler)(const URI&); //38

    P(InputStream) openRead(const URI&); //44

    P(OutputStream) openWrite(const URI&); //50

    void link(const URI& destination, const std::string& alias); //68

    static void addSchemeReadHandler(const std::string& scheme, ReadHandler handler); //73

    static void addSchemeWriteHandler(const std::string& scheme, WriteHandler handler); //78

    void copy(const URI&, const URI&); //84

    void move(const URI&, const URI&); //90

    void rename(const URI&, const std::string&); //96

    void remove(const URI&); //101

    void mkdir(const URI&); //107

    void setMappings(const std::map<char, char>&); //112

    std::map<std::string, std::string>& getMappings(); //117

    URIIterator enumerate(const URI&); //124
};

}

#endif // !_IO_VFS_H
