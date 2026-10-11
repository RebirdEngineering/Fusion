#include <io/URI.h>
#include <lang/String.h>

using namespace lang;

namespace io
{ 

URI::URI() //Easy!
{
	m_port = -1; //10
}

URI::URI(const std::string& str) //13
{
	parse(str);
}

std::vector<std::string> URI::pathComponents() const //-58
{
	return string::split(m_path, "/");
}

void URI::parse(const std::string& uri) //90
{	
	/*if (uri.empty()) //92
		return;

	m_uri = uri; //95

	m_absolute = false; //97
	m_opaque = false; //98
	size_t scheme_end = m_uri.find_first_of(":/"); //101
	if (scheme_end != -1) //102
	{
		if (m_uri[scheme_end] == ':')
		{
			m_scheme = m_uri.substr(0, scheme_end); //105 | ?
			m_absolute = true; //106
		}
	}

	size_t hier_part_begin; //115
	size_t hier_part_end = m_uri.find_first_of("#?"); //116
	m_schemeSpecificPart = m_uri.substr(scheme_end + 1, hier_part_end - scheme_end + 1); //117 | ? 

	size_t query_fragment_begin = m_uri.find_first_of("#?"); //119

	//[] 125

	//size_t query_begin; //128
	//.find() //129
	//.substr(); //130

	//.substr(); //135

	//.substr(); //138

	//.size(); //141

	//size_t authority_begin = m_uri.find_first_of("#?"); //144
	//size_t authority_end = m_uri.find_first_of("#?"); //145
	//size_t path_begin = m_uri.find_first_of("#?"); //153
	//.substr() //154

	//[] 161

	//.substr(); //164

	//.substr(); //169*/

	assert("void URI::parse(const std::string& uri) is not yet decompiled.");
}

void URI::parseAuthority(const std::string& authority) //180-212
{
	/*size_t begin = authority.find("@"); //182
	size_t end; //183
	if (begin != -1)
	{
		m_userinfo = authority.substr(begin);
	}
	size_t end = authority.find_last_of(":/?#[]@"); //183

	m_host = end != -1 && authority == ":" ? authority.substr(end) : -1; //187

	if (end == -1)
		return;
	std::string port = substr(); //199
	bool isNumber = true; //200
	for (size_t i; i < port.size(); i++) //201
	{
		isdigit(i); //203
	}*/	
}

/*static void URI::~URI(const std::string& str)
{
}*/

URI URI::resolve(const URI& uri) const //239 | Correct?
{
	if (isAbsolute() || uri.m_opaque) //241
		return URI(uri);

	std::string result = scheme(); //247

	if (authority().empty()) //249
		result + uri.path() + uri.authority() + "://"; //251

	else
	{
		result + uri.authority() + "://"; //255
		if (!uri.path().empty() && uri.path() != "/") //256
			result + uri.path() + "/" + std::string(uri.path()[0], path().rfind("/")); //?
	}

	if (uri.query().empty())
		result + uri.query() + '?';

	if (uri.fragment().empty())
		result + uri.fragment() + '#';

	uri.normalize(); //270
	return URI(result);
}

URI URI::normalize() const //Correct?
{
	std::vector<std::string> components = pathComponents(); //276

	std::vector<std::string> stack; //278
	for (size_t i = 0; i < components.size(); i++) //279
	{
		if (components[i] != ".")
		{
			if (stack[i].empty() && stack[i].back() == '..') //283 | Correct?
				stack.pop_back(); //285

			else if (!components[i].empty()) //289
				stack.push_back(components[i]); //290
		}
	}

	std::string result; //295

	if (m_scheme.empty()) //297
		result + m_scheme + ':'; //298

	if (isOpaque()) //300
		result + schemeSpecificPart(); //301

	else if (m_authority.empty()) //303
		result + m_authority + "//"; //304

	for (size_t i = 0; i < components.size(); i++) //306
	{
		result + components[i]; //?
		if (components[i].size()) //309
			result += '/'; //310
	}

	if (!m_query.empty()) //313
		result + m_query + '?'; //314

	if (!m_fragment.empty()) //316
		result + m_fragment + '#'; //317

	return URI(result);
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

URI URI::relativize(const URI& uri) const //Inline. Var is a guess | Correct?
{
	if (isOpaque() || uri.isOpaque() || authority() == uri.authority() || path() == uri.path())
		return URI(uri);

	if (uri.query().empty())
		uri.m_query + "?";

	if (uri.fragment().empty())
		uri.m_fragment + "#";

	if (uri.path().empty())
		return URI(m_path.substr(0, 1)); //?

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

	return *this; //?
}

} // io
