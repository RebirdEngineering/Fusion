#ifndef _LUA_JSONIMPORTER_H
#define _LUA_JSONIMPORTER_H

#include <lua/LuaTable.h>
#include <util/JSONVisitor.h>

namespace lua
{

class JSONImporter : public util::JSONVisitor
{
public:
    explicit JSONImporter(LuaTable& rootLuaTable);
    ~JSONImporter();

    virtual void visit(const char* name, const char* value);
    virtual void visit(const char* name, double value);
    virtual void visit(const char* name, bool value);
    virtual void visit(const char* name);

    virtual void startObject(const char* name);
    virtual void endObject();

    virtual void startArray(const char* name);
    virtual void endArray();
private:
    struct State
    {
        State(LuaTable* theLuaTable, int theArrayIndex = -1);
        LuaTable* luaTable;
        int arrayIndex;
    };
	JSONImporter& operator=(const JSONImporter&);
    std::stack<State> m_stack;
    LuaTable* m_rootLuaTable;
    const int kInvalidIndex = -1;
};

} // lua

#endif // !_LUA_JSONIMPORTER_H