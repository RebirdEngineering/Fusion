#include <io/PathName.h>
#include <gr/Context.h> //We don't include renderer contexts since WinMain loads it from gr*.dll
#include <gr/GraphicsException.h>
#include <lang/System.h>
#include <lang/Exception.h>
#include <framework/App.h>
#include <pf/TextInput.h>
#include <framework/VisualStudioLogger.h>

#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <shlobj.h>
#include <io.h>
#include <xinput.h>

using namespace io;
using namespace gr;
using namespace lang;
using namespace lua;
using namespace pf;
using namespace framework;


class OSWin32 : //Not in framework namespace?
	public OSInterface
{
public:
	void							loadShaders(const std::string& path, bool recursesubdirs);
	std::string						getDefaultDataPath();
	void							setResolution(int width, int height);
	void							setOrientation(gr::Context::OrientationType orientation); //5350F0
	void							allowSleep(bool allow);
	bool							isSilentProfile();
	void							startUpdate(); //534F30
	void							stopUpdate(); //534F70
	void							setFullscreen(bool fullscreen);
	bool							isFullscreen() const;
	bool							captureMouse(bool capture);
	bool							isMouseCaptured() const;
	bool							setMousePosition(int x, int y);
	void							setCursor(const std::string& cursor);

private:
	std::string m_defaultDataPath; //Taken from iOS
};

