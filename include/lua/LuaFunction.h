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
    
    template <class A1> void operator()(A1 a1);
    template <class A1, class A2> void operator()(A1 a1, A2 a2);
    //template <class A1, class A2, class A3> void operator()(A1 a1, A2 a2, A3 a3);
    //template <class A1, class A2, class A3, class A4> void operator()(A1 a1, A2 a2, A3 a3, A4 a4);
    //template <class A1, class A2, class A3, class A4, class A5> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5);
    //template <class A1, class A2, class A3, class A4, class A5, class A6> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11);
    //template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> void operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12);
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