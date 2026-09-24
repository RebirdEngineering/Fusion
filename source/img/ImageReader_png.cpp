#ifdef IMG_PNG_SUPPORT

#include <img/ImageReader.h>
#include <io/IOException.h>
#include <lang/Log.h>
#include <external/libpng/png.h>


using namespace io;
using namespace lang;

namespace img
{

static void readfunc( png_structp pngptr, png_bytep data, png_size_t length )
{
	InputStream* in = reinterpret_cast<InputStream*>( png_get_io_ptr(pngptr) );
	assert( in != 0 ); //[NOTE] DF line 20 / AA line 19
	in->read( data, length );
}

static void errorhandler( struct png_struct_def* pngptr, const char* text)
{
    //Debug::printf("ERROR:  PNG: %s\n"); //[ADD] printout from SSTV [OLD]
	//InputStream* in = reinterpret_cast<InputStream*>(png_get_io_ptr(pngptr));
	//LANG_LOG("PNG", LANG_LOG_PRIORITY_ERROR, "%s (offset %zu in file %s)", text, in->toString()); //28
}

static void warninghandler( struct png_struct_def* pngptr, const char* text )
{
    //Debug::printf("WARN:  PNG: %s\n"); //[ADD] printout from SSTV
	//InputStream* in = reinterpret_cast<InputStream*>(png_get_io_ptr(pngptr));
	//LANG_LOG("PNG", LANG_LOG_PRIORITY_WARN, "%s (offset %zu in file %s)", text, in->toString()); //34
}

void ImageReader::readHeader_png() //Correct?
{
	png_byte sig[8];
	m_in->read(sig, sizeof(sig));
	if ( !png_sig_cmp(sig, 0, 8) )
		throwError( IOException( Format("png_check_sig failed while loading \"{0}\". File is not png?", m_in->toString()) ) );    
    
	// BUG: overwrites some memory?? crashes zaxdemo etc.

	png_structp pngptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, errorhandler, warninghandler ); //ABS410 is 1.6.2.
	if ( !pngptr )
		throwError( IOException( Format("png_create_read_struct failed while loading \"{0}\"", m_in->toString()) ) );

	png_infop infoptr = png_create_info_struct( pngptr );
	if ( !infoptr )
	{
		png_destroy_read_struct( &pngptr, 0, 0 );
		throwError( IOException( Format("png_create_info_struct failed while loading \"{0}\"", m_in->toString()) ) );
	}

	png_set_read_fn( pngptr, m_in, readfunc );
	png_set_error_fn( pngptr, 0, errorhandler, warninghandler );
	png_set_sig_bytes( pngptr, 8 ); //[UNCOMMENTED]
	png_read_info( pngptr, infoptr );

	png_uint_32 w, h;
	int bitspp, colortype;
	png_get_IHDR( pngptr, infoptr, &w, &h, &bitspp, &colortype, 0, 0, 0 );
	// expand gray scale & 1-4 bitsperpixel -> 8 bit indexed
	if (png_get_bit_depth(pngptr, infoptr) < 8)
		png_set_expand(pngptr);
	// refresh info
	png_read_update_info(pngptr, infoptr);
	png_get_IHDR( pngptr, infoptr, &w, &h, &bitspp, &colortype, 0, 0, 0 );
	
	m_width = w;
	m_height = h;
	m_bitsPerPixel = m_fmt.bitsPerPixel();
	m_pitch = m_fmt.getMemoryUsage(m_width, 1);
	m_mipLevels = 1;
	m_surfaces = 1;

	switch ( colortype )
	{
	case PNG_COLOR_TYPE_GRAY:
		m_fmt = SurfaceFormat::SURFACE_L8;
		break;
	case PNG_COLOR_TYPE_RGB:
		m_fmt = SurfaceFormat::SURFACE_B8G8R8;
		break;
	case PNG_COLOR_TYPE_PALETTE:
		m_fmt = SurfaceFormat::SURFACE_P8;
		m_palfmt = SurfaceFormat::SURFACE_A8R8G8B8;
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		m_fmt = SurfaceFormat::SURFACE_A8L8;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		m_fmt = SurfaceFormat::SURFACE_A8R8G8B8;
		break;
	}

	// read color map
	if ( PNG_COLOR_TYPE_PALETTE == colortype ) //According to decomp it's in case 3, is that true?
	{
		memset( m_colormap, 0xFF, sizeof(m_colormap) );

		png_colorp pal;
		int numpal;
		png_get_PLTE( pngptr, infoptr, &pal, &numpal );
		assert( numpal <= 256 ); //[NOTE] DF line 79 / AA line 81

		for ( int i = 0 ; i < numpal ; ++i )
		{
			m_colormap[i][0] = pal[i].blue;
			m_colormap[i][1] = pal[i].green;
			m_colormap[i][2] = pal[i].red;
		}
	}
    //assert(m_fmt.bitsPerPixel() == infoptr->pixel_depth); //[NOTE] DF line 102 / AA line 104
    //assert((unsigned int)m_fmt.getMemoryUsage(w, 1) == infoptr->rowbytes); //[NOTE] DF line 103 / AA line 105


    // read transparency

	assert( !(png_get_valid(pngptr, infoptr, PNG_INFO_tRNS) && bitspp > 8) ); // weird combo?? bpp>8 and still tRNS chunk? //[NOTE] DF line 113 / AA line 115
	if ( png_get_valid(pngptr, infoptr, PNG_INFO_tRNS) && bitspp > 8 )
		png_set_tRNS_to_alpha( pngptr );
	if ( png_get_valid(pngptr, infoptr, PNG_INFO_tRNS) && bitspp <= 8 )
	{
		png_bytep trans = 0;
		int numtrans = 0;
		png_color_16p transvalues = 0;
		png_get_tRNS( pngptr, infoptr, &trans, &numtrans, &transvalues );
		assert( numtrans <= 256 ); //[NOTE] DF line 122 / AA line 124
	
		for ( int i = 0 ; i < numtrans ; ++i )
			m_colormap[i][3] = trans[i];
	}

	// read surface
	int channels = png_get_channels( pngptr, infoptr );
	std::vector<png_byte*> rowptrs( m_height );
	m_surfaceBuffer.resize( 1 );
	Surface& surface = m_surfaceBuffer[0];
	surface.width = m_width;
	surface.height = m_height;
	surface.data.resize( m_height*m_pitch );
	for ( int i = 0 ; i < m_height ; ++i )
		rowptrs[i] = &surface.data[m_pitch*i];
	png_read_image(pngptr, &rowptrs[0] );

	if ( pngptr && infoptr )
		png_destroy_read_struct( &pngptr, &infoptr, 0 );
}


} // img

#else // !IMG_PNG_SUPPORT

#include <img/ImageReader.h>
#include <io/InputStream.h>
#include <io/IOException.h>

void img::ImageReader::readHeader_png()
{
	lang::throwError( io::IOException( lang::Format("PNG file support is not enabled (file {0})", m_in->toString()) ) );
}

#endif // IMG_PNG_SUPPORT

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
