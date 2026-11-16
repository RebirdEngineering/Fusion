#ifndef _LANG_STRING_H
#define _LANG_STRING_H

#include <lang/pp.h>

namespace lang
{

typedef std::basic_string<unsigned short> u16string;
typedef std::basic_string<unsigned int> u32string;

/** 
 * Immutable Unicode character string. Used encoding is UTF-8.
 * String uses internal memory pool, which allows
 * low-overhead allocation and compact operation to avoid
 * run-time memory fragmentation. Not thread-safe.
 * 
 * @ingroup lang
 */
namespace string
{
	std::string		to_string(int val);

	std::string		to_string(long val);

	std::string		to_string(long long val);

	std::string		to_string(unsigned int val);

	std::string		to_string(unsigned long val);

	std::string		to_string(unsigned long long val);

	std::string		to_string(float val);

	std::string		to_string(double val);

	std::string		to_string(long double val);

	/**
	 * Returns a new string that has all characters of this string converted to lowercase.
	 * Doesn't handle locale dependent special casing.
	 * @exception OutOfMemoryException
	 */
	std::string		tolower(const std::string& str); //[NOTE] changed to lowercase

	/**
	 * Returns a new string that has all characters of this string converted to uppercase.
	 * Doesn't handle locale dependent special casing.
	 * @exception OutOfMemoryException
	 */
	std::string		toupper(const std::string& str); //[NOTE] changed to lowercase

	/**
	 * Returns a new string that is otherwise identical to this string 
	 * but has whitespace removed from both ends of the string.
	 * @exception OutOfMemoryException
	 */
	std::string		trim(const std::string& str);

	std::vector<std::string>		split(const std::string& str, const std::string& delimiter);

	std::string				toUTF8string(const std::wstring& str);

	std::string 				toUTF8string(const u16string& str);

	std::string 				toUTF8string(const u32string& str);

	u16string 				toUTF16string(const std::string& str);

	u16string 				toUTF16string(const u32string& str);

	u16string 				toUTF16string(const std::wstring& str);

	u32string 			toUTF32string(const std::string& str);

	u32string 			toUTF32string(const u16string& str);

	u32string 			toUTF32string(const std::wstring& str);

	std::wstring			towstring(const std::string& str);

	std::wstring			towstring(const u16string& str);

	std::wstring			towstring(const u32string& str);

	double scanDouble(const char* nptr, const char** endptr, int* err);

	std::string scanString(const char* sz, char* buf, int bufLen, const char** szend);
};

int						strprintf(const char* ...);

int						vsnprintf(char* buf, int n, const char* format, va_list arg);

int						snprintf(char* buf, int n, const char* format);

int						vstrprintf(std::string&, const char*, char*);

int						strprintf(const std::string&, const char* ...);


} // lang


#endif // _LANG_STRING_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
