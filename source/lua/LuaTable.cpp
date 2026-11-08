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

LuaTable::LuaTable() : //So the Fusion LuaTable just carbon copies most stuff
	m_luastate( 0 ),
	m_ref( -1 )
{
}

LuaTable::LuaTable( LuaState* luastate ) : //29-38
	m_luastate( luastate ),
	m_ref( -1 )
{
	if ( luastate )
	{
		m_luastate->newTable();
		m_ref = lua_ref( m_luastate->impl(), true ); //36
	}
}

LuaTable::LuaTable( const LuaTable& other ) : //40-50
	m_luastate( other.m_luastate ),
	m_ref( -1 )
{
	if ( other.m_luastate && other.m_ref >= 0 )
	{
		lua_State* impl = m_luastate->impl(); //46
		lua_getref( impl, other.m_ref ); //47
		m_ref = lua_ref( impl, true ); //48
	}
}

LuaTable::LuaTable( LuaTable&& other) :
	m_luastate(other.m_luastate),
	m_ref(other.m_ref)
{
	m_luastate = 0;
	m_ref = -1;
}

LuaTable::~LuaTable()
{
	if ( m_ref >= 0 )
		lua_unref( m_luastate->impl(), m_ref ); //64
}

LuaTable& LuaTable::operator=( const LuaTable& other ) //67-89
{
	int oldref = m_ref; //69
	lua_State* oldlua = m_luastate ? m_luastate->impl() : 0; //70

	if ( other.m_luastate != 0 && other.m_luastate->impl() && other.m_ref >= 0 ) //72
	{
		lua_State* impl = other.m_luastate->impl(); //74
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
		lua_unref( oldlua, oldref ); //86

	return *this;
}

LuaTable& LuaTable::operator=( LuaTable&& other ) //91
{
	swap(other); //94
	return *this;
}

void LuaTable::remove( int index ) //98-107
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //102
	LuaStackRestore lsr( impl ); //103
	lua_getref( impl, m_ref );
	lua_pushnil( impl );
	lua_rawseti( impl, -2, index );
}

void LuaTable::remove( const std::string& name ) //109-119
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //113
	LuaStackRestore lsr( impl );
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushnil( impl );
	lua_rawset( impl, -3 );
}

void LuaTable::remove(const char* name) //121-131
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //125
	LuaStackRestore lsr(impl); //126
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushnil(impl);
	lua_rawset(impl, -3);
}

void LuaTable::setString( int index, const std::string& v ) //133-142
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //137
	LuaStackRestore lsr( impl ); //138
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, v );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setString(int index, const char* v) //144-153
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //148
	LuaStackRestore lsr(impl); //149
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, v);
	lua_rawseti(impl, -2, index);
}

void LuaTable::setNumber( int index, float v ) //155-164
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //159
	LuaStackRestore lsr( impl ); //160
	lua_getref( impl, m_ref );
	lua_pushnumber( impl, v );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setTable( int index, const LuaTable& v ) //166-175
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //170
	LuaStackRestore lsr( impl ); //171
	lua_getref( impl, m_ref ); //172
	LuaState::pushTable( impl, &v ); //173
	lua_rawseti( impl, -2, index ); //174
}

void LuaTable::setTable(int index, const LuaTable* v) //Unknown line but 177-186 seems accurate
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushTable(impl, v);
	lua_rawseti(impl, -2, index);
}

void LuaTable::setBoolean( int index, bool v ) //188-197
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //192
	LuaStackRestore lsr( impl ); //193
	lua_getref( impl, m_ref );
	lua_pushboolean( impl, v?1:0 );
	lua_rawseti( impl, -2, index );
}

