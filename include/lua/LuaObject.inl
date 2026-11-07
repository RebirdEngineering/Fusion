template <class V> void getValue( LuaState* luastate, int index, V& v ) //1
{
	luastate->toValue( index, v ); //3
}

template <class V> void getValue( LuaState* luastate, int index, V*& v ) //Not on iOS.
{
	LuaTable* tab = LuaState::getThisPtr( luastate->impl(), index );
	v = dynamic_cast<V*>(tab);
	if ( 0 == v )
		luastate->incorrectType( index );
}

template <class V> int pushValue( LuaState* luastate, const V& v ) //14
{
	luastate->pushValue( v ); //16
	return 1;
}

template <class R> class ReturnValue //21
{
public:
	template <class T> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)() ) //25
	{
		return pushValue( luastate, (thisptr->*funcptr)() ); //27
	}

	template <class T, class A1> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1) )
	{
		A1 a1; getValue(luastate,1,a1);
		return pushValue( luastate, (thisptr->*funcptr)( a1 ) );
	}

	template <class T, class A1, class A2> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2) )
	{
		A1 a1; getValue(luastate,1,a1); //40
		A2 a2; getValue(luastate,2,a2); //41
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2 ) ); //42
	}

	template <class T, class A1, class A2, class A3> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3 ) );
	}

	template <class T, class A1, class A2, class A3, class A4> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4, a5 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		A6 a6; getValue(luastate,6,a6);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4, a5, a6 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		A6 a6; getValue(luastate,6,a6);
		A7 a7; getValue(luastate,7,a7);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		A6 a6; getValue(luastate,6,a6);
		A7 a7; getValue(luastate,7,a7);
		A8 a8; getValue(luastate,8,a8);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7, a8 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> static int
		callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		A6 a6; getValue(luastate,6,a6);
		A7 a7; getValue(luastate,7,a7);
		A8 a8; getValue(luastate,8,a8);
		A9 a9; getValue(luastate,9,a9);
		return pushValue( luastate, (thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7, a8, a9 ) );
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> static int
		callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10))
	{
		A1 a1; getValue(luastate, 1, a1);
		A2 a2; getValue(luastate, 2, a2);
		A3 a3; getValue(luastate, 3, a3);
		A4 a4; getValue(luastate, 4, a4);
		A5 a5; getValue(luastate, 5, a5);
		A6 a6; getValue(luastate, 6, a6);
		A7 a7; getValue(luastate, 7, a7);
		A8 a8; getValue(luastate, 8, a8);
		A9 a9; getValue(luastate, 9, a9);
		A10 a10; getValue(luastate, 10, a10);
		return pushValue(luastate, (thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> static int
		callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11))
	{
		A1 a1; getValue(luastate, 1, a1);
		A2 a2; getValue(luastate, 2, a2);
		A3 a3; getValue(luastate, 3, a3);
		A4 a4; getValue(luastate, 4, a4);
		A5 a5; getValue(luastate, 5, a5);
		A6 a6; getValue(luastate, 6, a6);
		A7 a7; getValue(luastate, 7, a7);
		A8 a8; getValue(luastate, 8, a8);
		A9 a9; getValue(luastate, 9, a9);
		A10 a10; getValue(luastate, 10, a10);
		A11 a11; getValue(luastate, 11, a11);
		return pushValue(luastate, (thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> static int
		callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12))
	{
		A1 a1; getValue(luastate, 1, a1);
		A2 a2; getValue(luastate, 2, a2);
		A3 a3; getValue(luastate, 3, a3);
		A4 a4; getValue(luastate, 4, a4);
		A5 a5; getValue(luastate, 5, a5);
		A6 a6; getValue(luastate, 6, a6);
		A7 a7; getValue(luastate, 7, a7);
		A8 a8; getValue(luastate, 8, a8);
		A9 a9; getValue(luastate, 9, a9);
		A10 a10; getValue(luastate, 10, a10);
		A11 a11; getValue(luastate, 11, a11);
		A12 a12; getValue(luastate, 12, a12);
		return pushValue(luastate, (thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
	}
};

template <> class ReturnValue<void> //182
{
public:
	template <class T> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)() ) //186
	{
		(thisptr->*funcptr)(); return 0;
	}

	template <class T, class A1> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1) ) //192
	{
		A1 a1; getValue(luastate,1,a1); //194
		(thisptr->*funcptr)( a1 ); return 0;
	}

	template <class T, class A1, class A2> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2) ) //199
	{
		A1 a1; getValue(luastate,1,a1); //201
		A2 a2; getValue(luastate,2,a2); //202
		(thisptr->*funcptr)( a1, a2 ); return 0;
	}

	template <class T, class A1, class A2, class A3> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3) ) //207
	{
		A1 a1; getValue(luastate,1,a1); //209
		A2 a2; getValue(luastate,2,a2); //210
		A3 a3; getValue(luastate,3,a3); //211
		(thisptr->*funcptr)( a1, a2, a3 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4) ) //216
	{
		A1 a1; getValue(luastate,1,a1); //218
		A2 a2; getValue(luastate,2,a2); //219
		A3 a3; getValue(luastate,3,a3); //220
		A4 a4; getValue(luastate,4,a4); //221
		(thisptr->*funcptr)( a1, a2, a3, a4 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4,A5) ) //226
	{
		A1 a1; getValue(luastate,1,a1); //228
		A2 a2; getValue(luastate,2,a2); //229
		A3 a3; getValue(luastate,3,a3); //230
		A4 a4; getValue(luastate,4,a4); //231
		A5 a5; getValue(luastate,5,a5); //232
		(thisptr->*funcptr)( a1, a2, a3, a4, a5 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4,A5,A6) ) //237
	{
		A1 a1; getValue(luastate,1,a1); //239
		A2 a2; getValue(luastate,2,a2); //240
		A3 a3; getValue(luastate,3,a3); //241
		A4 a4; getValue(luastate,4,a4); //242
		A5 a5; getValue(luastate,5,a5); //243
		A6 a6; getValue(luastate,6,a6); //244
		(thisptr->*funcptr)( a1, a2, a3, a4, a5, a6 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7) ) //249
	{
		A1 a1; getValue(luastate,1,a1); //251
		A2 a2; getValue(luastate,2,a2); //252
		A3 a3; getValue(luastate,3,a3); //253
		A4 a4; getValue(luastate,4,a4); //254
		A5 a5; getValue(luastate,5,a5); //255
		A6 a6; getValue(luastate,6,a6); //256
		A7 a7; getValue(luastate,7,a7); //257
		(thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8) )
	{
		A1 a1; getValue(luastate,1,a1);
		A2 a2; getValue(luastate,2,a2);
		A3 a3; getValue(luastate,3,a3);
		A4 a4; getValue(luastate,4,a4);
		A5 a5; getValue(luastate,5,a5);
		A6 a6; getValue(luastate,6,a6);
		A7 a7; getValue(luastate,7,a7);
		A8 a8; getValue(luastate,8,a8);
		(thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7, a8 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> static int
		callMethod( LuaState* luastate, T* thisptr, void (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9) ) //276
	{
		A1 a1; getValue(luastate,1,a1); //278
		A2 a2; getValue(luastate,2,a2); //279
		A3 a3; getValue(luastate,3,a3); //280
		A4 a4; getValue(luastate,4,a4); //281
		A5 a5; getValue(luastate,5,a5); //282
		A6 a6; getValue(luastate,6,a6); //283
		A7 a7; getValue(luastate,7,a7); //284
		A8 a8; getValue(luastate,8,a8); //285
		A9 a9; getValue(luastate,9,a9); //286
		(thisptr->*funcptr)( a1, a2, a3, a4, a5, a6, a7, a8, a9 ); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> static int
		callMethod(LuaState* luastate, T* thisptr, void (T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) //291
	{
		A1 a1; getValue(luastate, 1, a1); //294
		A2 a2; getValue(luastate, 2, a2); //295
		A3 a3; getValue(luastate, 3, a3); //296
		A4 a4; getValue(luastate, 4, a4); //297
		A5 a5; getValue(luastate, 5, a5); //298
		A6 a6; getValue(luastate, 6, a6); //299
		A7 a7; getValue(luastate, 7, a7); //300
		A8 a8; getValue(luastate, 8, a8); //301
		A9 a9; getValue(luastate, 9, a9); //302
		A10 a10; getValue(luastate, 10, a10); //303
		(thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> static int
		callMethod(LuaState* luastate, T* thisptr, void (T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) //307
	{
		A1 a1; getValue(luastate, 1, a1);
		A2 a2; getValue(luastate, 2, a2);
		A3 a3; getValue(luastate, 3, a3);
		A4 a4; getValue(luastate, 4, a4);
		A5 a5; getValue(luastate, 5, a5);
		A6 a6; getValue(luastate, 6, a6);
		A7 a7; getValue(luastate, 7, a7);
		A8 a8; getValue(luastate, 8, a8);
		A9 a9; getValue(luastate, 9, a9);
		A10 a10; getValue(luastate, 10, a10);
		A11 a11; getValue(luastate, 11, a11);
		(thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11); return 0;
	}

	template <class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> static int
		callMethod(LuaState* luastate, T* thisptr, void (T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) //324
	{
		A1 a1; getValue(luastate, 1, a1);
		A2 a2; getValue(luastate, 2, a2);
		A3 a3; getValue(luastate, 3, a3);
		A4 a4; getValue(luastate, 4, a4);
		A5 a5; getValue(luastate, 5, a5);
		A6 a6; getValue(luastate, 6, a6);
		A7 a7; getValue(luastate, 7, a7);
		A8 a8; getValue(luastate, 8, a8);
		A9 a9; getValue(luastate, 9, a9);
		A10 a10; getValue(luastate, 10, a10);
		A11 a11; getValue(luastate, 11, a11);
		A12 a12; getValue(luastate, 12, a12);
		(thisptr->*funcptr)(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); return 0;
	}
};

template <class R, class T> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)() ) //343
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr ); //345
}

template <class R, class T, class A1> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1) ) //349
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2) ) //355
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3) ) //361
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4) ) //367
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5) ) //373
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6) ) //379
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7) ) //385
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8) )
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> int
	callMethod( LuaState* luastate, T* thisptr, R (T::*funcptr)(A1,A2,A3,A4,A5,A6,A7,A8,A9) ) //397
{
	return ReturnValue<R>::callMethod( luastate, thisptr, funcptr );
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> int
	callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)) //403
{
	return ReturnValue<R>::callMethod(luastate, thisptr, funcptr);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> int
	callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)) //409
{
	return ReturnValue<R>::callMethod(luastate, thisptr, funcptr);
}

