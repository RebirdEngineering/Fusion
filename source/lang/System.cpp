#include <lang/System.h>
#include <lang/pp.h>

#ifdef PLATFORM_WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <mmsystem.h>
	#pragma comment( lib, "winmm" )
#endif

#ifdef PLATFORM_WINCE
	#include <windows.h>
	#include <mmsystem.h>
	#pragma comment( lib, "Mmtimer.lib" )
#endif

#ifdef PLATFORM_BREW
	#include <AEEStdLib.h>
#endif

#include <time.h>


BEGIN_NAMESPACE(lang) 


int System::currentTimeMillis()
{
#ifdef PLATFORM_WIN32

	LARGE_INTEGER freq;
	if ( QueryPerformanceFrequency(&freq) )
	{
		LARGE_INTEGER cur;
		QueryPerformanceCounter( &cur );
		if ( freq.QuadPart >= 1000 )
		{
			__int64 msdiv = __int64(freq.QuadPart) / __int64(1000);
			__int64 c = __int64(cur.QuadPart) / msdiv;
			return (int)c;
		}
	}

	return (int)timeGetTime();

#elif defined(PLATFORM_WINCE)

	return (int)timeGetTime();
    
//Add iOS
    
#elif defined(PLATFORM_IOS)
	const int64_t kOneMillion = 1000000;
	static mach_timebase_info_data_t s_timebase_info;
	if (!s_timebase_info.denom)
		mach_timebase_info(mach_timebase_info);
	return s_timebase_info.number * mach_absolute_time() / (kOneMillion)*s_timebase_info.denom;

#elif defined(PLATFORM_PS2)
	
	#warning System::currentTimeMillis not defined on PS2 (returns 0)
	return 0;

#elif defined(PLATFORM_SYMBIAN)
	
	#warning System::currentTimeMillis not defined on Symbian (returns 0)
	return 0;

#elif defined(PLATFORM_BREW)
	
	return GETTIMEMS();

#endif
}

int64_t System::currentTimeMicros()
{
#if defined(PLATFORM_IOS)
	const int64_t kOneThousand = 1000;
	static mach_timebase_info_data_t s_timebase_info;
	if (!s_timebase_info.denom)
		mach_timebase_info(mach_timebase_info);
	return s_timebase_info.number * mach_absolute_time() / (kOneThousand)*s_timebase_info.denom;
#else
	return 0;
#endif
}


END_NAMESPACE() // lang

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
