#ifndef _LUA_LUATABLEVISITOR_H
#define _LUA_LUATABLEVISITOR_H

#include <lang/pp.h>

namespace lua
{


/**
 *
 *
 * @ingroup lua
 */
class LuaTableVisitor
{
public:
    
    ~LuaTableVisitor();

    
	virtual void visit(const char* name, double value) = 0;
	virtual void visit(const char* name, bool value) = 0;
	virtual void visit(const char* name) = 0;

	virtual void visit(int index, const char* name) = 0;
	virtual void visit(int index, double value) = 0;
    virtual void visit(int index, bool value) = 0;
    virtual void visit(int index) = 0;

	virtual void openTable(const char* name) = 0;
	virtual void closeTable() = 0;

    virtual void start() = 0;
    virtual void end() = 0;
};


} // lua


#endif // _LUA_LUATABLEVISITOR_H