template <class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> int
	callMethod(LuaState* luastate, T* thisptr, R(T::* funcptr)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)) //415
{
	return ReturnValue<R>::callMethod(luastate, thisptr, funcptr);
}

template <typename T, typename F> class LuaRawMethodDispatcher //421
{
public:
	static int dispatch( lua_State* impl ) //424
	{
		LuaState* luastate; //426
		LuaFunctor lf; //427
		LuaState::getDispatchData( impl, &luastate, &lf );
		return callMethod( luastate, static_cast<T*>(lf.obj), *reinterpret_cast<F*>(lf.func) ); //429
	}
};

template <typename T, typename F> void
	LuaObject::registerMethod( const char* name, T* obj, F func ) //434
{
	LuaFunctor lf;
	assert( sizeof(F) <= sizeof(lf.func) );
	lf.obj = obj;
	for ( int i = 0 ; i < int(sizeof(F)) ; ++i )
		lf.func[i] = reinterpret_cast<const char*>(&func)[i];
	registerClosure( name, &lf, LuaRawMethodDispatcher<T,F>::dispatch );
}

template <class T> void	
	LuaObject::registerLuaMethod( const char* name, T* obj, int (T::*func)(LuaState*) ) //445
{
	assert( func != 0 && obj != 0 ); //447 in ABC 3.0.1 OSX
	LuaState* luastate = luaState(); //448
	LuaStackRestore lsr( luastate );
	luastate->pushTable( this ); //450
	luastate->pushString( name );
	luastate->pushMethodClosure( obj, func );
	assert( !luastate->isNil(-1) ); //453 in ABC 3.0.1 OSX
	luastate->setTable( -3 );
}

