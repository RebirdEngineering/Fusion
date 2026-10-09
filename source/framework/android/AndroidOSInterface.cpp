#include <framework/android/AndroidOSInterface.h>

using namespace gr;

namespace framework
{

AndroidOSInterface::AndroidOSInterface()
{
}

void AndroidOSInterface::loadShaders(const std::string& path, bool recursesubdirs)
{
}

std::string AndroidOSInterface::getDefaultDataPath() //Correct?
{
	return "";
}

void AndroidOSInterface::setResolution(int width, int height)
{
}

void AndroidOSInterface::setOrientation(Context::OrientationType orientation)
{
}

void AndroidOSInterface::allowSleep(bool allow)
{
	//TODO REQUIRES JNI
}

bool AndroidOSInterface::isSilentProfile()
{
	//TODO REQUIRES JNI
	return false;
}

void AndroidOSInterface::startUpdate()
{
}

void AndroidOSInterface::stopUpdate()
{
}

void AndroidOSInterface::setFullscreen(bool fullscreen)
{
}

bool AndroidOSInterface::isFullscreen() const
{
	return true;
}

bool AndroidOSInterface::captureMouse(bool capture)
{
	return true;
}

bool AndroidOSInterface::isMouseCaptured() const
{
	return false;
}

bool AndroidOSInterface::setMousePosition(int x, int y)
{
	return false;
}

void AndroidOSInterface::setCursor(const std::string& cursor)
{

}

}