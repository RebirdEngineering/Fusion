#include <lang/String.h>
#include <lang/UTFConverter.h>

namespace lang
{

std::string string::to_string(int val)
{
	char buf[128];
	sprintf(buf, "%d", val);
	return buf;
}

std::string string::to_string(long val) //The below ones are in beyond Seasons
{
	char buf[128];
	sprintf(buf, "%ld", val);
	return buf;
}

std::string string::to_string(long long val)
{
	char buf[128];
	sprintf(buf, "%lld", val);
	return buf;
}

std::string string::to_string(uint32_t val)
{
	char buf[128];
	sprintf(buf, "%u", val);
	return buf;
}

std::string string::to_string(unsigned long val)
{
	char buf[128];
	sprintf(buf, "%lu", val);
	return buf;
}

std::string string::to_string(unsigned long long val)
{
	char buf[128];
	sprintf(buf, "%llu", val);
	return buf;
}

std::string string::to_string(float val)
{
	char buf[128];
	sprintf(buf, "%f", val);
	return buf;
}

std::string string::to_string(double val)
{
	char buf[128];
	sprintf(buf, "%f", val);
	return buf;
}

std::string string::to_string(long double val)
{
	char buf[128];
	sprintf(buf, "%Lf", val);
	return buf;
}

std::string string::tolower(const std::string& str)
{
	std::string result = str;
	transform(result.begin(), result.end(), result.begin(), ::tolower); //?
	return result;
}

std::string string::toupper(const std::string& str)
{
	std::string result = str;
	transform(result.begin(), result.end(), result.begin(), ::toupper); //?
	return result;
}

std::string string::trim(const std::string& str) const
{
	size_t begin	= str.find_first_of(" \n\t\r");
	size_t end		= str.find_last_of(" \n\t\r");
	return begin != -1 ? str.substr(begin) + str.substr(end) : ""; //?
}

std::vector<std::string> string::split(const std::string& str, const std::string& delimiter)
{
	typedef std::string::size_type size_type;
	std::vector<std::string> result;

	size_type begin = str.find(delimiter);
	size_type end = str.find(delimiter, 0);

	//find length and substr are used

	while (begin != end)
	{
		result.push_back(str.substr(begin));
		begin++;
	}
	//result.push_back(str.substr(begin) + ); //?
	return result;
}

std::string string::toUTF8string(const u16string& str)
{
	typedef char value_type;
	std::string result;
	UTFConverter decoder(UTFConverter::ENCODING_UTF16);
	UTFConverter encoder(UTFConverter::ENCODING_UTF8);

	const value_type* s = reinterpret_cast<const value_type*>(str.data()); //?
	int len = str.length();
	int index = 0;
	while (index < len)
	{
		int decodedBytes = 2; //[LHR] I prefer to use sizeof u16string eh
		int cp;
		if (decoder.decode(s + 2 * index, s + 2 * len, &decodedBytes, &cp))
		{
			index += decodedBytes;

			int encodedBytes = 0;
			if (encoder.encode(&s, &cp, &encodedBytes, cp))
				result.append(s, encodedBytes);
		}
		else
		{
			index++;
		}
	}

	return result;
}

std::string string::toUTF8string(const u32string& str)
{
	typedef char value_type;
	std::string result;

	UTFConverter encoder(UTFConverter::ENCODING_UTF8);

	const value_type* s = reinterpret_cast<const value_type*>(str.data()); //?
	int len = str.length();
	int read = 0;
	while (read < len)
	{
		int cp;

		char temp[40];
		int encodedbytes = 0;
		if (encoder.encode(temp, temp + 4, &encodedbytes, cp))
			result.append(read, encodedbytes);
		else
		{
			read += 4;
		}
	}

	return result;
}

u16string string::toUTF16string(const std::string& str)
{
	u16string result;

	UTFConverter decoder(UTFConverter::ENCODING_UTF8);
	UTFConverter encoder(UTFConverter::ENCODING_UTF16);

	const char* s = reinterpret_cast<const char*>(str.data()); //?
	int len = str.length();
	int read = 0;
	while (read < len)
	{
		int cp;

		char temp[40];
		int encodedbytes = 0;
		if (encoder.encode(temp, temp + 4, &encodedbytes, cp))
			result.append(read, encodedbytes/2);
		else
		{
			read += 4;
		}
	}

	return result;
}

u32string string::toUTF32string(const std::string& str)
{
	u32string result;

	UTFConverter encoder(UTFConverter::ENCODING_UTF16);

	const char* s = reinterpret_cast<const char*>(str.data()); //?
	int len = str.length();
	int read = 0;
	while (read < len)
	{
		int cp;

		char temp[40];
		int encodedbytes = 0;
		if (encoder.encode(temp, temp + 4, &encodedbytes, cp))
			result.append(read, encodedbytes / 2);
		else
		{
			read += 4;
		}
	}

	return result;
}

inline int vsnprintf(char* buf, int n, const char* format, va_list arg)
{
	int ret = ::vsnprintf(buf, n, format, arg);
	return ret;
}

/*void string::scanDouble(const char**, const char**, int*) //Not in 4.1.0
{
	assert(nptr != 0) //line 697 of RCSDEBUG
}*/

} // lang

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
