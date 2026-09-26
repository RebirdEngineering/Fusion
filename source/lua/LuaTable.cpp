#include <lua/LuaTable.h>
#include <io/InputStream.h>
#include <io/OutputStream.h>
#include <lua/LuaFunction.h>
#include <lua/LuaState.h>
#include <lua/LuaStackRestore.h>
#include <lua/LuaException.h>
#include <external/lua/src/lua.h>
#include <external/lua/src/lauxlib.h>


using namespace io;
using namespace lang;


namespace lua
{ 

bool isDigit(char chr) //?
{
	return false; //?
}

class LuaKeywordChecker
{
public:
	LuaKeywordChecker()
	{
		const char* const keywords[] = { "and", "break", "do", "else", "elseif", "end", "false", "for", "function", "if", "in", "local", "nil", "not", "or", "repeat", "return", "then", "true", "nil"};

		for (int i = 0 < sizeof(keywords)/sizeof keywords[0]; i++; )
		{
			//isValidKeyName(keywords[i]);
		}
	}
	bool isValidKeyName(const char* key)
	{
		static LuaKeywordChecker checker;
		for (int i = 0 < sizeof(checker.m_keywords) / sizeof checker.m_keywords[0]; i++; )
		{
			//checker.isValidKeyName(m_keywords[i]);
		}
		return false;
	}
private:
	std::map<std::string, bool> m_keywords;
};

LuaTable::LuaTable() : //So the Fusion LuaTable just carbon copies most stuff
	m_luastate( 0 ),
	m_ref( -1 )
{
}

LuaTable::LuaTable( LuaState* luastate ) :
	m_luastate( luastate ),
	m_ref( -1 )
{
	if ( luastate )
	{
		m_luastate->newTable();
		m_ref = lua_ref( m_luastate->impl(), true );
	}
}

LuaTable::LuaTable( const LuaTable& other ) :
	m_luastate( other.m_luastate ),
	m_ref( -1 )
{
	if ( other.m_luastate && other.m_ref >= 0 )
	{
		lua_State* impl = m_luastate->impl();
		lua_getref( impl, other.m_ref );
		m_ref = lua_ref( impl, true );
	}
}

LuaTable::LuaTable( LuaTable&& other) :
	m_luastate(other.m_luastate),
	m_ref(other.m_ref)
{
}

LuaTable::~LuaTable()
{
	if ( m_ref >= 0 )
		lua_unref( m_luastate->impl(), m_ref );
}

LuaTable& LuaTable::operator=( const LuaTable& other )
{
	int oldref = m_ref;
	lua_State* oldlua = m_luastate ? m_luastate->impl() : 0;

	if ( other.m_luastate != 0 && other.m_luastate->impl() && other.m_ref >= 0 )
	{
		lua_State* impl = other.m_luastate->impl();
		lua_getref( impl, other.m_ref );
		m_luastate = other.m_luastate;
		m_ref = lua_ref( impl, true );
	}
	else
	{
		m_luastate = 0;
		m_ref = -1;
	}

	if ( oldlua && oldref >= 0 )
		lua_unref( oldlua, oldref );

	return *this;
}

LuaTable& LuaTable::operator=( LuaTable&& other )
{
	swap(other);
	return *this;
}

void LuaTable::remove( int index )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	lua_pushnil( impl );
	lua_rawseti( impl, -2, index );
}

void LuaTable::remove( const std::string& name )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushnil( impl );
	lua_rawset( impl, -3 );
}

void LuaTable::remove(const char* name)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushnil(impl);
	lua_rawset(impl, -3);
}

void LuaTable::setString( int index, const std::string& v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, v );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setString(int index, const char* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, v);
	lua_rawseti(impl, -2, index);
}

