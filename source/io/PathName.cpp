#include <io/PathName.h>
#include <io/IOException.h>

using namespace lang;

namespace io
{ 

PathName::PathName() :
	m_alloc( 0 )
{
	m_path = m_drv = m_dir = m_basename = m_suffix = allocate(1); //15
}

PathName::PathName( const char* pathname ) //18
{
	parse( pathname, 0 );
}

PathName::PathName( const std::string& pathname ) //23
{
	parse( pathname.c_str(), 0); //25
}

PathName::PathName( const char* first, const char* second ) //Not on iOS.
{
	parse( first, second );
}

PathName::PathName( const std::string& first, const std::string& second ) //33
{
	parse(first.c_str(), second.c_str()); //35
}

PathName::PathName(const PathName& first, const PathName& second) //38
{
	parse(first.m_path, second.m_path);
}

PathName::PathName(const PathName& other)
{
	*this = other;
}

PathName& PathName::operator=( const PathName& other ) //48
{
	m_path		= m_buf + (other.m_path - other.m_buf);
	m_drv		= m_buf + (other.m_drv - other.m_buf);
	m_dir		= m_buf + (other.m_dir - other.m_buf);
	m_basename	= m_buf + (other.m_basename - other.m_buf);
	m_suffix	= m_buf + (other.m_suffix - other.m_buf);
	m_alloc		= other.m_alloc;
	memcpy( m_buf, other.m_buf, other.m_alloc );

	assert( !strcmp(m_drv,other.m_drv) ); //Assert on line 58 in RCSSDKDEBUG
	assert( !strcmp(m_dir,other.m_dir) ); //Assert on line 59 in RCSSDKDEBUG
	assert( !strcmp(m_basename,other.m_basename) ); //Assert on line 60 in RCSSDKDEBUG
	assert( !strcmp(m_suffix,other.m_suffix) ); //Assert on line 61 in RCSSDKDEBUG
	return *this;
}

PathName PathName::parent() const
{
	char buf[MAXLEN]; //67
	strcpy( buf, m_path );
	int len = strlen(buf); //69
	if ( len > 0 && buf[len-1] == '/' )
		buf[len-1] = 0;
	char* sep = strrchr( buf, '/' ); //72
	if ( sep != 0 )
		*sep = 0;
	else
		buf[0] = 0;
	return PathName( buf ); //77
}

char* PathName::allocate( int chars ) //80
{
	assert( m_alloc+chars <= (int)sizeof(m_buf) ); //Assert on line 98 (moved) or 82 in RCSSDKDEBUG
	if ( m_alloc+chars > (int)sizeof(m_buf) )
		throwError( IOException( Format("Path name buffer overflow, {0} bytes. Initial path name was \"{1}\".", m_alloc+chars, m_path) ) ); //84

	char* p = m_buf + m_alloc; //86
	m_alloc += chars;
	memset( p, 0, chars );
	return p;
}

void PathName::parse( const char* path, const char* second ) //92 | TODO
{
	assert( path != 0 ); //Assert on line 110 or 94 in RCSSDKDEBUG

	int len1 = strlen(path); //96 | Got rid of a comment?

	// skip preceding / from second path
	if (len1 && second != 0 && (*second == '/' || *second == '\\') ) //99
		++second;

	// reset
	m_alloc = 0;
	m_path = m_drv = m_dir = m_basename = m_suffix = allocate(1); //104

	// get whole path
	int len2 = 0; //108
	if ( second != 0 )
		len2 = strlen(second); //110
	int len = len1 + len2; //111
	m_path = allocate( len+2 ); //112
	strcpy( m_path, path ); //113
	if ( second != 0 )
	{
		if ( len1 > 0 && m_path[len1-1] != '/' && m_path[len1-1] != '\\' )		
			m_path[len1++] = '/';
		memcpy( m_path+len1, second, len2 ); //118
		len = len1+len2;
		m_path[len] = 0;
	}

	// Fix backslashes
	for ( char* s = m_path ; *s != 0 ; ++s ) //124
	{

		if ( *s == '\\' )
			*s = '/';		
	}

	/*for (char* s = m_path; *s != 0; ++s) //132 | TODO START
	{
		if (*s != '.')
			break;
		
		if (s[1] == '.')
		{
			int endlen = strlen(&s[2]); //139

			if (endlen > 0)
			{
				if (s == m_path)
					break;

				char* parent = s; //150
				int counter = 1; //151
				while (parent >= m_path) //Todo change?
				{
					if (*parent == '/' && !counter)
						break;
					counter--;
				}

				memmove(parent + 1, &s[3], endlen - 1);
				memset(&parent[1][&endlen], 0, s[3] - parent[1]);
			}
		}

		else if (s[1] == '/')
		{
			int endlen = strlen(&s[1]); //171

			if (endlen > 0)
			{
				for (char* current = &s[1]; current < m_path && *current != '/'; current--) //175 | Todo change?
				{
					memmove(&s[1], &s[2], endlen - 1 ); //187
					memset(&s[endlen - 1], 0, s + 2 - s + 1); //188
					*s = current[1] - 1;
				}
			}
		}
	} //TODO END*/

	// parse drive letter: C:/mydocs/myfile.doc -> C:
	const char* sep = strchr( path, ':' ); //198
	if ( 0 != sep )
	{
		int n = sep - path + 1; //201
		m_drv = allocate( n+1 );
		memcpy( m_drv, path, n );
		m_drv[n] = 0;
		path = sep + 1;
	}

	// parse directory: /mydocs/myfile.doc -> /mydocs/
	sep = strrchr( path, '/' );
	if ( 0 != sep )
	{
		int n = sep - path + 1; //224
		m_dir = allocate( n+1 );
		memcpy( m_dir, path, n );
		m_dir[n] = 0;
		path += n;
	}

	// parse basename and suffix
	sep = strrchr( path, '.' );
	if ( 0 != sep )
	{
		int n = sep - path; //235
		m_basename = allocate( n+1 );
		memcpy( m_basename, path, n );
		m_basename[n] = 0;
		m_suffix = allocate( strlen(sep)+1 );
		strcpy( m_suffix, sep ); //240
	}
	else if ( strlen(path) > 0 )
	{
		m_basename = allocate( strlen(path)+1 ); //244
		strcpy( m_basename, path ); //245
	}
}

std::string PathName::filename() const
{
	char buf[MAXLEN]; //251
	strcpy( buf, basename().c_str() );
	strcat( buf, suffix().c_str());
	return buf;
}


} // io

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
