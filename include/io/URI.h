#ifndef _IO_URI_H
#define _IO_URI_H

#include <lang/pp.h>

namespace io
{

class URI
{
public:
	URI();

	URI(const std::string& str);

	URI(const char* str);

	const std::string& scheme() const;

	const std::string& authority() const;

	const std::string& userInfo() const;

	const std::string& host() const;

	int port() const;

	const std::string& path() const;

	std::vector<std::string> pathComponents() const;

	const std::string& query() const;

	const std::string& fragment() const;

	const std::string& schemeSpecificPart() const;

	bool isAbsolute() const;

	bool isOpaque() const;

	URI relativize(const URI&) const;

	URI resolve(const URI&) const;

	URI normalize() const;

	const std::string& toString() const;
private:
	void parse(const std::string& uri);
	void parseAuthority(const std::string& authority);

	std::string m_uri;
	std::string m_scheme;
	std::string m_authority;
	std::string m_userinfo;
	std::string m_host;
	int m_port;
	std::string m_path;
	std::string m_query;
	std::string m_fragment;
	std::string m_schemeSpecificPart;
	bool m_absolute;
	bool m_opaque;
};

}

#endif