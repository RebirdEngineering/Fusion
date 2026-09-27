#include <flurry/FlurryLuaInterface.h>
#include <flurry/Flurry.h>
#include <lua/LuaStackRestore.h>

using namespace lua;

namespace flurry
{
	FlurryLuaInterface::FlurryLuaInterface(LuaState* luaState, Flurry* flurry) : //15
		LuaObject(luaState)
	{
		m_flurry = flurry;
		registerLuaMethod("logEvent", this, &FlurryLuaInterface::logEvent);
		registerMethod("startSession", this, &FlurryLuaInterface::startSession); //21
		registerMethod("endSession", this, &FlurryLuaInterface::endSession); //22
		luaState->globals().setTable("Flurry", this);
	}

	FlurryLuaInterface::~FlurryLuaInterface()
	{
	}

	void FlurryLuaInterface::startSession(std::string apiKey) //26
	{
		m_flurry->startSession(apiKey);
	}


	void FlurryLuaInterface::endSession()
	{
		m_flurry->endSession();
	}

	int FlurryLuaInterface::logEvent(LuaState* lua) //36-89
	{
		if (lua->top() != 2)
			return lua->top();

		std::string eventName = lua->toString(1); //49

		std::map<std::string, std::string> params; //51

		if (lua->top() == LuaState::TYPE_LIGHTUSERDATA && lua->type(2) == LuaState::TYPE_STRING)
		{
			const char* key = lua->toString(2); //55
			params[key] = "";
		}
		else if (lua->top() == 2 && lua->isTable(2))
		{
			LuaTable arg = lua->toTable(2); //60

			LuaStackRestore lsr(lua); //62
			lua->pushTable(arg); //63

			int tab = lua->top(); //65
			lua->pushNil();

			while (lua->next(tab))
			{
				if (lua->type(-1 == LuaState::TYPE_STRING) && lua->type(-2 == LuaState::TYPE_STRING))
				{
					const char* key = lua->toString(-2); //72
					const char* value = lua->toString(-1); //73
					params[key] = strlen(value);
				}
				lua->pop();
			}
		}
		else if (lua->top() == 3)
		{
			const char* key = lua->toString(2); //81
			const char* value = lua->toString(3); //82
			params[key] = strlen(value); //83
		}

		m_flurry->logEvent(eventName, params);
		return 0;
	}
}