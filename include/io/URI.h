#ifndef _IO_URI_H
#define _IO_URI_H

#include <lang/pp.h>

namespace io
{

class URI //11
{
public:
	URI(); //17

	URI(const std::string& str); //23

	URI(const char* str); //29

	const std::string& scheme() const; //34

	const std::string& authority() const; //39

	const std::string& userInfo() const; //44

	const std::string& host() const; //49

	int port() const; //55

	const std::string& path() const; //60

	std::vector<std::string> pathComponents() const; //65

	const std::string& query() const; //70

	const std::string& fragment() const; //75

	const std::string& schemeSpecificPart() const; //80

	bool isAbsolute() const; //85

	bool isOpaque() const; //90

	URI relativize(const URI&) const; //95

	URI resolve(const URI&) const; //100

	URI normalize() const; //105

	const std::string& toString() const; //110

private:
	std::string m_uri; //113
	std::string m_scheme; //114
	std::string m_authority; //115
	std::string m_userinfo; //116
	std::string m_host; //117
	int m_port; //118
	std::string m_path; //119
	std::string m_query; //120
	std::string m_fragment; //121
	std::string m_schemeSpecificPart; //122
	bool m_absolute; //123
	bool m_opaque; //124

	void parse(const std::string& uri); //126
	void parseAuthority(const std::string& authority); //127
};

}

#endif