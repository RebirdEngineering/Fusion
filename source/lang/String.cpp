#include <lang/String.h>
#include <lang/UTFConverter.h>

namespace lang
{

std::string string::to_string(int val) //12 | 4F4BB0
{
	char buf[128]; //14
	sprintf(buf, "%d", val);
	return buf;
}

std::string string::to_string(long val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%ld", val);
	return buf;
}

std::string string::to_string(long long val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%lld", val);
	return buf;
}

std::string string::to_string(uint32_t val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%u", val);
	return buf;
}

std::string string::to_string(unsigned long val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%lu", val);
	return buf;
}

std::string string::to_string(unsigned long long val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%llu", val);
	return buf;
}

std::string string::to_string(float val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%f", val);
	return buf;
}

std::string string::to_string(double val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%f", val);
	return buf;
}

std::string string::to_string(long double val) //Not on iOS and Win32.
{
	char buf[128];
	sprintf(buf, "%Lf", val);
	return buf;
}

std::string string::tolower(const std::string& str) //75-80
{
	std::string result = str; //77
	transform(result.begin(), result.end(), result.begin(), ::tolower); //78 | ?
	return result;
}

std::string string::toupper(const std::string& str) //82
{
	std::string result = str; //84
	transform(result.begin(), result.end(), result.begin(), ::toupper); //85 | ?
	return result;
}

std::string string::trim(const std::string& str) //89
{
	size_t begin	= str.find_first_of(" \n\t\r"); //91
	size_t end		= str.find_last_of(" \n\t\r"); //92
	return begin != -1 ? str.substr(begin) + str.substr(end) : ""; //93 | ?
}

std::vector<std::string> string::split(const std::string& str, const std::string& delimiter) //96-113 | https://github.com/zz6974/API/blob/9058f9c3fd20ad4ea7f6de4ef9dd6dec784ba90f/CC_SDK/src/basic/CCString.cpp#L169 | https://github.com/DiggerMan-cpp/DiggerString/blob/2f2c46f17513f0c8e39b149ca8094e2c763ec05e/src/Split.cpp#L3
{
	std::vector<std::string> result; //98

	std::string::size_type begin = 0; //100
	std::string::size_type end = str.find(delimiter, 0); //101

	while (end != -1)
	{
		result.push_back(str.substr(begin, end - begin));
		begin = end + delimiter.length(); //106
		end = str.find(delimiter, begin);
	}

	result.push_back(str.substr(begin)); //110

	return result;
}

std::string string::toUTF8string(const u16string& str) //402-436 | Correct? | similar to KA3D [int String::getBytes( void* buf, int bufsize, Converter& encoder ) const]
{
	std::string result; //404

	UTFConverter decoder(UTFConverter::ENCODING_UTF16); //406
	UTFConverter encoder(UTFConverter::ENCODING_UTF8); //407

	const u16string::value_type* s = reinterpret_cast<const u16string::value_type*>(str.data()); //409
	int len = str.length(); //410
	int index = 0; //411

	while (index < len)
	{
		int decodedbytes = 2; //415 | [LHR] I prefer to use sizeof u16string eh
		int cp; //416
		if (decoder.decode(s + 2 * index, s + 2 * len, &decodedbytes, &cp)) //417
		{
			index += decodedbytes / 2;

			char temp[4]; //421
			int encodedBytes = 0; //422
			if (encoder.encode(&temp, &cp, &encodedBytes, cp)) //423 | Correct?
			{
				result.append(temp, encodedBytes); //425
				index += decodedbytes / 2;
			}
		}
		else
		{
			index++;
		}
	}

	return result;
}

std::string string::toUTF8string(const u32string& str) //438-461 | Correct?
{
	std::string result; //440

	UTFConverter encoder(UTFConverter::ENCODING_UTF8); //442

	const u32string::value_type* s = reinterpret_cast<const u32string::value_type*>(str.data()); //444 | Correct?
	int len = str.length(); //445
	int read = 0; //446

	while (read < len)
	{
		int cp = *(s + 4 * read); //450 | Correct?

		char temp[4]; //452
		int encodedbytes = 0; //453
		if (encoder.encode(&temp, &cp, &encodedbytes, cp)) //454 | Correct?
		{
			result.append(temp, encodedbytes); //456
		}
	}

	return result;
}

std::string string::toUTF8string(const std::wstring& str) //Correct? | Not on iOS.
{
	return ""; //tostringimpl(str);
}

//std::string string::tostringimpl(const std::wstring& str) //Not on iOS
//{
//	std::string result;
//
//	UTFConverter encoder(UTFConverter::ENCODING_UTF8);
//
//	const std::wstring::value_type* s = str.data();
//	int len = str.length();
//	int read = 0;
//
//	while (read < len)
//	{
//		int cp = *(s + 4 * read);
//
//		char temp[4];
//		int encodedbytes = 0;
//		if (encoder.encode(&temp, &cp, &encodedbytes, cp))
//		{
//			result.append(temp, encodedbytes);
//		}
//	}
//
//	return result;
//}

u16string string::toUTF16string(const std::string& str) //468-502 | 4F4EC0 | Correct?
{
	u16string result; //470

	UTFConverter decoder(UTFConverter::ENCODING_UTF8); //472
	UTFConverter encoder(UTFConverter::ENCODING_UTF16); //473

	const char* s = str.data(); //475 | ?
	int len = str.length(); //476
	int read = 0; //477

	while (read < len)
	{
		int decodedbytes = 1; //481
		int cp; //482
		if (decoder.decode(s + read, s + len, &decodedbytes, &cp)) //483
		{
			read += decodedbytes;

			u16string::value_type temp[2]; //487
			int encodedbytes = 0; //488
			if (encoder.encode(temp, &cp, &encodedbytes, cp)) //489 | Correct?
			{
				result.append(temp, encodedbytes / 2); //491
			}
			else
			{
				read++;
			}
		}
	}

	return result;
}

u16string string::toUTF16string(const u32string& str) //Not on iOS.
{
	u16string result;

	UTFConverter encoder(UTFConverter::ENCODING_UTF16);

	const u32string::value_type* s = str.data();
	int len = str.length();
	int read = 0;

	while (read < len)
	{
		u16string::value_type temp[2];
		int encodedbytes = 0;
		int cp = *(s + 4 * read);
		if (encoder.encode(temp, &cp, &encodedbytes, cp))
		{
			result.append(temp, encodedbytes / 2);
		}
		else
		{
			read++;
		}
	}

	return result;
}

//u16string string::toUTF16string(const std::wstring& str) //TODO | Not on iOS.
//{
//	return tou16stringimpl(str);
//}

//u16string tou16stringimpl(const std::wstring& str)
//{
//	u16string result;
//
//	UTFConverter encoder(UTFConverter::ENCODING_UTF16);
//
//	const std::wstring::value_type* s = str.data();
//	int len = str.length();
//	int read = 0;
//
//	while (read < len)
//	{
//		u16string::value_type temp[2];
//		int cp = *(s + 4 * read);
//		int encodedbytes = 0;
//		if (encoder.encode(temp, &cp, &encodedbytes, cp))
//		{
//			result.append(temp, encodedbytes / 2);
//		}
//		else
//		{
//			read++;
//		}
//	}
//
//	return result;
//}

u32string string::toUTF32string(const std::string& str) //534-561 | Correct?
{
	u32string result; //536

	UTFConverter decoder(UTFConverter::ENCODING_UTF8); //538
	
	const char* s = str.data(); //540 | ?
	int len = str.length(); //541
	int read = 0; //542
	
	while (read < len)
	{
		int decodedbytes = 0; //546
		int cp; //547
		if (decoder.decode(read + s, len + s, &decodedbytes, &cp)) //548 | Correct?
		{
			result.push_back(cp); //550 | Correct?
			read += decodedbytes;
		}
		else
		{
			read++;
		}
	}

	return result;
}

u32string string::toUTF32string(const u16string& str) //TODO | Not on iOS.
{
	u32string result;

	UTFConverter decoder(UTFConverter::ENCODING_UTF16);

	const u16string::value_type* s = str.data(); //?
	int len = str.length();
	int read = 0;

	while (read < len)
	{
		int decodedbytes = 0;
		int cp;
		if (decoder.decode(s + 2 * read, s + 2 * len, &decodedbytes, &cp)) //Correct?
		{
			result.push_back(cp); //Correct?
			read += decodedbytes / 2;
		}
		else
		{
			read++;
		}
	}

	return result;
}

//u32string string::toUTF32string(const std::wstring& str) //TODO | Not on iOS.
//{
//	return tou32stringimpl(str);
//}

//u32string string::tou32stringimpl(const std::wstring str) //TODO | Not on iOS.
//{
//	u32string ret;
//	return ret;
//}

//std::wstring string::towstring(const std::string& str) //TODO | Not on iOS.
//{
//	return towstringimpl(str);
//}

//std::wstring string::towstringimpl(const std::string& str) //TODO | Not on iOS.
//{
//	std::wstring result;
//
//	UTFConverter decoder(UTFConverter::ENCODING_UTF8);
//
//	const char* s = str.data();
//	int len = str.length();
//	int read = 0;
//
//	while (read < len)
//	{
//		int decodedbytes = 1;
//		int cp;
//		if (decoder.decode(read + s, len + s, &decodedbytes, &cp))
//		{
//			result.push_back(cp);
//		}
//		else
//		{
//			read++;
//		}
//	}
//
//	return result;
//}

//std::wstring string::towstring(const u16string& str) //TODO | Not on iOS.
//{
//	return towstringimpl(str);
//}

//std::wstring string::towstringimpl(const u16string& str) //TODO | Not on iOS.
//{
//	std::wstring result;
//
//	UTFConverter decoder(UTFConverter::ENCODING_UTF16);
//
//	const std::wstring::value_type* s = str.data();
//	int len = str.length();
//	int read = 0;
//
//	while (read < len)
//	{
//		int decodedbytes = 0;
//		int cp;
//		if (decoder.decode(read + s, len + s, &decodedbytes, &cp))
//		{
//			result.push_back(cp);
//			read += decodedBytes / 2;
//		}
//		else
//		{
//			read++;
//		}
//	}
//
//	return result;
//}

//std::wstring string::towstring(const u32string& str) //TODO | Not on iOS.
//{
//	return towstringimpl(str);
//}

//std::wstring string::towstringimpl(const u32string& str) //TODO | Not on iOS.
//{
// //?
//}

double string::scanDouble(const char* nptr, const char** endptr, int* err) //TODO | Not on iOS.
{
	//assert(nptr != 0); //697 (RCSSDK debug)

	return 0.0;

	//assert(!isdigit(ch)) //768 (RCSSDK debug)
}

std::string string::scanString(const char* sz, char* buf, int bufLen, const char** szend) //Correct? | Not on iOS.
{
	const char* dummyptr = sz;

	while (*dummyptr && isspace(*dummyptr))
		dummyptr++;

	const char* start = dummyptr;

	while (*dummyptr && isspace(*dummyptr))
		dummyptr++;

	if (szend)
		*szend = dummyptr;

	int len = static_cast<int>(dummyptr - start);

	if (len >= bufLen)
		len = bufLen - 1;

	if (len > 0)
		memcpy(buf, start, len);

	return buf;
}

int snprintf(char*, int, const char*, ...) //TODO
{
	va_list args;
	//va_start(args, )
	int ret; //= ::vsnprintf(buf, n, format, arg);
	return ret;
}

int vsnprintf(char* buf, int n, const char* format, va_list arg) //813
{
	int ret = ::vsnprintf(buf, n, format, arg); //815
	return ret;
}

int strprintf(std::string&, const char*, ...) //TODO
{
	va_list args;
	//va_start(args, fmt);
	int ret; //= vstrprintf("", "", args);
	return ret;
}

int vstrprintf(const char*, ...) //TODO
{
	int ret;
	return ret;
}

int strprintf(const char*, ...) //TODO
{
	va_list args;
	//va_start(args, fmt);
	int ret; //= vstrprintf("", "", args);
	return ret;
}

} // lang

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
