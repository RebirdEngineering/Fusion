#ifndef _FRAMEWORK_APP_H
#define _FRAMEWORK_APP_H


#include <lang/Event.h>
#include <framework/OSInterface.h>


namespace io
{ 
	class DataInputStream;
	class DataOutputStream;}

namespace gr {
	class Context;}

namespace framework
{

class TouchEvent //[ADD]
{
public:
	TouchEvent(); //20
	TouchEvent(int, int, int); //21

	int id; //23
	int x; //24
	int y; //25

	bool operator==(const TouchEvent&) const; //27
};

struct DropFiles //30 | [ADD]
{
	std::vector<std::string> fileNames; //32
	int x; //33
	int y; //34
};

/** 
 * Base class for application instances.
 * There must be only one application instance.
 * Application instance must always be allocated to heap (with operator new).
 * @ingroup framework
 */
class App
{
public:
	/** Initialization parameters. */
	class Configuration //47
	{
	public:
		/** Name of the application (main window). */
		std::string		        	name; //51
		/** Width of rendering target. */
		int					        	width; //53
		/** Height of rendering target. */
		int					        	height; //55
        /**  */
		int					        	minWidth; //57
		/**  */
		int					        	minHeight; //59
		/** Bits per pixel. */
		int 				        	bits; //61
		/** Fullscreen window. */
		bool 				        	fullscreen; //63
        /**  */
		bool				        	showCursor; //65
        /**  */
		bool				        	depthbuffer; //67
        /** Stencil buffer required. */
		bool 				        	stencilbuffer; //69
		/** Capture all mouse input. */
		bool				        	captureMouse; //71
		/** Icon resource id. 0 if default. */
		int					        	iconResourceID; //73 | Previously icon in private KA3D
		/** Debug/trace memory allocations. Default is true for _DEBUG build. */
		bool				        		debugMemoryAllocs; //75
        /**  */
		gr::Context::OrientationType			orientation; //77
        /**  */
		std::vector<gr::Context::OrientationType>	autoOrientations; //79
        /**  */
        int                         		framerate; //81
        /**  */
		std::string	            		publisher; //83
        /**  */
		std::string	            		product; //85
        /**  */
		std::string	            		dllPath; //87
        /**  */
		std::vector<gr::Context::PlatformType>		renderer; //89
        /**  */
        bool                        		singleton; //91

		Configuration(); //93
	};

	enum ControllerAxis //96 | This was never used in the engine.
	{
		AXIS_UNKNOWN,
		GAMEPAD_LEFT_STICK_X,
		GAMEPAD_LEFT_STICK_Y,
		GAMEPAD_RIGHT_STICK_X,
		GAMEPAD_RIGHT_STICK_Y,
		GAMEPAD_LEFT_TRIGGER,
		GAMEPAD_RIGHT_TRIGGER,
		GAMEPAD_BRAKE,
		GAMEPAD_GAS,
		GAMEPAD_HAT_X,
		GAMEPAD_HAT_Y,
		GAMEPAD_DPAD_X,
		GAMEPAD_DPAD_Y
	};

