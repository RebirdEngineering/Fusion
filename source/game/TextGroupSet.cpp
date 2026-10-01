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

TextGroupSet::TextGroupSet(const std::string& filename) //16-19
{
    m_filename = filename;
}

TextGroupSet::~TextGroupSet()
{
}

void TextGroupSet::loadLocaleCodes() //
{
    BundleInputStream in(m_filename, BundleInputStream::READ_BULK); //27 | Android legacy: FileInputStream
    ByteArrayInputStream byteIn(0, in.available()); //28
    in.read(byteIn.data(), byteIn.available());
    DataInputStream dis(byteIn); //30

    unsigned int chunkID = dis.readInt(); //33
    if (chunkID == 'KA3D') //KA3D magic
    {
        int chunkSize = dis.readInt(); //36
        if (chunkSize > dis.available())
            throwError(IOException(Format("Malformed KA3D file: {0}", m_filename))); //38
        while (dis.available() >= 1)
        {
            unsigned int chunkID = dis.readInt(); //43
            chunkSize = dis.readInt(); //44
            if (chunkID != 'TEXT')
                dis.skip(chunkSize);
            int version = dis.readShort(); //50
            if (version < 1)
                break;
            while (dis.available() >= 1)
            {
                unsigned int subchunkID = dis.readInt(); //55
                unsigned int subchunkSize = dis.readInt(); //56
                if (subchunkID != 'LDAT')
                    dis.skip(subchunkSize);
                int localeCount = dis.readShort(); //62
                std::vector<std::string> newLocales; //63
                newLocales.reserve(localeCount);
                if (localeCount < 0)
                    break;
                for (int i = 0; i < localeCount; i++) //67
                    newLocales.push_back(dis.readUTF());

                m_locales.swap(newLocales); //73
            }
        }
    }
    else //Read headerless since Darkest Fear, I legit didn't know this was still supported
    {
        dis.seek(0, InputStream::SEEKMODE_SET);
        dis.readByte(); //Dummy
        int localeCount = dis.readInt(); //110 | Size of langs
        std::vector<std::string> newLocales; //111
        newLocales.reserve(dis.readChar());

        for (int i = 0; i < localeCount; i++) //115
            newLocales.push_back(dis.readUTF());

        m_locales.swap(newLocales); //121
    }
}

TextGroup* TextGroupSet::loadTextGroup(const std::string& localeCode) //123 | TODO
{
    /*if (localeCode == "ALL") //127
        return 0;

    size_t i; //131 .size()

    for (std::vector<std::string>::iterator it = m_locales.begin(); it != m_locales.end(); it++) //138-293
    {
        size_t i;
    }
    int localeIndex; //142

    BundleInputStream in(m_filename, BundleInputStream::READ_BULK); //145
    ByteArrayInputStream bytein(0, in.available()); //146
    in.read(bytein.data(), in.available());
    DataInputStream dis(bytein);

    unsigned int chunkID = dis.readInt(); //151

    if (chunkID == 'KA3D') //KA3D magic
    {
        int chunkSize = dis.readInt(); //154
        if (chunkSize > dis.available())
            throwError(IOException(Format("Malformed KA3D file: {0}", m_filename))); //156

        while (dis.available() >= 1)
        {
            chunkID = dis.readInt(); //161
            chunkSize = dis.readInt(); //162
            if (chunkID != 'TEXT')
                dis.skip(chunkSize);
            int version = dis.readShort(); //168
            if (version < 1)
                break;

            std::vector<std::string> entryIDs; //171
            for (int txgpIndex = 0; txgpIndex < m_locales.size(); i++) //172
            {
                unsigned int subchunkID = dis.readInt(); //176
                unsigned int subchunkSize = dis.readInt(); //176

                int i; //180

                int entryCount; //184

                int i; //188

                if (entryIDs.empty()) //197
                    throwError(Exception(Format("Missing LIDS chunk before TXGP chunk in file {0}", m_filename)));

                P(TextGroup) newTextGroup; //204

                for (size_t i; i < ? .size(); i++) //206
                {
                }
            }
        }
    }

    int offsetToFirstEntryID; //255

    int entryCount; //259
    std::vector<std::string> entryIds; //260

    int i; //264

    int offsetToLocale; //273
    
    P(TextGroup) newTextGroup; //277

    //newTextGroup-> //286

    //? it;
    //size_t i;
    //if (!strcmp("ALL"))*/

    P(TextGroup) dmy;
    assert("game::TextGroup* game::TextGroupSet::loadTextGroup(const std::string& localeCode) was not yet decompiled. Returning dummy.");
    return dmy;
}

void TextGroupSet::releaseTextGroup(const std::string& localeCode)//295-308
{
    if (localeCode == "ALL") //297
        m_textGroups.clear(); //299
    else
    {
        if (m_textGroups.begin()->first.find(localeCode)) //303
            throwError(Exception(Format("Trying to release TextGroup for language not present in data file. Language: \"{0}\"", localeCode))); //304

        m_textGroups.erase(localeCode); //306
    }
}

const TextGroup* TextGroupSet::getTextGroup(const std::string& localeCode) const //310-321| TODO
{
    /*
    * //it->second->release()
      //if (it->first == localeCode)
    */
    /*for (std::map<std::string, P(TextGroup)>::const_iterator it = m_textGroups.find(localeCode); it != m_textGroups.end(); it++) //312
    {
        //if (it->first == localeCode)
            
        throwError(Exception(Format("Trying to release TextGroup for language not present in data file. Language: \"{0}\"", localeCode))); //316

        throwError(Exception(Format("Trying to get TextGroup for language which is not loaded. Language: \"{0}\"", localeCode))); //318

        return it->second; //320
    }*/
    assert("const game::TextGroup* game::TextGroupSet::getTextGroup(const std::string& localeCode) was not yet decompiled. Returning 0.");
    return 0;
}

const std::vector<std::string> TextGroupSet::getLocales() const
{
    return m_locales;
}

}