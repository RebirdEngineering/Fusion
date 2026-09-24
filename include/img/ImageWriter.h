#ifndef _IMG_IMAGEWRITER_H
#define _IMG_IMAGEWRITER_H


#include <img/SurfaceFormat.h> //Move
#include <io/OutputStream.h>
#include <io/FileFormat.h>

BEGIN_NAMESPACE(io)
	class OutputStream; END_NAMESPACE()

BEGIN_NAMESPACE(img)

/**
 * Image file writer.
 * @ingroup img
 */
class ImageWriter :
	public NS(lang,Object)
{	
public:
	/**
	 * Saves image file and tries to guess format by filename.
	 * @exception IOException
	 */
	static void	write( NS(io, OutputStream)& out, NS(io, FileFormat) fileformat, //33
					const void* data, int width, int height,
					NS(img, SurfaceFormat) srcformat, NS(img, SurfaceFormat) dstformat);
	/**
	 * Saves image as PNG file.
	 * @exception IOException
	 */                    
    static void	writePNG( NS(io, OutputStream)& out,
					const void* data, int width, int height, NS(img, SurfaceFormat) srcformat );
    
    /**
	 * 
	 * 
	 */                
    static void	writeJPG( NS(io ,OutputStream)& out,
					const void* data, int width, int height, NS(img, SurfaceFormat) srcformat, int quality );
                    
    /**
	 * 
	 * 
	 */                
    static void	writePVR( NS(io, OutputStream)& out,
					const void* data, int width, int height, NS(img, SurfaceFormat) srcformat, int quality );


	/**
	 *
	 *
	 */
	static void	writeLosslessWebP(NS(io, OutputStream) & out,
		const void* data, int width, int height, NS(img, SurfaceFormat) srcformat );


	/**
	 *
	 *
	 */
	static void	writeLossyWebP(NS(io, OutputStream) & out,
		const void* data, int width, int height, NS(img, SurfaceFormat) srcformat, int quality);

};


END_NAMESPACE() // img


#endif // _IMG_IMAGEWRITER_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
