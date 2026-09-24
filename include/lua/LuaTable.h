#ifndef _LUA_LUATABLE_H
#define _LUA_LUATABLE_H


#include <lang/Object.h>
#include <lua/LuaTableVisitor.h>


struct lua_State;

namespace io
{ 
	class InputStream;
	class OutputStream;}


namespace lua
{
 


class LuaState;
class LuaFunction;


/** 
 * Handle to Lua table.
 * 
 * @ingroup lua
 */
class LuaTable :
	public lang::Object
{
public:
	/** Skips table initialization. */
	LuaTable();

	/** Creates a table to LuaState. */
	explicit LuaTable( LuaState* state );

	/** Copy by reference. */
	LuaTable( const LuaTable& other );
	
	/**  */
	LuaTable( LuaTable&& other );
	
	/** Releases a reference. */
	~LuaTable();

	/** Copy by reference. */
	LuaTable& operator=( const LuaTable& other );
	
	/**  */
	LuaTable& operator=( LuaTable&& other );

	/**
	 * Writes Lua table to output stream. Note that
	 * functions are not written to the output.
	 * @exception IOException
	 * @exception LuaException
	 */
	void write( io::OutputStream& out, int margin=0 );

	/**
	 * Reads Lua table from input stream.
	 * @exception IOException
	 * @exception LuaException
	 */
	void read(io::InputStream& in );
	
	/**
	 * 
	 * @exception IOException
	 * @exception LuaException
	 */
	void read( const std::vector<unsigned char>& in ); //Not on iOS.
	
	/**
	 * 
	 * @exception IOException
	 * @exception LuaException
	 */
	void read( const std::string& in ); //Not on iOS.
	
	/**  */
	void traverse( LuaTableVisitor& visitor );

	/** Removes the member from the table. */
	void remove( int index );

	/** Removes the member from the table. */
	void remove( const std::string& name );
	
	/** Removes the member from the table. */
	void remove( const char* name );

	/** Sets boolean member value. */
	void setBoolean( int index, bool v );

	/** Sets boolean member value. */
	void setBoolean( const std::string& name, bool v );
	
	/** Sets boolean member value. */
	void setBoolean( const char* name, bool v );

	/** Sets number member value. */
	void setNumber( int index, float v );

	/** Sets number member value. */
	void setNumber( const std::string& name, float v );
	
	/** Sets string member value. */
	void setNumber( const char* name, float v );

	/** Sets string member value. */
	void setString( int index, const std::string& v );
	
	/** Sets string member value. */
	void setString( int index, const char* v );
	
	/** Sets string member value. */
	void setString( const std::string& name, const std::string& v );
	
	/** Sets string member value. */
	void setString( const char* name, const std::string& v );
	
	/** Sets string member value. */
	void setString( const std::string& name, const char* v );
	
	/** Sets string member value. */
	void setString( const char* name, const char* v );

	/** Sets table member value. */
	void setTable( int index, const LuaTable& v );

	/** Sets table member value. */
	void setTable( int index, const LuaTable* v );

	/** Sets table member value. */
	void setTable( const std::string& name, const LuaTable& v );

	/** Sets table member value. */
	void setTable( const std::string& name, const LuaTable* v );
	
	/** Sets table member value. */
	void setTable( const char* name, const LuaTable& v );

	/** Sets table member value. */
	void setTable( const char* name, const LuaTable* v );
	
	/**  */
	void setFunction( int index, const LuaFunction& v );
	
	/**  */
	void setFunction( int index, const LuaFunction* v );
	
	/**  */
	void setFunction( const std::string& name, const LuaFunction& v );
	
	/**  */
	void setFunction( const std::string& name, const LuaFunction* v );
	
	/**  */
	void setFunction( const char* name, const LuaFunction& v );
	
	/**  */
	void setFunction( const char* name, const LuaFunction* v );

	/** Sets member value. */
	void setMember( int index, bool v )									{setBoolean(index,v);}

	/** Sets member value. */
	void setMember( const std::string& name, bool v )					{setBoolean(name,v);}
	
	/** Sets member value. */
	void setMember( const char* name, bool v )					{setBoolean(name,v);}

	/** Sets member value. */
	void setMember( int index, float v )								{setNumber(index,v);}

	/** Sets member value. */
	void setMember( const std::string& name, float v )					{setNumber(name,v);}
	
	/** Sets member value. */
	void setMember( const char* name, float v )					{setNumber(name,v);}

	/** Sets member value. */
	void setMember( int index, const std::string& v )					{setString(index,v);}
	
	/** Sets member value. */
	void setMember( int index, const char* v )					{setString(index,v);}
	
	/** Sets member value. */
	void setMember( const std::string& name, const std::string& v )	{setString(name,v);}
	
	/** Sets member value. */
	void setMember( const std::string& name, const char* v )	{setString(name,v);}
	
	/** Sets member value. */
	void setMember( const char* name, const std::string& v )	{setString(name,v);}
	
	/** Sets member value. */
	void setMember( const char* name, const char* v )	{setString(name,v);}

	/** Sets member value. */
	void setMember( int index, const LuaTable& v )						{setTable(index,v);}

	/** Sets member value. */
	void setMember( int index, const LuaTable* v )						{setTable(index,v);}

	/** Sets member value. */
	void setMember( const std::string& name, const LuaTable& v )		{setTable(name,v);}

	/** Sets member value. */
	void setMember( const std::string& name, const LuaTable* v )		{setTable(name,v);}
	
	/** Sets member value. */
	void setMember( const char* name, const LuaTable& v )		{setTable(name,v);}

	/** Sets member value. */
	void setMember( const char* name, const LuaTable* v )		{setTable(name,v);}

	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( const char* name ) const;
	
	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( const std::string& name ) const;

	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( int index ) const;
	
	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( const char* name ) const;

	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( const std::string& name ) const;
	
	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( int index ) const;
	
	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( const char* name ) const;

	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( const std::string& name ) const;

	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( int index ) const;
	
	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( const char* name ) const;

	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( const std::string& name ) const;

	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( int index ) const;
	
	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( const char* name ) const;

	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( const std::string& name ) const;

	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( int index ) const;
	
	/** Returns true if the member is boolean. */
	bool isBoolean( const char* name ) const;

	/** Returns true if the member is boolean. */
	bool isBoolean( const std::string& name ) const;

	/** Returns true if the member is boolean. */
	bool isBoolean( int index ) const;
	
	/** Returns true if the member is nil. */
	bool isNil( const char* name ) const;

	/** Returns true if the member is nil. */
	bool isNil( const std::string& name ) const;

	/** Returns true if the member is nil. */
	bool isNil( int index ) const;
	
	/** Returns true if the member is number. */
	bool isNumber( const char* name ) const;

	/** Returns true if the member is number. */
	bool isNumber( const std::string& name ) const;

	/** Returns true if the member is number. */
	bool isNumber( int index ) const;
	
	/** Returns true if the member is string. */
	bool isString( const char* name ) const;

	/** Returns true if the member is string. */
	bool isString( const std::string& name ) const;

	/** Returns true if the member is string. */
	bool isString( int index ) const;
	
	/** Returns true if the member is table. */
	bool isTable( const char* name ) const;

	/** Returns true if the member is table. */
	bool isTable( const std::string& name ) const;

	/** Returns true if the member is table. */
	bool isTable( int index ) const;
	
	/**  */
	bool isFunction( const char* name ) const;

	/**  */
	bool isFunction( const std::string& name ) const;

	/**  */
	bool isFunction( int index ) const;

	/** Pushes member by name to LuaState stack. */
	void pushMember( int index ) const;

	/** Pushes member by index to LuaState stack. */
	void pushMember( const std::string& name ) const;
	
	/** Pushes member by index to LuaState stack. */
	void pushMember( const char* name ) const;

	/** Returns number of items in the table. */
	int size() const;

	/** Returns pointer to low level Lua state object. */
	LuaState*	luaState() const			{return m_luastate;}
	
	/**  */
	void		getRef() const;
	
	/**  */
	void		swap( LuaTable& other );

private:
	friend class LuaState;

	LuaState*	m_luastate;
	int			m_ref;

	void	writeChar( io::OutputStream& out, int ch );
	void	writeMargin( io::OutputStream& out, int margin );
	void	writeString( io::OutputStream& out, const char* str );
	void	writeStringLiteral( io::OutputStream& out, const char* str );
	void	writeValue( io::OutputStream& out, int index, int margin );
	
	void 	traverseRecursively( LuaTableVisitor& visitor );
};


} // lua


#endif // _LUA_LUATABLE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
