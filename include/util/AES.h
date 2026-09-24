#ifndef _UTIL_AES_H
#define _UTIL_AES_H

#include <lang/Ptr.h>

namespace util
{

class AES
{
public:
	static const int BLOCK_SIZE = 16;
	enum KeyLengthBits
	{
		KEY_LENGTH_AUTODETECT,
		KEY_LENGTH_128,
		KEY_LENGTH_192,
		KEY_LENGTH_256,
	};
	enum PadMode
	{
		PAD_MODE_PKCS7,
		PAD_MODE_FIPS81,
		PAD_MODE_NOPAD,
	};
	AES(const std::vector<unsigned char>& key, KeyLengthBits keyLength, PadMode pad);

	~AES();

	void encrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out); //Never seen in 4.1.0 and RCS.

	void encrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out);

	bool decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out); //Never seen in 4.1.0 and RCS.

	bool decrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out); //Not on iOS.
private:
	class Impl;
	P(Impl) m_impl;
};

}

#endif