static const int s_keyToVk[] = //575608
{
	0,
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
	VK_NEXT,
	VK_PRIOR,
	VK_HOME,
	VK_END,
	VK_INSERT,
	VK_DELETE,
	VK_RETURN,
	VK_SHIFT,
	VK_CONTROL,
	VK_TAB,
	VK_SPACE,
	VK_BACK,
	VK_PAUSE,
	VK_ESCAPE,
	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	0,
	0,
	0,
	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
	VK_MULTIPLY,
	VK_ADD,
	VK_SUBTRACT,
	VK_DIVIDE,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	VK_MENU,
	VK_OEM_MINUS,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

static std::string s_dataPath; //595448
static bool s_59AB9D; //59AB9D
//keyUp? 59AD0C
//? 59AD24 //?
static HWND							s_hwnd; //5B1930
static TRACKMOUSEEVENT s_5B1934; //5B1934
static HCURSOR s_5B1944; //5B1944
static RECT s_5B1948; //5B1948 Rect
//5B1CA8

static bool							s_captureMouse; //5B1958
static WINDOWPLACEMENT s_5B195C; //5B195C
static HDC s_5B1988; //5B1988 HDC
static wchar_t s_5B1990[256]; //5B1990


static bool							s_active			= false; //5B1B90
static bool							s_5B1B91			= false; //5B1B91
static bool							s_5B1B92			= false; //5B1B92
static bool							s_fullscreen			= false; //5B1B93
static bool							s_5B1B94			= false; //5B1B94
//5B1CC4
static std::map<std::string, HCURSOR> s_5B1CD8; //mouse related? Is this is a vector or map? 5B1CD8
//static bool s_5B1CDC;
//; Controller related? //5B1CE8
//; std::map? //5B1CEC
//; std::string? //5B1CF8
//; std::string? //5B1CFC
//; ? //5B1D00
//; ? //5B1D04
static P(Context)					s_context = 0; //5B1D08
//? 5B1D10
//static std::vector<XINPUT_STATE> s_5B1D0C; //5B1D0C
//? 5B1D1C //Controller related?
//? 5B1D20 //Controller related?
//? 5B1D2C //Controller related?
//? 5B1D30 //Controller related?
//? 5B1D34 //Controller related?
//? 5B1D3C //Controller related?
//? 5B1D40 //Controller related?
//? 5B1D44 //Controller related?
//? 5B1D48 //Controller related?
//? 5B1D50 //Controller related?
//? 5B1D54 //Controller related?
//? 5B1D58 //Controller related?
//? 5B1D5C //Controller related?
//? 5B1D64 //Controller related?
//? 5B1D68 //Controller related?
//? 5B1D6C //Controller related?
//? 5B1D70 //Controller related?
//? 5B1D78 //Controller related?
//? 5B1D7C //Controller related?
//? 5B1D80 //Controller related?
//? 5B1D84 //Controller related?
//? 5B1D8C //Controller related?
//? 5B1D90 //Controller related?


//std::vector?; //5B1C08
//ArgList?; //5B1C14 (surrogate pair p1)
static bool s_5B1C16; //5B1C16

static App::Configuration			s_config; //5B1C18 (Starts with string)
//5B1C34 s_config.width
//5B1C38 s_config.height
//5B1C48 ?
//5B1C4C ?
//? //5B1C50
//? //5B1C58
//?; //5B1C6C
//?; //5B1C70
//?; //5B1C80
//?; //5B1C8C
//?; //5B1C9C
//; //? renderers?
//; //?
//; s_config.singleton//5B1CD4

//Based off https://github.com/weolar/miniblink49/blob/master/content/browser/TouchStruct.h
typedef BOOL(__stdcall* PFN_RegisterTouchWindow)(HWND hwnd, ULONG ulFlags);
typedef BOOL(__stdcall* PFN_GetTouchInputInfo)(HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize);
typedef BOOL(__stdcall* PFN_CloseTouchInputHandle)(HTOUCHINPUT hTouchInput);
static PFN_RegisterTouchWindow s_registerTouchWindow; //5B1B98
static PFN_GetTouchInputInfo s_getTouchInputInfo; //5B1B9C
static PFN_CloseTouchInputHandle s_closeTouchInputHandle; //5B1BA0

//static controller related; //005B1BA4

//?; //5B1BA8
//?; //5B1BB4
//?; //5B1BB8
//?; //5B1BBC
//?; //5B1BC0
//?; //5B1BC4
//?; //5B1BC8
//?; //5B1BD8
//?; //5B1BD4
//?; //5B1BD8
//?; //5B1BDC
//?; //5B1BE0
//?; //5B1BE4
//?; //5B1BE8
//?; //5B1BF4
//?; //5B1BF8
//?; //5B1C04

/** Translates Win32 Virtual Key codes to KeyType. */
static App::KeyType translateVKCode( int vk ) //53BA30
{
	assert( sizeof(s_keyToVk)/sizeof(s_keyToVk[0]) == App::KEY_COUNT );

	if ( vk >= '1' && vk <= '9' || vk == '0' )
	{
		if ( vk >= '1' && vk <= '9' )
			return (App::KeyType)( App::KEY_1 + (vk - '1') );
		else
			return App::KEY_0;
	}

	for ( int i = 0 ; i < App::KEY_COUNT ; ++i )
	{
		if ( s_keyToVk[i] == vk )
			return (App::KeyType)i;
	}

	return App::KEY_COUNT;
}

/** Sets key state and signals application by calling keyDown/keyUp if state changed */
static void setKeyState( App* a, App::KeyType key, bool keydown ) //538CD0
{
	if ( a != 0 )
	{
		if ( keydown )
		{
			if (!a->isKeyDown(key)) //446720
			{
				a->keyDown(key);
				//sub_538110?
			}
		}
		else
		{
			a->keyUp( key );
			//sub_538110
		}
		a->setKeyDown( key, keydown ); //446700
	}
}

/*static void setWheelState( App* a, ? ) //UNOFFICIAL
{
	if ( a != 0 )
	{
		
	}
}*/

static LRESULT wndproc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp ) //538E50
{
	App* a = 0;
	if ( App::initialized() )
		a = App::get();

	switch ( msg ) //[LHR] I prefer it in order
	{

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_SETCURSOR:
		if (s_active)
		{
			SetCursor(s_captureMouse ? s_5B1944 : 0);
			return 1;
		}
		break;

	case WM_GETMINMAXINFO: //TODO
		/*RECT r;
		r.right = s_config.minWidth;
		r.bottom = s_config.minHeight;

		HWND hwnd;

		AdjustWindowRectEx(&r, GetWindowLongW(hwnd, GWL_STYLE), FALSE, GetWindowLongW(hwnd, GWL_EXSTYLE));*/
		break;
		
	case WM_WINDOWPOSCHANGING: //TODO
		/*if (s_active)
		{
			SetCursor(s_captureMouse ? s_5B1944 : 0);
			return TRUE;
		}

		DefWindowProcW(hwnd, msg, wp, lp);*/
		break;
		
	case WM_DISPLAYCHANGE: //TODO
		/*if (!(s_fullscreen || s_active || s_context || s_5B1B91))
			return 0;

		MONITORINFO mi;
		mi.cbSize = sizeof(MONITORINFO);
		
		HMONITOR m = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
		if (!GetMonitorInfoW(m, &mi))
			return 0;

		int monX = mi.rcMonitor.left;
		int monY = mi.rcMonitor.top;
		int monCX = mi.rcMonitor.right - monX;
		int monCY = mi.rcMonitor.bottom - monY;

		SetWindowPos(hwnd, HWND_TOP, monX, monY, monCX, monCX, SWP_NOOWNERZORDER | SWP_NOCOPYBITS| SWP_NOACTIVATE | SWP_NOZORDER);
		s_5B1948 = mi.rcMonitor;
		ClipCursor(&s_5B1948);*/
		return FALSE;

	case WM_LBUTTONDOWN:
		setKeyState( a, App::KEY_LBUTTON, true );
		break;

	case WM_LBUTTONUP:
		setKeyState( a, App::KEY_LBUTTON, false );
		break;

	case WM_MBUTTONDOWN:
		setKeyState( a, App::KEY_MBUTTON, true );
		break;

	case WM_MBUTTONUP:
		setKeyState( a, App::KEY_MBUTTON, false );
		break;

	case WM_RBUTTONDOWN:
		setKeyState( a, App::KEY_RBUTTON, true );
		break;

	case WM_RBUTTONUP:
		setKeyState( a, App::KEY_RBUTTON, false );
		break;

	case WM_MOUSEWHEEL:
		//setWheelState( a );
		break;

	case WM_DROPFILES:
	{
		int files = DragQueryFileW((HDROP)wp, -1, 0, 0);
		wchar_t szF[MAX_PATH];

		for (int i = 0; i < files; i++)
		{
			DragQueryFileW((HDROP)wp, i, szF, sizeof(szF) / 2);

		}

		break;
	}

	case WM_TOUCH: //TODO
	{
		/*HTOUCHINPUT ti;
		TOUCHINPUT touchInputs;
		GetTouchInputInfo(ti, wp, &touchInputs, sizeof(touchInputs));

		//if (touchInputs)
		{
			POINT p;
			//p.x = touchInputs.;
			//ScreenToClient(hwnd, );
			//s_context->transformPointToScreen(); //45CFC0
		}

		CloseTouchInputHandle(ti);*/
		break;
	}

	case WM_MOUSEMOVE:
		if ( a != 0 )
		{
			int cx = 0;
			int cy = 0;

			if ( s_captureMouse )
			{
				RECT rc;
				GetClientRect( hwnd, &rc );
				cx = rc.right/2;
				cy = rc.bottom/2;
			}

			POINT p;
			p.x = short(lp&0xFFFF);
			p.y = short((lp>>16)&0xFFFF);
			App::get()->mouseMove( p.x-cx, p.y-cy );
		}
		return 0;
		
	case WM_MOUSELEAVE:
		setKeyState( a, App::KEY_LBUTTON, false );
		setKeyState( a, App::KEY_MBUTTON, false );
		setKeyState( a, App::KEY_RBUTTON, false );

		s_59AB9D = true;
		return 0;
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:{
		App::KeyType key = translateVKCode((int)wp);
		if ( key != App::KEY_COUNT )
			setKeyState( a, key, WM_KEYDOWN==msg );
		break;}

	case WM_CHAR: //todo
	{
		/*if (wp == 0xFFFF)
			return TRUE;

		int conv = wp + 9216;
		if (s_5B1C16)
		{
			if (conv > 1023)
			{
				LANG_LOG("Framework", LANG_LOG_PRIORITY_ERROR, "Invalid UTF-16 surrogate pair (%04X, %04X) received with WM_CHAR." ?, wp); //457
				//TODO
			}
			else
			{
			}
		//}
		else if (conv > 1023)
		{
			//sub_4C5E20();

			else
			{
				LANG_LOG("Framework", LANG_LOG_PRIORITY_ERROR, "Received low surrogate (%04X) without existing high surrogate."); //462
				return FALSE;
			}
		}
		*/
		return 0;
	}
		
	case WM_SYSKEYDOWN: //TODO
	{
		/*if (wp == VK_RETURN) //ALT-ENTER
		{
			toggleFullscreen(s_hwnd, s_fullscreen);
			return false;
		}

		if (wp == VK_F4)
		{
			PostQuitMessage(0);
			return false;
		}
		

		if (wp == VK_MENU)
		{
			Def
		}

		if (wp == WM_GETTEXT)
		{
			return FALSE;
		}
		if (wp != WM_QUIT)
		{
			if (wp == WM_MEASUREITEM_CLIENTDATA | WM_DESTROY)
			{
				DefWindowProcW(hwnd, msg, wp, lp);
			}
		}

		App::KeyType key = translateVKCode(VK_MENU);

		//setKeyState(a, App::KEY_LBUTTON, true);*/
		
		break;
	}
	
	case WM_SYSKEYUP: //Correct?
	{
		if (wp == VK_CONTROL)
		{
			App::KeyType key = translateVKCode(VK_CONTROL);
			setKeyState(a, key, false);
		}

		else if (wp == VK_MENU)
		{
			App::KeyType key = translateVKCode(VK_MENU);
			setKeyState(a, key, false);
		}
		
		//538110()?

		break;
	}
	
	case WM_KEYLAST: //TODO
	{
		if (wp == 0xFFFF)
			return TRUE;

		//TextInput tp(wp);
		//tp.();

		return 0;
	}
	
	case WM_SYSCOMMAND:
	{
		if (wp == SC_KEYMENU)
			return 0;
	}

	case WM_SIZE:
		if (s_context && !s_5B1B91 && !lp && !lp)
		{
			//s_context->reset(lp, lp);
			if (a)
			{
				a->resolutionChanged();
				//sub_4FA830(s_59AD40);
			}
			a->update(0.0, s_context, App::UPDATE_DRAW);
			//sub_535FA0(lp, lp); //?
		}
		break;

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:{
		s_active = ( LOWORD(wp) != WA_INACTIVE );

		wchar_t name[256];
		GetWindowTextW( hwnd, name, sizeof(name) );
		//Debug::printf( "framework: Window \"%s\" %s\n", name, (s_active?"activated":"deactivated") );

		//if (?)
		{
			if (s_fullscreen)
			{
				if (s_active)
				{
					MONITORINFO mi;
					mi.cbSize = sizeof(MONITORINFO);

					HMONITOR monFromWin = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
					if (GetMonitorInfoW(monFromWin, &mi))
					{
						s_5B1948 = mi.rcMonitor;
						s_5B1B94 = true;
						ShowWindow(hwnd, SW_RESTORE);
						ClipCursor(&s_5B1948);
					}
					else
					{
						ShowWindow(hwnd, SW_MINIMIZE);
						ClipCursor(0);
					}
				}
			}

			if (a)
			{
				a->activate(s_active);
				//?(s_active)
				a->activateAudio(s_active); //This is always set to true so why even
				//?(s_active)
				return 0;
			}
		}

		break;}
	}

	return DefWindowProcW( hwnd, msg, wp, lp );
}

