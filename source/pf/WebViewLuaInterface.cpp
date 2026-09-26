#include <pf/WebViewLuaInterface.h>
#include <pf/WebView.h>
#include <external/lua/src/lauxlib.h>
#include <lang/Log.h>
#include <lang/String.h>

using namespace lua;

namespace pf
{

class WebViewLuaListener : public WebViewListener //Originally in lua in ABC <3.1.2, Friends (Fusion) <1.1.0, ABR <1.6.1, ABS <3.3.0, ABSP <1.5.2, ABSW <1.2.2 and Croods <1.1.0
{
public:
	WebViewLuaListener()
	{
		mNameSpaceForJSCalls = "";
	}
	~WebViewLuaListener()
	{
	}

	void onWebViewPageLoaded(bool success, const std::string& pageTitle, WebView& webView) //20
	{
		if (webView.m_func_ref == -1)
			return;

		const char* title = pageTitle.c_str(); //24

		lua_State* L = mLuaState; //26

		lua_rawgeti(L, LUA_REGISTRYINDEX, webView.m_callback);
		lua_pushlightuserdata(L, &webView);
		lua_pushboolean(L, success);
		lua_pushstring(L, title);

		if (lua_pcall(L, 3, 0, 0))
		{
			const char* error = lua_tostring(L, -1); //35
			LANG_LOG_DEBUG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //36 on ABS410, 38 on ABS 311 OSX, Space 1.4.0 and ABC 300+301 OSX
		}
	}

	LinkClickedResult onWebViewLinkClicked(const std::string& url, WebView& webView) //41 | TODO
	{
		if (webView.m_callback == -1)
			return LOAD_PAGE_INTO_WEBVIEW;
		const char* url_s = url.c_str(); //47
		int len = url.size(); //48

		lua_State* L = mLuaState; //50

		lua_rawgeti(L, LUA_REGISTRYINDEX, webView.m_callback);
		lua_pushlightuserdata(L, &webView);
		lua_pushlstring(L, url_s, len);
		int status = lua_pcall(L, 2, 2, 0); //56
		if (status)
		{
			const char* error = lua_tolstring(L, -1, 0); //59
			lua_settop(L, -2);
			LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //61, 70 on ABC 300+301 OSX
			return LOAD_PAGE_INTO_WEBVIEW;
		}

		ptrdiff_t returnCode = lua_tointeger(L, -1); //65
		lua_settop(L, -2);
		if (returnCode >= LOAD_PAGE_INTO_EXTERNAL_BROWSER)
		{
			LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Unknown return code from onLinkClicked()"); //80, legacy name?, 89 on ABC 300+301 OSX
			return LOAD_PAGE_INTO_WEBVIEW;
		}
		return (LinkClickedResult)returnCode;
		//return LOAD_PAGE_INTO_WEBVIEW;
	}

	void onWebViewCallFromJavaScript(const std::string& message, WebView& webView)
	{
		if (mNameSpaceForJSCalls.empty()) //92
			return;

		std::vector<std::string> ns = lang::string::split(mNameSpaceForJSCalls, "."); //97

		CallDescription cd = parseCall(message); //99

		if (cd.success)
		{
			lua_State* L = mLuaState; //103

			for (size_t i = 0; i < cd.arguments.size(); i++) //106
			{
				cd.arguments[i].empty() ? lua_getfield(L, -1, "") : lua_getglobal(L, cd.functionName.c_str()); //108
			}

			//.c_str() // 121

			for (size_t i = 0; i < cd.arguments.size(); i++) //124
			{
				const char* s_ptr = cd.arguments[i].c_str(); //126

				if (cd.argumentIsNumber[i])
				{
					lua_Number n = atof(s_ptr); //130
					lua_pushnumber(L, n);
				}
				else
					lua_pushstring(L, s_ptr);
			}

			int argument_count = lua_pcall(L, 0, 0, 0); //140
			const int return_value_count = 0; //141

			const char* error = lua_tostring(L, -1); //145
			lua_settop(L, -2);
			LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //147 (156 on ABS 3.1.0 [AND] + ABSpace 1.4.0 [And] + ABS 311 OSX+ABR 1.5.0 [And], 149 in Croods + ABF 1.0.0-1.6.1 AND, 156 in ABC 300+301 OSX)
		}
	}

	void setJSCallNameSpace(const std::string& ns) //152
	{
		mNameSpaceForJSCalls = ns;
	}

	struct CallDescription
	{
	public:
		bool success;
		std::string functionName;
		std::vector<std::string> arguments;
		std::vector<bool> argumentIsNumber;
	};
private:
	WebView* m_webView;
	lua_State* mLuaState; //Broke the naming convention?
	std::string mNameSpaceForJSCalls;

