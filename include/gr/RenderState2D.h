#ifndef _GR_RENDERSTATE2D_H
#define _GR_RENDERSTATE2D_H

#include <gr/Rect.h>
#include <math/float4x4.h>
#include <math/Transform.h>

BEGIN_NAMESPACE(gr) //We use this since it's vastly similar to KA3D

class RenderState2D //14
{
public:
	enum BlendingFactor //20
	{
		ZERO,
		ONE,
		SRC_COLOR,
		ONE_MINUS_SRC_COLOR,
		SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA,
		DST_ALPHA,
		ONE_MINUS_DST_ALPHA,
		DST_COLOR,
		ONE_MINUS_DST_COLOR,
		SRC_ALPHA_SATURATE,
	};

	RenderState2D() : //35
		m_clip(-32000, -32000, -32000, -32000),
		m_col0(0, 1),
		m_col1(0, 1),
		m_translation(0, 0),
		m_scale(1, 1),
		m_pivot(0, 0),
		m_alpha(1.f),
		m_angle(0.f),
		m_worldtmSet(false),
		m_worldtm(1),
		m_blendEnabled(true),
		m_blendSrc(ONE),
		m_blendDst(ONE_MINUS_SRC_ALPHA)
	{
	}

	void reset() //40 | Called by GameLua::drawRect, GameLua::drawTexturedRect, GameLua::drawForegroundNative, GameLua::drawLayer
	{
		memcpy(this, this, sizeof(RenderState2D));
	}

	void setClip(int x0, int y0, int x1, int y1) //43 | Symbol only exists in ABS410. Unknown paramaters, guessing Rect's.
	{
		m_clip = Rect(x0, y0, x1, y1);
	}

	void setClip(const Rect& rect) //46 | Called by game::Resources::setClipRect, rovioshelf::RovioShelf::Impl::render(won't be part of Fusion)
	{
		m_clip = rect;
	}

	void setRotationPivot(const NS(math, float2)& pivot) //49 | Called by GameLua::setRenderState
	{
		m_pivot = pivot;
	}

	void setScalePivot(const NS(math, float2)& pivot) //52 | Unknown parameter. Assuming pivot
	{
		m_scalePivot = pivot;
	}

	void setTranslation(const NS(math, float2)& translation) //55 | Called by GameLua::setRenderState, GameLua::drawBox, GameLua::drawSlingScope, GameLua::drawGame, GameLua::drawLayer and rovioshelf::RovioShelf::Impl::render
	{
		m_translation = translation;
	}

	void setScale(const NS(math, float2)& scale) //58 | Called by GameLua::setRenderState, GameLua::drawBox, GameLua::drawSlingScope, rovioshelf::RovioShelf::Impl::render
	{
		m_scale = scale;
	}

	void setAngle(float angle) //61 | Called by GameLua::setRenderState, GameLua::drawBackgroundNative, GameLua::drawGame, particle::Manager::draw
	{
		m_angle = angle;
	}

	void setAlpha(float alpha) //64 | Called by GameLua::setRenderState, GameLua::setAlpha (really a pointer to this), GameLua::drawUITextInternal, GameLua::drawBackgroundNative, GameLua::drawForegroundNative
	{
		m_alpha = alpha;
	}

	void setSaturation(float saturation) //67
	{
		m_saturation = saturation;
	}

	Rect getClip() const //70
	{
		return m_clip;
	}

	NS(math, float2) getRotationPivot() const //73 | Called by MaskTexturizer::addMask, gr::gles2::GL_Context::fillCircle2D
	{
		return m_pivot;
	}

	NS(math, float2) getScalePivot() const //76
	{
		return m_scalePivot;
	}

	NS(math, float2) getTranslation() const //79
	{
		return m_translation;
	}

	NS(math, float2) getScale() const //82 | Called by gr::gles2::GL_Context::fillCircle2D, gr::gles2::GL_Image::draw, rovioshelf::RovioShelf::Impl::render
	{
		return m_scale;
	}

	float getAngle() const //85 | Called by gr::RenderBatcher::flush
	{
		return m_angle;
	}

	float getAlpha() const //88 | Called by gr::gles2::GL_Context::fillCircle2D, gr::gles2::GL_Context::drawLine2D, gr::gles2::GL_Context::fillRect2D
	{
		return m_alpha;
	}

	float getSaturation() const //91
	{
		return m_saturation;
	}

	void setWorldTransform(const NS(math, float4x4)& worldtm) //94 | Unknown parameter, assuming worldtm
	{
		m_worldtm = worldtm;
	}

	void resetWorldTransform() //97 | Unused?
	{
	}
	
	const NS(math, float4x4)& getWorldTransform() const //100 | Called by MaskTexturizer::render, Spotlight::render, Vignette::render, gr::RenderBatcher::flush
	{
		return m_worldtm;
	}

	void resetTransform() //102 | Called by game::CompoSprite::draw
	{
		m_translation = NS(math, float2)(0, 0);
		m_angle = 0.f;
		m_scale = NS(math, float2)(1, 1);
	}

	NS(math, Transform) getTransform() const //109
	{
		return NS(math, Transform)();
	}

	Rect m_clip; //121
	NS(math, float2) m_col0; //122
	NS(math, float2) m_col1; //123
	NS(math, float2) m_translation; //124
	NS(math, float2) m_scale; //125
	NS(math, float2) m_pivot; //126
	NS(math, float2) m_scalePivot; //127
	float m_alpha; //128
	float m_saturation; //129
	float m_angle; //130
	bool m_worldtmSet; //131
	NS(math, float4x4) m_worldtm; //132

	bool m_blendEnabled; //135
	BlendingFactor m_blendSrc; //136
	BlendingFactor m_blendDst; //137
};

END_NAMESPACE()

#endif