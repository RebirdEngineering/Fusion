#include <pf/Camera.h>

using namespace lang;

namespace pf
{

class CameraImpl : public Object
{
public:
	CameraImpl(Camera::Position, CameraListener*)
	{
	}

	~CameraImpl()
	{
	}

	void showPreview();

	void hidePreview();

	std::vector<Camera::Size> getSupportedImageResolutions();

	void setImageResolution(Camera::Size);

	void setPreviewBounds(int, int, Camera::Size);

	bool isSupported()
	{
		return false;
	}

	bool isAvailable();
};

//#include <pf/common/Camera.h> //Doesn't exist? Well then how does this work?

}