	/** Key type. */
	enum KeyType //114
	{
		/// Invalid key code
		KEY_NONE,
		///
		KEY_A,
		///
		KEY_B,
		///
		KEY_C,
		///
		KEY_D,
		///
		KEY_E,
		///
		KEY_F,
		///
		KEY_G,
		///
		KEY_H,
		///
		KEY_I,
		///
		KEY_J,
		///
		KEY_K,
		///
		KEY_L,
		///
		KEY_M,
		///
		KEY_N,
		///
		KEY_O,
		///
		KEY_P,
		///
		KEY_Q,
		///
		KEY_R,
		///
		KEY_S,
		///
		KEY_T,
		///
		KEY_U,
		///
		KEY_V,
		///
		KEY_W,
		///
		KEY_X,
		///
		KEY_Y,
		///
		KEY_Z,
		///
		KEY_PAGEDOWN,
		///
		KEY_PAGEUP,
		///
		KEY_HOME,
		///
		KEY_END,
		///
		KEY_INSERT,
		///
		KEY_DELETE,
		///
		KEY_RETURN,
		///
		KEY_SHIFT,
		///
		KEY_CONTROL,
		///
		KEY_TAB,
		///
		KEY_SPACE,
		///
		KEY_BACKSPACE,
		///
		KEY_PAUSE,
		///
		KEY_ESCAPE,
		///
		KEY_F1,
		///
		KEY_F2,
		///
		KEY_F3,
		///
		KEY_F4,
		///
		KEY_F5,
		///
		KEY_F6,
		///
		KEY_F7,
		///
		KEY_F8,
		///
		KEY_F9,
		///
		KEY_F10,
		///
		KEY_F11,
		///
		KEY_F12,
		/** Arrow left. */
		KEY_LEFT,
		/** Arrow right. */
		KEY_RIGHT,
		/** Arrow up. */
		KEY_UP,
		/** Arrow down. */
		KEY_DOWN,
		/** Left mouse button. */
		KEY_LBUTTON,
		/** Middle mouse button. */
		KEY_MBUTTON,
		/** Right mouse button. */
		KEY_RBUTTON,
		/** Keypad number */
		KEY_0,
		/** Keypad number */
		KEY_1,
		/** Keypad number */
		KEY_2,
		/** Keypad number */
		KEY_3,
		/** Keypad number */
		KEY_4,
		/** Keypad number */
		KEY_5,
		/** Keypad number */
		KEY_6,
		/** Keypad number */
		KEY_7,
		/** Keypad number */
		KEY_8,
		/** Keypad number */
		KEY_9,
        /**  */
		KEY_MULTIPLY,
        /**  */
		KEY_ADD,
        /**  */
		KEY_SUBTRACT,
        /**  */
		KEY_DIVIDE,
		/** Left soft key */
		KEY_LEFTSOFT,
		/** Right soft key */
		KEY_RIGHTSOFT,
		/** Middle soft key */
		KEY_MIDDLE,
		/** Asterisk mark */
		KEY_ASTERISK,
		/** Hash mark */
		KEY_HASH,
		/** Clear key */
		KEY_CLEAR,
		/** Edit key */
		KEY_EDIT,
		/** Send key */
		KEY_SEND,
		/** Volume up key */
		KEY_VOLUME_UP,
		/** Volume down key */
		KEY_VOLUME_DOWN,
        /**  */
		KEY_GAMING_A,
        /**  */
		KEY_GAMING_B,
        /**  */
		KEY_BACK,
        /**  */
		KEY_MENU,
        /**  */
		KEY_ALT,
        /**  */
		KEY_DASH,
        /**  */
		KEY_ZOOM,
        /**  */
		KEY_FASTFORWARD,
        /**  */
		KEY_REWIND,
        /**  */
		KEY_REPLAY,
        /**  */
        KEY_GAMEPAD_1,
        /**  */
        KEY_GAMEPAD_2,
        /**  */
        KEY_GAMEPAD_3,
        /**  */
        KEY_GAMEPAD_4,
        /**  */
        KEY_GAMEPAD_5,
        /**  */
        KEY_GAMEPAD_6,
        /**  */
        KEY_GAMEPAD_7,
        /**  */
        KEY_GAMEPAD_8,
        /**  */
        KEY_GAMEPAD_9,
        /**  */
        KEY_GAMEPAD_10,
        /**  */
        KEY_GAMEPAD_11,
        /**  */
        KEY_GAMEPAD_12,
        /**  */
        KEY_GAMEPAD_13,
        /**  */
        KEY_GAMEPAD_14,
        /**  */
        KEY_GAMEPAD_15,
        /**  */
        KEY_GAMEPAD_16,
        /**  */
        KEY_GAMEPAD_A,
        /**  */
        KEY_GAMEPAD_B,
        /**  */
        KEY_GAMEPAD_C,
        /**  */
        KEY_GAMEPAD_L1,
        /**  */
        KEY_GAMEPAD_L2,
        /**  */
        KEY_GAMEPAD_MODE,
        /**  */
        KEY_GAMEPAD_R1,
        /**  */
        KEY_GAMEPAD_R2,
        /**  */
        KEY_GAMEPAD_SELECT,
        /**  */
        KEY_GAMEPAD_START,
        /**  */
        KEY_GAMEPAD_BACK,
        /**  */
        KEY_GAMEPAD_THUMBL,
        /**  */
        KEY_GAMEPAD_THUMBR,
        /**  */
        KEY_GAMEPAD_X,
        /**  */
        KEY_GAMEPAD_Y,
        /**  */
        KEY_GAMEPAD_Z,
        /**  */
        KEY_GAMEPAD_DPAD_DOWN,
        /**  */
        KEY_GAMEPAD_DPAD_LEFT,
        /**  */
        KEY_GAMEPAD_DPAD_RIGHT,
        /**  */
        KEY_GAMEPAD_DPAD_UP,
        /**  */
        KEY_GAMEPAD_DPAD_CENTER,
		/** Number of key codes. */
		KEY_COUNT
	};
	
