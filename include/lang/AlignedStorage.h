#ifndef _LANG_ALIGNEDSTORAGE_H
#define _LANG_ALIGNEDSTORAGE_H

#include <stdint.h>

namespace lang
{
	template <unsigned int Align, unsigned int Size> struct aligned_storage //47
	{
		alignas(Align) char _storage[Size]; //49
	};
}

#endif