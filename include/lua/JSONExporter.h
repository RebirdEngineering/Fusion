#ifndef _LUA_JSONEXPORTER_H
#define _LUA_JSONEXPORTER_H

#include <lua/LuaTableVisitor.h>

namespace lua
{

class JSONExporter : //14
    public LuaTableVisitor
{
public:
    JSONExporter(); //18

    void visit(const char* name, const char* value); //20
    void visit(const char* name, double value); //21
    void visit(const char* name, bool value); //22
    void visit(const char* name); //23

    void visit(int index, const char* value); //25
    void visit(int index, double value); //26
    void visit(int index, bool value); //27
    void visit(int index); //28

	void openTable(const char* value); //30
	void closeTable(); //31

	void start(); //33
	void end(); //34
    
	std::string getJSON(); //36

    struct State //39
    {
        State(bool, int); //41

        bool m_firstItem; //44
        int m_currentIndex; //45
    };
private:
    std::string m_json; //48
    std::stack<State> m_states; //49
    State m_currentState; //50

    void addName(const std::string& name); //52
    void addValue(const std::string& value); //53

    void addArrayItem(int index, const std::string& value); //55

    std::string doubleToString(double value); //57
    std::string backslashEscape(const char* s); //58

	static const int kInvalidIndex = -1; //60
};

} // lua

#endif // !_LUA_JSONEXPORTER_H