void LuaTable::setString( const std::string& name, const std::string& v ) //199-209
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //203
	LuaStackRestore lsr( impl ); //204
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushString( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setString( const char* name, const std::string& v ) //211-221
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //215
	LuaStackRestore lsr( impl ); //216
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushString( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setString(const std::string& name, const char* v) //223-233
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //227
	LuaStackRestore lsr(impl); //228
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushString(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setString(const char* name, const char* v) //235-245
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //239
	LuaStackRestore lsr(impl); //240
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushString(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setNumber( const std::string& name, float v ) //247-257
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //251
	LuaStackRestore lsr( impl ); //252
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushnumber( impl, v );
	lua_rawset( impl, -3 );
}

void LuaTable::setNumber(const char* name, float v) //259-269
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //263
	LuaStackRestore lsr(impl); //264
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushnumber(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setTable( const std::string& name, const LuaTable& v ) //271-282
{
	assert( m_ref >= 0 );
	assert( v.m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //276
	LuaStackRestore lsr( impl ); //277
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	LuaState::pushTable( impl, &v );
	lua_rawset( impl, -3 );
}

void LuaTable::setTable(const char* name, const LuaTable& v) //284-295
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //289
	LuaStackRestore lsr(impl); //290
	lua_getref(impl, m_ref); //291
	LuaState::pushString(impl, name); //292
	LuaState::pushTable(impl, &v); //293
	lua_rawset(impl, -3); //294
}

void LuaTable::setTable(const std::string& name, const LuaTable* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushTable(impl, v);
	lua_rawset(impl, -3);
}

void LuaTable::setTable( const char* name, const LuaTable* v ) //309-319
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //313
	LuaStackRestore lsr( impl ); //314
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
	LuaState::pushFunction(impl, &v);
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

void LuaTable::setFunction(const std::string& name, const LuaFunction& v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushFunction(impl, &v);
	lua_rawset(impl, -2);
}

void LuaTable::setFunction(const std::string& name, const LuaFunction* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushFunction(impl, v);
	lua_rawset(impl, -2);
}

void LuaTable::setFunction(const char* name, const LuaFunction& v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushFunction(impl, &v);
	lua_rawset(impl, -2);
}

void LuaTable::setFunction(const char* name, const LuaFunction* v)
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	LuaState::pushFunction(impl, v);
	lua_rawset(impl, -2);
}

void LuaTable::setBoolean( const std::string& name, bool v ) //344-354
{
	assert( m_ref >= 0 );

	lua_State* impl = m_luastate->impl(); //348
	LuaStackRestore lsr( impl ); //349
	lua_getref( impl, m_ref );
	LuaState::pushString( impl, name );
	lua_pushboolean( impl, v?1:0 );
	lua_rawset( impl, -3 );
}

void LuaTable::setBoolean(const char* name, bool v) //356-366
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //360
	LuaStackRestore lsr(impl); //361
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_pushboolean(impl, v ? 1 : 0);
	lua_rawset(impl, -3);
}

std::string LuaTable::getString(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	LuaStackRestore lsr(impl);
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	return lua_tostring(impl, -1);
}

std::string LuaTable::getString(const char* name) const //382-394
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //386
	LuaStackRestore lsr(impl); //387
	lua_getref(impl, m_ref); //388
	LuaState::pushString(impl, name); //389
	lua_rawget(impl, -2); //390
	const char* string = lua_tostring(impl, -1); //391

	return string;
}

float LuaTable::getNumber(const std::string& name) const //396-407
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //400
	LuaStackRestore lsr(impl); //401
	lua_getref(impl, m_ref); //402
	LuaState::pushString(impl, name); //403
	lua_rawget(impl, -2); //404

	return lua_tonumber(impl, -1); //406
}

float LuaTable::getNumber(const char* name) const //409-420
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //413
	LuaStackRestore lsr(impl); //414
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name); //416
	lua_rawget(impl, -2);

	return lua_tonumber(impl, -1); //419
}

LuaTable LuaTable::getTable(const char* name) const //422-443
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //426
	LuaStackRestore lsr(impl); //427
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_TABLE; //432
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1); //433
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype)))); //436
	}

	LuaTable tab; //439
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

LuaTable LuaTable::getTable(const std::string& name) const //445-466
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //449
	LuaStackRestore lsr(impl); //450
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_TABLE; //455
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1); //456
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype)))); //459
	}

	LuaTable tab; //462
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

LuaFunction LuaTable::getFunction(const char* name) const //490-511
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //494
	LuaStackRestore lsr(impl); //495
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	LuaState::Type expectedtype = LuaState::TYPE_FUNCTION; //500
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1); //501
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			name, LuaState::toString(type), LuaState::toString(expectedtype)))); //504
	}

	LuaFunction fun; //507
	fun.m_luastate = m_luastate;
	fun.m_ref = lua_ref(impl, true);
	return fun;
}

LuaFunction LuaTable::getFunction(const std::string& name) const
{
	assert(m_ref >= 0);

	return getFunction(name.c_str());
}

