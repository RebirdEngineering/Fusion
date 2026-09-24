template <typename A1> void LuaFunction::operator()(const A1& a1) //2 | const char[]&, const int&
{
	std::enable_if<(std::is_integral<A1>::value) || (std::is_floating_point<A1>::value), void>::type lua::LuaState::pushValue<A1>(A1); //5
}

template <class A1, typename A2> void LuaFunction::operator()(const A1& a1, const A2& a2) //10
{
	//TODO
	LuaState::pushValue(LuaFunction(a1)); //13
	LuaState::pushValue(LuaFunction(a2)); //14
}