template <class A1> void LuaObject::call( const char* name, A1 a1 ) //458
{
	LuaState* luastate = luaState(); //460
	LuaStackRestore lsr( luastate ); //461
	pushMember( name );
	pushValue( luastate, a1 ); //463
	luastate->call( 1, 0 );
}

template <class A1, class A2> void LuaObject::call( const char* name, A1 a1, A2 a2 ) //468
{
	LuaState* luastate = luaState(); //470
	LuaStackRestore lsr( luastate ); //471
	pushMember( name );
	pushValue( luastate, a1 ); //473
	pushValue( luastate, a2 ); //474
	luastate->call( 2, 0 );
}

template <class A1, class A2, class A3> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3 ) //479
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr( luastate );
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	luastate->call( 3, 0 );
}

template <class A1, class A2, class A3, class A4> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4 )
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr( luastate );
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	luastate->call( 4, 0 );
}

template <class A1, class A2, class A3, class A4, class A5> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) //491
{
	LuaState* luastate = luaState(); //493
	LuaStackRestore lsr( luastate ); //494
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	pushValue( luastate, a5 );
	luastate->call( 5, 0 );
}

template <class A1, class A2, class A3, class A4, class A5, class A6> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 )
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr( luastate );
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	pushValue( luastate, a5 );
	pushValue( luastate, a6 );
	luastate->call( 6, 0 );
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 )
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr( luastate );
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	pushValue( luastate, a5 );
	pushValue( luastate, a6 );
	pushValue( luastate, a7 );
	luastate->call( 7, 0 );
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) //549
{
	LuaState* luastate = luaState(); //551
	LuaStackRestore lsr( luastate ); //552
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	pushValue( luastate, a5 );
	pushValue( luastate, a6 );
	pushValue( luastate, a7 );
	pushValue( luastate, a8 );
	luastate->call( 8, 0 );
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> void LuaObject::call( const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9 )
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr( luastate );
	pushMember( name );
	pushValue( luastate, a1 );
	pushValue( luastate, a2 );
	pushValue( luastate, a3 );
	pushValue( luastate, a4 );
	pushValue( luastate, a5 );
	pushValue( luastate, a6 );
	pushValue( luastate, a7 );
	pushValue( luastate, a8 );
	pushValue( luastate, a9 );
	luastate->call( 9, 0 );
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10> void LuaObject::call(const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr(luastate);
	pushMember(name);
	pushValue(luastate, a1);
	pushValue(luastate, a2);
	pushValue(luastate, a3);
	pushValue(luastate, a4);
	pushValue(luastate, a5);
	pushValue(luastate, a6);
	pushValue(luastate, a7);
	pushValue(luastate, a8);
	pushValue(luastate, a9);
	pushValue(luastate, a10);
	luastate->call(10, 0);
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11> void LuaObject::call(const char*name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11)
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr(luastate);
	pushMember(name);
	pushValue(luastate, a1);
	pushValue(luastate, a2);
	pushValue(luastate, a3);
	pushValue(luastate, a4);
	pushValue(luastate, a5);
	pushValue(luastate, a6);
	pushValue(luastate, a7);
	pushValue(luastate, a8);
	pushValue(luastate, a9);
	pushValue(luastate, a10);
	pushValue(luastate, a11);
	luastate->call(11, 0);
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12> void LuaObject::call(const char* name, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12)
{
	LuaState* luastate = luaState();
	LuaStackRestore lsr(luastate);
	pushMember(name);
	pushValue(luastate, a1);
	pushValue(luastate, a2);
	pushValue(luastate, a3);
	pushValue(luastate, a4);
	pushValue(luastate, a5);
	pushValue(luastate, a6);
	pushValue(luastate, a7);
	pushValue(luastate, a8);
	pushValue(luastate, a9);
	pushValue(luastate, a10);
	pushValue(luastate, a11);
	pushValue(luastate, a12);
	luastate->call(12, 0);
}

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
