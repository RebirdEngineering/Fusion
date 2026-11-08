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
class LuaTable : //25
	public lang::Object
{
public:
	/** Skips table initialization. */
	LuaTable(); //30

	/** Creates a table to LuaState. */
	explicit LuaTable( LuaState* state ); //33

	/** Copy by reference. */
	LuaTable( const LuaTable& other ); //36
	
	/** Parameter is guessed. */
	LuaTable( LuaTable&& other ); //39
	
	/** Releases a reference. */
	~LuaTable(); //42

	/** Copy by reference. */
	LuaTable& operator=( const LuaTable& other ); //45
	
	/**  */
	LuaTable& operator=( LuaTable&& other ); //48

	/**
	 * Writes Lua table to output stream. Note that
	 * functions are not written to the output.
	 * @exception IOException
	 * @exception LuaException
	 */
	void write( io::OutputStream& out, int margin=0, bool nested = false ); //56

	/**
	 * Reads Lua table from input stream.
	 * @exception IOException
	 * @exception LuaException
	 */
	void read(io::InputStream& in ); //63
	
	/**
	 * 
	 * @exception IOException
	 * @exception LuaException
	 */
	void read( const std::vector<unsigned char>& in ); //70 | Not on iOS.
	
	/**
	 * 
	 * @exception IOException
	 * @exception LuaException
	 */
	void read( const std::string& in ); //77 | Not on iOS.
	
	/**  */
	void traverse( LuaTableVisitor& visitor ); //80

	/** Removes the member from the table. */
	void remove( int index ); //83

	/** Removes the member from the table. */
	void remove( const std::string& name ); //86
	
	/** Removes the member from the table. */
	void remove( const char* name ); //89

	/** Sets boolean member value. */
	void setBoolean( int index, bool v ); //92

	/** Sets boolean member value. */
	void setBoolean( const std::string& name, bool v ); //95
	
	/** Sets boolean member value. */
	void setBoolean( const char* name, bool v ); //98

	/** Sets number member value. */
	void setNumber( int index, float v ); //101

	/** Sets number member value. */
	void setNumber( const std::string& name, float v ); //104
	
	/** Sets string member value. */
	void setNumber( const char* name, float v ); //107

	/** Sets string member value. */
	void setString( int index, const std::string& v ); //110
	
	/** Sets string member value. */
	void setString( int index, const char* v ); //113
	
	/** Sets string member value. */
	void setString( const std::string& name, const std::string& v ); //116
	
	/** Sets string member value. */
	void setString( const char* name, const std::string& v ); //119
	
	/** Sets string member value. */
	void setString( const std::string& name, const char* v ); //122
	
	/** Sets string member value. */
	void setString( const char* name, const char* v ); //125

	/** Sets table member value. */
	void setTable( int index, const LuaTable& v ); //128

	/** Sets table member value. */
	void setTable( int index, const LuaTable* v ); //131

	/** Sets table member value. */
	void setTable( const std::string& name, const LuaTable& v ); //134

	/** Sets table member value. */
	void setTable( const std::string& name, const LuaTable* v ); //137
	
	/** Sets table member value. */
	void setTable( const char* name, const LuaTable& v ); //140

	/** Sets table member value. */
	void setTable( const char* name, const LuaTable* v ); //143
	
	/**  */
	void setFunction( int index, const LuaFunction& v ); //146
	
	/**  */
	void setFunction( int index, const LuaFunction* v ); //149
	
	/** SYMBOL NEVER SEEN ACROSS GAMES! WIP DECOMPILATION */
	void setFunction( const std::string& name, const LuaFunction& v ); //152
	
	/** SYMBOL NEVER SEEN ACROSS GAMES! WIP DECOMPILATION */
	void setFunction( const std::string& name, const LuaFunction* v ); //155
	
	/** SYMBOL NEVER SEEN ACROSS GAMES! WIP DECOMPILATION */
	void setFunction( const char* name, const LuaFunction& v ); //158
	
	/**  */
	void setFunction( const char* name, const LuaFunction* v ); //161

	/** Sets member value. */
	void setMember( int index, bool v )									{setBoolean(index,v);} //164

	/** Sets member value. */
	void setMember( const std::string& name, bool v )					{setBoolean(name,v);} //167
	
	/** Sets member value. */
	void setMember( const char* name, bool v )					{setBoolean(name,v);} //170

	/** Sets member value. */
	void setMember( int index, float v )								{setNumber(index,v);} //173

	/** Sets member value. */
	void setMember( const std::string& name, float v )					{setNumber(name,v);} //176
	
	/** Sets member value. */
	void setMember( const char* name, float v )					{setNumber(name,v);} //179

	/** Sets member value. */
	void setMember( int index, const std::string& v )					{setString(index,v);} //182
	
	/** Sets member value. */
	void setMember( int index, const char* v )					{setString(index,v);} //185
	
	/** Sets member value. */
	void setMember( const std::string& name, const std::string& v )	{setString(name,v);} //188
	
	/** Sets member value. */
	void setMember( const std::string& name, const char* v )	{setString(name,v);} //191
	
	/** Sets member value. */
	void setMember( const char* name, const std::string& v )	{setString(name,v);} //194
	
	/** Sets member value. */
	void setMember( const char* name, const char* v )	{setString(name,v);} //197

	/** Sets member value. */
	void setMember( int index, const LuaTable& v )						{setTable(index,v);} //200

	/** Sets member value. */
	void setMember( int index, const LuaTable* v )						{setTable(index,v);} //203

	/** Sets member value. */
	void setMember( const std::string& name, const LuaTable& v )		{setTable(name,v);} //205

	/** Sets member value. */
	void setMember( const std::string& name, const LuaTable* v )		{setTable(name,v);} //209
	
	/** Sets member value. */
	void setMember( const char* name, const LuaTable& v )		{setTable(name,v);} //212

	/** Sets member value. */
	void setMember( const char* name, const LuaTable* v )		{setTable(name,v);} //215

	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( const char* name ) const; //221
	
	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( const std::string& name ) const; //227

	/** 
	 * Returns boolean member of the table. 
	 * @exception LuaException
	 */
	bool getBoolean( int index ) const; //233
	
	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( const char* name ) const; //239

	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( const std::string& name ) const; //245
	
	/** 
	 * Returns number member of the table. 
	 * @exception LuaException
	 */
	float getNumber( int index ) const; //251
	
	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( const char* name ) const; //257

	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( const std::string& name ) const; //263

	/** 
	 * Returns string member of the table. 
	 * @exception LuaException
	 */
	std::string getString( int index ) const; //269
	
	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( const char* name ) const; //275

	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( const std::string& name ) const; //281

	/** 
	 * Returns handle to table member of the table. 
	 * @exception LuaException
	 */
	LuaTable getTable( int index ) const; //287
	
	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( const char* name ) const; //293

	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( const std::string& name ) const; //299

	/** 
	 * 
	 * @exception LuaException
	 */
	LuaFunction getFunction( int index ) const; //305
	
	/** Returns true if the member is boolean. */
	bool isBoolean( const char* name ) const; //308

	/** Returns true if the member is boolean. */
	bool isBoolean( const std::string& name ) const; //311

	/** Returns true if the member is boolean. */
	bool isBoolean( int index ) const; //314
	
	/** Returns true if the member is nil. */
	bool isNil( const char* name ) const; //317

	/** Returns true if the member is nil. */
	bool isNil( const std::string& name ) const; //320

	/** Returns true if the member is nil. */
	bool isNil( int index ) const; //323
	
	/** Returns true if the member is number. */
	bool isNumber( const char* name ) const; //326

	/** Returns true if the member is number. */
	bool isNumber( const std::string& name ) const; //329

	/** Returns true if the member is number. */
	bool isNumber( int index ) const; //332
	
	/** Returns true if the member is string. */
	bool isString( const char* name ) const; //335

	/** Returns true if the member is string. */
	bool isString( const std::string& name ) const; //338

	/** Returns true if the member is string. */
	bool isString( int index ) const; //341
	
	/** Returns true if the member is table. */
	bool isTable( const char* name ) const; //344

	/** Returns true if the member is table. */
	bool isTable( const std::string& name ) const; //347

	/** Returns true if the member is table. */
	bool isTable( int index ) const; //350
	
	/**  */
	bool isFunction( const char* name ) const; //353

	/**  */
	bool isFunction( const std::string& name ) const; //356

	/**  */
	bool isFunction( int index ) const; //359

	/** Pushes member by name to LuaState stack. */
	void pushMember( int index ) const; //362

	/** Pushes member by index to LuaState stack. */
	void pushMember( const std::string& name ) const; //365
	
	/** Pushes member by index to LuaState stack. */
	void pushMember( const char* name ) const; //368

	/** Returns number of items in the table. */
	int size() const; //371

	/** Returns pointer to low level Lua state object. */
	LuaState*	luaState() const			{return m_luastate;} //374
	
	/**  */
	void		getRef() const; //377
	
	/**  */
	void		swap( LuaTable& other ); //380

private:
	friend class LuaState;

	LuaState*	m_luastate; //385
	int			m_ref; //386

	void	writeChar( io::OutputStream& out, int ch ); //388
	void	writeMargin( io::OutputStream& out, int margin ); //389
	void	writeString( io::OutputStream& out, const char* str ); //390
	void	writeStringLiteral( io::OutputStream& out, const char* str ); //391
	void	writeValue( io::OutputStream& out, int index, int margin ); //392
	
	void 	traverseRecursively( LuaTableVisitor& visitor ); //394
};


} // lua


#endif // _LUA_LUATABLE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