	enum UpdateFlags //353
	{
		UPDATE_DRAW,
		UPDATE_SIMULATION,
		UPDATE_ALL,
	};

	static const lang::event::Event<void(KeyType)> EVENT_KEY_DOWN; //363
	static const lang::event::Event<void(KeyType)> EVENT_KEY_UP; //364
	static const lang::event::Event<void(int)> EVENT_MOUSE_MOVE;
	static const lang::event::Event<void(int, int)> EVENT_MOUSE_WHEEL;
	static const lang::event::Event<void(const TouchEvent&)> EVENT_TOUCH_BEGAN;
	static const lang::event::Event<void(const TouchEvent&)> EVENT_TOUCH_MOVED;
	static const lang::event::Event<void(const TouchEvent&)> EVENT_TOUCH_ENDED;
	static const lang::event::Event<void(bool)> EVENT_ACTIVATE;
	static const lang::event::Event<void(bool)> EVENT_ACTIVATE_AUDIO;
	static const lang::event::Event<void()> EVENT_RESOLUTION_CHANGED;
	static const lang::event::Event<void(float, gr::Context*)> EVENT_UPDATE;
	static const lang::event::Event<void(const DropFiles&)> EVENT_DROPFILES;
	static const lang::event::Event<void(int, int)> EVENT_HOVER_BEGAN;
	static const lang::event::Event<void(int, int)> EVENT_HOVER_MOVED;
	static const lang::event::Event<void(int, int)> EVENT_HOVER_ENDED;
	static const lang::event::Event<void(KeyType, int)> EVENT_CONTROLLER_KEY_DOWN;
	static const lang::event::Event<void(KeyType, int)> EVENT_CONTROLLER_KEY_UP;
	static const lang::event::Event<void(ControllerAxis, float, int)> EVENT_CONTROLLER_AXIS_UPDATE; //424

	explicit App( OSInterface* os, const std::string& datapath); //432 | Previously explicit App( OSInterface* os );

	virtual ~App(); //437
	
	/**
	 * 
	 */
	virtual void 				init(); //442

	/** 
	 * Main loop for your application.
	 * @param dt Time (seconds) since last update.
	 * @param context Rendering device context.
	 * @param ?
	 */
	virtual void				update( float dt, gr::Context* context, int ) = 0; //450

	/**
	 * Called when user pressed key down.
	 * Called only once per key press, i.e. keeping key down doesnt cause more key presses.
	 * Default implementation does nothing.
	 */
	virtual void				keyDown( KeyType key ); //457

	/**
	 * Called when user releases key.
	 * Default implementation does nothing.
	 */
	virtual void				keyUp( KeyType key ); //463

	/**
	 * Called when the orientation of the screen changes.
	 */
	virtual void				orientationChanged(); //468
    
    /**
	 * 
	 */
	virtual void				resolutionChanged(); //473

	/**
	 * Called when user moves the mouse.
	 * If mouse has been captured (config.captureMouse=true in App init() function),
	 * then relative coordinates are received. Otherwise the coordinates
	 * are absolute, in window client area.
	 */
	virtual void				mouseMove( int dx, int dy ); //481
    
    /**
	 * 
	 * 
	 */
	virtual void				motion( double dx, double dy ); //487 | Unknown param names.
    
    /*
	 *
	 */
	virtual bool     			setControlsPresent(bool); //494 | Unknown param name.
    
    /**
	 *
	 */
	virtual void				mouseWheel( int ticks ); // 500 | Recover from GameApp
    
    /**
	 * 
	 */
	virtual void				touchBegan( const TouchEvent& touch ); //506
    