static HWND createMainWindow(int iconresid, const wchar_t* classname, const wchar_t* name,
	int w, int h, bool fullscreen, HINSTANCE instance ) //539E70 | Params were altered
{	
	HICON icon = 0;
	if ( iconresid > 0 )
		icon = LoadIconW( instance, MAKEINTRESOURCE(iconresid) );

	WNDCLASSEXW wndclassexw;
	wndclassexw.cbSize			= sizeof(WNDCLASSEXW); 
	wndclassexw.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclassexw.lpfnWndProc		= (WNDPROC)wndproc;
	wndclassexw.cbClsExtra		= 0;
	wndclassexw.cbWndExtra		= 0;
	wndclassexw.hInstance		= (HINSTANCE)instance;
	wndclassexw.hIcon			= icon;
	wndclassexw.hCursor			= s_5B1CD8["DEFAULT"]; //428B20
	wndclassexw.hbrBackground	= 0;
	wndclassexw.lpszMenuName		= 0;
	wndclassexw.lpszClassName	= classname;
	wndclassexw.hIconSm			= 0;
	bool ok = RegisterClassExW(&wndclassexw) != 0;
	assert( ok );

	DWORD style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = w;
	rect.left = h;
	AdjustWindowRectEx(&rect, style, 0, 0);

	int newRight = rect.right -= rect.left;
	int newBottom = rect.bottom -= rect.top;

	int newX = 0;

	rect.right = newRight;
	rect.bottom = newBottom;
	rect.left = 0;
	rect.top = 0;

	s_5B195C.length = sizeof(WINDOWPLACEMENT);
	s_5B195C.flags = WPF_SETMINPOSITION;
	s_5B195C.ptMinPosition = { 0, 0 };
	s_5B195C.ptMaxPosition = { 0, 0 };
	s_5B195C.rcNormalPosition = { 0, 0 };
	s_5B195C.rcNormalPosition = { newRight, newBottom };

	int newY = 0;

	if ( fullscreen )
	{
		MONITORINFO mi;
		mi.cbSize = sizeof(MONITORINFO);

		HMONITOR m = MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
		GetMonitorInfoW(m, &mi);
		newX = mi.rcMonitor.left;
		newY = mi.rcMonitor.top;
		s_5B1948 = mi.rcMonitor;
		newRight = mi.rcMonitor.right - mi.rcMonitor.left;
		newBottom = mi.rcMonitor.bottom - mi.rcMonitor.top;
		style = WS_VISIBLE | WS_POPUP;
	}

	HWND hwnd = CreateWindowExW(0, classname, name, style, newX, newY, w, h, 0, 0, instance, 0 );
	if ( !hwnd )
	{
		UnregisterClassW(classname, instance );
		return 0;
	}
	
	DragAcceptFiles(hwnd, TRUE);
	return hwnd;
}

