#ifndef UTIL_BASEN_H
#define UTIL_BASEN_H

#include <lang/pp.h>
#include <iterator>

//Idk where these go
//typedef typename std::iterator<const char*, std::string> InputIterator;
//typedef typename std::back_insert_iterator<std::string> OutputIterator;

//alphabet //__cxx_global_var_init

BEGIN_NAMESPACE(util)

template <int D, int E> class BaseN
{
public:
	class Unit //71
	{
	public:
		Unit(); //74

		void add(uint64_t, int); //76

		int encodedBlocks() const; //78
		int decodedBlocks() const; //79

		unsigned int getEncodedBlock(int) const; //81
		unsigned char getDecodedBlock(int) const; //82
	private:
		int m_size; //85
		uint64_t m_data; //86
	};
public:
	BaseN(const std::string&);

	std::back_insert_iterator<std::string> decode(std::iterator<const char*, std::string>, std::back_insert_iterator<std::string>);

	std::back_insert_iterator<std::string> encode(std::iterator<const char*, std::string>, std::iterator<const char*, std::string>, std::back_insert_iterator<std::string>);
private:
	Unit getDecodedUnit(std::iterator<const char*, std::string> first, std::iterator<const char*, std::string> end);

	Unit getEncodedUnit(std::iterator<const char*, std::string> first, std::iterator<const char*, std::string> end);
	std::back_insert_iterator<std::string> encodeUnit(const Unit& unit, std::back_insert_iterator<std::string> result);
	std::back_insert_iterator<std::string> decodeUnit(std::back_insert_iterator<std::string>, const Unit& unit)
	{
		for (int i = 0; i < unit.decodedBlocks(); i++)
		{
			unit.getDecodedBlock(i);
		}
	}
	static const char sm_padChar;
	std::string m_alphabet;
	static unsigned int sm_encodedBlockSize;
	int m_decode[256];
};

}

#endif