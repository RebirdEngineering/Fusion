#ifndef _GR_GL_IMAGE_H
#define _GR_GL_IMAGE_H

#include <gr/gl/GL_Context.h>
#include <gr/Image.h>

BEGIN_NAMESPACE(math)
	class float2;
	class float3;
	class float4;END_NAMESPACE()

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //I'm just as confused as you are

class GL_Image : //15
	public Image
{
public:
	GL_Image(GL_Context* context, int width, int height, int mipcount, Context::UsageFlags usage, NS(img, SurfaceFormat) format, bool flipped); //22

	~GL_Image(); //25

	void draw(Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH); //27

	void draw(Context* context, float dstX, float dstY, float targetW, float targetH, const NS(math, float2)* uv); //29

	void draw(Context* context, const NS(math, float3)* corners, const NS(math, float2)* uv, Shader* shader); //31
	void draw(Context* context, const NS(math, float3)* corners, const NS(math, float2)* uv, const NS(math, float4)* vertexColors, Shader* shader); //32

	void blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const NS(img, SurfaceFormat)& fmt); //46

	void clear(); //52

	int width() const; //57

	int height() const; //62

	bool flipped() const; //67

	img::SurfaceFormat format() const; //72

	void getData(void** bits, int* pitch) const; //77

	Texture* getTexture() const; //83

private:
	GL_Context* m_context; //86
	P(Texture) m_texture; //87
	int m_width; //88
	int m_height; //89
	bool m_flipped; //90

	void lock(LockType lock); //92
	void unlock(); //93
};

}
}

#endif