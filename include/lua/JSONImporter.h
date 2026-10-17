#ifndef _LUA_JSONIMPORTER_H
#define _LUA_JSONIMPORTER_H

#include <lua/LuaTable.h>
#include <util/JSONVisitor.h>

namespace lua
{

class JSONImporter : //15
    public util::JSONVisitor
{
public:
    explicit JSONImporter(LuaTable& rootLuaTable); //19
    ~JSONImporter(); //20

    void visit(const char* name, const char* value); //22
    void visit(const char* name, double value); //23
    void visit(const char* name, bool value); //24
    void visit(const char* name); //25

    void startObject(const char* name); //27
    void endObject(); //28

    void startArray(const char* name); //30
    void endArray(); //31

private:
	JSONImporter& operator=(const JSONImporter&); //34

    struct State //36
    {
        State(LuaTable* theLuaTable, int theArrayIndex = -1); //38
        LuaTable* luaTable; //42
        int arrayIndex; //43
    };

    std::stack<State> m_stack; //46
    LuaTable* m_rootLuaTable; //47

    static const int kInvalidIndex = -1; //49
};

} // lua

#endif // !_LUA_JSONIMPORTER_H