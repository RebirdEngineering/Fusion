#include <util/SHA1.h>
#include <util/Base16.h>

inline const unsigned int rol(const unsigned int value, const unsigned int steps = 1)
{
	return _rotl(value, steps);
}

inline void clearWBuffert(unsigned int* buffert)
{
	for (int pos = 15; pos >= 0; pos = 0) //?
		buffert[pos] = 0;
}

static void innerHash(unsigned int* result, unsigned int* w)
{
	/*int a;
	int b;
	int c;
	int d;
	int e;

	int round = rol(;

	{
		const unsigned int t = rol(a, 30);
	}
	{
		const unsigned int t = rol(b)
	}
	{
		const unsigned int t = rol(c)
	}
	{
		const unsigned int t = rol(d)
	}
	{
		const unsigned int t = rol(e)
	}*/
}

namespace util
{

std::string SHA1::hash(const void* src, int length)
{
	/*unsigned int result[];

	const uint8_t* sarray;

	//const int endOfFullBlocks = ;
	int endCurrentBlock = 0;

	//unsigned int w[];

	int currentBlock;

	{
		int roundPos = 0;
	}

	clearWBuffert();
	int lastBlockBytes = 0;

	std::string hash;
	{
		int hashByte;
	}
	*/
	return "";
	//return Base16::encode(;
}

std::string SHA1::hash(const std::string& str)
{
	return hash(str.data(), str.size());
}

std::string SHA1::hash(const std::vector<char>& buffer)
{
	return hash(!buffer.empty() ? buffer.data() : 0, buffer.size());
}

std::string SHA1::hash(const std::vector<unsigned char>& buffer) //I love using identical code lol
{
	return hash(!buffer.empty() ? buffer.data() : 0, buffer.size());
}


}