
template <class A1> void LuaFunction::operator()(A1 a1) //2 | const char[]&, const int&
{
	LuaState::pushValue(a1); //5
}

template <class A1, typename A2> void LuaFunction::operator()(A1 a1, A2 a2) //10 //TODO
{
	LuaState::pushValue(a1); //13
	LuaState::pushValue(a2); //14
}