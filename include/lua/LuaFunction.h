#ifndef _LUA_LUAFUNCTION_H
#define _LUA_LUAFUNCTION_H

#include <lang/Object.h>

namespace lua
{

    class LuaState;

/**
 * 
 *
 * @ingroup lua
 */
class LuaFunction : //21
    public lang::Object
{
public:
    /**  */
    LuaFunction(); //27

    /**  */
    explicit LuaFunction( LuaState* state, int ref ); //30 | Does not exist on iOS? (_ZN3lua11LuaFunctionC2EPNS_8LuaStateEi / lua::LuaFunction::LuaFunction(lua::LuaState*, int)). Symbol exists up to ABC 520 and ABC_CHN 5.4.0

    /** Copy by reference. */
    LuaFunction( const LuaFunction& other ); //33

    /** Releases a reference. */
    ~LuaFunction(); //36

    /** Copy by reference. */
    LuaFunction& operator=( const LuaFunction& other ); //39

    void operator()(); //41
    
    template <class A1> void operator()(const A1& a1);
    template <class A1, class A2> void operator()(const A1& a1, const A2& a2);
private:
    friend class LuaState;
    friend class LuaTable; //Needed?

    LuaState*   m_luastate; //83
    int         m_ref; //84

    void getRef(); //86
};

#include <lua/LuaFunction.inl>


} // lua


#endif // _LUA_LUAFUNCTION_H