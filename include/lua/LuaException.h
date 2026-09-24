#ifndef _LUA_LUAEXCEPTION_H
#define _LUA_LUAEXCEPTION_H

#include <lang/Exception.h>

BEGIN_NAMESPACE(lua) 

/**
 * Thrown if Lua operation fails.
 * @ingroup lua
 */
class LuaException : //12
	public NS(lang,Exception)
{
public:
	LuaException( const NS(lang,Format)& msg )				: Exception(msg) {} //16
};


END_NAMESPACE() // lua


#endif // _LUA_LUAEXCEPTION_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
