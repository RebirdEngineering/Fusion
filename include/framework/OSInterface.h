#ifndef _FRAMEWORK_OSINTERFACE_H
#define _FRAMEWORK_OSINTERFACE_H


#include <io/PathName.h>
#include <gr/Context.h>


namespace io {
	class DataInputStream;
	class DataOutputStream;}

namespace framework
{


/**
 * Interface to operating system specific functionality.
 */
class OSInterface
{
public:
	~OSInterface(); //27
	/**
	 * Loads all shaders from specific directory.
	 * After this the application can refer to the shader with
	 * its basename. For example after loading "high-end-shaders/bumpspecular.fx"
	 * application can simply request "bumpspecular" shader and
	 * get an instance of the previously loaded shader.
	 */
	virtual void							loadShaders( const std::string& path, bool recursesubdirs ) = 0; //35
	
	/**
	 * Returns path to default data directory.
	 */
	virtual std::string					getDefaultDataPath() = 0; //40

    virtual void							setResolution( int width, int height) = 0; //45

    virtual void							setOrientation( gr::Context::OrientationType orientation ) = 0; //50

    virtual void							allowSleep( bool allow ) = 0; //55

    virtual bool							isSilentProfile() = 0; //60

    virtual void							startUpdate() = 0; //65

    virtual void							stopUpdate() = 0; //71

    virtual void							setFullscreen( bool fullscreen ) = 0; //76 | Recover param name from ABFM

    virtual bool							isFullscreen() const = 0; //81

    virtual bool							captureMouse( bool capture ) = 0; //86 | Recover param name from ABFM

    virtual bool							isMouseCaptured() const = 0; //91

    virtual bool							setMousePosition( int x, int y ) = 0; //96 | Assuming lost param name from AB GameLua

    virtual void							setCursor( const std::string& cursor ) = 0; //103 | Recover from public KA3D

    const std::vector<std::string>&    getCommandLineArguments( ) const; //109

    int 									getArgc( ) const; //115

    char** 									getArgv( ) const; //121

    void									setCommandLineArguments( const std::vector<std::string>& ); //127

    void									setCommandLineArguments(int, char**); //134
    
private:
    std::vector<char*>								m_argv; //137
    std::vector<std::string>					m_arguments; //138
};


} // framework


#endif // _FRAMEWORK_OSINTERFACE_H
