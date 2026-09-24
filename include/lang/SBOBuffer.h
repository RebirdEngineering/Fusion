#ifndef _LANG_SBOBUFFER_H
#define _LANG_SBOBUFFER_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)

template <class T, unsigned long StackCount = 1024> class SBOBuffer
{
public:
	const size_t stackCount = StackCount;

	SBOBuffer(size_t count);

	~SBOBuffer();

	size_t size() const;

	size_t bytes() const;

	T* data();
	const T* data() const;

	T* operator()() const;
private:
	SBOBuffer(const SBOBuffer&);
	SBOBuffer& operator=(const SBOBuffer&);
	size_t m_count;
	T* m_ptr;
	T m_data[StackCount];
};

}

#endif