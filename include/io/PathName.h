#ifndef _IO_PATHNAME_H
#define _IO_PATHNAME_H

#include <lang/pp.h>

namespace io
{ 

class PropertyParser;
class FileBundle;

/**
 * Class for manipulating path names.
 * The class overcomes problems caused by different path name separator characters and tricky manual iteration of name components.
 * Path name consists of optional drive letter and ':',
 * directories separated with '/' or '\' and
 * file name which consists of basename followed by '.' and suffix.
 *
 * PathName class is convenient for path name manipulation as name suggests.
 * For example if you have a directory name and you want to concatenate
 * a file name to it, you can write PathName(dirname,fname) without
 * need to check does the directory name already end with slash or backslash.
 * You can also retrieve directory name from file name by calling parent()
 * method, for example in a situation where you want to load textures
 * from the same directory as the filename.
 *
 * @ingroup io
 */
class PathName //25
{
public:
	enum 
	{
		/** Maximum number of characters in a path name. */
		MAXLEN=512 //[CHANGED] Previously 250
	};

	/**
	 * Empty path.
	 */
	PathName(); //37

	/** 
	 * Copy by value.
	 */
	PathName( const PathName& other ); //42

	/**
	 * Path name from string.
	 * @exception IOException If path name too long.
	 */
	PathName( const char* pathname ); //48

	/**
	 * Path name from string.
	 * @exception IOException If path name too long.
	 */
	PathName( const std::string& pathname ); //54

	/**
	 * Combines two path names.
	 * Note that path name with drive letter cannot be combined
	 * with any path.
	 * @exception IOException If path name too long.
	 */
	PathName( const char* first, const char* second ); //62

	/**
	 * Combines two path names.
	 * Note that path name with drive letter cannot be combined
	 * with any path.
	 * @exception IOException If path name too long.
	 */
	PathName( const std::string& first, const std::string& second ); //70

	/**
	 * Combines two path names.
	 * Note that path name with drive letter cannot be combined
	 * with any path.
	 * @exception IOException If path name too long.
	 */
	PathName(const PathName& first, const PathName& second); //78

	/** 
	 * Copy by value.
	 */
	PathName& operator=( const PathName& other ); //83

	/**
	 * Returns drive letter of the path name.
	 * Returns empty string if the component is not in path name.
	 */
	std::string		drive() const			{return m_drv;} //89

	/**
	 * Returns basename of the path name.
	 * Returns empty string if the component is not in path name.
	 * Basename is the name before suffix and after last directory separator.
	 */
	std::string		basename() const		{return m_basename;} //96

	/**
	 * Returns suffix of the path name including preceding dot.
	 * Returns empty string if the component is not in path name.
	 */
	std::string		suffix() const			{return m_suffix;} //102

	/**
	 * Returns basename with suffix.
	 */
	std::string		filename() const; //107

	/**
	 * Returns parent path.
	 * Parent path is path before last directory separator.
	 */
	PathName		parent() const; //113

	/**
	 * Returns path name as 0-terminated string.
	 */
	std::string		toString() const		{return m_path;} //118

private:
	char*	m_path; //136
	char*	m_drv; //137
	char*	m_dir; //138
	char*	m_basename; //139
	char*	m_suffix; //140
	int		m_alloc; //141
	char	m_buf[MAXLEN*2]; //142

	char*	allocate( int chars ); //144
	void	parse( const char* path, const char* second ); //145
};


} // io


#endif // _IO_PATHNAME_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
