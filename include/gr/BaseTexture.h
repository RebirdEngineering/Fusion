#ifndef _GR_BASETEXTURE_H 
#define _GR_BASETEXTURE_H

#include <gr/ContextObject.h>
#include <img/SurfaceFormat.h> //Move to img

BEGIN_NAMESPACE(gr)

/**
 * Base class for platform dependent textures.
 * @ingroup gr
 */
class BaseTexture : //12
	public ContextObject
{
public:
	explicit BaseTexture( ClassId classid ); //16

	/**
	 * Returns texture top level surface width in pixels.
	 */
	virtual int				width() const = 0; //21

	/**
	 * Returns texture top level surface height in pixels.
	 */
	virtual int				height() const = 0; //26

	/**
	 * Returns surface pixel storage format of this texture.
	 */
	virtual NS(img, SurfaceFormat) 	format() const = 0; //31
};


END_NAMESPACE() // gr


#endif // _GR_BASETEXTURE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
