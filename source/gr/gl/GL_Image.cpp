#include <gr/gl/GL_Image.h>
#include <gr/Texture.h>

USING_NAMESPACE(img)
USING_NAMESPACE(math)

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //I'm just as confused as you are

GL_Image::GL_Image(GL_Context* context, int width, int height, int mipcount, Context::UsageFlags usage, SurfaceFormat format, bool flipped) : //40-57
	m_context(context),
	m_texture(0),
	m_width(width),
	m_height(height),
	m_flipped(flipped)
{
	m_texture = context->createTexture(width, height, mipcount, format.m_type, usage); //53-60
}

GL_Image::~GL_Image()
{
	m_context->getBatcher().flush(); //58
	delete m_texture;
}

void GL_Image::draw(Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH) //62
{
	/*const RenderState2D& state = m_context->getRenderState2D(); //64
	float3 vertpos[4]; //69
	float2 offset = state.getTranslation(); //72
	float2 scale = state.getScale(); //73
	float2 pivot = state.getRotationPivot(); //74
	float2 col0; //75
	float2 col1; //76
	//if (m_angle)
	float ex; //78
	float ey; //79
	float tx; //80
	float ty; //81
	float proj00 = m_context->viewport().width(); //82
	float proj11 = m_context->viewport().height(); //83
	float minx; //101
	float miny; //102
	float maxx; //103
	float maxy; //104
	int i; //105

	float2 offset; //118
	float2 scale; //119
	float tx; //121
	float ty; //122
	float proj00 = m_context->viewport().width(); //123
	float proj11 = m_context->viewport().height(); //124
	
	const float invWidth = m_texture->width(); //168
	const float invHeight = m_texture->height(); //169

	const float texXStart; //171
	const float texYStart; //172
	const float texXEnd; //173
	const float texYEnd; //174

	float2 vertuv[4]; //176

	//m_texture->clear();
	Shader* shader = m_texture->format().hasAlpha() || state.m_alpha > 1.0f ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader(); //184
	context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, vertuv, 0, this); //185*/
	assert("void GL_Image::draw(gr::Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH) is not yet decompiled.");
}

void GL_Image::draw(Context* context, float dstX, float dstY, float targetW, float targetH, const float2* uv) //188
{
	/*const RenderState2D& state = m_context->getRenderState2D(); //190

	float3 vertpos[4]; //195

	if (state.m_worldtmSet)
	{
		//Shader* shader = m_texture->; //212
	}

	float2 offset = state.getTranslation(); //219
	float2 scale = state.getScale(); //220
	float2 pivot = state.getRotationPivot(); //221
	float2 col0; //222
	float2 col1; //223
	
	float ex; //225
	float ey; //226
	float tx; //227
	float ty; //228
	float proj00 = .width(); //229
	float proj11 = .height(); //230
	float minx; //248
	float miny; //249
	float maxx; /250
	float maxy; //251
	int i; //252

	float2 offset; //265
	float2 scale; //266

	float tx; //268
	float ty; //269
	float proj00 = .width(); //270
	float proj11 = .height(); //271
	
	Shader* shader = m_texture->format().hasAlpha() || state.m_alpha > 1.0f ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader(); //315
	
	m_context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, uv, 0, this); //316*/
	assert("void GL_Image::draw(gr::Context* context, float dstX, float dstY, float targetW, float targetH, const math::float2* uv) is not yet decompiled.");
}

void GL_Image::draw(Context* context, const float3* corners, const float2* uv, Shader* shader) //319
{
	draw(context, corners, uv, 0, shader);
}

void GL_Image::draw(Context* context, const float3* corners, const float2* uv, const float4* vertexColors, Shader* shader) //324
{
	/*float proj00 = m_context->viewport().width(); //329
	float proj11 = m_context->viewport().height(); //330
	float3 vertpos[4]; //332
	vertpos[0] = float3(corners->x, corners->y, corners->z); //?
	vertpos[1] = float3(corners->x, corners->y, corners->z); //?
	vertpos[2] = float3(corners->x, corners->y, corners->z); //?
	vertpos[3] = float3(corners->x, corners->y, corners->z); //?

	float minx; //345
	float miny; //346
	float maxx; //347
	float maxy; //348
	int i; //349

	Shader* shader = m_texture->format().hasAlpha() ? m_context->getSpriteAlphaShader() : m_context->getSpriteShader(); //364
	m_context->getBatcher().render(RenderBatcher::TYPE_TEX, shader, vertpos, uv, vertexColors, this); //365*/
	assert("void GL_Image::draw(gr::Context* context, const math::float3* corners, const math::float2* uv, const math::float4* vertexColors, gr::Shader* shader) is not yet decompiled.");
}

void GL_Image::blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const SurfaceFormat& fmt) //368
{
	m_texture->blt(x, y, data, pitch, miplevel, w, h, fmt); //370
}

void GL_Image::clear()
{
	assert(!"Not implemented!"); //Yup
}

int GL_Image::width() const
{
	return m_width;
}

int GL_Image::height() const
{
	return m_height;
}

bool GL_Image::flipped() const
{
	return m_flipped;
}

SurfaceFormat GL_Image::format() const
{
	return m_texture->format(); //395
}

void GL_Image::lock(LockType lock)
{
	m_texture->lock(lock); //400
}

void GL_Image::unlock()
{
	m_texture->unlock(); //405
}

void GL_Image::getData(void** bits, int* pitch) const //408
{
	//assert(!"Not implemented!");
	m_texture->getData(bits, pitch); //410
}

Texture* GL_Image::getTexture() const
{
	return m_texture; //415
}

}
}