#ifndef _UTIL_AES_H
#define _UTIL_AES_H

#include <lang/Ptr.h>

namespace util
{

class AES //15
{
public:
	static const int BLOCK_SIZE = 16; //18

	enum KeyLengthBits //20
	{
		KEY_LENGTH_AUTODETECT,
		KEY_LENGTH_128,
		KEY_LENGTH_192,
		KEY_LENGTH_256
	};

	enum PadMode //26
	{
		PAD_MODE_PKCS7,
		PAD_MODE_FIPS81,
		PAD_MODE_NOPAD
	};

	AES(const std::vector<unsigned char>& key, KeyLengthBits keyLength, PadMode pad);

	~AES(); //42

	void encrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out); //49 | Never seen in 4.1.0 and RCS.

	void encrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out); //57

	bool decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out); //65 | Never seen in 4.1.0 and RCS.

	bool decrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out); //75 | Not on iOS.

private:
	class Impl; //79
	P(Impl) m_impl;
};

}

#endif