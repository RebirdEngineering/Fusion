#include <flurry/FlurryLuaInterface.h>
#include <flurry/Flurry.h>
#include <lua/LuaStackRestore.h>

using namespace lua;

namespace flurry
{
	FlurryLuaInterface::FlurryLuaInterface(LuaState* luaState, Flurry* flurry) :
		LuaObject(luaState)
	{
		m_flurry = flurry;
		registerLuaMethod("logEvent", this, &FlurryLuaInterface::logEvent);
		registerMethod("startSession", this, &FlurryLuaInterface::startSession);
		registerMethod("endSession", this, &FlurryLuaInterface::endSession);
		luaState->globals().setTable("Flurry", this);
	}

	FlurryLuaInterface::~FlurryLuaInterface()
	{
	}

	void FlurryLuaInterface::startSession(std::string apiKey)
	{
		m_flurry->startSession(apiKey);
	}


	void FlurryLuaInterface::endSession()
	{
		m_flurry->endSession();
	}

	int FlurryLuaInterface::logEvent(LuaState* lua)
	{
		if (lua->top() != 2)
			lua->top();

		std::string eventName = lua->toString(1);
		std::map<std::string, std::string> params;
		const char* key;

		if (lua->top() == 2 && lua->type(2) == LuaState::TYPE_STRING)
		{
			const char* key = lua->toString(2);
			params[key] = "";
		}
		else if (lua->top() == 2 && lua->isTable(2))
		{
			LuaTable arg = lua->toTable(2);
			LuaStackRestore lsr(lua);
			lua->pushTable(arg);
			int tab = lua->top();
			lua->pushNil();

			while (lua->next(tab))
			{
				if (lua->type(-1 == LuaState::TYPE_STRING) && lua->type(-2 == LuaState::TYPE_STRING))
				{
					const char* key = lua->toString(-2);
					const char* value = lua->toString(-1);
					params[key] = strlen(value);
				}
				lua->pop();
			}	
		}

		else if (lua->top() == 3)
		{
			const char* key = lua->toString(2);
			const char* value = lua->toString(3);
			params[key] = strlen(value);
		}

		m_flurry->logEvent(eventName, params);
		return 0;
	}
}