#ifndef _GR_IMAGE_H
#define _GR_IMAGE_H


#include <img/SurfaceFormat.h> //Move to img
#include <gr/ContextObject.h>

BEGIN_NAMESPACE(math) 
	class float2;
	class float3;
	class float4;END_NAMESPACE()

BEGIN_NAMESPACE(gr)

class Texture;
class Context;
class Shader;

/**
 * Simple 32-bit A8R8G8B8 image.
 * @ingroup gr (moved from img)
 */
class Image : //20
	public ContextObject
{	
public:
	Image( ); //24
	
	virtual void 				draw(Context* context, float dstX, float dstY, int srcX, int srcY, int w, int h, float targetW, float targetH) = 0; //26
	
	virtual void 				draw(Context* context, float dstX, float dstY, float srcX, float srcY, const math::float2* uv) = 0; //28
	
	virtual void 				draw(Context* context, const math::float3* corners, const math::float2* uv, Shader* shader) = 0; //30
		
	virtual void 				draw(Context* context, const math::float3* corners, const math::float2* uv, const math::float4* vertexColors, Shader* shader) = 0; //32 | Unused? Names are guessed.

	virtual void 				blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const img::SurfaceFormat& fmt) = 0; //46
	
	virtual void 				clear() = 0; //52

	/**
	 * Returns image width in pixels.
	 */
	virtual int					width() const = 0; //57

	/**
	 * Returns image height in pixels.
	 */
	virtual int					height() const = 0; //62
	
	virtual bool				flipped() const = 0; //67

	virtual img::SurfaceFormat		format() const = 0; //72
	
	/**
	 * Returns access to locked data. Requires that texture is locked before calling this.
	 */
	virtual void				getData( void** bits, int* pitch ) const = 0; //77
    
	virtual Texture*			getTexture() const { return 0; } //83
};


} // gr


#endif // _GR_IMAGE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
