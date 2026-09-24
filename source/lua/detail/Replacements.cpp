#include <lua/detail/Replacements.h>
#include <ctime>
#include <string.h>

namespace lua //Originally in root of detail, moved according to ABC_CHN
{
	namespace detail
	{
		int getboolfield(lua_State* L, const char* key)
		{
			int res;
			lua_getfield(L, -1, key);
			if (lua_type(L, -1))
				res = lua_toboolean(L, -1);
			lua_settop(L, -2);
			return res;
		}
		int getfield(lua_State* L, const char* key, int d = 0)
		{
			int res;
			lua_getfield(L, -1, key);
			if (lua_isnumber(L, -1))
				res = lua_tointeger(L, -1);
			else
			{
				res = d;
				if (d < 0)
					luaL_error(L, "field '%s', missing in date table", key);
			}
			lua_settop(L, -2);
			return res;
		}
		void setboolfield(lua_State* L, const char* key, int value)
		{
			lua_pushboolean(L, value);
			lua_setfield(L, -2, key);
		}
		void setfield(lua_State* L, const char* key, int value)
		{
			lua_pushinteger(L, value);
			lua_setfield(L, -2, key);
		}
		static int os_date(lua_State* L)
		{
			const char* s = luaL_optlstring(L, 1, "%c", 0);
			time_t t = lua_type(L, 2) ? time(0) : (time_t)luaL_checknumber(L, 2);
			tm* stm;
			if (*s == '!')
			{
				stm = gmtime(&t);
				s++;
			}
			else
				stm = localtime(&t);
			if (stm)
			{
				if (!strcmp(s, "*t"))
				{
					lua_createtable(L, 0, 9);
					setfield(L, "sec", stm->tm_sec);
					setfield(L, "min", stm->tm_min);
					setfield(L, "hour", stm->tm_hour);
					setfield(L, "day", stm->tm_mday);
					setfield(L, "month", stm->tm_mon + 1);
					setfield(L, "year", stm->tm_year + 1900);
					setfield(L, "wday", stm->tm_wday + 1);
					setfield(L, "yday", stm->tm_yday + 1);
					if (stm->tm_isdst) setboolfield(L, "tm_isdst", stm->tm_isdst);
				}
				/*else //TODO
				{
					char cc[];
					luaL_Buffer b;
					luaL_buffinit(L, &b);
					size_t reslen;
					char buff[];

					luaL_addlstring(&b, s, sizeof(stm));

					luaL_prepbuffer(&b)

					luaL_pushresult(&b);
				}*/
			}
			else
			{
				lua_pushnil(L);
			}
			return 1;
		}
		static int os_time(lua_State* L)
		{
			time_t t;

			if (lua_type(L, 1) <= 0)
			{
				t = time(0);
			}
			else
			{
				tm ts;

				ts.tm_sec = getfield(L, "sec");
				ts.tm_min = getfield(L, "min");
				ts.tm_hour = getfield(L, "hour");
				ts.tm_mday = getfield(L, "day", -1);
				ts.tm_mon = getfield(L, "month" , -1) - 1;
				ts.tm_year = getfield(L, "year") - 1900;
				ts.tm_isdst = getboolfield(L, "isdst");

				t = mktime(&ts);
			}
			t == -1 ? lua_pushnil(L) : lua_pushnumber(L, (time_t)t);
			return 1;
		}

		static int os_difftime(lua_State* L)
		{
			lua_pushnumber(L, difftime((time_t)luaL_checknumber(L, 1), (time_t)luaL_optnumber(L, 2, 0.0)));
			return 1;
		}

		static int os_clock(lua_State* L)
		{
			lua_pushnumber(L, clock() / 1000000.0);
			return 1;
		}		

		static const luaL_reg syslib[] = {
			{"clock", os_clock},
			{"date", os_date},
			{"difftime", os_difftime},
			{"time", os_time},
			{0, 0}
		};

		static int luaopen_os(lua_State* L)
		{
			luaL_register(L, "os", syslib);
			return 1;
		}
	}
}