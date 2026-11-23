#include <gr/dx11/DX11_Image.h>
#include <gr/dx11/DX11_Texture.h>
#include <gr/dx11/DX11_Context.h>

using namespace img;
using namespace math;

namespace gr
{
	DX11_Image::DX11_Image(DX11_Context* context, int width, int height, int mipcount, Context::UsageFlags usage, NS(img, SurfaceFormat) format, int usageFlags) :
		m_context(context),
		m_texture(0),
		m_flipped(false),
		m_width(width),
		m_height(height)
	{
		m_texture = m_context->createTexture(width, height, mipcount, format, usageFlags);
	}

	void DX11_Image::lock(LockType lock) //10007E70
	{
		m_texture->lock(lock);
	}

	void DX11_Image::unlock() //10007E70
	{
		m_texture->unlock();
	}

	//void DX11_Image::draw() //10008BF0
	//{
	//
	//}

	void DX11_Image::draw(Context* context, const float3* corners, const float2* uv, const float4* vertexColors, Shader* shader) //10007DD0
	{
		draw(context, corners, uv, 0, shader);
	}

	//void DX11_Image::draw() //10008600
	//{
	//
	//}

	//void DX11_Image::draw() //10007FE0
	//{
	//
	//}

	void DX11_Image::blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const SurfaceFormat& fmt) //10007E30
	{
		m_texture->blt(x, y, data, pitch, miplevel, w, h, fmt);
	}

	void DX11_Image::clear()
	{
	}

	int DX11_Image::width() const //1007DF00
	{
		return m_width;
	}

	int DX11_Image::height() const //10007E00
	{
		return m_height;
	}

	bool DX11_Image::flipped() const //10007E10
	{
		return m_flipped;
	}

	SurfaceFormat DX11_Image::format() const //10007E40
	{
		return m_texture->format();
	}

	void DX11_Image::getData(void** bits, int* pitch) const //10007E80
	{
		m_texture->getData(bits, pitch);
	}

	Texture* DX11_Image::getTexture() const //10007E90
	{
		return m_texture;
	}
}