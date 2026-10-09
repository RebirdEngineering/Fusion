#include <framework/OSInterface.h>

namespace framework
{

class AndroidOSInterface : public OSInterface
{
public:
	AndroidOSInterface();

	~AndroidOSInterface();

	/**
	 * Loads all shaders from specific directory.
	 * After this the application can refer to the shader with
	 * its basename. For example after loading "high-end-shaders/bumpspecular.fx"
	 * application can simply request "bumpspecular" shader and
	 * get an instance of the previously loaded shader.
	 */
	void							loadShaders(const std::string& path, bool recursesubdirs);

	/**
	 * Returns path to default data directory.
	 */
	std::string					getDefaultDataPath();

	void							setResolution(int width, int height);

	void							setOrientation(gr::Context::OrientationType orientation);

	void							allowSleep(bool allowSleep);

	bool							isSilentProfile();

	void							startUpdate();

	void							stopUpdate();

	void							setFullscreen(bool fullscreen);

	bool							isFullscreen() const;

	bool							captureMouse(bool capture);

	bool							isMouseCaptured() const;

	bool							setMousePosition(int x, int y);

	void							setCursor(const std::string& cursor);

private: //GUESSES FROM iOS
	int m_appController;
	int m_orientation;
	std::string m_defaultDataPath;
	bool m_userDisabledUpdate;
};

}