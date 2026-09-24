#ifndef _PF_CAMERA_H
#define _PF_CAMERA_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class Camera :
	public NS(lang,Object)
{
public:
	class Size
	{
	public:
		int width;
		int height;
		Size();
	};
	enum Position
	{
		CAMERA_BACK,
		CAMERA_FRONT
	};
	enum Status
	{
		STATUS,
		READY,
		ERROR_GENERIC,
		ERROR_INIT,
		ERROR_SHOW
	};
	Camera(Position, CameraListener*);
	~Camera();

	void showPreview();

	void hidePreview();

	std::vector<Size> getSupportedImageResolutions();

	void setImageResolution(Size);

	void setPreviewBounds(int, int, Size);

	bool isSupported();

	bool isAvailable();

	Camera(const Camera&);
	Camera& operator=(const Camera&);
private:
	SP(Impl) m_impl;
};

class CameraListener
{
public:
	virtual void onFrameAvailable(unsigned char*, size_t, int, int);

	virtual unsigned char* getBuffer(size_t);

	virtual void onCameraStatus(Status, const std::string&);
protected:
	std::vector<unsigned char> m_buffer;
};

}

#endif // !_PF_CAMERA_H