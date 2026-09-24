#ifndef _LUA_JSONEXPORTER_H
#define _LUA_JSONEXPORTER_H

#include <lua/LuaTableVisitor.h>

namespace lua
{

class JSONExporter : public LuaTableVisitor
{
public:
    JSONExporter();

    virtual void visit(const char* name, const char* value);
    void visit(const char* name, double value);
    void visit(const char* name, bool value);
    void visit(const char* name);

    void visit(int index, const char* value);
    void visit(int index, double value);
    void visit(int index, bool value);
    void visit(int index);

	void openTable(const char* value);
	void closeTable();

	void start();
	void end();
    
	std::string getJSON();

    struct State
    {
        State(bool, int);
        bool m_firstItem;
        int m_currentIndex;
    };
private:
    std::string m_json;
    std::stack<State> m_states;
    State m_currentState;
    void addName(const std::string& name); //Inline
    void addValue(const std::string& value); //Inline

    void addArrayItem(int index, const std::string& value); //Inline

    std::string doubleToString(double value); //Inline
    std::string backslashEscape(const char* s);
	const int kInvalidIndex = -1;
};

} // lua

#endif // !_LUA_JSONEXPORTER_H