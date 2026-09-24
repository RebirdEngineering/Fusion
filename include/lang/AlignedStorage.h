#ifndef _LANG_ALIGNEDSTORAGE_H
#define _LANG_ALIGNEDSTORAGE_H

#include <stdint.h>

namespace lang
{
	template <unsigned int Align, unsigned int Size> struct aligned_storage
	{
	public:
		char _storage[Align * Size / Align];
	};
}

#endif