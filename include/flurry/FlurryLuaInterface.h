#ifndef FLURRY_FLURRYLUAINTERFACE_H
#define FLURRY_FLURRYLUAINTERFACE_H

#include <lua/LuaObject.h>

namespace flurry
{

	class Flurry;

class FlurryLuaInterface : //24
	public lua::LuaObject
{
public:
	FlurryLuaInterface(lua::LuaState* luaState, Flurry* flurry);
	~FlurryLuaInterface();
private:
	Flurry* m_flurry;

	void startSession(std::string apiKey);
	void endSession();
	int logEvent(lua::LuaState* lua);

	FlurryLuaInterface(const FlurryLuaInterface&);
	FlurryLuaInterface& operator=(const FlurryLuaInterface&);
};

}

#endif // !FLURRY_FLURRYLUAINTERFACE_H