void LuaTable::setNumber( int index, float v ) 
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	lua_pushnumber( impl, v );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setTable( int index, const LuaTable& v ) 
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushTable( impl, &v );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setBoolean( int index, bool v ) 
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	lua_pushboolean( impl, v?1:0 );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setString( const std::string& name, const std::string& v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushString( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setString( const char* name, const std::string& v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushString( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setString(const std::string& name, const char* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushString(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setString(const char* name, const char* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushString(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setNumber( const std::string& name, float v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushnumber( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setNumber(const char* name, float v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushnumber(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setTable( const std::string& name, const LuaTable& v )
{
	assert( m_ref >= 0 );
	assert( v.m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushTable( impl, &v );
	lua_rawset( impl, -3 );
}

void LuaTable::setTable(const char* name, const LuaTable& v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushTable(impl, &v);
	lua_rawset(impl, -3);
}

void LuaTable::setTable( const char* name, const LuaTable* v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushTable( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setFunction(int index, const LuaFunction& v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushFunction(impl, v);
	lua_rawseti(impl, -2, index);
}

void LuaTable::setFunction(int index, const LuaFunction* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushFunction(impl, v);
	lua_rawseti(impl, -2, index);
}

void LuaTable::setBoolean( const std::string& name, bool v )
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushboolean( impl, v?1:0 );
	lua_rawset( impl, -3 );
}

void LuaTable::setBoolean(const char* name, bool v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushboolean(impl, v ? 1 : 0);
	lua_rawset(impl, -3);
}

std::string LuaTable::getString(const std::string& name) const //According to the DWARF it's not in CPP yet ELF shows this symbol, why?
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_STRING;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tostring(impl, -1);
}

std::string LuaTable::getString(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_STRING;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tostring(impl, -1);
}

float LuaTable::getNumber(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_NUMBER;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tonumber(impl, -1);
}

float LuaTable::getNumber(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_NUMBER;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tonumber(impl, -1);
}

LuaTable LuaTable::getTable(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_TABLE;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	LuaTable tab;
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

LuaTable LuaTable::getTable(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_TABLE;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	LuaTable tab;
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

LuaFunction LuaTable::getFunction(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_FUNCTION;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	LuaFunction fun;
	fun.m_luastate = m_luastate;
	fun.m_ref = lua_ref(impl, true);
	return fun;
}

LuaFunction LuaTable::getFunction(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_FUNCTION;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	LuaFunction fun;
	fun.m_luastate = m_luastate;
	fun.m_ref = lua_ref(impl, true);
	return fun;
}

LuaFunction LuaTable::getFunction(int index) const
{
	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	LuaState::Type expectedtype = LuaState::TYPE_FUNCTION;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);

	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype))));
	}
	LuaFunction fun;
	fun.m_luastate = m_luastate;
	fun.m_ref = lua_ref(impl, true);
	return fun;
}

std::string LuaTable::getString(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	LuaState::Type expectedtype = LuaState::TYPE_STRING;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tostring(impl, -1);
}

float LuaTable::getNumber(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	LuaState::Type expectedtype = LuaState::TYPE_NUMBER;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return lua_tonumber(impl, -1);
}

LuaTable LuaTable::getTable(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	LuaState::Type expectedtype = LuaState::TYPE_TABLE;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	LuaTable tab;
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

bool LuaTable::getBoolean(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_BOOLEAN;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::getBoolean(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_BOOLEAN;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::getBoolean(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	LuaState::Type expectedtype = LuaState::TYPE_BOOLEAN;
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1);
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype))));
	}

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::isNil(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnil(impl, -1);
	return res;
}

bool LuaTable::isNil(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnil(impl, -1);
	return res;
}

bool LuaTable::isNil(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isnil(impl, -1);
	return res;
}

bool LuaTable::isString(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isstring(impl, -1);
	return res;
}

bool LuaTable::isString(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isstring(impl, -1);
	return res;
}

bool LuaTable::isNumber(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnumber(impl, -1);
	return res;
}

bool LuaTable::isNumber(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnumber(impl, -1);
	return res;
}

bool LuaTable::isNumber(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isnumber(impl, -1);
	return res;
}

bool LuaTable::isTable(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_istable(impl, -1);
	return res;
}

bool LuaTable::isTable(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_istable(impl, -1);
	return res;
}

bool LuaTable::isBoolean(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isboolean(impl, -1);
	return res;
}

bool LuaTable::isBoolean(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isboolean(impl, -1);
	return res;
}

bool LuaTable::isBoolean(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isboolean(impl, -1);
	return res;
}

bool LuaTable::isTable(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_istable(impl, -1);
	return res;
}

void LuaTable::pushMember(const char* name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	lua_remove(impl, -2);
}

void LuaTable::pushMember(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	lua_remove(impl, -2);
}

void LuaTable::writeChar(OutputStream& out, int ch)
{
	assert(ch >= 0 && ch < 256);
	char b = (char)ch;
	out.write(&b, sizeof(b));
}

void LuaTable::writeMargin(OutputStream& out, int margin)
{
	for (int i = 0; i < margin; ++i)
		writeChar(out, ' ');
}

void LuaTable::writeString(OutputStream& out, const char* str)
{
	const int len = strlen(str);
	for (int i = 0; i < len; ++i)
		writeChar(out, str[i]);
}

void LuaTable::writeStringLiteral(OutputStream& out, const char* str)
{
	const int len = strlen(str);
	for (int i = 0; i < len; ++i)
		writeChar(out, str[i]);
}

void LuaTable::writeValue(OutputStream& out, int index, int margin)
{
	LuaState::Type valuetype = m_luastate->type(index);
	switch (valuetype)
	{
	case LuaState::TYPE_BOOLEAN:
		if (m_luastate->toBoolean(index))
			writeString(out, "true");
		else
			writeString(out, "false");
		break;
	case LuaState::TYPE_NUMBER: {
		char buf[32];
		sprintf(buf, "%g", (float)m_luastate->toNumber(index));
		writeString(out, buf);
		break;
	}
	case LuaState::TYPE_STRING:
		writeString(out, "\"");
		writeString(out, m_luastate->toString(index));
		writeString(out, "\"");
		break;
	case LuaState::TYPE_TABLE: {
		writeString(out, "{\n");
		LuaTable tab = m_luastate->toTable(index);
		tab.write(out, margin + 4);
		writeString(out, "\n");
		writeMargin(out, margin);
		writeString(out, "}");
		break;
	}
	default:
		writeString(out, "nil");
		break;
	}
}

void LuaTable::write(OutputStream& out, int margin)
{
	assert(m_luastate);

	LuaStackRestore lsr(m_luastate);
	m_luastate->pushTable(this);
	int tab = m_luastate->top();
	bool first = true;
	bool strkeys = false;
	int keyindex = 1;

	for (m_luastate->pushNil(); m_luastate->next(tab); m_luastate->pop())
	{
		LuaState::Type keytype = m_luastate->type(-2);
		if (keytype == LuaState::TYPE_STRING)
		{
			if (!strcmp(m_luastate->toString(-2), "_G"))
			{
				continue;
			}

			writeMargin(out, margin);
			writeString(out, m_luastate->toString(-2));
			writeString(out, " = ");
			writeValue(out, -1, margin);
			writeString(out, "\n");

			strkeys = true;
		}
		else if (!strkeys)
		{
			if (first)
				writeMargin(out, margin);
			else
				writeString(out, ",");

			writeValue(out, -1, margin);

			++keyindex;
		}

		first = false;
	}
}

void LuaTable::read(InputStream& in)
{
	assert(m_luastate);
	m_luastate->compile(in, in.available(), in.toString(), this);
}

void LuaTable::read(const std::vector<unsigned char>& in)
{
	assert(m_luastate);
	if (in.data())
	{
		const char* buf;
		//m_luastate->compile(buf, in.size(), in, this); //?
	}
}

void LuaTable::read(const std::string& in)
{
	assert(m_luastate);
	if (in.data())
	{
		const char* buf;
		m_luastate->compile(buf, in.size(), in.substr(), this); //?
	}
}

void LuaTable::traverse(LuaTableVisitor& visitor)
{
	visitor.closeTable();
	traverseRecursively(visitor);
	visitor.start();
}

void LuaTable::traverseRecursively(LuaTableVisitor& visitor)
{
	/*LuaStackRestore lsr(m_luastate);
	m_luastate->pushTable(this);
	int tableRef = m_luastate->top();
	for (m_luastate->pushNil(); m_luastate->next(tableRef); m_luastate->pop())
	{
		const int nameIndex = -2;
		const int valueIndex = -1;

		LuaState::Type nameType = m_luastate->type(-2);
		LuaState::Type valueType = m_luastate->type(-1);

		const char* name = m_luastate->toString(-2);
		if (nameType == LuaState::TYPE_STRING)
		{
			if (!strcmp(name, "_G"))
			{
				continue;
			}
			else
			{
				m_luastate->toTable()
				const bool value;
				const double value;
				const char* value;
				LuaTable innerTable = m_luastate->toTable(;
				switch (valueType)
				{
				case LuaState::TYPE_NIL: break;
				case LuaState::TYPE_BOOLEAN: break;
				case LuaState::TYPE_LIGHTUSERDATA: break;
				case LuaState::TYPE_NUMBER: break;
				case LuaState::TYPE_STRING: break;
				case LuaState::TYPE_TABLE: traverseRecursively(visitor); break;
				case LuaState::TYPE_FUNCTION: break;
				case LuaState::TYPE_USERDATA: break;
				case LuaState::TYPE_THREAD: break;
				}
			}
		}
	}*/
}

int LuaTable::size() const
{
	assert(m_luastate);

	LuaStackRestore lsr(m_luastate);
	m_luastate->pushTable(this);
	int tab = m_luastate->top();

	int count = 0;
	for (m_luastate->pushNil(); m_luastate->next(tab); m_luastate->pop())
		++count;
	return count;
}

void LuaTable::getRef() const
{
	lua_State* impl = m_luastate->impl(); //Assuming
	lua_getref(impl, m_ref);
}

void LuaTable::swap(LuaTable& other)
{
	other.m_luastate = m_luastate;
	other.m_ref = m_ref;
}

} // lua

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
