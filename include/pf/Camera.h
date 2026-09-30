#ifndef _PF_CAMERA_H
#define _PF_CAMERA_H

#include <lang/Object.h>

namespace pf //8
{

class CameraListener;

class Camera : //19 | Only mentioned via header?
	public lang::Object
{
public:
	class Size //23
	{
	public:
		Size(); //26
		int width; //27
		int height; //28

		Size(int w, int h); //30
	};
	enum Position //36
	{
		CAMERA_BACK,
		CAMERA_FRONT
	};
	enum Status //46
	{
		STATUS,
		READY,
		ERROR_GENERIC,
		ERROR_INIT,
		ERROR_SHOW
	};
	Camera(Position, CameraListener*); //64

	~Camera(); //66

	void showPreview(); //74

	void hidePreview(); //82

	std::vector<Size> getSupportedImageResolutions(); //89

	void setImageResolution(Size); //99

	void setPreviewBounds(int, int, Size); //108

	bool isSupported(); //114

	bool isAvailable(); //122

	Camera(const Camera&); //125
	Camera& operator=(const Camera&); //126
private:
	class Impl;
	std::shared_ptr<Impl> m_impl; //129
};

class CameraListener //137
{
public:
	virtual void onFrameAvailable(unsigned char*, size_t, int, int); //151

	virtual unsigned char* getBuffer(size_t); //160

	virtual void onCameraStatus(Camera::Status, const std::string&); //167
protected:
	std::vector<unsigned char> m_buffer; //170
};

}

#endif // !_PF_CAMERA_H