LuaFunction LuaTable::getFunction(int index) const
{
	assert(m_ref >= 0);

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

std::string LuaTable::getString(int index) const //518-529
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //522
	LuaStackRestore lsr(impl); //523
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	return lua_tostring(impl, -1); //528
}

float LuaTable::getNumber(int index) const //531
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //535
	LuaStackRestore lsr(impl); //536
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	return lua_tonumber(impl, -1);
}

LuaTable LuaTable::getTable(int index) const //543-563
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //547
	LuaStackRestore lsr(impl); //548
	lua_getref(impl, m_ref); //549
	lua_rawgeti(impl, -1, index); //550

	LuaState::Type expectedtype = LuaState::TYPE_TABLE; //552
	LuaState::Type type = (LuaState::Type)lua_type(impl, -1); //553
	if (type != expectedtype)
	{
		throwError(LuaException(Format("Tried to get value {0} from table, but type was {1} instead of {2}",
			index, LuaState::toString(type), LuaState::toString(expectedtype)))); //556
	}

	LuaTable tab; //559
	tab.m_luastate = m_luastate;
	tab.m_ref = lua_ref(impl, true);
	return tab;
}

bool LuaTable::getBoolean(const std::string& name) const //565-576
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //569
	LuaStackRestore lsr(impl); //570
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::getBoolean(const char* name) const //578-589
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //582
	LuaStackRestore lsr(impl); //583
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::getBoolean(int index) const //591-601
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //595
	LuaStackRestore lsr(impl); //596
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);

	return 0 != lua_toboolean(impl, -1);
}

bool LuaTable::isNil(const char* name) const //603-614
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //608
	LuaStackRestore lsr(impl); //607
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnil(impl, -1); //612
	return res;
}

bool LuaTable::isNil(const std::string& name) const //616-627
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //620
	LuaStackRestore lsr(impl); //621
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnil(impl, -1); //625
	return res;
}

bool LuaTable::isNil(int index) const //629-639
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //633
	LuaStackRestore lsr(impl); //634
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isnil(impl, -1); //637
	return res;
}

bool LuaTable::isString(const char* name) const //641-652
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //645
	LuaStackRestore lsr(impl); //646
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isstring(impl, -1); //650
	return res;
}

bool LuaTable::isString(int index) const //667-677
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //671
	LuaStackRestore lsr(impl); //672
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isstring(impl, -1); //675
	return res;
}

bool LuaTable::isNumber(const char* name) const //679-690
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //683
	LuaStackRestore lsr(impl); //684
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnumber(impl, -1); //688
	return res;
}

bool LuaTable::isNumber(const std::string& name) const //692-703
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //696
	LuaStackRestore lsr(impl); //697
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isnumber(impl, -1); //701
	return res;
}

bool LuaTable::isNumber(int index) const //705-715
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //709
	LuaStackRestore lsr(impl); //710
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isnumber(impl, -1); //713
	return res;
}

bool LuaTable::isTable(const char* name) const //742-753
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //746
	LuaStackRestore lsr(impl); //747
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_istable(impl, -1); //751
	return res;
}

bool LuaTable::isTable(const std::string& name) const //755-766
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //759
	LuaStackRestore lsr(impl); //760
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_istable(impl, -1); //764
	return res;
}

bool LuaTable::isTable(int index) const //768-778
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //772
	LuaStackRestore lsr(impl); //773
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_istable(impl, -1); //776
	return res;
}

bool LuaTable::isBoolean(const char* name) const //780-791
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //784
	LuaStackRestore lsr(impl); //785
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	bool res = 0 != lua_isboolean(impl, -1); //789
	return res;
}

bool LuaTable::isBoolean(const std::string& name) const //793-804
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //797
	LuaStackRestore lsr(impl); //798
	lua_getref(impl, m_ref); //799
	LuaState::pushString(impl, name); //800
	lua_rawget(impl, -2); //801
	bool res = 0 != lua_isboolean(impl, -1); //802
	return res;
}

bool LuaTable::isBoolean(int index) const //806-816
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //810
	LuaStackRestore lsr(impl); //811
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	bool res = 0 != lua_isboolean(impl, -1); //814
	return res;
}

void LuaTable::pushMember(int index) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	lua_getref(impl, m_ref);
	lua_rawgeti(impl, -1, index);
	lua_remove(impl, -2);
}

