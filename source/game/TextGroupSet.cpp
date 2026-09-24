#include <game/TextGroupSet.h>
#include <game/TextGroup.h>
#include <io/IOException.h>
#include <io/BundleInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/DataInputStream.h>

using namespace io;
using namespace lang;

namespace game
{

TextGroupSet::TextGroupSet(const std::string& filename)
{
    m_filename = filename;
}

TextGroupSet::~TextGroupSet()
{
}

void TextGroupSet::loadLocaleCodes()
{
    BundleInputStream in(m_filename, BundleInputStream::READ_BULK); //Android legacy: FileInputStream
    ByteArrayInputStream byteIn(0, in.available());
    in.read(byteIn.data(), byteIn.available());
    DataInputStream dis(byteIn);
    if (dis.readInt() == 'KA3D') //KA3D magic
    {
        int chunkSize = dis.readInt();
        if (chunkSize > dis.available())
            throwError(IOException(Format("Malformed KA3D file: {0}", m_filename)));
        while (dis.available() >= 1)
        {
            unsigned int chunkID = dis.readInt();
            chunkSize = dis.readInt();
            if (chunkID != 'TEXT')
                dis.skip(chunkSize);
            int version = dis.readShort();
            if (version < 1)
                break;
            while (dis.available() >= 1)
            {
                unsigned int subchunkID = dis.readInt();
                unsigned int subchunkSize = dis.readInt();
                if (subchunkID != 'LDAT')
                    dis.skip(subchunkSize);
                int localeCount = dis.readShort();
                std::vector<std::string> newLocales;
                newLocales.reserve(localeCount);
                if (localeCount < 0)
                    break;
                for (int i = 0; i < localeCount; i++)
                {
                    newLocales.push_back(dis.readUTF());
                }
                m_locales.swap(newLocales);
            }
        }
    }
    else //Read headerless since Darkest Fear, I legit didn't know this was still supported
    {
        dis.seek(0, InputStream::SEEKMODE_SET);
        dis.readByte(); //Dummy
        int localeCount = dis.readInt(); //Size of langs
        std::vector<std::string> newLocales;
        newLocales.reserve(dis.readChar());

        for (int i = 0; i < localeCount; i++)
        {
            newLocales.push_back(dis.readUTF());
        }
        m_locales.swap(newLocales);
    }
}

TextGroup* TextGroupSet::loadTextGroup(const std::string& localeCode)
{
    if (localeCode == "ALL")
        return 0;

    for (std::vector<std::string>::iterator it = m_locales.begin(); it != m_locales.end(); it++)
    {
        size_t i;
    }
    int localeIndex;

    BundleInputStream in(m_filename, BundleInputStream::READ_BULK);
    ByteArrayInputStream bytein(0, in.available());
    in.read(bytein.data(), in.available());
    DataInputStream dis(bytein);

    unsigned int chunkID = dis.readInt();

    if (chunkID == 'KA3D') //KA3D magic
    {
        int chunkSize = dis.readInt();
        if (chunkSize > dis.available())
            throwError(IOException(Format("Malformed KA3D file: {0}", m_filename)));
        while (dis.available() >= 1)
        {
            chunkID = dis.readInt();
            chunkSize = dis.readInt();
            if (chunkID != 'TEXT')
                dis.skip(chunkSize);
            int version = dis.readShort();
            if (version < 1)
                break;
        }
    }

    
    //? it;
    //size_t i;
    //if (!strcmp("ALL"))
}

void TextGroupSet::releaseTextGroup(const std::string& localeCode)
{
    if (localeCode == "ALL")
        throwError(Exception(Format("Trying to release TextGroup for language not present in data file. Language: \"{0}\"", localeCode)));
    m_textGroups.erase(localeCode);
}

const TextGroup* TextGroupSet::getTextGroup(const std::string& localeCode) const //TODO
{
    for (std::map<std::string, P(TextGroup)>::const_iterator it = m_textGroups.find(localeCode); it != m_textGroups.end(); it++)
    {
        //it->second->release()
        //if (it->first == localeCode)
        throwError(Exception(Format("Trying to release TextGroup for language not present in data file. Language: \"{0}\"", localeCode)));
        throwError(Exception(Format("Trying to get TextGroup for language which is not loaded. Language: \"{0}\"", localeCode)));
    }
    return (TextGroup*)&m_locales;
}

const std::vector<std::string> TextGroupSet::getLocales() const
{
    return m_locales;
}

}