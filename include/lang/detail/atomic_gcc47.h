#ifndef _LANG_ATOMICGCC47_H
#define _LANG_ATOMICGCC47_H

#include <lang/pp.h>

BEGIN_NAMESPACE(lang)

typedef std::memory_order memory_order; //Why did you define it here? Nah let's take the enums instead!

BEGIN_NAMESPACE(detail)

template <bool T> struct atomic_arg_type
{
    typedef T type;
};

template <bool T> struct atomic_storage //I don't get it
{
public:
    typedef T int_type;
    void init(bool) volatile;
    bool load(memory_order) const volatile;
    void store(int_type, memory_order) volatile;
    bool fetch_add(int_type, memory_order) volatile;
    bool fetch_sub(int_type, memory_order) volatile;
    bool fetch_and(int_type, memory_order) volatile;
    bool fetch_or(int_type, memory_order) volatile;
    bool fetch_xor(int_type, memory_order) volatile;
    bool exchange(int_type, memory_order) volatile;
    bool compare_exchange_weak(bool&, bool, memory_order, memory_order) volatile;
    bool compare_exchange_strong(bool&, bool, memory_order, memory_order) volatile;
    bool value;
    T value;
};

}
}