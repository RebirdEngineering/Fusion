#ifndef _PF_WEBVIEWLUAINTERFACE_H
#define _PF_WEBVIEWLUAINTERFACE_H

#include <lua/LuaObject.h>

namespace pf
{

class WebView;

class WebViewLuaInterface :
	public lua::LuaObject
{
public:
	WebViewLuaInterface(lua::LuaState* lua); //23
	~WebViewLuaInterface(); //24

private:
	static int create(lua_State* L); //28
	static int destroy(lua_State* L); //29

	static int loadPage(lua_State* L); //31
	static int loadLocalPage(lua_State* L); //32
	static int reloadPage(lua_State* L); //33

	static int show(lua_State* L); //35
	static int hide(lua_State* L); //36

	static int setPosition(lua_State* L); //38
	static int setSize(lua_State* L); //39

	static int setOnPageLoadedCallback(lua_State* L); //41
	static int setOnLinkClickedCallback(lua_State* L); //42

	static int allowCallsFromJavaScript(lua_State* L); //44
	static int executeJavaScript(lua_State* L); //45
	static int asyncExecuteJavaScript(lua_State* L); //46

	static WebView* checkWebView(lua_State* L); //55

	lua::LuaState* mLuaState; //49

	static WebViewLuaInterface* s_instance; //51
	static const char* s_tableName; //52
	static const char* s_metaTableName; //53

	WebViewLuaInterface(const WebViewLuaInterface&); //57
	WebViewLuaInterface& operator=(const WebViewLuaInterface&); //58
};

}

#endif