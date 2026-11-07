#ifndef _LUA_LUASTACKRESTORE_H
#define _LUA_LUASTACKRESTORE_H

#include <lang/pp.h>

struct lua_State;

namespace lua
{

class LuaState;

/** 
 * Helper class for storing and restoring Lua stack stack top position.
 * Stores the top at the construction and restores it at the end of scope.
 * 
 * @ingroup lua
 */
class LuaStackRestore //17
{
public:
	/** Saves Lua stack top position. */
	LuaStackRestore( LuaState* luastate ); //21

	/** Saves Lua stack top position. */
	LuaStackRestore( lua_State* impl ); //24

	/** Restores Lua stack top position. */
	~LuaStackRestore(); //27

private:
	lua_State*	m_impl; //30
	int			m_top; //31

	LuaStackRestore( const LuaStackRestore& ); //33
	LuaStackRestore& operator=( const LuaStackRestore& ); //34
};


} // lua


#endif // _LUA_LUASTACKRESTORE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
