#include <util/SHA1.h>
#include <util/Base16.h>

const unsigned int rol(const unsigned int value, const unsigned int steps = 30) //35 | //Carbon copy of https://code.google.com/archive/p/smallsha1/ (sha1::rol)
{
	return ((value << steps) | (value >> (32 - steps))); //_rotl(value, steps) //?
}

void clearWBuffert(unsigned int* buffert) //43 | //Carbon copy of https://code.google.com/archive/p/smallsha1/ (sha1::clearWBuffert)
{
	for (int pos = 16; --pos >= 0;) //45
	{
		buffert[pos] = 0;
	}
}

void innerHash(unsigned int* result, unsigned int* w) //51 | Carbon copy of https://code.google.com/archive/p/smallsha1/ (sha1::innerHash)
{
	unsigned int a = result[0]; //53
	unsigned int b = result[1]; //54
	unsigned int c = result[2]; //55
	unsigned int d = result[3]; //56
	unsigned int e = result[4]; //57

	int round = 0; //59

#define sha1macro(func,val) \
			{ \
                const unsigned int t = rol(a, 5) + (func) + e + val + w[round]; \
				e = d; \
				d = c; \
				c = rol(b, 30); \
				b = a; \
				a = t; \
			}

	while (round < 16)
	{
		sha1macro((b & c) | (~b & d), 0x5a827999) //73
		++round;
	}
	while (round < 20)
	{
		w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1); //78
		sha1macro((b & c) | (~b & d), 0x5a827999) //79
		++round;
	}
	while (round < 40)
	{
		w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1); //84
		sha1macro(b ^ c ^ d, 0x6ed9eba1) //85
		++round;
	}
	while (round < 60)
	{
		w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1); //90
		sha1macro((b & c) | (b & d) | (c & d), 0x8f1bbcdc) //91
		++round;
	}
	while (round < 80)
	{
		w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1); //96
		sha1macro(b ^ c ^ d, 0xca62c1d6) //97
		++round;
	}

#undef sha1macro

	result[0] += a;
	result[1] += b;
	result[2] += c;
	result[3] += d;
	result[4] += e;
}

namespace util
{

std::string SHA1::hash(const void* src, int length) //113 | Carbon copy of https://code.google.com/archive/p/smallsha1/ (sha1::calc) except modified to return a Fusion Base16 (Hex) encoded string of the SHA1 hash.
{
	// Init the result array.
	unsigned int result[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 }; //116

	// Cast the void src pointer to be the byte array we can work with.
	const unsigned char* sarray = (const unsigned char*)src; //119

	// The reusable round buffer
	unsigned int w[80]; //122

	// Loop through all complete 64byte blocks.
	const int endOfFullBlocks = length - 64; //125
	int endCurrentBlock; //126
	int currentBlock = 0; //127

	while (currentBlock <= endOfFullBlocks)
	{
		endCurrentBlock = currentBlock + 64;

		// Init the round buffer with the 64 byte block data.
		for (int roundPos = 0; currentBlock < endCurrentBlock; currentBlock += 4) //134
		{
			// This line will swap endian on big endian and keep endian on little endian.
			w[roundPos++] = (unsigned int)sarray[currentBlock + 3]
				| (((unsigned int)sarray[currentBlock + 2]) << 8)
				| (((unsigned int)sarray[currentBlock + 1]) << 16)
				| (((unsigned int)sarray[currentBlock]) << 24);
		}
		innerHash(result, w); //142
	}

	// Handle the last and not full 64 byte block if existing.
	endCurrentBlock = length - currentBlock;
	clearWBuffert(w); //147
	int lastBlockBytes = 0; //148
	for (; lastBlockBytes < endCurrentBlock; ++lastBlockBytes)
	{
		w[lastBlockBytes >> 2] |= (unsigned int)sarray[lastBlockBytes + currentBlock] << ((3 - (lastBlockBytes & 3)) << 3);
	}
	w[lastBlockBytes >> 2] |= 0x80 << ((3 - (lastBlockBytes & 3)) << 3);
	if (endCurrentBlock >= 56)
	{
		innerHash(result, w); //156
		clearWBuffert(w); //157
	}
	w[15] = length << 3;
	innerHash(result, w); //160

	std::string hash; //163

	for (int hashByte = 20; --hashByte >= 0;) //165
	{
		hash[hashByte] = (result[hashByte >> 2] >> (((3 - hashByte) & 0x3) << 3)) & 0xff;
	}

	return Base16::encode(hash); //169
}

std::string SHA1::hash(const std::string& str) //172
{
	return hash(str.data(), str.size()); //174
}

std::string SHA1::hash(const std::vector<unsigned char>& buffer)
{
	return hash(!buffer.empty() ? buffer.data() : 0, buffer.size());
}

std::string SHA1::hash(const std::vector<char>& buffer) //182 | I love using identical code lol
{
	return hash(!buffer.empty() ? buffer.data() : 0, buffer.size()); //184
}


}