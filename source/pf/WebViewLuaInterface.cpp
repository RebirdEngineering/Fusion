#include <pf/WebViewLuaInterface.h>
#include <pf/WebView.h>
#include <external/lua/src/lauxlib.h>
#include <lang/Log.h>
#include <lang/String.h>

using namespace lua;

namespace pf
{

class WebViewLuaListener : public WebViewListener //12 | Originally in lua in ABC <3.1.2, Friends (Fusion) <1.1.0, ABR <1.6.1, ABS <3.3.0, ABSP <1.5.2, ABSW <1.2.2 and Croods <1.1.0
{
public:
	const char* s_tableName = "WebView";
	const char* s_metaTableName = "rovio.webview";

	WebViewLuaListener(WebView* webView, lua_State* lua) //15
	{
		mNameSpaceForJSCalls = "";
	}

	void onWebViewPageLoaded(bool success, const std::string& pageTitle, WebView& webView) //20
	{
		if (webView.m_func_ref == -1)
		{
			const char* title = pageTitle.c_str(); //24

			lua_State* L = mLuaState; //26

			lua_getref(L, webView.m_callback); //28
			lua_pushlightuserdata(L, &webView); //29
			lua_pushboolean(L, success); //30
			lua_pushstring(L, title); //31

			if (lua_pcall(L, 3, 0, 0))
			{
				const char* error = lua_tostring(L, -1); //35
				LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //36 on ABS410, 38 on ABS 311 OSX, Space 1.4.0 and ABC 300+301 OSX
			}
		}
	}

	LinkClickedResult onWebViewLinkClicked(const std::string& url, WebView& webView) //41 | Correct?
	{
		if (webView.m_callback == -1)
			return LOAD_PAGE_INTO_WEBVIEW;

		const char* url_s = url.c_str(); //47
		int len = url.size(); //48

		lua_State* L = mLuaState; //50

		lua_getref(L, webView.m_callback); //52
		lua_pushlightuserdata(L, &webView); //53
		lua_pushlstring(L, url_s, len); //54

		int status = lua_pcall(L, 2, 2, 0); //56
		if (status)
		{
			const char* error = lua_tolstring(L, -1, 0); //59
			lua_settop(L, -2); //60
			LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //61, 70 on ABC 300+301 OSX
			return LOAD_PAGE_INTO_WEBVIEW;
		}

		ptrdiff_t returnCode = lua_tointeger(L, -1); //65
		lua_settop(L, -2); //66

		if (returnCode >= LOAD_PAGE_INTO_EXTERNAL_BROWSER)
		{
			LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Unknown return code from onLinkClicked()"); //80, legacy name?, 89 on ABC 300+301 OSX
			return LOAD_PAGE_INTO_WEBVIEW;
		}
		return (LinkClickedResult)returnCode;
	}

	void onWebViewCallFromJavaScript(const std::string& message, WebView& webView) //90 | Correct?
	{
		if (mNameSpaceForJSCalls.empty()) //92
			return;

		std::vector<std::string> ns = lang::string::split(mNameSpaceForJSCalls, "."); //97

		CallDescription cd = parseCall(message); //99

		if (cd.success)
		{
			lua_State* L = mLuaState; //103

			for (size_t i = 0; i < ns.size(); i++) //106
			{
				if (!ns[i].empty()) //108
					lua_getglobal(L, ns[i].c_str()); //111
				else
					lua_getfield(L, -1, ""); //115
			}

			lua_getfield(L, -1, cd.functionName.c_str()); //121

			for (size_t i = 0; i < cd.arguments.size(); i++) //124
			{
				const char* s_ptr = cd.arguments[i].c_str(); //126

				if (cd.argumentIsNumber[i]) //128
				{
					lua_Number n = atof(s_ptr); //130
					lua_pushnumber(L, n); //131
				}

				else
					lua_pushstring(L, s_ptr); //135
			}

			int argument_count = lua_pcall(L, cd.arguments.size(), 0, 0); //140
			const int return_value_count = 0; //141

			if (argument_count == return_value_count)
			{
				const char* error = lua_tostring(L, -1); //145
				lua_settop(L, -2); //146
				LANG_LOG("WebView Lua", LANG_LOG_PRIORITY_ERROR, "Error: %s", error); //147 (156 on ABS 3.1.0 [AND] + ABSpace 1.4.0 [And] + ABS 311 OSX+ABR 1.5.0 [And], 149 in Croods + ABF 1.0.0-1.6.1 AND, 156 in ABC 300+301 OSX)
			}
		}
	}

	void setJSCallNameSpace(const std::string& ns) //152
	{
		mNameSpaceForJSCalls = ns;
	}

private:
	WebView* m_webView; //158
	lua_State* mLuaState; //159 | Broke the naming convention?
	std::string mNameSpaceForJSCalls; //160

	struct CallDescription //167
	{
		bool success; //169
		std::string functionName; //170
		std::vector<std::string> arguments; //171
		std::vector<bool> argumentIsNumber; //172
	};

