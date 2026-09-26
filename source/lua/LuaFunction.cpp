#include <lua/LuaFunction.h>
#include <lua/LuaState.h>
#include <external/lua/src/lua.h>
#include <external/lua/src/lauxlib.h>

namespace lua
{

LuaFunction::LuaFunction() : //Why is this a carbon copy like literally why 
    m_luastate(0),
    m_ref(-1)
{
}

LuaFunction::LuaFunction(LuaState* luastate, int ref) : //Oh yay look at that, one semi original function! Idk the var so "ref" is set.
	m_luastate(luastate),
	m_ref(ref)
{
	if (luastate)
	{
		m_luastate->pushNumber(ref);
		m_ref = lua_ref(m_luastate->impl(), true);
	}
}

LuaFunction::LuaFunction(const LuaFunction& other) :
    m_luastate(other.m_luastate),
    m_ref(-1)
{
    if (other.m_luastate && other.m_ref >= 0)
    {
        lua_State* impl = m_luastate->impl();
        lua_getref(impl, other.m_ref);
        m_ref = lua_ref(impl, true);
    }
}

LuaFunction::~LuaFunction()
{
	if (m_ref >= 0)
		lua_unref(m_luastate->impl(), m_ref);
}

LuaFunction& LuaFunction::operator=(const LuaFunction& other)
{
	int oldref = m_ref;
	lua_State* oldlua = m_luastate ? m_luastate->impl() : 0;

	if (other.m_luastate != 0 && other.m_luastate->impl() && other.m_ref >= 0)
	{
		lua_State* impl = other.m_luastate->impl();
		lua_getref(impl, other.m_ref);
		m_luastate = other.m_luastate;
		m_ref = lua_ref(impl, true);
	}
	else
	{
		m_luastate = 0;
		m_ref = -1;
	}

	if (oldlua && oldref >= 0)
		lua_unref(oldlua, oldref);

	return *this;
}

void LuaFunction::operator()()
{
	getRef();
	m_luastate->call(0, 0);
}

void LuaFunction::getRef()
{
	lua_getref(m_luastate->impl(), m_ref);
}

}