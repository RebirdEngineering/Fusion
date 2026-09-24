#include <io/PathName.h>
#include <io/FindFile.h>
#include <io/FileInputStream.h>
#include <gr/Context.h>

//#include <gr/dx11/DX11_Context.h>

#include <hgr/ParticleSystem.h>
#include <hgr/DefaultResourceManager.h>
#include <lang/System.h>
#include <lang/Exception.h>
#include <framework/App.h>
#include <stdio.h>
#include <direct.h>
#include <windows.h>
#include <crtdbg.h>
//#include <config.h>

#include <framework/VisualStudioLogger.h>


using namespace io;
using namespace gr;
using namespace hgr; //NOT USED IN FUSION PAST ABSPACE?
using namespace lang;
using namespace framework;


class OSWin32 : //Not in framework namespace?
	public OSInterface
{
public:
	void			loadShaders( const std::string& path, bool recursesubdirs ); //Blank?
	std::string	getDefaultDataPath();
	void	setCursor(const std::string& cursor);
	void	setResolution(int width, int height);
	void	setOrientation(Context::OrientationType orientation);
	void	allowSleep(bool allowSleep);
	bool	isSilentProfile();
	void	startUpdate();
	void	stopUpdate();
	void	setFullScreen(bool fullscreen);
	bool	isFullscreen() const;
	bool	captureMouse(bool capture);
	bool	isMouseCaptured() const;
	bool	setMousePosition(int x, int y);
};

static const int s_keyToVk[] =
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

static P(Context)					s_context			= 0;
static P(DefaultResourceManager)	s_defResMgr			= 0;
static bool							s_active			= false;
static HWND							s_hwnd;
static bool							s_captureMouse;
static App::Configuration			s_config;

bool OSWin32::setMousePosition(int x, int y) //According to GameLua
{
	return true;
}

/** Translates Win32 Virtual Key codes to KeyType. */
static App::KeyType translateVKCode( int vk )
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
static void setKeyState( App* a, App::KeyType key, bool keydown )
{
	if ( a != 0 )
	{
		if ( keydown )
		{
			if ( !a->isKeyDown(key) )
				a->keyDown( key );
		}
		else
		{
			a->keyUp( key );
		}
		a->setKeyDown( key, keydown );
	}
}

static void setWheelState( App* a, ? ) //UNOFFICIAL
{
	if ( a != 0 )
	{
		
	}
}

