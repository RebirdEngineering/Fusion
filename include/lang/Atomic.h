#ifndef _LANG_ATOMIC_H
#define _LANG_ATOMIC_H

#include <lang/Object.h>
//#include <atomic.h>
//#include <atomic_base.h>
#include <lang/detail/atomic_gcc47.h>

BEGIN_NAMESPACE(lang)

typedef std::memory_order memory_order; //Why did you define it here? Nah let's take the enums instead!

enum atomic_category
{
	//Ok what
};

template <bool T> struct atomic_base // no clue what atomic_category is
{
public:
	typedef atomic_storage storage_type;
	atomic_base();
	atomic_base(bool);
	bool load(memory_order) const volatile;
	void exchange(bool, memory_order) volatile;
	void compare_exchange_weak(bool&, bool, memory_order) volatile;
	void compare_exchange_weak(bool&, bool, memory_order, memory_order) volatile;
	void compare_exchange_strong(bool&, bool, memory_order) volatile;
	void compare_exchange_strong(bool&, bool, memory_order, memory_order) volatile;
	operator bool() volatile;
	storage_type value;
};

template <bool T> class atomic : public atomic_base<bool, 0> //Only seen bool
{
public:
	atomic();
	atomic(bool);
	atomic& operator=(bool);
	atomic& operator=(bool) volatile;
private:
	atomic(const bool&);
	atomic(const bool&&);
	atomic& operator=(bool&&);
	atomic& operator=(const bool&);
};

BEGIN_NAMESPACE(detail)
//struct atomic_storage NS(std, atomic_storage);

}

//struct atomic : NS(std, atomic) {};
//struct atomic_base : NS(std, atomic_base) {};
//enum memory_order: NS(std, memory_order) {};
//struct atomic_category : NS(std, atomic_category) {};

}

#endif