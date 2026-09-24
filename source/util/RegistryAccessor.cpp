#include <util/RegistryAccessor.h>
#include <io/AppDataInputStream.h>
#include <util/AES.h>
#include <io/AppDataOutputStream.h>
#include <lang/Log.h>

using namespace io;
using namespace lang;

namespace util
{

static Mutex s_mutex;
static JSON s_data;
static int s_refs;
static std::string s_filename = "fusion.registry";

#define FUSION_REGISTRY_KEY 0x3A, 0x7D, 0x2E, 0x03, 0x79, 0xE6, 0x49, 0x85, 0xA0, 0x1F, 0xA8, 0x01, 0x04, 0xD5, 0xD7, 0x7D, 0xA1, 0xBC, 0x7A, 0xE7, 0x03, 0x63, 0x24, 0x8E, 0x7A, 0xC9, 0xC0, 0xAD, 0x5F, 0x46, 0x60, 0xEA

inline std::vector<unsigned char> getKey()
{
	std::vector<unsigned char> key = { FUSION_REGISTRY_KEY };
	/* If this is really the way they did the key its ugly
	key[0] = 0x3A;
	key[1] = 0x7D;
	key[2] = 0x2E;
	key[3] = 0x03;
	key[4] = 0x79;
	key[5] = 0xE6;
	key[6] = 0x49;
	key[7] = 0x85;
	key[8] = 0xA0;
	key[9] = 0x1F;
	key[10] = 0xA8;
	key[11] = 0x01;
	key[12] = 0x04;
	key[13] = 0xD5;
	key[14] = 0xD7;
	key[15] = 0x7D;
	key[16] = 0xA1;
	key[17] = 0xBC;
	key[18] = 0x7A;
	key[19] = 0xE7;
	key[20] = 0x03;
	key[21] = 0x63;
	key[22] = 0x24;
	key[23] = 0x8E;
	key[24] = 0x7A;
	key[25] = 0xC9;
	key[26] = 0xC0;
	key[27] = 0xAD;
	key[28] = 0x5F;
	key[29] = 0x46;
	key[30] = 0x60;
	key[31] = 0xEA;*/
	return key;
}

RegistryAccessor::RegistryAccessor() :
	m_lock(s_mutex)
{
	//const exception&;
	if (s_refs++ <= 0)
	{
		//s_data;
		AppDataInputStream in(s_filename);
		const std::vector<unsigned char>& encrypted = toVector(in);

		const std::vector<unsigned char>& key = getKey();

		AES aes(key, AES::KEY_LENGTH_AUTODETECT, AES::PAD_MODE_FIPS81);

		std::vector<unsigned char> plain; //(encrypted.begin(), encrypted.end()
		if (aes.decrypt(encrypted, plain))
		{
			JSON json;
			//s_data = json.parse();
		}
		else
			LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Registry load failed because the file seems to be corrupted"); //99
		//exception e&;
		//const JSON::JSONException& e;
	}
	//m_lock.Lock();
	/*JSONException&;
	AppDataInputStream in("fusion.registry");
	AES aes(getKey(), AES::KEY_LENGTH_AUTODETECT, AES::PAD_MODE_FIPS81);
	if (!aes.decrypt(encrypted, plain);
		//?
	JSON json;
	std::vector<uint8_t> encrypted;
	std::vector<uint8_t> key;
	std::vector<uint8_t> plain;
	catch (exception&)
	{
	}*/
	//s_mutex.lock();
}

RegistryAccessor::~RegistryAccessor()
{
	const std::string& data = s_data.toString(false);

	const std::vector<unsigned char> key = getKey();

	AES aes(key, AES::KEY_LENGTH_AUTODETECT, AES::PAD_MODE_FIPS81);

	std::vector<unsigned char> plain(data.begin(), data.end());
	std::vector<unsigned char> encrypted;
	aes.encrypt(plain, encrypted);
	AppDataOutputStream out(s_filename); //fusion.registry
	if (!encrypted.empty())
		out.write(encrypted.data(), encrypted.size());
	s_refs--;
}

JSON& RegistryAccessor::registry()
{
	return s_data;
}

}