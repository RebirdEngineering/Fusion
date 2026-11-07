class LuaFunctor //1
{
public:
	void*	obj; //5

	char	func[8]; //8
};

template <typename T> class LuaStateMethodDispatcher //12
{
public:
	typedef int (T::*LuaStateMethod_t)( LuaState* ); //15

	static int dispatch( lua_State* impl ) //17
	{
		LuaState* luastate; //19
		LuaFunctor lf; //20
		LuaState::getDispatchData( impl, &luastate, &lf );
		LuaStateMethod_t func = *reinterpret_cast<LuaStateMethod_t*>(lf.func); //22
		return (static_cast<T*>(lf.obj)->*func)( luastate );
	}
};

template <class T> void LuaState::pushMethodClosure( T* obj, int (T::*func)(LuaState*) ) //28
{
	LuaFunctor lf;
	assert( sizeof(func) <= sizeof(lf.func) );
	lf.obj = obj;
	for ( int i = 0 ; i < int(sizeof(func)) ; ++i )
		lf.func[i] = reinterpret_cast<const char*>(&func)[i];

	// store data as light user data values
	void* const* data = reinterpret_cast<void* const*>(&lf); 
	const int datasize = int(sizeof(LuaFunctor)/sizeof(void*)); //38
	for ( int i = 0 ; i < datasize ; ++i )
		pushLightUserData( data[i] );
	pushCClosure( LuaStateMethodDispatcher<T>::dispatch, datasize );
}

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