	CallDescription parseCall(const std::string& s) //175 | TODO
	{
		/*CallDescription cd; //?
		if (s.find("(") != -1) //178
			return;

		//cd.functionName;

		//.empty() //186

		size_t pos2; //188

		//.size() //190

		//pos2 = s.find('(');
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

			[] //215

			[] //222
		}	
		*/
		return CallDescription();
	}
};

WebViewLuaInterface::WebViewLuaInterface(LuaState* lua) : //236
	LuaObject(lua),
	mLuaState(lua)
{
	static bool initialized = false; //240 | It's local var soooo static?

	if (WebView::isSupported() && !initialized) //242 |TODO?
	{
		const luaL_Reg webView_f[] = //244
		{
			{ "new", create },
			{ 0, 0 }
		};

		const luaL_Reg webView_m[] = //250
		{
			{ "delete", destroy },
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

		lua_State* L = lua->impl(); //268

		luaL_newmetatable(L, s_metaTableName); //270

		lua_pushvalue(L, -1); //272
		lua_setfield(L, -2, "__index"); //273

		luaL_register(L, 0, webView_m); //275
		luaL_register(L, s_tableName, webView_f); //276

		lua_settop(L, -3); //278

		lua_getglobal(L, s_tableName); //281

		lua_pushstring(L, "0"); //283
		lua_setfield(L, -2, "DONT_LOAD_PAGE"); //284

		lua_pushstring(L, "1"); //286
		lua_setfield(L, -2, "LOAD_PAGE_INTO_WEBVIEW"); //287

		lua_pushstring(L, "2"); //289
		lua_setfield(L, -2, "LOAD_PAGE_INTO_EXTERNAL_BROWSER"); //290

		lua_settop(L, -2); //292

		s_instance = this; //294

		initialized = true;
	}
}

WebViewLuaInterface::~WebViewLuaInterface() //301-303
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
	view->setListener(listener); //315

	lua_pushlightuserdata(L, view); //317

	lua_getfield(L, LUA_REGISTRYINDEX, s_metaTableName); //319
	lua_setmetatable(L, -2); //320

	return 1; //322
}

int WebViewLuaInterface::destroy(lua_State* L) //325
{
	WebView* view = checkWebView(L); //327

	view->m_func_ref = -1;
	view->m_callback = -1;

	return 0;
}

int WebViewLuaInterface::loadPage(lua_State* L) //338
{
	WebView* view = checkWebView(L); //340

	const char* p = lua_tostring(L, 2); //342
	std::string url = p; //343

	view->loadUrl(url); //345

	return 0;
}

int WebViewLuaInterface::loadLocalPage(lua_State* L) //350
{
	WebView* view = checkWebView(L); //352

	const char* p = lua_tostring(L, 2); //354
	const std::string filename = p; //355
	view->loadLocalUrl(filename); //356

	return 0;
}

int WebViewLuaInterface::reloadPage(lua_State* L) //361
{
	WebView* view = checkWebView(L); //363
	view->reload(); //364

	return 0;
}

int WebViewLuaInterface::show(lua_State* L) //369
{
	WebView* view = checkWebView(L); //371
	view->show(); //372

	return 0;
}

int WebViewLuaInterface::hide(lua_State* L) //377
{
	WebView* view = checkWebView(L); //379
	view->hide(); //380

	return 0;
}

int WebViewLuaInterface::setPosition(lua_State* L) //385
{
	WebView* view = checkWebView(L); //387
	view->setPosition(lua_tointeger(L, 2), lua_tointeger(L, 3)); //388

	return 0;
}

int WebViewLuaInterface::setSize(lua_State* L) //393
{
	WebView* view = checkWebView(L); //395
	view->setSize(lua_tointeger(L, 2), lua_tointeger(L, 3)); //396

	return 0;
}

int WebViewLuaInterface::executeJavaScript(lua_State* L) //401
{
	WebView* view = checkWebView(L); //403

	const char* p = lua_tostring(L, 2); //405
	std::string javaScript = p; //406

	std::string* result = view->executeJavaScript(javaScript); //408

	if (result)
		lua_pushstring(L, result->c_str()); //412

	else
		lua_pushstring(L, ""); //417

	return 1;
}

int WebViewLuaInterface::asyncExecuteJavaScript(lua_State* L) //423
{
	WebView* view = checkWebView(L); //425

	const char* p = lua_tostring(L, 2); //427
	std::string javaScript = p; //428
	
	view->asyncExecuteJavaScript(p); //430

	return 0;
}

int WebViewLuaInterface::setOnLinkClickedCallback(lua_State* L) //435
{
	WebView* view = checkWebView(L); //437

	if (lua_isfunction(L, 2)) //439
	{
		luaL_checktype(L, 2, LUA_TFUNCTION); //441
		lua_pushvalue(L, 2); //442
		view->m_callback = luaL_ref(L, LUA_REGISTRYINDEX); //443
	}

	else
		view->m_callback = -1;

	return 0;
}

int WebViewLuaInterface::setOnPageLoadedCallback(lua_State* L) //453
{
	WebView* view = checkWebView(L); //455

	if (lua_isfunction(L, 2)) //457
	{
		luaL_checktype(L, 2, LUA_TFUNCTION); //459
		lua_pushvalue(L, 2); //460
		view->m_func_ref = lua_ref(L, false); //461
	}

	else
		view->m_func_ref = -1;

	return 0;
}

int WebViewLuaInterface::allowCallsFromJavaScript(lua_State* L) //471
{
	WebView* view = checkWebView(L); //473

	const char* p = lua_tostring(L, 2); //475
	std::string ns = p; //476

	WebViewListener* listener = view->getListener(); //480
	WebViewLuaListener* luaObserver = (WebViewLuaListener*)listener; //481

	luaObserver->setJSCallNameSpace(ns); //484

	return 0;
}

WebView* WebViewLuaInterface::checkWebView(lua_State* L) //490
{
	return (WebView*)luaL_checkudata(L, 1, s_metaTableName); //492
}

}