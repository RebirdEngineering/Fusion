#ifndef _LANG_THROWABLE_H
#define _LANG_THROWABLE_H


#include <lang/pp.h>
#include <lang/Format.h>


BEGIN_NAMESPACE(lang) 


/**
 * Base class for all exceptions.
 * 
 * @ingroup lang
 */
class Throwable : //14
	public std::exception //Now uses std::exception
{
public:
	/** 
	 * Creates throwable object with no error description. 
	 */
	Throwable(); //21
	
	virtual ~Throwable(); //26

	/** 
	 * Creates throwable object with error description. 
	 * @exception FormatException If message is not valid.
	 */
	Throwable( const Format& msg ); //32

	/** 
	 * Returns the error message format object. 
	 */
	const Format& getMessage() const; //37
	
	/** 
	 * 
	 */
	const char* what() const; //42

	/*
	 * Used by implementation to show error message dialog box.
	 */
	void showExceptionDialog(); //47

private:
	Format	m_msg; //50
	std::string	m_str; //51
};
/** 
 * Wrapper for throwing exceptions.
 * Can be made 'work' also on platforms which do not support exceptions.
 */
template <class T> void throwError( T e )
{
#ifdef LANG_EXCEPTIONS
	throw e;
#else
	e.showExceptionDialog();
#endif
}


} // lang


#endif // _LANG_THROWABLE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
