#ifndef _LANG_STRING_H
#define _LANG_STRING_H


#include <lang/pp.h>


namespace lang
{
typedef std::basic_string<unsigned short> u16string; //Do we use std::wstring or std::u16string or stick to the demangled symbol (std::basic_string<unsigned short>)?

//Both: std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> >
//Symbol: std::basic_string<unsigned short,std::char_traits<unsigned short>,std::allocator<unsigned short> 

typedef std::basic_string<unsigned int> u32string; //Same for std::u32string (std::basic_string<unsigned int>)?

//u32string: std::basic_string<char32_t,std::char_traits<char32_t>,std::allocator<char32_t> >
//Symbol: std::basic_string<unsigned int,std::char_traits<unsigned int>,std::allocator<unsigned int> >

/** 
 * Immutable Unicode character string. Used encoding is UTF-8.
 * String uses internal memory pool, which allows
 * low-overhead allocation and compact operation to avoid
 * run-time memory fragmentation. Not thread-safe.
 * 
 * @ingroup lang
 */
class string
{
public:
	/**
	 * 
	 * 
	 * @exception 
	 */
	static std::string		to_string(int val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(long val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(long long val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(unsigned int val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(unsigned long val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(unsigned long long val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(float val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(double val);

	/**
	 *
	 *
	 * @exception
	 */
	static std::string		to_string(long double val);

	/**
	 * Returns a new string that has all characters of this string converted to lowercase.
	 * Doesn't handle locale dependent special casing.
	 * @exception OutOfMemoryException
	 */
	static std::string		tolower(const std::string& str); //[NOTE] changed to lowercase

	/**
	 * Returns a new string that has all characters of this string converted to uppercase.
	 * Doesn't handle locale dependent special casing.
	 * @exception OutOfMemoryException
	 */
	static std::string		toupper(const std::string& str); //[NOTE] changed to lowercase

	/**
	 * Returns a new string that is otherwise identical to this string 
	 * but has whitespace removed from both ends of the string.
	 * @exception OutOfMemoryException
	 */
	std::string		trim(const std::string& str) const;

	static std::vector<std::string>		split(const std::string& str, const std::string& delimiter);

	static std::string 				toUTF8string(const u16string& str);

	static std::string 				toUTF8string(const u32string& str);

	static u16string 				toUTF16string(const std::string& str);

	static u32string 			toUTF32string(const std::string& str);
};

int						vsnprintf(char* buf, int n, const char* format, va_list arg); //Unofficial?


} // lang


#endif // _LANG_STRING_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
