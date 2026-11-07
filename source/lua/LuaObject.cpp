#include <lua/LuaObject.h>
#include <lua/LuaState.h>
#include <lua/LuaStackRestore.h>
#include <external/lua/src/lua.h>


USING_NAMESPACE(lang)


BEGIN_NAMESPACE(lua) 


LuaObject::LuaObject( LuaState* luastate ) : //11
	LuaTable( luastate )
{
	LuaStackRestore lsr( luastate ); //14
	luastate->pushTable( this ); //15

	luastate->pushLightUserData( this );
	luastate->rawSetI( -2, 0 );

	luastate->pushString( "_G" );
	luastate->push( LuaState::ENV_GLOBALS );
	luastate->setTable( -3 );

	luastate->pushString( "this" );
	luastate->pushTable( this ); //25
	luastate->setTable( -3 );
}

LuaObject::~LuaObject()
{
}

void LuaObject::registerClosure( const char* name, //44
	const LuaFunctor* lf, LuaState::CFunction dispatcher ) //45 | Assert was likely removed.
{
	LuaState* luastate = luaState(); //47
	LuaStackRestore lsr( luastate ); //48

	luastate->pushTable( this ); //50
	luastate->pushString( name );

	// store data as light user data values
	void* const* data = reinterpret_cast<void* const*>(lf); //54
	const int datasize = int(sizeof(LuaFunctor)/sizeof(void*)); //55
	for ( int i = 0 ; i < datasize ; ++i ) //56
		luastate->pushLightUserData( data[i] );

	luastate->pushCClosure( dispatcher, datasize );
	luastate->setTable( -3 );
}

void LuaObject::call( const char* name ) //63
{
	LuaState* luastate = luaState(); //65
	LuaStackRestore lsr( luastate ); //66
	pushMember( name );
	luastate->call( 0, 0 );
}

int LuaObject::resume( const char* name )
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr(luastate);
	pushMember(name);
	return luastate->resume(0);
}


END_NAMESPACE() // lua

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