    /**
	 * 
	 */
	virtual void				touchMoved( const TouchEvent& touch ); //512
    
    /**
	 * 
	 */
	virtual void				touchEnded( const TouchEvent& touch ); //512
    
    /**
	 * 
	 */
	virtual void				touchCancel(); //518
    
    /**
	 * 
	 */
	virtual void				hoverBegan(int, int); //530 | Unknown parameter names.
    
    /**
	 * 
	 */
	virtual void				hoverMoved(int, int); //536
    
    /**
	 * 
	 */
	virtual void				hoverEnded(int, int); //542 | Unknown parameter names.

	/**
	 * Called when main window is activated or deactivated.
	 */
	virtual void				activate( bool active ); //548
    
    /**
	 * 
	 */
	virtual void				loadFromUrl( const std::string& url); //553
    
    /**
	 * 
	 */
	virtual bool				activateAudio( bool active ); //562 Recover param name via GameApp
    
    /**
	 * 
	 */
	const std::vector<TouchEvent>&	touches() const; //567

	/**
	 * Request application exit.
	 */
	void							quit( int returnCode ); //572 | [EDIT] Add return code

	/**
	 * Sets default data path.
	 */
	void							setDataPath( const std::string& datapath ); //577

	/**
	 * Returns expanded default path to data files.
	 */
	std::string						path( const std::string& filename="" ) const; //582

	/**
	 * Returns true if specified key is currently pressed down.
	 * State returned by this function is updated in default keyEvent implementation.
	 */
	bool						isKeyDown( KeyType key ) const; //588

	/** 
	 * Returns the application instance. 
	 */
	static App*					get(); //593

	/**
	 * Converts key type to string representation.
	 */
	static const char*			toString( KeyType key ); //598 | Is this still static?

	/*
	 * USED BY PLATFORM SPECIFIC IMPLEMENTATION.
	 * Note that platform specific implementation needs to use this
	 * since otherwise the state returned by isKeyDown state is not right.
	 * Note also that for example focus losing/gaining might cause
	 * key state buffer to be reset, so thats why better that
	 * platform specific impl handles everything instead of user application.
	 * Note that assumed behavior for focus lost/gain is that
	 * all key states are set to false, i.e. to application losing/gaining
	 * focus always looks like all the keys were released.
	 * Sets key down state.
	 * @see isKeyDown
	 */
	void						setKeyDown( KeyType key, bool down ); //613

	/*
	 * USED BY PLATFORM SPECIFIC IMPLEMENTATION.
	 * Returns true if application has requested exit.
	 */
	bool						quitRequested() const; //619
    
    /*
	 * 
	 */
	virtual bool				safeToQuit() const; //627
    
    /*
	 * 
	 */
	int   						getReturnCode() const; //632 | Not in ABSW XGS fork
    
    /*
	 * ?
	 */
	virtual void   		        softQuit(); //637
    
    /*
	 * 
	 * 
	 */
	virtual void   		        setMouseAvailable( bool ); //643 | Unknown param name.
    
    /*
	 * 
	 */
	OSInterface*   		        getOSInterface() const; //648 | Not in ABSW XGS fork

	/*
	 * USED BY PLATFORM SPECIFIC IMPLEMENTATION.
	 * Deletes application instance. 
	 */
	static void					deleteApp(); //654

	/*
	 * USED BY PLATFORM SPECIFIC IMPLEMENTATION.
	 * Returns true if App has been initialized.
	 */
	static bool					initialized(); //660

protected:
	OSInterface*						m_os; //663 | Protected now
	
private:
	io::PathName						m_dataPath; //666
	bool								m_keyDown[KEY_COUNT]; //667
	bool								m_quit; //668
	int                 				m_returnCode; //669
	std::vector<TouchEvent>   		m_touches; //670

	static App* 						sm_app; //672

	App( const App& ); //674
	App& operator=( const App& ); //675
};


/**
 * Allows application to adjust rendering device initialization parameters.
 * Called before init().
 * Implemented by the application.
 */
void configure( App::Configuration& config, OSInterface& os);

/**
 * Initializes the application instance.
 * Implemented by the application.
 */
framework::App* init(OSInterface* os, gr::Context* context);


} // framework


#endif // _FRAMEWORK_APP_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