static bool flushMessages() //Is this still a standalone function?
{
	MSG msg;
	if ( PeekMessage(&msg,0,0,0,PM_NOREMOVE) )
	{
		while ( WM_QUIT != msg.message &&
			PeekMessage(&msg,0,0,0,PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		return WM_QUIT != msg.message;
	}
	return true;
}


static int run( HINSTANCE instance ) //53A740
{
	TIMECAPS tc;
	timeGetDevCaps(&tc, 8);
	timeBeginPeriod(tc.wPeriodMax);

	try
	{
		OSWin32 os;

		if (__argc > 1) //Change dir to lua file
		{
			std::string path = __argv[1];
			size_t slashOff = path.find_last_of('\\');
			if (slashOff != -1)
				chdir(path.substr(0, slashOff).c_str());
		}

		wchar_t cwd[1024];
		GetCurrentDirectoryW(sizeof(cwd), cwd);
		LANG_LOG_DEBUG("Framework", LANG_LOG_PRIORITY_DEBUG, "Current working directory is %s\n", cwd); //Debug::printf( "Current working directory is %s\n", cwd ); //Restoration

		std::vector<std::string> args;

		for (int i = 0; i < __argc; i++)
			args.push_back(__argv[i]);

		s_config.width = 800;
		s_config.height = 600;
		s_config.framerate = 2056;
		s_config.fullscreen = false;
		s_config.showCursor = true;
		//s_config.bits = 256;

		configure(s_config, os); //AB 412460->446F10 aka parseConfigFromLuaTable

		if (s_config.singleton)
		{
			if (args[0] == "\\")
				args[0] = "/";

			CreateMutexW(0, TRUE, string::toUTF16string(args[0]).c_str());

			//?

			if (GetLastError() == ERROR_ALREADY_EXISTS)
			{
				HWND window = FindWindowW(string::toUTF16string(args[0]).c_str(), 0);
				if (window)
					SetForegroundWindow(window);

				args.clear();

				return 0;
			}
		}

		//TODO FROM HERE

		if (!s_config.publisher.empty() && s_config.product.empty())
		{
			WCHAR psz_Path[MAX_PATH];
			if (SHGetFolderPathAndSubDirW(0, CSIDL_APPDATA | CSIDL_FLAG_CREATE, 0, 0, string::toUTF16string(s_config.publisher + "\\" + s_config.product).c_str(), psz_Path)) //%AppData%/Roaming/Rovio/Angry Birds Seasons
			{
				//sub_41C680(psz_Path, sizeof)
			}
		}

		//s_cursors.push_back("EMPTY");
		//s_cursors.push_back("DEFAULT");

		//LoadCursorW(0, IDC_ARROW);
		//
		//if (s_config.showCursor)
		//{
		//	//s_cursors.push_back = "DEFAULT";
		//	5B1944 = s_cursors["DEFAULT"];
		//}
		//
		////string::toUTF16string(cwd);
		//
		////if (? && ? )
		//{
		//	wchar_t pathBuf[MAX_PATH];
		//	//if (SHGetFolderPathAndSubDirW(0, CSIDL_FLAG_CREATE | CSIDL_APPDATA, 0, 0, string::toUTF16string(), pathBuf))
		//	{
		//		//? = ?
		//	}
		//}

		//PathName(?)

		//string::toUTF16string()

		s_captureMouse = s_config.captureMouse;
		s_fullscreen = s_config.fullscreen;

		int winw = s_config.width;
		int winh = s_config.height;

		// create main window
		s_hwnd = createMainWindow(s_config.iconResourceID, string::toUTF16string(s_config.name).c_str(), L"Loading...", winw, winh, s_config.fullscreen, instance);

		if (!s_hwnd)
		{
			MessageBoxW(0, L"Failed to create main window", L"Error", MB_OK);
			return 1;
		}

		s_5B1988 = GetDC(s_hwnd);

		//s_context = sub_536700(s_config.dllPath);

		if (!s_5B1988)
			s_context->resetCachedState();

		App* app = init(&os, s_context); //call to 40B430
		app->init();

		RECT rc;
		GetClientRect(s_hwnd, &rc);
		sub_535FA0(rc.right, rc.bottom);

		if (s_captureMouse)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(s_hwnd, &pt);

			int pt_y = pt.y;
			int pt_x = pt.x;

			if (s_context->platform() < Context::PLATFORM_GL2 && s_context->platform() > Context::PLATFORM_GLES1)
				s_context->transformPointToScreen(pt_x, pt_y);

			app->mouseMove(pt_x, pt_y);
			//?
		}

		s_5B1934.cbSize = sizeof(TRACKMOUSEEVENT);
		s_5B1934.hwndTrack = s_hwnd;
		s_5B1934.dwFlags = TME_LEAVE;
		TrackMouseEvent(&s_5B1934);

		HMODULE userHNDL = GetModuleHandleW(L"user32.dll");
		s_registerTouchWindow = (PFN_RegisterTouchWindow)GetProcAddress(userHNDL, "RegisterTouchWindow");
		s_getTouchInputInfo = (PFN_GetTouchInputInfo)GetProcAddress(userHNDL, "GetTouchInputInfo");
		s_closeTouchInputHandle = (PFN_CloseTouchInputHandle)GetProcAddress(userHNDL, "CloseTouchInputHandle");

		if (s_registerTouchWindow && s_getTouchInputInfo && s_closeTouchInputHandle)
			s_registerTouchWindow(s_hwnd, TWF_FINETOUCH | TWF_WANTPALM);

		app->activate(s_active);
		//?
		app->activateAudio(s_active);
		//?

		int oldtime = System::currentTimeMicros();

		while (flushMessages())
		{
			int time = System::currentTimeMicros();
			if (time - oldtime < 1000 / 30)
				continue;
			float dt = float(time - oldtime) * 1e-3f;
			oldtime = time;
		}
	}

	catch (Throwable& e)
	{
		if (s_fullscreen)
		{
			s_5B1B91 = true;
		}

		deinit();

		// minimize window so that it doesn't overlap message box
		if (s_hwnd != 0)
		{
			ShowCursor(TRUE);
			MoveWindow(s_hwnd, 0, 0, 4, 4, TRUE);
			ClipCursor(0);
		}

		MessageBox(s_hwnd, L"Unknown exception happened", L"Error!", MB_OK);
	}
	
	/*

	RECT rc;

	GetClientRect(s_hwnd, &rc);

	POINT c;
	c.x = rc.right/2;
	c.y = rc.bottom/2;
	ClientToScreen( s_hwnd, &c );
	SetCursorPos( c.x, c.y );

	//if (!?)
	{
		GetCursorPos(&c);
		ScreenToClient(s_hwnd, &c);

		if (s_context->platform() < Context::PLATFORM_GL2 && s_context->platform() > Context::PLATFORM_GLES1)
		{
			//s_context->
		}
	}

	s_5B1934.cbSize = sizeof(TRACKMOUSEEVENT);
	s_5B1934.hwndTrack = s_hwnd;
	s_5B1934.dwFlags = TME_LEAVE;
	TrackMouseEvent(&s_5B1934);

	HMODULE userHNDL = GetModuleHandleW(L"user32.dll");
	s_registerTouchWindow = (PFN_RegisterTouchWindow)GetProcAddress(userHNDL, "RegisterTouchWindow");
	s_getTouchInputInfo = (PFN_GetTouchInputInfo)GetProcAddress(userHNDL, "GetTouchInputInfo");
	s_closeTouchInputHandle = (PFN_CloseTouchInputHandle)GetProcAddress(userHNDL, "CloseTouchInputHandle");

	app->activate(s_active);
	//?
	app->activateAudio(s_active);
	//?

	int oldtime = System::currentTimeMicros();
	while (flushMessages())
	{
	}

//	try
//	{
//		OSWin32 os;
//
//		char cwd[1024];
//		_getcwd( cwd, sizeof(cwd) );
//		//Debug::printf( "Current working directory is %s\n", cwd );
//
//		int keycodes = sizeof(s_keyToVk)/sizeof(s_keyToVk[0]);
//		int keytypes = App::KEY_COUNT;
//		assert( keycodes == keytypes && "App::KeyType codes don't match Win32 virtual key codes" );
//		
//		// application specific config
//		s_config.name = "Example Application";
//		s_config.width = 800;
//		s_config.height = 600;
//		s_config.bits = 256;
//		s_config.fullscreen = false;
//		s_config.stencilbuffer = true;
//		s_config.captureMouse = false;
//		s_config.iconResourceID = 0;
//#ifdef _DEBUG
//		s_config.debugMemoryAllocs = true;
//#else
//		s_config.debugMemoryAllocs = false;
//#endif
//		configure( s_config, os );
//
//
//		s_captureMouse = s_config.captureMouse;
//		
//		int winw = s_config.width;
//		int winh = s_config.height;
//
//		// create main window
//		s_hwnd = createMainWindow( __FILE__, L"Loading...", winw, winh, s_config.fullscreen, instance, s_config.iconResourceID );
//		if ( !s_hwnd )
//		{
//			MessageBox( 0, L"Failed to create main window", L"Error", MB_OK );
//			return 1;
//		}
//
//		// init rendering context
//
//		//#ifdef _DEBUG
//		//s_config.name = s_config.name + " (DEBUG/" + String(s_context->platformString()).toUpperCase() + ")";
//		//SetWindowTextW( s_hwnd, s_config.name.c_str() );
//		//#endif
//
//		// init app instance
//		App* app = init( &os, s_context );
//		assert( app != 0 );
//		SetWindowTextW( s_hwnd, s_config.name.c_str() );
//
//		// prepare for mouse input
//		MOUSEMOVEPOINT prevmousepoint;
//		ZeroMemory( &prevmousepoint, sizeof(prevmousepoint) );
//
//		// main loop
//		int oldtime = System::currentTimeMillis();
//		while ( flushMessages() )
//		{ 
//			if ( s_config.captureMouse )
//			{
//				if ( s_active && s_context->ready() && !app->quitRequested() )
//				{
//					SetCapture( s_hwnd );
//					ShowCursor( FALSE );
//
//					RECT rc;
//					GetClientRect( s_hwnd, &rc );
//					POINT c;
//					c.x = rc.right/2;
//					c.y = rc.bottom/2;
//					ClientToScreen( s_hwnd, &c );
//					SetCursorPos( c.x, c.y );
//				}
//				else
//				{
//					ReleaseCapture();
//					ShowCursor( TRUE );
//				}
//			}
//
//			int time = System::currentTimeMillis();
//			if ( time-oldtime < 1000/30 )
//				continue;
//			float dt = float(time-oldtime)*1e-3f;
//			oldtime = time;
//
//			if ( s_active && s_context->ready() )
//			{
//				if ( dt > 1.f )
//					dt = 1.f;
//
//				app->update( dt, s_context );
//
//				if ( app->quitRequested() )
//				{
//					ReleaseCapture();
//					break;
//				}
//				else
//				{
//				}
//			}
//		}
//	}
//	catch ( Throwable& e )
//	{	
//		// minimize window so that it doesn't overlap message box
//		if ( s_hwnd != 0 )
//		{
//			ShowCursor( TRUE );
//			MoveWindow( s_hwnd, 0, 0, 4, 4, TRUE );
//		}
//
//		MessageBoxW( s_hwnd, e.getMessage().format().c_str(), "Error", MB_OK);
//	}
//
//	if ( s_hwnd )
//	{
//		DestroyWindow( s_hwnd ); 
//		s_hwnd = 0;
//	}
//*/

	deinit();

	timeEndPeriod(tc.wPeriodMin);

    return 0;
}

int WINAPI WinMain( HINSTANCE instance, HINSTANCE, LPSTR /*commandline*/, int /*commandshow*/ )
{
	VisualStudioLogger();
	int retval = run( instance );
	return retval;
}

void sub_535030(wchar_t* buf, wchar_t* format, ...) //copies to buf
{
	va_list l;
	va_start(l, format);
	vswprintf(buf, 256, format, l);
}

static void deinit() //537780
{
	if (!s_5B1B92)
		return;

	ClipCursor(0);
	s_5B1B92 = true;
	//s_1?
	//s_2?x
	//s_3x = 0 //?

	s_config = App::Configuration(); //446900 (create config)->5360B0(assign config)

	if (App::initialized())
		App::deleteApp();

	if (s_context)
		s_context->resetCachedState();

	if (s_hwnd)
	{
		if (s_5B1988)
			ReleaseDC(s_hwnd, s_5B1988);

		if (s_hwnd)
			DestroyWindow(s_hwnd);
	}

	s_hwnd = 0;
	s_5B1988 = 0;

}

void sub_535FA0(int w, int h) //Adjusts the window display
{
	sub_535030(s_5B1990, L"%s (%dx%d)", string::toUTF16string(s_config.name), w, h);

	SetWindowTextW(s_hwnd, s_5B1990);
}

/*Context* sub_536700(const std::string& dllPath) //TODO gets DLLs
{
	if (dllPath != s_config.dllPath)
		throwError(GraphicsException(Format("No renderer defined!")));

	catch(Throwable)
	{
		throwError(GraphicsException(Format("{0} renderer not supported!", dllPath)));
	}

	return sub_5363E0(dllPath);
}

Context* sub_5363E0(const std::string& renderer) //TODO returns renderer context
{
	RECT r;
	GetClientRect(s_hwnd, &r);

	int w = r.right - r.left;
	int h = r.bottom - r.top;

	int errorMode = SetErrorMode(SEM_FAILCRITICALERRORS);

	//if ()
	{
	}

	std::string dllFile = sub_536310();

	HMODULE dllModule = LoadLibraryW(string::toUTF16string(dllFile).c_str());

	SetErrorMode(errorMode);

	if (!dllModule)
		throwError(GraphicsException(Format("Renderer for platform {0} ({1}) not found!", s_context->platformString(), renderer)));

	typedef Context*(WINAPI* CreateContextFunction)(int w, int h, Context::OrientationType orientation, HWND hwnd, HDC hdc);
	CreateContextFunction createContextFunc = (CreateContextFunction)GetProcAddress(dllModule, "createContext");

	if (!createContextFunc)
		throwError(GraphicsException(Format("Renderer {0} was missing entrypoint \"createContext\"", renderer)));

	Context* context = createContextFunc(w, h, s_config.orientation, s_hwnd, s_5B1988);

	if (!context)
	{
		ReleaseDC(s_hwnd, s_5B1988);
		s_5B1988 = GetDC(s_hwnd);
		throwError(Exception());
	}

	return context;
}*/

std::string sub_536310() //Returns the gr*.dll name.
{
	return Format("gr", s_context->platformString(), ".dll").format();
}

//void sub_538110(App* a, )
//{
//}

void sub_538D30(LPARAM lp, HWND hwnd, App* app) //Correct?
{
	if (!app)
		return;

	if (s_59AB9D)
	{
		TrackMouseEvent(&s_5B1934);
		s_59AB9D = false;
	}

	int cx = 0;
	int cy = 0;

	if (s_captureMouse)
	{
		RECT rc;
		GetClientRect(hwnd, &rc);
		cx = rc.right / 2;
		cy = rc.bottom / 2;
	}

	POINT p;
	p.x = short(lp & 0xFFFF);
	p.y = short((lp >> 16) & 0xFFFF);

	if (s_context->platform() < Context::PLATFORM_GL2 && s_context->platform() > Context::PLATFORM_GLES1)
		s_context->transformPointToScreen(cx, cy);

	app->mouseMove(p.x - cx, p.y - cy);
	//538260(
}

void sub_53A5B0(float dt)
{
	if (!App::initialized()) //4466C0
		return;
	
	App* app = App::get(); //446690
	//sub_53A550(); //Init xinput controllers
	if (s_captureMouse)
	{
		if (s_active && s_context->ready() && !app->quitRequested())
		{
			SetCapture(s_hwnd);

			RECT rc;
			GetClientRect(s_hwnd, &rc);
			POINT c;
			c.x = rc.right / 2;
			c.y = rc.bottom / 2;
			ClientToScreen(s_hwnd, &c);
			SetCursorPos(c.x, c.y);
		}

		else
			ReleaseCapture();
	}

	if (s_context->ready())
	{
		dt = max(0.0f, 0.1f);

		s_context->setTime(s_context->time() + dt);
		app->update(dt, s_context, App::UPDATE_ALL);
		//?

		if (app->quitRequested())
		{
			ReleaseCapture();
			PostQuitMessage(app->getReturnCode());
		}
	}
}

/*void sub_53A550() //controller init
{
	for (int i = 0; i < 4; i++) //4 controllers
	{
		XINPUT_STATE state;
		if (!XInputGetState(i, &state))
			sub_53A150(&state, i);
	}
}

void sub_53A150(XINPUT_STATE* xs, int index) //process controller state
{
	sub_53A0B0(index, App::KEY_GAMEPAD_L1, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_R1, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_DPAD_UP, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_DPAD_DOWN, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_DPAD_LEFT, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_DPAD_RIGHT, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_START, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_BACK, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_THUMBL, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_THUMBR, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_A, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_B, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_X, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
	sub_53A0B0(index, App::KEY_GAMEPAD_Y, (xs->Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);

	//xs->Gamepad.sThumbLX;
}

void sub_53A0B0(int index, App::KeyType controllerKey, bool pressed)
{
	//sub_5379B0(?, index);
}

void sub_5379B0()
{
	.clear();
}*/

std::string OSWin32::getDefaultDataPath() //536080
{
	return m_defaultDataPath;
}

void OSWin32::setCursor(const std::string& cursor) //536A40
{
	//LoadImageW(0, )
	//HANDLE cursorImg = LoadImageW(cursor);

	HCURSOR newCur = (HCURSOR)LoadImageW(0, string::toUTF16string(cursor).c_str(), IMAGE_CURSOR, 0, 0, 80);
	
	if (!newCur)
		throwError(Exception(Format("Setting cursor \"{0}\" failed! Code: {1}", cursor, GetLastError())));

	s_5B1944 = newCur;
	SetCursor(newCur);
}

void OSWin32::loadShaders( const std::string& path, bool recursesubdirs ) //Blank.
{
}

void OSWin32::setResolution(int width, int height) //534EC0
{
	RECT cr;
	GetClientRect(s_hwnd, &cr);

	RECT wr;
	GetWindowRect(s_hwnd, &wr);

	MoveWindow(s_hwnd, wr.left, wr.top, width + (wr.right - cr.right - wr.left), height + (wr.bottom - cr.bottom - wr.top), TRUE);
}

void OSWin32::setOrientation(Context::OrientationType orientation) //5350F0
{
	if (s_context)
	{
		s_context->setOrientation(orientation);
		if (App::initialized())
		{
			App* app = App::get();
			app->orientationChanged();
			app->resolutionChanged();
		}
	}
}

void OSWin32::allowSleep(bool allow) //Blank
{
	
}

bool OSWin32::isSilentProfile() //4C6C10
{
	return false;
}

void OSWin32::startUpdate() //534F30
{
	s_active = true;

	App* app = App::get();
	if (app)
	{
		app->activate(s_active);
		app->activateAudio(s_active);
	}
}

void OSWin32::stopUpdate() //534F70
{
	s_active = false;

	App* app = App::get();
	if (app)
	{
		app->activate(s_active);
		app->activateAudio(s_active);
	}
}

void toggleFullscreen(HWND hwnd, bool fullscreen) //534D40 | Unofficial name.
{
	LONG w = GetWindowLongW(hwnd, GWL_STYLE);
	LONG wExStyle = GetWindowLongW(hwnd, GWL_EXSTYLE);

	if (s_fullscreen)
	{
		if (!fullscreen)
		{
			SetWindowLongW(hwnd, GWL_STYLE, w | WS_OVERLAPPEDWINDOW);
			SetWindowPlacement(hwnd, &s_5B195C);
			SetWindowLongW(hwnd, GWL_EXSTYLE, wExStyle | WS_OVERLAPPEDWINDOW);
			SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
			s_fullscreen = false;
			ClipCursor(0);
		}
	}

	else if (fullscreen)
	{
		if ((w & WS_OVERLAPPEDWINDOW) != 0)
		{
			MONITORINFO mi;
			mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(hwnd, &s_5B195C))
			{
				HMONITOR hm = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);
				int monX = mi.rcMonitor.left;
				int monY = mi.rcMonitor.top;
				int monCX = mi.rcMonitor.right - monX;
				int monCY = mi.rcMonitor.bottom - monY;

				if (GetMonitorInfoW(hm, &mi))
				{
					SetWindowLongW(hwnd, GWL_STYLE, w & 0xFF30FFFF);
					SetWindowLongW(hwnd, GWL_EXSTYLE, wExStyle & 0xFF30FFFF);
					SetWindowPos(hwnd, HWND_TOP, monX, monY, monCX, monCY, SWP_NOCOPYBITS | SWP_NOOWNERZORDER| SWP_NOACTIVATE | SWP_NOZORDER);

					s_5B1948 = mi.rcMonitor;
					s_fullscreen = true;
					ClipCursor(&s_5B1948);
				}
			}
		}
	}
}

bool OSWin32::captureMouse(bool capture) //534FE0
{
	s_captureMouse = capture;
	return true; //According to ASM
}

bool OSWin32::isMouseCaptured() const ///535000
{
	return s_captureMouse;
}

void OSWin32::setFullscreen(bool fullscreen) //534FB0
{
	toggleFullscreen(s_hwnd, fullscreen);
}

bool OSWin32::isFullscreen() const //534FD0
{
	return s_fullscreen; //By contrary this does NOT use s_config.fullscreen!
}

bool OSWin32::setMousePosition(int x, int y) //435EF0 | According to GameLua
{
	return false;
}

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
// 
// Decompiled by Rebird Engineering, original copyright above.
