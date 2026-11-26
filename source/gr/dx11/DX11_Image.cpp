#include <gr/dx11/DX11_common.h>
#include <gr/dx11/DX11_Image.h>
#include <gr/dx11/DX11_Context.h>

using namespace img;
using namespace math;

namespace gr
{
	DX11_Image::DX11_Image(DX11_Context* context, int width, int height, int mipcount, Context::UsageFlags usage, SurfaceFormat format, int usageFlags) : //10007EA0
		m_context(context),
		m_texture(0),
		m_flipped(false),
		m_width(width),
		m_height(height)
	{
		m_texture = m_context->createTexture(width, height, mipcount, format, usageFlags);
	}

	DX11_Image::~DX11_Image() //10007F40
	{
		if (m_context->getBatcher().getImage() == this)
			m_context->getBatcher().flush();
	}

	void DX11_Image::lock(LockType lock) //10007E70
	{
		m_texture->lock(lock);
	}

	void DX11_Image::unlock() //10007E70
	{
		m_texture->unlock();
	}

	void DX11_Image::draw(Context* context, const float3* corners, const float2* uv, const float4* vertexColors, Shader* shader) //10008BF0 | TODO
	{
		//float proj00 = 2.0f / m_context->viewport().width();
		//float proj11 = -2.0f / m_context->viewport().height();
		//
		//float3 vertpos[4] = {
		//	float3(corners->x, corners->y, corners->z),
		//	float3(corners[1].x, corners[1].y, corners[1].z),
		//	float3(corners[2].x, corners[2].y, corners[2].z),
		//	float3(corners[3].x, corners[1].y, corners[3].z) };
		//
		//vertpos[0].x *= proj00 + -1.0;
		//vertpos[0].y *= proj11 + 1.0;
		//
		//vertpos[1].x *= proj00 + -1.0;
		//vertpos[1].y *= proj11 + 1.0;
		//
		//vertpos[2].x *= proj00 + -1.0;
		//vertpos[2].y *= proj11 + 1.0;
		//
		//vertpos[3].x *= proj00 + -1.0;
		//vertpos[3].y *= proj11 + 1.0;
		//
		//if (!shader)
		//	shader = m_texture->format().hasAlpha() ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader();
		//
		//m_context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, uv, vertexColors, this);;
	}

	void DX11_Image::draw(Context* context, const float3* corners, const float2* uv, Shader* shader) //10007DD0
	{
		draw(context, corners, uv, 0, shader);
	}

	void DX11_Image::draw(Context* context, float dstX, float dstY, float targetW, float targetH, const float2* uv) //10008600 | TODO
	{
		//const RenderState2D& state = m_context->getRenderState2D();
		//
		//float3 vertpos[4]; //Similar to hgr::Pipe::createOverlayPrimitive
		//
		//if (state.m_worldtmSet)
		//{
		//	vertpos[0] = float3(dstX, dstY, 0.f);
		//	vertpos[1] = float3(dstX + targetW, dstY, 0.f);
		//	vertpos[2] = float3(dstX, dstY + targetH, 0.0);
		//	vertpos[3] = float3(vertpos[1].x, vertpos[2].y, 0.f);
		//}
		//
		//if (state.getAngle() == 0.0)
		//{
		//	vertpos[0] = float3(?, ?, 0.001f);
		//	vertpos[1] = float3(?, ?, 0.001f);
		//	vertpos[2] = float3(?, ?, 0.001f);
		//	vertpos[3] = float3(?, ?, 0.001f);
		//}
		//
		//Shader* shader = m_texture->format().hasAlpha() || state.getAlpha() > 1.0f ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader();
		//m_context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, uv, 0, this);
	}

	void DX11_Image::draw(Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH) //10007FE0 | TODO
	{
		//const RenderState2D& state = m_context->getRenderState2D();
		//
		//float3 vertpos[4]; //Similar to hgr::Pipe::createOverlayPrimitive
		//
		//if (state.getAngle() == 0.0)
		//{
		//}
		//
		//float2 uv(1.0, 1.0);
		//
		//Shader* shader = m_texture->format().hasAlpha() || state.getAlpha() > 1.0f ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader();
		//m_context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, &uv, 0, this);
	}

	void DX11_Image::blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const SurfaceFormat& fmt) //10007E30
	{
		m_texture->blt(x, y, data, pitch, miplevel, w, h, fmt);
	}

	void DX11_Image::clear() //Blank!
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