#ifndef _LUA_LUASTATE_H
#define _LUA_LUASTATE_H


#include <lua/LuaTable.h>
#include <lua/LuaFunction.h>
#include <lang/Object.h>
#include <io/InputStream.h>


struct lua_State;

namespace io
{ 
	class InputStream; class OutputStream;
}

namespace lang
{
	class Throwable;
}


namespace lua
{
 


class LuaTable;
class LuaFunctor;


/**
 * State of Lua script running environment.
 * 
 * @ingroup lua
 */
class LuaState :
	public lang::Object //31
{
public:
	typedef int (*CFunction)( lua_State* ); //35
	
	/** Type of Lua value. */
	enum Type //38
	{
		/** Nil. */
		TYPE_NIL,
		/** Boolean. */
		TYPE_BOOLEAN,
		/** Light user data. */
		TYPE_LIGHTUSERDATA,
		/** Number. */
		TYPE_NUMBER,
		/** String (UTF-8). */
		TYPE_STRING,
		/** Table. */
		TYPE_TABLE,
		/** Function. */
		TYPE_FUNCTION,
		/** User data. */
		TYPE_USERDATA,
		/** Thread. */
		TYPE_THREAD,
	};

	/** Pseudo table indices which can be used to refer environments. */
	enum Environment
	{
		/** Index of globals table. */
		ENV_GLOBALS = -10002, //Now -10002
	};

	enum Status //60
	{
		OK,
		YIELD,
		ERRRUN,
		ERRSYNTAX,
		ERRMEM,
		ERRERR
	};

	/** 
	 * Creates Lua state by calling lua_open. 
	 * @exception LuaException
	 */
	LuaState(); //81

	/** Destroys Lua state by calling lua_close. */
	~LuaState(); //84

	/**
	 * Returns table of Lua state globals.
	 */
	LuaTable& globals(); //89

	/** 
	 * Sets top of stack. Accepts any acceptable index,
	 * or 0, and sets the stack top to that index. If the 
	 * new top is larger than the old one, then the new 
	 * elements are filled with nil. If index is 0, then
	 * all stack elements are removed. 
	 */
	void setTop( int index ); //98 | (Note inlined on iOS)

	/**
	 * Pops n values from the stack.
	 * Usually do not use this method (unless while iterating a table),
	 * but LuaStackRestore instead.
	 */
	void pop( int n=1 ); //105

	/**
	 * Pushes onto the stack a copy of the element at the given index.
	 */
	void push( int index ); //110

	/**
	 * Removes the element at the given position, shifting down the 
	 * elements above that position to fill the gap
	 */
	void remove( int index ); //116

	/**
	 * Moves the top element into the given position, shifting up 
	 * the elements above that position to open space.
	 */
	void insert( int index ); //122

	/**
	 * Moves the top element into the given position, without 
	 * shifting any element therefore replacing the value 
	 * at the given position.
	 */
	void replace( int index ); //129

	/** Returns type of value at specified stack index. */
	Type type( int index ); //132

	/** Returns true if value at specified stack index is nil. */
	bool isNil( int index ); //135

	/** Returns true if value at specified stack index is boolean. */
	bool isBoolean( int index ); //138

	/** Returns true if value at specified stack index is number. */
	bool isNumber( int index ); //141

	/** Returns true if value at specified stack index is string. */
	bool isString( int index ); //144

	/** Returns true if value at specified stack index is table. */
	bool isTable( int index ); //147

	/** Returns true if value at specified stack index is function. */
	bool isFunction( int index ); //150

	/** Returns true if value at specified stack index is C-function. */
	bool isCFunction( int index ); //153

	/** Returns true if value at specified stack index is user data. */
	bool isUserData( int index ); //156

	/** Returns true if value at specified stack index is light user data. */
	bool isLightUserData( int index ); //159

	/** Compares values at two stack positions. */
	bool equal( int index1, int index2 ); //162

	/** Compares values at two stack positions. */
	bool lessThan( int index1, int index2 ); //165

	/** Compares values at two stack positions without using metamethods. */
	bool rawEqual( int index1, int index2 ); //168

	/**
	 * Returns boolean at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	bool toBoolean( int index ); //174

	/**
	 * Returns number at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	float toNumber( int index ); //180

	/**
	 * Returns zero-terminated string at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	const char* toString( int index ); //186

	/**
	 * Returns C-function at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	CFunction toCFunction( int index ); //192

	/**
	 * Returns light user data at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void* toLightUserData( int index ); //198

	/**
	 * Returns user data at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void* toUserData( int index ); //204

	/**
	 * Returns handle to table at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	LuaTable toTable( int index ); //210
	
	/**
	 * 
	 * @exception LuaException If types do not match.
	 */
	LuaFunction toFunction( int index ); //216

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	template <class T> void toValue(int index, T v); //223 | TODO

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void toValue( int index, bool& v )					{v=toBoolean(index);} //229

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void toValue(int index, std::string& v) { v = toString(index); } //235

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void toValue(int index, const char*& v) { v = toString(index); } //241

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void toValue(int index, LuaTable& v) { v = toTable(index); } //247

	/**
	 * Returns value at specified stack position.
	 * @exception LuaException If types do not match.
	 */
	void toValue(int index, LuaFunction& v); //253

	/** Pushes boolean onto the Lua stack. */
	void pushBoolean( bool v ); //256
	
	/** Pushes number onto the Lua stack. */
	void pushNumber( float v ); //259
	
	/** Pushes zero-terminated string onto the Lua stack. */
	void pushString( const char* v ); //262

	/** Pushes string onto the Lua stack. */
	void pushString( const std::string& v ); //265
	
	/** Pushes nil onto the Lua stack. */
	void pushNil(); //268
	
	/** Pushes C-function onto the Lua stack. */
	void pushCFunction( CFunction v ); //271

	/** Pushes light user data onto the Lua stack. */
	void pushLightUserData( void* v ); //274

	/** Pushes value onto the Lua stack. */
	void pushValue( bool v )					{pushBoolean(v);} //277

	template <class T> void pushValue(T v) { pushValue(v); } //282
	
	/** Pushes value onto the Lua stack. */
	void pushValue( const std::string& v )		{pushString(v);} //285
	
	/**  */
	void pushValue( const char* v ); //288

	/** Pushes value onto the Lua stack. */
	void pushValue( const LuaTable* v )			{pushTable(v);} //291

	/** Pushes value onto the Lua stack. */
	void pushValue( const LuaTable& v )			{pushTable(v);} //294
	
	/**  */
	void pushValue( const LuaFunction& v )		{pushFunction(v);} //297

	/** Pushes C function closure onto the Lua stack. */
	void pushCClosure( CFunction v, int n ); //300

	/** 
	 * Pushes method closure onto the Lua stack. 
	 * Method has fixed function calling convention, returns int
	 * and accepts one argument, LuaState*. Arguments passed from
	 * the script to the function are passed on top of Lua stack,
	 * and return value(s) are returned on top of Lua stack.
	 * Function should return number of return values in Lua stack.
	 */
	template <class T> void pushMethodClosure( T* obj, int (T::*func)(LuaState*) );

	/** Returns index of n-th up-value, starting from 1. */
	int upValueIndex( int n ); //313

	/** Pushes table onto the Lua stack. */
	void pushTable( const LuaTable* v )			{pushTable(m_impl,v);} //316

	/** Pushes table onto the Lua stack. */
	void pushTable( const LuaTable& v )			{pushTable(m_impl,&v);} //319
	
	/**  */
	void pushFunction( const LuaFunction* v )	{pushFunction(m_impl,v);} //322
	
	/**  */
	void pushFunction( const LuaFunction& v )		{pushFunction(m_impl,&v);} //325

	/** 
	 * 
	 * @exception LuaException
	 */
	LuaState* newThread(); //331
	 
	/** 
	 * Creates a new, empty table and pushes it onto the stack. 
	 * @exception LuaException
	 */
	void newTable(); //337

	/**
	 * Pops a key from the stack and returns (on the stack) 
	 * the contents of the table at that key.
	 * The table is left where it was in the stack.
	 * @exception LuaException
	 */
	void getTable( int index ); //345

	/**
	 * Pops a key from the stack and returns (on the stack) 
	 * the contents of the table at that key.
	 * The table is left where it was in the stack.
	 * Ignores metamethods.
	 * @exception LuaException
	 */
	void rawGet( int index ); //354

	/** 
	 * Pops from the stack both the key and the value.
	 * Key must be pushed first, and then value.
	 * The table is left where it was in the stack.
	 * @exception LuaException
	 */
	void setTable( int index ); //362

	/** 
	 * Pops from the stack both the key and the value.
	 * Key must be pushed first, and then value.
	 * The table is left where it was in the stack.
	 * Ignores metamethods.
	 * @exception LuaException
	 */
	void rawSet( int index ); //371

	/**
	 * The function pops a key from the stack, and pushes a key-value pair 
	 * from the table (the "next" pair after the given key). If there are 
	 * no more elements, then next returns false and pushes nothing. 
	 * Use a nil key to signal the start of a traversal.
	 * @exception LuaException
	 */
	bool next( int index ); //380

	/**
	 * Pushes the value of the n-th element of the table at stack position index.
	 * @exception LuaException
	 */
	void rawGetI( int index, int n ); //386

	/**
	 * Sets the value of the n-th element of the table at stack position index 
	 * to the value at the top of the stack, removing this value from the stack.
	 * @exception LuaException
	 */
	void rawSetI( int index, int n ); //393

	/**
	 * Pops a table from the stack and sets it as the new environment 
	 * for the function at index index in the stack.
	 * @exception LuaException
	 */
	void setFEnv( int index ); //400

	/**
	 * Pushes on the stack the environment table of the function 
	 * at index index in the stack.
	 * @exception LuaException
	 */
	void getFEnv( int index ); //407

	/**
	 * Calls Lua function. Functions defined in Lua and C functions registered in 
	 * Lua can be called from the host program. This is done using the following 
	 * protocol: First, the function to be called is pushed onto the stack; 
	 * then, the arguments to the function are pushed in direct order, that is, 
	 * the first argument is pushed first.
	 * @param nargs Number of arguments that you pushed onto the stack.
	 * @param nresults Number of results returned are adjusted to this number.
	 * @exception LuaException
	 */
	void call( int nargs, int nresults ); //419
	
	/**
	 * 
	 * 
	 *
	 * @param nargs
	 * @exception LuaException
	 */
	int resume( int nargs); //429 | Not on iOS.
	
	/**
	 * 
	 * 	 
	 * @param nresults
	 * @exception LuaException
	 */
	int yield( int nresults ); //437 | Not on iOS.

	/**
	 * Compiles Lua chunk from memory buffer.
	 * @param buffer Lua chunk (ASCII/binary).
	 * @param size Size of Lua chunk in bytes.
	 * @param name Name of Lua chunk.
	 * @param env Function environment if any.
	 * @exception LuaException
	 */
	void compile( const char* buffer, int size, const std::string& name, LuaTable* env ); //447
	
	/**
	 * 
	 * @param 
	 * @param 
	 * @param 
	 * @exception LuaException
	 */
	void getByteCode( const char* buffer, int size, io::OutputStream& ); //456 | Not on iOS.

	/**
	 * Compiles Lua chunk from file.
	 * @param in Lua chunk (ASCII/binary) input stream.
	 * @param size Size of Lua chunk in bytes.
	 * @param name Name of Lua chunk.
	 * @param env Function environment if any.
	 * @exception LuaException
	 */
	void compile( io::InputStream& in, const std::string& name, LuaTable* env ); //465

	/** 
	 * Checks type at specified stack index.
	 * @exception LuaException If types don't match.
	 */
	void checkType( int index, Type type ); //471

	/** 
	 * Called after dynamic cast fails to specified type when dispatching calls.
	 * Used by implementation.
	 * @param index Lua stack index where the incorrect type was found.
	 * @exception LuaException Always.
	 */
	void incorrectType( int index ); //479

	/** Returns low level Lua state object. */
	lua_State* impl()		{return m_impl;} //482

	/**
	 * Returns top of the stack.
	 */
	int top() const; //487
	
	
	Status status() const; //492

	/** Returns type name. */
	static const char* toString( Type type ); //395

	/* Concatenates stack trace to limited buffer. Used by implementation. [NOTE] changed from appendStackTrace*/
	static std::string getStackTrace( lua_State* impl ); //498

	/* Pushes string to Lua state stack. Used by implementation. */
	static void pushString( lua_State* impl, const std::string& v ); //501
	
	/* Pushes string to Lua state stack. Used by implementation. */
	static void pushString( lua_State* impl, const char* v ); //504

	/* Pushes table to Lua state stack. Used by implementation. */
	static void pushTable( lua_State* impl, const LuaTable* v ); //507
	
	/*  */
	static void pushFunction( lua_State* impl, const LuaFunction* v ); //510

	/* 
	 * Returns C++ this pointer from table in stack at specified position.
	 * C++ this pointer is set to index [0] of the table.
	 * If [0] is not this pointer, then the table has no C++ counterpart.
	 * Used by implementation.
	 * @exception LuaException
	 */
	static LuaTable* getThisPtr( lua_State* impl, int index ); //519

	/*
	 * Used by the implementation of Lua call dispatch system.
	 */
	static void getDispatchData( lua_State* impl, LuaState** luastate, LuaFunctor* lf ); //524

private:
	struct LoadBuffer //527
	{
		const char* buffer; //529
		int size; //530
	};

	struct LoadFile //533
	{
		LoadFile(io::InputStream& source) : //535
			in(source), size(source.available())
		{
		}

		io::InputStream& in; //540
		int size; //541
		char buf[2048]; //542

	private:
		LoadFile& operator=(const LoadFile&); //545
	};

	lua_State*			m_impl; //548
	LuaTable			m_globals; //549
	int					m_ref; //550

	LuaState(lua_State* impl); //552
	void				handleLoadResult( int err, const std::string& name, LuaTable* env ); //553
	static const char*	loadBuffer( lua_State* impl, void* data, size_t* size ); //554
	static const char*	loadFile( lua_State* impl, void* data, size_t* size ); //555
	static int			handleError( lua_State* impl ); //556
	static int			handleRuntimeError( lua_State* impl ); //557

	LuaState( const LuaState& ); //559
	LuaState& operator=( const LuaState& ); //560
};


#include <lua/LuaState.inl>


} // lua


#endif // _LUA_LUASTATE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