void LuaTable::pushMember(const std::string& name) const
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl();
	lua_getref(impl, m_ref);
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	lua_remove(impl, -2);
}

void LuaTable::pushMember(const char* name) const //839-848
{
	assert(m_ref >= 0);

	lua_State* impl = m_luastate->impl(); //843
	lua_getref(impl, m_ref); //844
	LuaState::pushString(impl, name);
	lua_rawget(impl, -2);
	lua_remove(impl, -2);
}

void LuaTable::writeChar(OutputStream& out, int ch) //850-855
{
	assert(ch >= 0 && ch < 256);
	char b = (char)ch; //853
	out.write(&b, sizeof(b));
}

void LuaTable::writeMargin(OutputStream& out, int margin) //857-861
{
	for (int i = 0; i < margin; ++i) //859
		writeChar(out, ' '); //860
}

void LuaTable::writeString(OutputStream& out, const char* str) //863-868
{
	const int len = strlen(str); //865
	for (int i = 0; i < len; ++i) //866
		writeChar(out, str[i]); //867
}

bool isDigit(char chr) //870-873 | Correct?
{
	return chr >= '0' && chr <= '9'; //return static_cast<unsigned char>(chr - '0') < 10; //?
}

void LuaTable::writeStringLiteral(OutputStream& out, const char* str) //875-955 | TODO
{
	/*const int length = strlen(str); //892
	for (int i = 0; i < length; ++i) //893
	{
		unsigned char chr; //896

		//writeString(out, chr); //900
		//writeString(out, chr); //903
		//writeString(out, chr); //906
		//writeString(out, chr); //909
		//writeString(out, chr); //912
		//writeString(out, chr); //915
		//writeString(out, chr); //918
		//writeString(out, chr); //921
		//writeString(out, chr); //924
		//writeString(out, chr); //927

		char buffer; //935
		const char* format = isDigit(chr); //936
		const int bytes; //937
		//writeString(out, chr); //941

		//throwError(LuaException(Format("Failed to generate numerical escape for string literal."))); //945

		//writeChar(out, chr); //950
	}*/
	assert("void LuaTable::writeStringLiteral(io::OutputStream& out, const char* str), is not yet decompiled.");
}

void LuaTable::writeValue(OutputStream& out, int index, int margin) //957-996
{
	/*LuaState::Type valuetype = m_luastate->type(index); //959
	switch (valuetype)
	{
	case LuaState::TYPE_BOOLEAN:
		if (m_luastate->toBoolean(index))
			writeString(out, "true"); //964
		else
			writeString(out, "false"); //966
		break;
	case LuaState::TYPE_NUMBER: {
		char buf[32]; //969
		float number = m_luastate->toNumber(index); //970
		sprintf(buf, "%g", number);
		//Math::isInf(number); //975
		writeString(out, buf); //983
		break;
	}
	case LuaState::TYPE_STRING:
		writeChar(out, '\"'); //986

		writeChar(out, '\"'); //988
		//writeString(out, "\"");
		//writeString(out, m_luastate->toString(index));
		//writeString(out, "\"");
		break;
	case LuaState::TYPE_TABLE: {
		writeString(out, "{"); //991
		LuaTable tab = m_luastate->toTable(index); //992
		tab.write(out, margin + 4);
		writeString(out, "\n");
		writeMargin(out, margin); //994
		writeString(out, "}"); //995
		break;
	}
	default:
		writeString(out, "nil");
		break;
	}*/

	assert("void LuaTable::writeValue(io::OutputStream& out, int index, int margin), is not yet decompiled.");
}

class LuaKeywordChecker //1003
{
public:
	LuaKeywordChecker() //1006
	{
		static const char* const keywords[] = { "and", "break", "do", "else", "elseif", "end", "false", "for", "function", "if", "in", "local", "nil", "not", "or", "repeat", "return", "then", "true", "nil" }; //1008

		for (int i = 0 < sizeof(keywords) / sizeof keywords[0]; i++; ) //1011
		{
			m_keywords[keywords[i]] = true;
		}
	}

