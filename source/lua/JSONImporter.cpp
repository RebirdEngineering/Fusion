#include <lua/JSONImporter.h>

namespace lua
{

JSONImporter::JSONImporter(LuaTable& rootLuaTable)
{
	m_rootLuaTable = &rootLuaTable;
	State state(m_rootLuaTable, kInvalidIndex);
	m_stack.push(state);
}

JSONImporter::~JSONImporter()
{
	State state = m_stack.top();
	m_stack.pop();
}

void JSONImporter::visit(const char* name, const char* value)
{
	State state = m_stack.top();

	if (state.arrayIndex < 0)
		state.luaTable->setMember(name, value); //Ignore the Android symbol, it's setMember according to DWARF
	else
	{
		state.luaTable->setMember(state.arrayIndex, value);
		state.arrayIndex++;
	}
}

void JSONImporter::visit(const char* name, double value)
{
	State state = m_stack.top();

	if (state.arrayIndex < 0)
		state.luaTable->setMember(name, (float)value); //Ignore the Android symbol, it's setMember according to DWARF
	else
	{
		state.luaTable->setMember(state.arrayIndex, (float)value);
		state.arrayIndex++;
	}
}

void JSONImporter::visit(const char* name, bool value)
{
	State state = m_stack.top();

	if (state.arrayIndex < 0)
		state.luaTable->setMember(name, value);
	else
	{
		state.luaTable->setMember(state.arrayIndex, value);
		state.arrayIndex++;
	}
}

void JSONImporter::visit(const char* name)
{
	State state = m_stack.top();

	if (state.arrayIndex < 0)
		state.luaTable->remove(name);
	else
	{
		state.luaTable->remove(state.arrayIndex);
		state.arrayIndex++;
	}
}

void JSONImporter::startObject(const char* name)
{
	/*LuaTable* current_table = new LuaTable(m_rootLuaTable->luaState());

	LuaTable* new_table =  m_stack.top().luaTable;

	State* state;

	m_stack.top();
	m_stack.top();
	m_stack.top();

	state->luaTable = new_table;
	m_stack.push(state);*/
}

void JSONImporter::endObject()
{
	State* state = &m_stack.top();
	m_stack.pop();
}

void JSONImporter::startArray(const char* name)
{
	m_stack.top().arrayIndex = 1;
}

void JSONImporter::endArray()
{
	//JSONVisitor::endArray();
}

} // lua