static LRESULT wndproc( HWND hwnd, UINT msg, WPARAM wp, LPARAM lp )
{
	App* a = 0;
	if ( App::initialized() )
		a = App::get();

	switch ( msg )
	{
	case WM_ERASEBKGND:
		return TRUE;
	case WM_SETCURSOR: //Changed?
		if ( s_captureMouse )
		{
			SetCursor( 0 );
			return TRUE;
		}
		break;
		
	case WM_GETMINMAXINFO: //TODO
		
		break;
		
	case WM_WINDOWPOSCHANGING: //TODO
		break;
		
	case WM_DISPLAYCHANGE: //TODO
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

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
		setWheelState( a );
		break;

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
		if (?)
		{
			//? = true
			//TrackMouseEvent
		}
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:{
		App::KeyType key = translateVKCode((int)wp);
		if ( key != App::KEY_COUNT )
			setKeyState( a, key, WM_KEYDOWN==msg );
		break;}

	case WM_CHAR:{ //todo
		if (?)
		{
			LANG_LOG("Framework", LANG_LOG_PRIORITY_ERROR, "Invalid UTF-16 surrogate pair (%04X, %04X) received with WM_CHAR."); //457
			LANG_LOG("Framework", LANG_LOG_PRIORITY_ERROR, "Received low surrogate (%04X) without existing high surrogate."); //462
		}
		
	case WM_SYSKEYDOWN: //TODO
	{
		break;
	}
	
	case WM_SYSKEYUP: //TODO
	{
		break;
	}
	
	case WM_KEYLAST: //TODO
	{
		break;
	}
	
	case WM_SYSCOMMAND:
	{
		if (wp == 61696)
			return 0;
	}

	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:{
		s_active = ( LOWORD(wp) != WA_INACTIVE );

		char name[256];
		GetWindowTextA( hwnd, name, sizeof(name) );
		//Debug::printf( "framework: Window \"%s\" %s\n", name, (s_active?"activated":"deactivated") );

		//ShowWindow(hwnd, SW_RESTORE);

		//ShowWindow(hwnd, SW_MINIMIZE);

		if ( App::initialized() )
		{
			App::get()->activate( s_active );
			App::get()->activateAudio( s_active ); //This is always set to true so why even
		}
		break;}
	}

	return DefWindowProc( hwnd, msg, wp, lp );
}

static HWND createMainWindow( const wchar_t* classname, const wchar_t* name,
	int w, int h, bool fullscreen, HINSTANCE instance, int iconresid ) //Params were altered
{
	DWORD style = WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	if ( fullscreen )
	{
		style = WS_VISIBLE|WS_POPUP;
		exstyle = WS_EX_TOPMOST;
		MONITORINFO mi;
		mi.cbSize = sizeof(MONITORINFO)
		HMONITOR m = MonitorFromPoint(0, MONITOR_DEFAULTTOPRIMARY);
		bool mok = GetMonitorInfoW(m, mi);
	}
	
	HICON icon = 0;
	if ( iconresid > 0 )
		icon = LoadIcon( instance, MAKEINTRESOURCE(iconresid) );

	WNDCLASSEXW wndclassexw;
	wndclassexw.cbSize			= sizeof(WNDCLASSEXW); 
	wndclassexw.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclassexw.lpfnWndProc		= (WNDPROC)wndproc;
	wndclassexw.cbClsExtra		= 0;
	wndclassexw.cbWndExtra		= 0;
	wndclassexw.hInstance		= (HINSTANCE)instance;
	wndclassexw.hIcon			= icon;
	wndclassexw.hCursor			= s_captureMouse ? 0 : LoadCursor(NULL, IDC_ARROW);
	wndclassexw.hbrBackground	= 0;
	wndclassexw.lpszMenuName		= 0;
	wndclassexw.lpszClassName	= classname;
	wndclassexw.hIconSm			= 0;
	bool ok = RegisterClassExW(&wndclassexw) != 0;
	assert( ok );
	RECT rect;
	AdjustWindowRectEx(

	void* userparam = 0;
	HWND hwnd = CreateWindowExW(0, classname, name, style, 0, 0, w, h, 0, 0, instance, userparam );
	if ( !hwnd )
	{
		UnregisterClass(MAKEINTRESOURCE(classname), instance );
		return 0;
	}
	else
	{
		DragAcceptFiles(hwnd, true);
		return hwnd;
	}
}

static bool flushMessages()
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

static int run( HINSTANCE instance )
{
	try
	{
		OSWin32 os;

		char cwd[1024];
		_getcwd( cwd, sizeof(cwd) );
		//Debug::printf( "Current working directory is %s\n", cwd );

		int keycodes = sizeof(s_keyToVk)/sizeof(s_keyToVk[0]);
		int keytypes = App::KEY_COUNT;
		assert( keycodes == keytypes && "App::KeyType codes don't match Win32 virtual key codes" );
		
		// application specific config
		s_config.name = "Example Application";
		s_config.width = 800;
		s_config.height = 600;
		s_config.bits = 256;
		s_config.fullscreen = false;
		s_config.stencilbuffer = true;
		s_config.captureMouse = false;
		s_config.iconResourceID = 0;
#ifdef _DEBUG
		s_config.debugMemoryAllocs = true;
#else
		s_config.debugMemoryAllocs = false;
#endif
		configure( s_config );

		if ( s_config.debugMemoryAllocs )
		{
			_CrtSetDbgFlag( _CRTDBG_CHECK_ALWAYS_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) );
		}

		s_captureMouse = s_config.captureMouse;
		
		int winw = s_config.width;
		int winh = s_config.height;

		// create main window
		s_hwnd = createMainWindow( __FILE__, L"Loading...", winw, winh, s_config.fullscreen, instance, s_config.iconResourceID );
		if ( !s_hwnd )
		{
			MessageBox( 0, L"Failed to create main window", L"Error", MB_OK );
			return 1;
		}

		// init rendering context

		#ifdef _DEBUG
		s_config.name = s_config.name + " (DEBUG/" + String(s_context->platformString()).toUpperCase() + ")";
		SetWindowTextW( s_hwnd, s_config.name.c_str() );
		#endif

		// set default resource manager
		s_defResMgr = new DefaultResourceManager( s_context );
		DefaultResourceManager::set( s_defResMgr );

		// find resources from current working directory
		s_defResMgr->findTextureResources( "*" );

		// init app instance
		App* app = init( &os, s_context );
		assert( app != 0 );
		SetWindowText( s_hwnd, s_config.name.c_str() );

		// prepare for mouse input
		MOUSEMOVEPOINT prevmousepoint;
		ZeroMemory( &prevmousepoint, sizeof(prevmousepoint) );

		// main loop
		int oldtime = System::currentTimeMillis();
		while ( flushMessages() )
		{ 
			if ( s_config.captureMouse )
			{
				if ( s_active && s_context->ready() && !app->quitRequested() )
				{
					SetCapture( s_hwnd );
					ShowCursor( FALSE );

					RECT rc;
					GetClientRect( s_hwnd, &rc );
					POINT c;
					c.x = rc.right/2;
					c.y = rc.bottom/2;
					ClientToScreen( s_hwnd, &c );
					SetCursorPos( c.x, c.y );
				}
				else
				{
					ReleaseCapture();
					ShowCursor( TRUE );
				}
			}

			int time = System::currentTimeMillis();
			if ( time-oldtime < 1000/30 )
				continue;
			float dt = float(time-oldtime)*1e-3f;
			oldtime = time;

			if ( s_active && s_context->ready() )
			{
				if ( dt > 1.f )
					dt = 1.f;

				app->update( dt, s_context );

				if ( app->quitRequested() )
				{
					ReleaseCapture();
					deinit();
					break;
				}
				else
				{
				}
			}
		}
	}
	catch ( Throwable& e )
	{	
		// minimize window so that it doesn't overlap message box
		if ( s_hwnd != 0 )
		{
			ShowCursor( TRUE );
			MoveWindow( s_hwnd, 0, 0, 4, 4, TRUE );
		}

		MessageBox( s_hwnd, e.getMessage().format().c_str(), "Error", MB_OK);
	}

	if ( s_hwnd )
	{
		DestroyWindow( s_hwnd ); 
		s_hwnd = 0;
	}

    return 0;
}

int WINAPI WinMain( HINSTANCE instance, HINSTANCE, LPSTR /*commandline*/, int /*commandshow*/ )
{
	VisualStudioLogger();
	int retval = run( instance );
	return retval;
}

std::string OSWin32::getDefaultDataPath()
{
	return PathName(m_defaultDataPath).toString();
}

void OSWin32::setCursor(const std::string& cursor) //unofficial name
{
	HANDLE cursorImg = LoadImageW();
	
	throwError(Exception(Format("Setting cursor \"{0}\" failed! Code: {1}", cursor, GetLastError())));
}

void OSWin32::loadShaders( const std::string& path, bool recursesubdirs )
{
}

void OSWin32::setResolution(int width, int height)
{
	s_config.width = width;
	s_config.height = height;
}

void OSWin32::setOrientation(Context::OrientationType orientation)
{
	s_config.orientation = orientation;
}

void OSWin32::allowSleep(bool allow)
{
	
}

bool OSWin32::isSilentProfile()
{

}

bool OSWin32::captureMouse(bool capture)
{
	s_captureMouse = capture;
	return capture; //According to ASM
}

bool OSWin32::isMouseCaptured() const
{
	return s_captureMouse;
}

void OSWin32::setFullScreen(bool fullscreen)
{
	//return (s_hwnd, fullscreen)
}

bool OSWin32::isFullscreen() const
{
	return s_config.fullscreen;
}

void OSWin32::setResolution(int width, int height)
{
	RECT cr;
	GetClientRect(s_hwnd, &cr);
	RECT wr;
	GetWindowRect(s_hwnd, &wr);
	MoveWindow(s_hwnd, wr.left, wr.top, width + (wr.right - cr.right - wr.left), height + (wr.bottom - cr.bottom - wr.top), TRUE);
}

bool OSWin32::setMousePosition(int x, int y)
{
	return false;
}

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
// 
// Decompiled by Rebird Engineering, original copyright above.
