#include <lua/LuaStackRestore.h>
#include <lua/LuaState.h>
#include <external/lua/src/lua.h>

BEGIN_NAMESPACE(lua) 

LuaStackRestore::LuaStackRestore( LuaState* luastate ) : //7
	m_impl( luastate->impl() ), //7
	m_top( lua_gettop(m_impl) ) //8
{
}

LuaStackRestore::LuaStackRestore( lua_State* impl ) : //13
	m_impl( impl ),
	m_top( lua_gettop(m_impl) )
{
}

LuaStackRestore::~LuaStackRestore()
{
	lua_settop( m_impl, m_top );
}


END_NAMESPACE() // lua

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
