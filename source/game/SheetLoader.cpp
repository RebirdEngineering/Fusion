#include <game/SheetLoader.h>
#include <io/MemoryAliasInputStream.h>
#include <util/StreamUtil.h>
#include <util/JSON.h>

using namespace io;
using namespace util;

namespace game
{
    void SheetLoader::setEncryptionKey(const lang::optional<std::vector<unsigned char>>& encryptionKey) //13
    {
        m_encryptionKey = encryptionKey; //15
    }

    void SheetLoader::setCompressionEnabled(bool compressionEnabled) //18
    {
        m_compressionEnabled = compressionEnabled;
    }

    JSON SheetLoader::decryptJSON(io::InputStream& in, bool isRaw) //23-28
    {
        std::vector<unsigned char> data = decryptAndDecompress(in, isRaw ? m_emptyKey : m_encryptionKey, m_compressionEnabled ? true : false); //25
        MemoryAliasInputStream dataStream(data.data(), data.size(), ""); //26
        return toJSON(dataStream); //27
    }
}