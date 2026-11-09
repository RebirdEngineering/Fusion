#include <net/HttpRequest.h>
#include <net/HttpRequestException.h>

#ifdef PLATFORM_ANDROID
#include <io/BundleInputStream.h>
#include <io/AppDataOutputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/PathName.h>

using namespace io;
#endif

#include <external/curl/include/curl/curl.h>

using namespace lang;


/*
494960 / 10445883 (RCS debug Win32): curl_easy_setopt
494A70: curl_easy_cleanup
*/

namespace net
{

class HttpRequest::Impl : public Object //Win32 (0x40 bytes | RCS debug 0x44 bytes), Posix [OSX, Android] (0x58 bytes), OSX RCS debug (0xB0 bytes) 
{
public:
	Impl() //493BB0
	{
		curlC = 0;

		curlC = curl_easy_init();

		if (!curlC)
			throwError(HttpRequestException(Format("Creating HttpRequest failed")));

		curl_easy_setopt(curlC, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(curlC, CURLOPT_COOKIEJAR, 0);

#ifdef PLATFORM_ANDROID //Android exclusive functionality. Correct?
		static bool initialized; //Unofficial

		if (!initialized) //This writes the APK's certificate to data/data/com.rovio.angrybirdsseasons/files, happens on every bootup.
		{
			BundleInputStream bndl("data/certificates/cacert.pem");
			ByteArrayInputStream bais(bndl);
			AppDataOutputStream adis("cacert.pem");
			adis.write(bais.data(), bais.available());
			initialized = true;
		}

		curl_easy_setopt(curlC, CURLOPT_CAINFO, PathName(AppDataOutputStream::path(), "cacert.pem").toString()); //Then it set curl's CA info file to the cert written to AppData
#endif

	}

	~Impl()
	{
		curl_easy_cleanup(curlC);
	}

	HttpResponse get(const std::string& url) //494660 | RCS debug (Win32): 10A4A718
	{
		curl_easy_setopt(curlC, CURLOPT_POST, 0);

		sendfunction98.clear();

		curl_easy_setopt(curlC, CURLOPT_HTTPGET, 1);

		return perform(url);
	}

	HttpResponse post(const std::string& url, const std::string& data) //4946B0 | RCS debug (Win32): 10A4B212
	{
		curl_easy_setopt(curlC, CURLOPT_POST, 0);

		sendfunction98.clear();

		curl_easy_setopt(curlC, CURLOPT_POST, 1);

		curl_easy_setopt(curlC, CURLOPT_POSTFIELDS, data.data());
		curl_easy_setopt(curlC, CURLOPT_POSTFIELDSIZE_LARGE, data.size());

		return perform(url);
	}

	HttpResponse post(const std::string& url, size_t size, const SendFunction sendfunction) //RCS debug (Win32): 10A4B390 | Not seen in ABSeasons 4.1.0 (Win32).
	{
		curl_easy_setopt(curlC, CURLOPT_POST, 1);
		curl_easy_setopt(curlC, CURLOPT_POSTFIELDS, 0);
		curl_easy_setopt(curlC, CURLOPT_POSTFIELDSIZE_LARGE, size);

		sendfunction98 = sendfunction;

		return perform(url);
	}

	HttpResponse del(const std::string& url) //494740 | RCS debug (Win32): 10A4B7B3
	{
		curl_easy_setopt(curlC, CURLOPT_POST, 0);

		sendfunction98.clear();

		curl_easy_setopt(curlC, CURLOPT_CUSTOMREQUEST, "DELETE");

		return perform(url);
	}

	void setConnectionTimeout(int milliseconds) //493520 | RCS debug (Win32): 10A4B8C4
	{
		curl_easy_setopt(curlC, CURLOPT_CONNECTTIMEOUT_MS, milliseconds);
	}

	void setHeader(const std::string& header) //493FB0 | RCS debug (Win32): 10A4B97D
	{
		size_t pos = header.find_first_of(":");

		if (pos == -1)
			throwError(HttpRequestException(Format("Malformed header {0}", header)));

		std::string key = header.substr(0, pos);
		std::string value = string::tolower(key).substr();

		m_headers[key] = value;
	}

	void resetHeaders()
	{
		m_headers.clear();
	}

	void addCookie(const std::string& cookie) // | Not seen in ABSeasons 4.1.0 (Win32).
	{
		std::string cookieList = "Set-Cookie" + cookie;
		curl_easy_setopt(curlC, CURLOPT_COOKIELIST, cookieList.c_str());
	}

	void resetCookies() // | Not seen in ABSeasons 4.1.0 (Win32).
	{
		curl_easy_setopt(curlC, CURLOPT_COOKIELIST, "ALL");
	}

	void setProgressFunction(const ProgressFunction& progressFunction) //RCS debug: 10A4BEE4 | Not seen in ABSeasons 4.1.0 (Win32)
	{
		if (m_progressFunction.empty())
		{
			curl_easy_setopt(curlC, CURLOPT_NOPROGRESS, 1);
			curl_easy_setopt(curlC, CURLOPT_PROGRESSFUNCTION, 0);
		}

		else
		{
			m_progressFunction = progressFunction;
			curl_easy_setopt(curlC, CURLOPT_NOPROGRESS, 0);
			curl_easy_setopt(curlC, CURLOPT_PROGRESSFUNCTION, customProgressFunction);
			curl_easy_setopt(curlC, CURLOPT_PROGRESSDATA, m_progressFunction);
		}
	}

	void setReceiveFunction(const ReceiveFunction& function)
	{
		m_writeFunction = function;
	}

	void setWriteHeaderFunction(const ReceiveFunction& writeHeaderFunction)
	{
		m_writeHeaderFunction = writeHeaderFunction;
	}

private:

	/* //Struct by IDA
	  _DWORD dwordC;
	  _BYTE gap10[4];
	  _DWORD dword14;
	  _DWORD dword18;
	  __declspec(align(8)) _DWORD dword20;
	  _DWORD dword24;
	  _DWORD dword28;
	  _DWORD dword2C;
	  _DWORD dword30;
	  _DWORD dword34;
	  _DWORD dword38;
	  _DWORD dword3C;
	*/

	CURL* curlC; //0x0C
	std::map<std::string, std::string> m_headers;
	
	ProgressFunction m_progressFunction; //0x50 on OSX
	ReceiveFunction m_writeFunction; //0x68 on OSX (receivefunction? m_recieveFunction?)
	ReceiveFunction m_writeHeaderFunction; //0x80 on OSX
	SendFunction sendfunction98; //0x98 on OSX

	static int defaultReceiveFunction(const char*, unsigned long, unsigned long, void*) //493540 | TODO
	{
		return 0;
	}

	static int defaultWriteHeaderFunction(const char*, unsigned long, unsigned long, void*) //493560 | TODO
	{
		return 0;
	}

	static int customReceiveFunction(char*, unsigned long, unsigned long, void*) //493650 | TODO
	{
		return 0;
	}

	static int customWriteHeaderFunction(char*, unsigned long, unsigned long, void*) //494100 | TODO
	{
		return 0;
	}

	static int customProgressFunction(void*, double, double, double, double) //RCS debug (Win32): 10451183 | TODO
	{
		return 0;
	}

	static int customSendFunction(char*, unsigned long, unsigned long, void*) //TODO
	{
		return 0;
	}

	HttpResponse perform(const std::string& url) //4941E0 | RCS debug (Win32): 10A4A7C5 | Correct?
	{
		curl_slist* list = 0; //?

		curl_easy_setopt(curlC, CURLOPT_URL, url.c_str());

		for (std::map<std::string, std::string>::const_iterator it = m_headers.begin(); it != m_headers.end(); it++)
		{
			curl_slist_append(list, it->second.c_str()); //Correct?
		}

		curl_easy_setopt(curlC, CURLOPT_HTTPHEADER, list->data); //Correct?

		HttpResponse response;

		if (m_writeFunction.empty())
		{
			curl_easy_setopt(curlC, CURLOPT_WRITEFUNCTION, defaultReceiveFunction);
			curl_easy_setopt(curlC, CURLOPT_WRITEDATA, response);
		}

		else
		{
			curl_easy_setopt(curlC, CURLOPT_WRITEFUNCTION, customReceiveFunction);
			curl_easy_setopt(curlC, CURLOPT_WRITEDATA, this);
		}

		if (m_writeHeaderFunction.empty())
		{
			curl_easy_setopt(curlC, CURLOPT_HEADERFUNCTION, defaultWriteHeaderFunction);
			curl_easy_setopt(curlC, CURLOPT_HEADERDATA, response);
		}

		else
		{
			curl_easy_setopt(curlC, CURLOPT_HEADERFUNCTION, customWriteHeaderFunction);
			curl_easy_setopt(curlC, CURLOPT_HEADERDATA, this);
		}

		if (sendfunction98.empty())
		{
			curl_easy_setopt(curlC, CURLOPT_READFUNCTION, 0);
			curl_easy_setopt(curlC, CURLOPT_READDATA, response);
		}

		else
		{
			curl_easy_setopt(curlC, CURLOPT_READFUNCTION, customSendFunction);
			curl_easy_setopt(curlC, CURLOPT_READDATA, this);
		}

		CURLcode curlcode = curl_easy_perform(curlC);

		if (curlcode)
			throwError(HttpRequestException(Format(curl_easy_strerror(curlcode))));

		curl_slist_free_all(list);

		DWORD status = 0;
		curl_easy_getinfo(curlC, CURLINFO_RESPONSE_CODE, status);
		response.status = status;

		curl_easy_getinfo(curlC, CURLINFO_EFFECTIVE_URL, list);
		response.effectiveUrl = list->next->data;
		
		for (int i = 0; i < sizeof(list); i++)
		{
			response.cookies.push_back(list[i].data);
		}
		
		curl_slist_free_all(list);


		if (!response.headers.empty())
		{
			if (response.headers.back().empty())
				response.headers.pop_back();
		}

		return response;
	}

	//void executeRequest(const std::string&, RequestType, const std::string&, const std::string&, HttpResponse&);
	//void executeRequestSynchronously(const std::string&, RequestType, const std::string&, const std::string&, HttpResponse&);
};

#include <net/common/HttpRequest.h>

}