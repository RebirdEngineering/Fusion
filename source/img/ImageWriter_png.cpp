#ifdef IMG_PNG_SUPPORT

#include <img/ImageWriter.h>
#include <io/IOException.h>
#include <lang/Log.h>
#include <external/libpng/png.h> //Todo replace


using namespace io;
using namespace lang;


namespace img
{

static void writefunc(struct png_struct_def* pngptr, unsigned char* data, png_size_t size)
{
	OutputStream* out = reinterpret_cast<OutputStream*>(png_get_io_ptr(pngptr));
	out->write(data, size);
}

static void flushfunc( png_structp )
{
}

static void errorhandler( struct png_struct_def*, const char* )
{
    //Debug::printf("ERROR:  PNG: %s\n"); //[ADD] Assuming this is here from SSTV
	LANG_LOG_DEBUG("", LANG_LOG_PRIORITY_ERROR, "ERROR:  PNG: %s\n");
}

static void warninghandler( struct png_struct_def*, const char* )
{
    //Debug::printf("WARN:  PNG: %s\n"); //[ADD] Assuming this is here from SSTV
	LANG_LOG_DEBUG("", LANG_LOG_PRIORITY_DEBUG, "WARN:  PNG: %s\n");
}

void ImageWriter::writePNG( OutputStream& out, const void* data, int width, int height, SurfaceFormat srcformat )
{
	// write header
	png_structp pngptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, errorhandler, warninghandler ); //[LHR] ABS4.1.0 is 1.6.2, ABC 5.2.0 is 1.6.17
	if ( !pngptr )
		throwError( IOException( Format("png_create_write_struct failed while saving \"{0}\" ({1}x{2}, srcformat {3})", out.toString(), width, height, srcformat.toString()) ) );

	png_infop infoptr = png_create_info_struct( pngptr );
	if ( !infoptr )
	{
		png_destroy_write_struct( &pngptr, 0 );
		throwError( IOException( Format("png_create_info_struct failed while saving \"{0}\" ({1}x{2}, format {3})", out.toString(), width, height, srcformat.toString()) ) );
	}

	png_set_write_fn( pngptr, &out, writefunc, flushfunc );
	SurfaceFormat dstformat = srcformat;
	int pngcolortype = srcformat.hasAlpha() ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB;
	dstformat = SurfaceFormat::SURFACE_R8G8B8;
	if ( srcformat.hasAlpha() )
		dstformat = SurfaceFormat::SURFACE_A8R8G8B8;

	png_set_IHDR( pngptr, infoptr, width, height, 8, pngcolortype,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE );

	png_set_bgr( pngptr );

	png_write_info( pngptr, infoptr );

	// write image
	std::vector<uint8_t> row(dstformat.getMemoryUsage(width, 1));
	for ( int i = 0 ; i < (int)height ; ++i )
	{
		const unsigned char* ptr;
		dstformat.copyPixels( &row.begin(), SurfaceFormat::SURFACE_UNKNOWN, 0, srcformat, data, SurfaceFormat::SURFACE_UNKNOWN, 0, width );
		png_write_row( pngptr, reinterpret_cast<png_bytep>(&row.begin()));
	}

	png_write_end( pngptr, infoptr );
	png_destroy_write_struct( &pngptr, &infoptr );
}


} // img

#endif // IMG_PNG_SUPPORT

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