	CallDescription parseCall(const std::string& s) //175
	{
		/*size_t pos2; //188

		pos2 = s.find('('); //190
		if (pos2 == -1)
			return;

		//.substr //194
		//.size(); //195

		//.size(); //197

		//.clear(); //199

		for (size_t i = 0; i < ?.size(); i++) //202
		{
			bool isQuoted = false; //205

			char c = []; //207

			[] //213
			[] //222
		}*/
		
		

		return CallDescription();
	}
};

WebViewLuaInterface::WebViewLuaInterface(LuaState* lua) :
	mLuaState(lua),
	LuaObject(lua)
{
	bool initialized = false; //?

	const luaL_Reg webView_f[] = { //224
		{ "new", create },
		{ 0, 0 }
	};

	const luaL_Reg webView_m[] = { //250
		{ "show", show },
		{ "hide", hide },
		{ "setPosition", setPosition },
		{ "setSize", setSize },
		{ "loadPage", loadPage },
		{ "loadLocalPage", loadLocalPage },
		{ "reloadPage", reloadPage },
		{ "setOnLinkClickedCallback", setOnLinkClickedCallback },
		{ "setOnPageLoadedCallback",setOnPageLoadedCallback },
		{ "allowCallsFromJavaScript", allowCallsFromJavaScript },
		{ "executeJavaScript", executeJavaScript },
		{ "asyncExecuteJavaScript", asyncExecuteJavaScript },
		{ 0, 0 }
	};

	if (WebView::isSupported() && !initialized)
	{
		lua_State* l = lua->impl();
		luaL_newmetatable(l, s_metaTableName);
		lua_pushvalue(l, -1);
		lua_setfield(l, -2, "__index");
		luaL_register(l, 0, webView_m);
		luaL_register(l, s_tableName, webView_f);
		lua_settop(l, -3);
		lua_getglobal(l, s_tableName);
		lua_pushstring(l, "0");
		lua_setfield(l, -2, "DONT_LOAD_PAGE");
		lua_pushstring(l, "1");
		lua_setfield(l, -2, "LOAD_PAGE_INTO_WEBVIEW");
		lua_pushstring(l, "2");
		lua_setfield(l, -2, "LOAD_PAGE_INTO_EXTERNAL_BROWSER");
		lua_settop(l, -2);
		s_instance = this;
		initialized = true;
	}
}

WebViewLuaInterface::~WebViewLuaInterface()
{
	s_instance = 0;
}

int WebViewLuaInterface::create(lua_State* L) //305
{
	int x = lua_tointeger(L, 1); //307
	int y = lua_tointeger(L, 2); //308
	int width = lua_tointeger(L, 3); //309
	int height = lua_tointeger(L, 4); //310

	WebView* view = new WebView(x, y, width, height, true); //312

	WebViewLuaListener* listener = new WebViewLuaListener(); //314
	view->setListener(listener);

	lua_pushlightuserdata(L, view);
	lua_getfield(L, LUA_REGISTRYINDEX, s_metaTableName);
	lua_setmetatable(L, -2);
	return 1;
}

int WebViewLuaInterface::destroy(lua_State* L)
{
	WebView* view = checkWebView(L);
	view->m_func_ref = -1;
	view->m_callback = -1;
	return 0;
}

int WebViewLuaInterface::loadPage(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	std::string url = lua_tostring(L, 2);
	const char* p = url.c_str();
	view->loadUrl(p);
	return 0;
}

int WebViewLuaInterface::loadLocalPage(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	std::string url = lua_tostring(L, 2);
	const char* p = url.c_str();
	view->loadLocalUrl(p);
	return 0;
}

int WebViewLuaInterface::reloadPage(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	view->reload();
	return 0;
}

int WebViewLuaInterface::show(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	view->show();
	return 0;
}

int WebViewLuaInterface::hide(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	view->hide();
	return 0;
}

int WebViewLuaInterface::setPosition(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	view->setPosition(lua_tointeger(L, 2), lua_tointeger(L, 3));
	return 0;
}

int WebViewLuaInterface::setSize(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	view->setSize(lua_tointeger(L, 2), lua_tointeger(L, 3));
	return 0;
}

int WebViewLuaInterface::executeJavaScript(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	std::string javaScript = lua_tostring(L, 2);
	const char* p = javaScript.c_str();
	std::string* result = view->executeJavaScript(p);
	lua_pushstring(L, result ? result->c_str() : "");
	return 0;
}

int WebViewLuaInterface::asyncExecuteJavaScript(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	std::string javaScript = lua_tostring(L, 2);
	const char* p = javaScript.c_str();
	view->asyncExecuteJavaScript(p);
	return 0;
}

int WebViewLuaInterface::setOnLinkClickedCallback(lua_State* L)
{
	WebView* view = checkWebView(L); //correct
	if (lua_isfunction(L, 2))
	{
		luaL_checktype(L, 2, LuaState::TYPE_FUNCTION);
		lua_pushvalue(L, 2);
		view->m_callback = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	else
		view->m_callback = -1;
	return 0;
}

int WebViewLuaInterface::setOnPageLoadedCallback(lua_State* L) //There's probably a better way to do this
{
	WebView* view = checkWebView(L); //correct
	if (lua_isfunction(L, 2))
	{
		luaL_checktype(L, 2, LuaState::TYPE_FUNCTION);
		lua_pushvalue(L, 2);
		view->m_func_ref = lua_ref(L, false);
	}
	else
		view->m_func_ref = -1;
	return 0;
}

int WebViewLuaInterface::allowCallsFromJavaScript(lua_State* L) //471
{
	WebView* view = checkWebView(L); //473 | correct

	const char* p = lua_tostring(L, 2); //475
	std::string ns = p; //476

	WebViewListener* listener = view->getListener(); //480
	WebViewLuaListener* luaObserver = (WebViewLuaListener*)listener; //481 | ?

	luaObserver->setJSCallNameSpace(ns); //484

	return 0;
}

WebView* WebViewLuaInterface::checkWebView(lua_State* L) //490
{
	return (WebView*)luaL_checkudata(L, 1, s_metaTableName); //?
}

}