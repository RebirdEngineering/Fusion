#ifndef UTIL_BASEN_H
#define UTIL_BASEN_H

#include <lang/Exception.h>
#include <lang/Format.h>
#include <iterator>

namespace util
{

template <int D, int E> class BaseN //TODO
{

public:
	BaseN(const std::string& alphabet); //44 | "0123456789ABCDEF" (32) | "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_" (64)
	//{
		//assert(m_alphabet.size() == 1u << sm_encodedBlockSize); //115 RCSSDK
		//m_alphabet = alphabet;
		//memset(m_decode, 255, sizeof(m_decode));
		//assert(chr < sizeof(m_decode));
	//}

	std::back_insert_iterator<std::string> encode(std::iterator<const char*, std::string> first, std::iterator<const char*, std::string> second, std::back_insert_iterator<std::string> result); //47 | Guessed params
	/*{
		while (first != second)
		{
			Unit unit = getDecodedUnit(first, second);
			encodeUnit(result, unit);
		}
	}*/

	std::back_insert_iterator<std::string> decode(std::iterator<const char*, std::string> first, std::iterator<const char*, std::string> second, std::back_insert_iterator<std::string> result); //50 | Guessed params

	class Unit //71
	{
	public:
		Unit(); //74

		void add(uint64_t data, int size); /*{ m_data += data; m_size += size; }*/ //76

		int encodedBlocks() const; //78
		int decodedBlocks() const; //79

		unsigned int getEncodedBlock(int pos) const; //81
		unsigned char getDecodedBlock(int) const; //82

	private:
		int m_size; //85
		uint64_t m_data; //86
	};
private:
	static const char sm_padChar; //89
	std::string m_alphabet; //90
	static unsigned int sm_encodedBlockSize; //91
	int m_decode[256]; //92

	std::back_insert_iterator<std::string> encodeUnit(std::back_insert_iterator<std::string> result, const Unit& unit); //95 | Correct?
	/*{
		int count;
		for (count = 0; i < unit.encodedBlocks(); i++)
			result +*= result[unit.getEncodedBlock(i)];

		for (count = 0; i < E; i++)
			result +*= "=";

		return result;
	}*/

	std::back_insert_iterator<std::string> decodeUnit(std::back_insert_iterator<std::string> result, const Unit& unit); //98
	/*{
		for (int i = 0; i < unit.encodedBlocks(); i++)
			result +*= result[unit.getDecodedBlock(i)];

		return result;
	}*/

	Unit getDecodedUnit(std::iterator<const char*, std::string>& first, std::iterator<const char*, std::string> end); //101
	/*{
		Unit unit;

		while (first != second)
			unit.add(first);

		return unit;
	}*/

	Unit getEncodedUnit(std::iterator<const char*, std::string>& first, std::iterator<const char*, std::string> end); //104
	/*{
		Unit unit;

		while (first != second)
		{
			//if (first ==)
		}

		return unit;
	}*/
	
};

}

#endif