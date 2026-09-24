#include <util/StreamUtil.h>
#include <util/AES.h>
#include <io/MemoryAliasInputStream.h>
#include <io/ZipFileInputStream.h>

using namespace lang;
using namespace io;

namespace util
{

std::vector<unsigned char> decryptAndDecompress(InputStream& input, optional<std::vector<unsigned char>>& encryptionKey, bool zipped) //8
{
	std::vector<unsigned char> data = toVector(input); //10
	if (encryptionKey.get().size() > 0) //?
	{
		AES crypt(encryptionKey.get(), AES::KEY_LENGTH_AUTODETECT, AES::PAD_MODE_PKCS7); //13
		std::vector<unsigned char> decrypted; //14
		crypt.decrypt(data, decrypted);
		data = decrypted;
	}
	if (zipped)
	{
		MemoryAliasInputStream dataStream(data.data(), input.available(), ""); //21
		ZipFileInputStream zip(dataStream, ZipFileInputStream::FORMAT_7ZIP); //22
		P(ZipEntryInputStream) entry = zip.getEntryStream(); //23
		data = toVector(*entry); //?
	}
	return data;
}

}