	bool isValidKeyName(const char* key) //1017 | Correct?
	{
		static LuaKeywordChecker checker; //1019

		if (strlen(key) < 0 || !((key[0] >= 'A' && key[0] <= 'Z') ||
			(key[0] >= 'a' && key[0] <= 'z') ||
			key[0] == '_'))
				return false;

		for (int i = 1 < strlen(key); i++; ) //1026
		{
			if (!(key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z') || (key[i] >= '0' && key[i] <= '9') || key[i] == '_')
				return false;
		}

		return checker.m_keywords.count(key) == 0; //1033
	}

private:
	std::map<std::string, bool> m_keywords; //1037
};

void LuaTable::write(OutputStream& out, int margin, bool nested) //1040 | TODO
{
	/*assert(m_luastate);

	LuaStackRestore lsr(m_luastate); //1044
	m_luastate->pushTable(this); //1045
	int tab = m_luastate->top(); //1046
	bool first = true; //1047
	bool inSequence; //1048
	int keyindex = 1; //1049

	//writeString //1097
	//writeString //11145

	for (m_luastate->pushNil(); m_luastate->next(tab); m_luastate->pop())
	{
		LuaState::Type keytype = m_luastate->type(-2); //1053
		LuaState::Type valuetype = m_luastate->type(-1); //1054

		bool isValueKey = false; //1074

		if (keytype == LuaState::TYPE_STRING)
		{
			if (!strcmp(m_luastate->toString(-2), "_G") && !isValidKeyName()
			{
				continue;
			}

			writeMargin(out, margin); //1117
			writeString(out, m_luastate->toString(-2));
			writeString(out, " = "); //1121
			writeValue(out, -1, margin);
			writeString(out, "\n"); //1123

			strkeys = true;
		}
		else if (!strkeys)
		{
			if (first)
				writeMargin(out, margin);
			else
				writeString(out, ","); //1131

			writeValue(out, -1, margin);

			++keyindex;
		}

		first = false;
	}*/
	assert("void LuaTable::write(OutputStream& out, int margin, bool nested), is not yet decompiled.");
}

void LuaTable::read(InputStream& in) //1149-1153
{
	assert(m_luastate);
	m_luastate->compile(in, in.toString(), this);
}

void LuaTable::read(const std::vector<unsigned char>& in)
{
	assert(m_luastate);
	if (in.data())
	{
		const char* buf;
		m_luastate->compile(buf, in.size(), "", this);
	}
}

void LuaTable::read(const std::string& in)
{
	assert(m_luastate);
	if (in.data())
	{
		const char* buf;
		m_luastate->compile(buf, in.size(), in.substr(), this);
	}
}

void LuaTable::traverse(LuaTableVisitor& visitor) //1169
{
	visitor.closeTable();
	traverseRecursively(visitor);
	visitor.start();
}

void LuaTable::traverseRecursively(LuaTableVisitor& visitor) //1176-1290 | TODO
{
	/*assert(m_luastate); //guess

	LuaStackRestore lsr(m_luastate); //1180

	m_luastate->pushTable(this); //1182
	int tableRef = m_luastate->top(); //1183
	for (m_luastate->pushNil(); m_luastate->next(tableRef); m_luastate->pop())
	{
		const int nameIndex = -2; //1187
		const int valueIndex = -1; //1188

		LuaState::Type nameType = m_luastate->type(-2); //1190
		LuaState::Type valueType = m_luastate->type(-1); //1191

		const char* name = m_luastate->toString(-2); //1193
		if (nameType == LuaState::TYPE_STRING)
		{
			if (!strcmp(name, "_G"))
			{
				continue;
			}
			else
			{
				m_luastate->toTable();
				const bool value; //1216
				const double value; //1231
				const char* value; //1246
				LuaTable innerTable = m_luastate->toTable(; //1274
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
	assert("void LuaTable::traverseRecursively(LuaTableVisitor& visitor), is not yet decompiled.");
}

int LuaTable::size() const
{
	assert(m_luastate);

	LuaStackRestore lsr(m_luastate); //1296
	m_luastate->pushTable(this);
	int tab = m_luastate->top(); //1298

	int count = 0; //1300
	for (m_luastate->pushNil(); m_luastate->next(tab); m_luastate->pop())
		++count;
	return count;
}

void LuaTable::getRef() const
{
	lua_State* impl = m_luastate->impl(); //Assuming
	lua_getref(impl, m_ref);
}

void LuaTable::swap(LuaTable& other) //1313
{
	std::swap(m_luastate, other.m_luastate);
	std::swap(m_ref, other.m_ref);
}

} // lua

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
