#include <game/SheetLoader.h>
#include <io/MemoryAliasInputStream.h>
#include <util/StreamUtil.h>
#include <util/JSON.h>

using namespace io;
using namespace util;

namespace game
{
    void SheetLoader::setCompressionEnabled(bool compressionEnabled)
    {
        m_compressionEnabled = compressionEnabled;
    };

    void SheetLoader::setEncryptionKey(const lang::optional<std::vector<unsigned char>>& encryptionKey)
    {
        m_encryptionKey = encryptionKey;
    };

    JSON SheetLoader::decryptJSON(io::InputStream& in, bool isRaw)
    {
        std::vector<unsigned char> data = decryptAndDecompress(in, isRaw ? m_emptyKey : m_encryptionKey, m_compressionEnabled ? true : false);
        MemoryAliasInputStream dataStream(data.data(), data.size(), "");

        return toJSON(dataStream);
    };
}