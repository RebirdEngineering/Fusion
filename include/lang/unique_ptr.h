#ifndef _LANG_UNIQUE_PTR_H
#define _LANG_UNIQUE_PTR_H

#include <lang/pp.h>

//Fusion's custom std::unique_ptr. Do we directly copy std's impl?
//https://en.cppreference.com/cpp/header/memory
//https://en.cppreference.com/cpp/memory/default_delete
//https://en.cppreference.com/cpp/memory/unique_ptr
//<memory>

//PLACEHOLDER
namespace lang 
{
	namespace detail
	{
		template <class T> class default_delete //14
		{
			void operator()(T*) const; //15
		};
	}

	template <class T, class Deleter> class unique_base //31 | Likely custom.
	{
	protected:
		T* m_pointer; //34

	public:
		unique_base(T*); //38

		unique_base(); //42

		~unique_base(); //46

		void swap(T*, T&); //51

		T& operator=(const T&); //58

		T* get(); //68

		typedef T** safe_bool_t; //74

		operator T*() const; //77

		T* release(); //82

		void reset(T*); //89

	protected:
		unique_base(const T&); //96
		T& operator=(const T&); //97
	};

	template <class T, class Deleter = detail::default_delete<T>> class unique_ptr //110
	{
	public:
		unique_ptr(); //115

		explicit unique_ptr(T*); //119

		unique_ptr(T); //123 (?)

		T& operator=(const T&&); //127

		type operator*() const; //133

		T* operator->() const; //139

		unique_ptr(const T&); //146
		T& operator=(const T&); //147
	};
}

#endif