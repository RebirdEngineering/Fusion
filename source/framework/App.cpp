#include <framework/App.h>
#include <io/PathName.h> //Redundant?
#include <lua/LuaTable.h>


using namespace io;
using namespace gr;
using namespace lua;


namespace framework
{

//
// To create this table:
// 1) Copypaste KeyType values to here, and
// 2) Replace ^:b+KEY_{[A-Z1-90]+},:b*$
//	  with         "\1",
// 
static const char* const s_keysz[] = //44
{
		/// Invalid key code
        "NONE",
		///
        "A",
		///
        "B",
		///
        "C",
		///
        "D",
		///
        "E",
		///
        "F",
		///
        "G",
		///
        "H",
		///
        "I",
		///
        "J",
		///
        "K",
		///
        "L",
		///
        "M",
		///
        "N",
		///
        "O",
		///
        "P",
		///
        "Q",
		///
        "R",
		///
        "S",
		///
        "T",
		///
        "U",
		///
        "V",
		///
        "W",
		///
        "X",
		///
        "Y",
		///
        "Z",
		///
        "PAGEDOWN",
		///
        "PAGEUP",
		///
        "HOME",
		///
        "END",
		///
        "INSERT",
		///
        "DELETE",
		///
        "RETURN",
		///
        "SHIFT",
		///
        "CONTROL",
		///
        "TAB",
		///
        "SPACE",
		///
        "BACKSPACE",
		///
        "PAUSE",
		///
        "ESCAPE",
		///
        "F1",
		///
        "F2",
		///
        "F3",
		///
        "F4",
		///
        "F5",
		///
        "F6",
		///
        "F7",
		///
        "F8",
		///
        "F9",
		///
        "F10",
		///
        "F11",
		///
        "F12",
		/** Arrow left. */
        "LEFT",
		/** Arrow right. */
        "RIGHT",
		/** Arrow up. */
        "UP",
		/** Arrow down. */
        "DOWN",
		/** Left mouse button. */
        "LBUTTON",
		/** Middle mouse button. */
        "MBUTTON",
		/** Right mouse button. */
        "RBUTTON",
		/** Keypad number */
        "0",
		/** Keypad number */
        "1",
		/** Keypad number */
        "2",
		/** Keypad number */
        "3",
		/** Keypad number */
        "4",
		/** Keypad number */
        "5",
		/** Keypad number */
        "6",
		/** Keypad number */
        "7",
		/** Keypad number */
        "8",
		/** Keypad number */
        "9",
        /**  */
        "MULTIPLY",
        /**  */
        "ADD",
        /**  */
        "SUBTRACT",
        /**  */
        "DIVIDE",
		/** Left soft key */
        "LEFTSOFT",
		/** Right soft key */
        "RIGHTSOFT",
		/** Middle soft key */
        "MIDDLE",
		/** Asterisk mark */
        "ASTERISK",
		/** Hash mark */
		"HASH",
		/** Clear key */
		"CLEAR",
		/** Edit key */
		"EDIT",
		/** Send key */
		"SEND",
		/** Volume up key */
		"VOLUME_UP",
		/** Volume down key */
		"VOLUME_DOWN",
        /**  */
		"KEY_GAMING_A",
        /**  */
		"KEY_GAMING_B",
        /**  */
		"KEY_BACK",
        /**  */
		"KEY_MENU", //[NOTE] Past these are Fusion
        /**  */
		"KEY_ALT",
        /**  */
		"DASH",
        /**  */
		"KEY_ZOOM",
        /**  */
		"FASTFORWARD",
        /**  */
		"REWIND",
        /**  */
		"REPLAY",
        /**  */
        "GAMEPAD_1",
        /**  */
        "GAMEPAD_2",
        /**  */
        "GAMEPAD_3",
        /**  */
        "GAMEPAD_4",
        /**  */
        "GAMEPAD_5",
        /**  */
        "GAMEPAD_6",
        /**  */
        "GAMEPAD_7",
        /**  */
        "GAMEPAD_8",
        /**  */
        "GAMEPAD_9",
        /**  */
        "GAMEPAD_10",
        /**  */
        "GAMEPAD_11",
        /**  */
        "GAMEPAD_12",
        /**  */
        "GAMEPAD_13",
        /**  */
        "GAMEPAD_14",
        /**  */
        "GAMEPAD_15",
        /**  */
        "GAMEPAD_16",
        /**  */
        "GAMEPAD_A",
        /**  */
        "GAMEPAD_B",
        /**  */
        "GAMEPAD_C",
        /**  */
        "GAMEPAD_L1",
        /**  */
        "GAMEPAD_L2",
        /**  */
        "GAMEPAD_MODE",
        /**  */
        "GAMEPAD_R1",
        /**  */
        "GAMEPAD_R2",
        /**  */
        "GAMEPAD_SELECT",
        /**  */
        "GAMEPAD_START",
        /**  */
        "GAMEPAD_BACK",
        /**  */
        "GAMEPAD_THUMBL",
        /**  */
        "GAMEPAD_THUMBR",
        /**  */
        "GAMEPAD_X",
        /**  */
        "GAMEPAD_Y",
        /**  */
        "GAMEPAD_Z",
        /**  */
        "GAMEPAD_DPAD_DOWN",
        /**  */
        "GAMEPAD_DPAD_LEFT",
        /**  */
        "GAMEPAD_DPAD_RIGHT",
        /**  */
        "GAMEPAD_DPAD_UP",
        /**  */
        "GAMEPAD_DPAD_CENTER"
};


App::Configuration::Configuration() //293
{
	name = "";
	width = 0;
	height = 0;
    minWidth = 0;
    minHeight = 0;
	bits = 16;
	fullscreen = true; //[NOTE] Changed to true, why idk
    showCursor = true; //[NOTE] Changed to true, why idk
    depthbuffer = false;
	stencilbuffer = false;
	captureMouse = false;
	iconResourceID = 0;
    debugMemoryAllocs = false;
    orientation = gr::Context::ORIENTATION_0;
    framerate = 60;
    publisher = "";
    product = "";
    dllPath = "";
}

App::App( OSInterface* os, //294 
    const std::string& pathname) : //295 | [Changed]?
	m_os( os ),
	m_quit( false )
{
	assert( !sm_app ); //Unofficial
	sm_app = this;

	for ( int i = 0 ; i < KEY_COUNT ; ++i ) //303
		m_keyDown[i] = false;

	setDataPath(pathname);
}

App::~App() //310
{
	delete sm_app;
    m_touches.clear(); //312
}

void App::init()
{
}

App* App::get()
{
    return sm_app;
}

void App::deleteApp()
{
    delete sm_app;
    sm_app = 0;
}

bool App::initialized()
{
	return sm_app != 0;
}

void App::activate( bool /*active*/ ) //335
{
	for ( int i = 0 ; i < KEY_COUNT ; ++i ) //337
		setKeyDown( (KeyType)i, false ); //338

    m_touches.resize(0);
}

void App::loadFromUrl(const std::string& url) //345
{
}

bool App::activateAudio(bool active) //349
{
	return true;
}

void App::keyUp( KeyType key ) //354
{
}

void App::keyDown( KeyType key ) //358
{
}

void App::orientationChanged()
{
}

void App::resolutionChanged()
{
}

void App::mouseMove( int dx, int dy ) //370
{
}

void App::motion( double dx, double dy ) //374
{
}

void App::mouseWheel( int ticks ) //378
{
}

void App::quit(int returnCode) //382 | [CHANGED] added return code
{
	m_quit = true;
    m_returnCode = returnCode;
}

bool App::quitRequested() const	
{
	return m_quit;
}

void App::setKeyDown( KeyType key, bool down ) //393
{
	m_keyDown[key]= down;
}

bool App::isKeyDown( KeyType key ) const //398
{
	return m_keyDown[key];
}

void App::touchBegan(const TouchEvent& touch) //403
{
    m_touches.push_back(touch); //405
}

void App::touchMoved(const TouchEvent& touch) //408 | ?
{
    std::vector<TouchEvent>::iterator it = m_touches.begin(); //410
    *it = touch;
    touchBegan(touch);
}

void App::touchEnded(const TouchEvent& touch) //415 | ?
{
    *m_touches.begin() = touch; //417
}

void App::hoverBegan(int, int) //420
{
}

void App::hoverMoved(int, int) //424
{
}

void App::hoverEnded(int, int) //428
{
}

void App::touchCancel()
{
    m_touches.clear(); //434
}

const std::vector<TouchEvent>& App::touches() const
{
    return m_touches;
}

const char* App::toString( KeyType key ) //442 | According to line numbers the assert was removed.
{
	return s_keysz[key];
}

void App::setDataPath( const std::string& datapath ) //447
{
	m_dataPath = PathName(datapath);
}

std::string App::path( const std::string& filename ) const //452
{
	return PathName( m_dataPath.toString(), PathName(filename).toString() ).toString(); //454
}

void App::softQuit()
{
}

bool App::setControlsPresent(bool)
{
	return true;
}

#ifndef PLATFORM_IOS //Inexistent on iOS but exists on Android and PC.
static App::Configuration parseConfigFromLuaTable(App::Configuration& config, LuaTable& table)
{
	if (table.isString("name")) config.name = table.getString("name");
	if (table.isNumber("width")) config.width = table.getNumber("width");
	if (table.isNumber("height")) config.height = table.getNumber("height");
	if (table.isNumber("bits")) config.bits = table.getNumber("bits");
	if (table.isBoolean("fullscreen")) config.fullscreen = table.getBoolean("fullscreen");
	if (table.isBoolean("showCursor")) config.showCursor = table.getBoolean("showCursor");
	if (table.isBoolean("depthbuffer")) config.depthbuffer = table.getBoolean("depthbuffer");
	if (table.isBoolean("captureMouse")) config.captureMouse = table.getBoolean("captureMouse");
	if (table.isString("dllPath")) config.dllPath = table.getString("dllPath");
	if (table.isString("iconResourceID")) config.iconResourceID = table.getNumber("iconResourceID");
	if (table.isBoolean("debugMemoryAllocs")) config.debugMemoryAllocs = table.getBoolean("debugMemoryAllocs");
	if (table.isNumber("orientation"))
	{
        int orientation = table.getNumber("orientation");
		switch (orientation)
		{
            case 270: config.orientation = Context::ORIENTATION_270;
			case 180: config.orientation = Context::ORIENTATION_180;
			case 90: config.orientation = Context::ORIENTATION_90;
			default: config.orientation = Context::ORIENTATION_0;
		}
	}
	if (table.isTable("autoOrientations"))
	{
		LuaTable orientationTypes = table.getTable("autoOrientations");
		for (int i = 0; i < orientationTypes.isNumber(i); i++)
			config.autoOrientations.push_back((Context::OrientationType)orientationTypes.getNumber(i));
	}
	if (table.isNumber("framerate")) config.framerate = table.getNumber("framerate");
	if (table.isString("publisher")) config.publisher = table.getString("publisher");
	if (table.isString("product")) config.product = table.getString("product");
	if (table.isTable("renderer"))
	{
		LuaTable renderers = table.getTable("renderer");
        for (int i = 1; i < renderers.isString(i); i++)
        {
            std::string rendererString = renderers.getString(i);
            std::string platformString = Context::getString((Context::PlatformType)i);
            if (rendererString == platformString)
            {
                if (i++ == Context::PLATFORM_COUNT)
                    break; //Too many.
                config.renderer.push_back((Context::PlatformType)i);
            }
        }
	}
	if (table.isBoolean("singleton")) config.singleton = table.getBoolean("singleton");
	return config;
}
#endif

} // framework

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
