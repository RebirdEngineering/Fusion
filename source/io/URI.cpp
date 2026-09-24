#include <io/URI.h>
#include <lang/String.h>

using namespace lang;

namespace io
{ 

URI::URI() //Easy!
{
	m_uri = "";
	m_scheme = "";
	m_authority = "";
	m_userinfo = "";
	m_host = "";
	m_port = -1;
	m_path = "";
	m_query = "";
	m_fragment = "";
	m_schemeSpecificPart = "";
}

URI::URI(const std::string& str)
{
	parse(str);
}

std::vector<std::string> URI::pathComponents() const
{
	return string::split(m_path, "/");
}

void URI::parse(const std::string& uri)
{	
	/*if (uri == "")
		return;
	//rcs::RequestImpl::setUrl(url); //4.0.0 abclassic android? Prob not
	m_uri = uri;
	m_absolute = false;
	m_opaque = false;
	size_t scheme_end = m_uri.find_first_of(":/");
	if (scheme_end != -1)
	{
		if (uri[scheme_end] == ':')
			m_scheme = scheme_end; //?
	}
	size_t hier_part_begin = m_uri.find_first_of("#?");
	size_t hier_part_end = m_uri.find_first_of("#?");
	size_t query_fragment_begin = m_uri.find_first_of("#?");
	size_t authority_begin = m_uri.find_first_of("#?");
	size_t authority_end = m_uri.find_first_of("#?");
	size_t path_begin = m_uri.find_first_of("#?");*/
}

void URI::parseAuthority(const std::string& authority)
{
	/*size_t begin = authority.find("@");
	if (begin != -1)
	{
		m_userinfo = authority.substr(begin);
	}
	size_t end = authority.find_last_of(":/?#[]@");
	m_host = end != -1 && authority == ":" ? authority.substr(end) : -1;
	if (end == -1)
		return;
	std::string port;
	bool isNumber = true;
	for (size_t i; i < port.size(); i++)
	{
		isdigit();
		isctype();
	}*/	
}

/*static void URI::~URI(const std::string& str)
{
}*/

URI URI::normalize() const
{
	/*std::vector<std::string> components = pathComponents();

	std::vector<std::string> stack;

	while (components.size())*/

	//size_t i;

	//std::string result;

	//isOpaque
	//schemeSpecificPart
	//.empty

	return URI();
	//return URI(result);
}

URI URI::resolve(const URI& uri) const
{
	if (isAbsolute() || uri.m_opaque)
		return uri;
	std::string result = scheme();
	if (authority().empty())
	{
		result.append(m_path);
		result.append("://");
		result.append(m_uri);
		result.append(m_authority);
	}
	else
	{
		
	}
	normalize();
	return uri;
	//return URI(result);
}

bool URI::isAbsolute() const
{
	return m_absolute;
}

const std::string& URI::scheme() const
{
	return m_scheme;
}

const std::string& URI::path() const
{
	return m_path;
}

const std::string& URI::schemeSpecificPart() const
{
	return m_schemeSpecificPart;
}

bool URI::isOpaque() const //Called in normalize
{
	return m_opaque;
}

URI URI::relativize(const URI& uri) const //Inline. Var is a guess
{
	/*if (isOpaque() || uri.isOpaque())
	{
		m_uri = uri.m_uri;
		m_scheme = uri.m_scheme;
		m_authority = uri.m_authority;
		m_userinfo = uri.m_userinfo;
		m_host = uri.m_host;
		m_port = uri.m_port;
		m_path = uri.m_path;
		m_query = uri.m_query;
		m_fragment = uri.m_fragment;
		m_schemeSpecificPart = uri.m_schemeSpecificPart;
		m_absolute = uri.m_absolute;
		m_opaque = uri.m_opaque;
	}*/
	//UNKNOWN
	return uri;
}

} // io
