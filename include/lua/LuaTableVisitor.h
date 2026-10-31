#ifndef _LUA_LUATABLEVISITOR_H
#define _LUA_LUATABLEVISITOR_H

#include <lang/pp.h>

namespace lua
{

class LuaTableVisitor //9
{
public:
    virtual ~LuaTableVisitor(); //12
    
	virtual void visit(const char* name, const char* value) = 0; //15
	virtual void visit(const char* name, double value) = 0; //16
	virtual void visit(const char* name, bool value) = 0; //17
	virtual void visit(const char* name) = 0; //18

	virtual void visit(int index, const char* name) = 0; //21
	virtual void visit(int index, double value) = 0; //22
    virtual void visit(int index, bool value) = 0; //23
    virtual void visit(int index) = 0; //24

	virtual void openTable(const char* name) = 0; //27
	virtual void closeTable() = 0; //28

    virtual void start() = 0; //31
    virtual void end() = 0; //32
};


} // lua


#endif // _LUA_LUATABLEVISITOR_H