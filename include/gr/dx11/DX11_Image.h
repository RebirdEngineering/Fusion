#ifndef _GR_DX11_Image_H
#define _GR_DX11_Image_H

#include <gr/Context.h>
#include <gr/Image.h>

namespace math
{
	class float2;
	class float3;
	class float4;
}

namespace gr
{

class DX11_Context;

class DX11_Image : //0x24 bytes.
	public Image
{
public:
	DX11_Image(DX11_Context* context, int width, int height, int mipcount, Context::UsageFlags usage, NS(img, SurfaceFormat) format, int usageFlags);

	~DX11_Image();

	void draw(Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH);

	void draw(Context* context, float dstX, float dstY, float targetW, float targetH, const NS(math, float2)* uv);

	void draw(Context* context, const NS(math, float3)* corners, const NS(math, float2)* uv, Shader* shader);
	void draw(Context* context, const NS(math, float3)* corners, const NS(math, float2)* uv, const NS(math, float4)* vertexColors, Shader* shader);

	void blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const NS(img, SurfaceFormat)& fmt);

	void clear();

	int width() const;

	int height() const;

	bool flipped() const;

	img::SurfaceFormat format() const;

	void getData(void** bits, int* pitch) const;

	Texture* getTexture() const;

private:
	DX11_Context* m_context; //0x10
	P(Texture) m_texture; //0x14 | Do we base off DX9? If so, tex, otherwise, we'll use GL's texture.
	int m_width; //0x18
	int m_height; //0x1C
	bool m_flipped; //0x20

	void lock(LockType lock);
	void unlock();
};

}

#endif