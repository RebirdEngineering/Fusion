#ifndef _LANG_OPTIONAL_H
#define _LANG_OPTIONAL_H

#include <lang/AlignedStorage.h>

namespace lang
{
	struct none_t;

	template <typename T> struct optional
	{
	public:
		optional(); //34

		optional(none_t); //39

		optional(const T&); //44

		optional(const optional<T>&); //53

		void emplace(); //76

		optional<T>& operator=(const optional<T>&); //92

		optional<T>& operator=(const T&); //111

		void reset() //122
		{
			if (initialized)
				initialized = false;
		}

		~optional() //131
		{
			reset();
			delete storage;
		}

		typedef optional<T>& safe_bool_type; //137
		//typedef void (*optional<T>::safe_bool_type)(optional<T>*); //138
		//safe_bool_type operator void() const;

		T& get(); //146
		const T& get() const; //147

		bool operator==(const optional<T>&) const; //204

		bool operator!=(const optional<T>&) const; //218
	private:
		aligned_storage<sizeof T, sizeof T - 4> storage; //224 | If ulong 4,4 / 4,12 if std::vector<uchar>
		bool initialized; //225
	};
}

#endif