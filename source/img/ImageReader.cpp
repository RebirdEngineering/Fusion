#include <img/ImageReader.h>
#include <io/IOException.h>


USING_NAMESPACE(io)
USING_NAMESPACE(lang)


BEGIN_NAMESPACE(img) //TODO ASSERTS


ImageReader::ImageReader() :
	m_in( 0 ),
	m_width( 0 ),
	m_height( 0 ),
	m_bitsPerPixel( 0 ),
	m_pitch( 0 ),
	m_mipLevels( 1 ),
	m_surfaces( 0 ),
	m_surfaceIndex( 0 ),
	m_fmt(),
	m_palfmt(),
	m_filefmt( FILEFORMAT_UNKNOWN ),
	m_bottomUp( false ),
	m_useRLE( false ),
	m_cubeMap( false ),
	m_colorKeyEnabled( false )
{
}

ImageReader::ImageReader( P(InputStream) in, FileFormat filefmt ) :
	m_in(in),
	m_width(0),
	m_height(0),
	m_bitsPerPixel(0),
	m_pitch(0),
	m_mipLevels(1),
	m_surfaces(0),
	m_surfaceIndex(0),
	m_fmt(),
	m_palfmt(),
	m_filefmt(filefmt),
	m_bottomUp(false)
{
	switch (m_filefmt)
	{
	case FILEFORMAT_BMP:	readHeader_bmp(); break;
	case FILEFORMAT_TGA:	readHeader_tga(); break;
#ifdef IMG_JPG_SUPPORT
	case FILEFORMAT_JPG:	readHeader_jpg(); break;
#endif
#ifdef IMG_IL_SUPPORT
	case FILEFORMAT_PNG:	readHeader_png(); break;
	case FILEFORMAT_DDS:
	case FILEFORMAT_PSD:
	case FILEFORMAT_PCX:
	case FILEFORMAT_PNM:
	case FILEFORMAT_GIF:
	//case FILEFORMAT_TIF:	readHeader_il(); break;
	case FILEFORMAT_PVR:	readHeader_pvr(); break;
	case FILEFORMAT_WEBP:	readHeader_webp(); break;
#endif // IMG_IL_SUPPORT
	default:				throwError(IOException(Format("Unsupported image file format while reading {0}", m_in->toString())));
	}
}

ImageReader::~ImageReader()
{
}

void ImageReader::readSurface( void* bits, int pitch, int w, int h, SurfaceFormat fmt,
	const void* pal, SurfaceFormat palfmt )
{
	assert( w == surfaceWidth() ); //[NOTE] Assert on line 103
	assert( h == surfaceHeight() ); //[NOTE] Assert on line 104
	
	switch ( m_filefmt )
	{
    case FILEFORMAT_PVR:
	case FILEFORMAT_BMP:
	case FILEFORMAT_TGA:
		readScanlines( bits, pitch, w, h, fmt, pal, palfmt );
		break;

#ifdef IMG_JPG_SUPPORT
	case FILEFORMAT_JPG:
		readSurface_jpg(bits, pitch, w, h, fmt, pal, palfmt);
		break;
#endif // IMG_JPG_SUPPORT

	default:
		readSurfaceFromSurfaceBuffer( bits, pitch, w, h, fmt, pal, palfmt );
		break;
	}
}

int ImageReader::surfaces() const
{
	return m_surfaces;
}

int	ImageReader::surfaceIndex() const
{
	return m_surfaceIndex;
}

bool ImageReader::cubeMap() const
{
	return m_cubeMap;
}

int ImageReader::mipLevels() const
{
	return m_mipLevels;
}

SurfaceFormat ImageReader::format() const
{
	return m_fmt;
}

const void* ImageReader::paletteData() const
{
	return &m_colormap[0][0];
}

SurfaceFormat ImageReader::paletteFormat() const
{
	return m_palfmt;
}

int ImageReader::surfaceWidth() const
{
	return m_width;
}

int ImageReader::surfaceHeight() const
{
	return m_height;
}

void ImageReader::readFully( P(InputStream) in, void* buf, int bytes ) //guessFileFormat has been moved to IO in private KA3D
{
	if ( in->read(buf,bytes) != bytes )
		throwError( IOException( Format("Failed to read {0} bytes from {1}", bytes, in->toString()) ) );
}

void ImageReader::readColorMap( P(InputStream) in, int entrysize, int entries, uint8_t* colormap )
{
	uint8_t colr[4];
	for ( int i = 0 ; i < entries ; ++i )
	{
		memset( colr, 0, sizeof(colr) );
		readFully( in, colr, entrysize );
		colormap[i*4+0] = colr[2];
		colormap[i*4+1] = colr[1];
		colormap[i*4+2] = colr[0];
		colormap[i*4+3] = colr[3];
	}
}

uint16_t ImageReader::getUInt16LE( const void* data, int offset )
{
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data) + offset;
	return uint16_t( ( unsigned(bytes[1]) << 8 ) + unsigned(bytes[0]) );
}

uint32_t ImageReader::getUInt32LE( const void* data, int offset )
{
	const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data) + offset;
	return ( uint32_t(bytes[3]) << 24 ) + ( uint32_t(bytes[2]) << 16 ) + ( uint32_t(bytes[1]) << 8 ) + uint32_t(bytes[0]);
}

void ImageReader::readScanlines( void* bits, int pitch, int w, int h, SurfaceFormat fmt,
	const void* pal, SurfaceFormat palfmt )
{
	assert( w == m_width ); //[NOTE] Assert on line 206
	assert( h == m_height ); //[NOTE] Assert on line 207

	// make sure we have big enough scanline buffer,
	// but use dynamic allocation only if absolutely necessary
	//ByteTempBuffer tempbuffer( m_pitch*2 );
	uint8_t* scanlinebuffer = (uint8_t*)m_tempBuffer.size();

	// read pixels
	for ( int j = 0 ; j < m_height ; ++j )
	{
		switch ( m_filefmt )
		{
		case FILEFORMAT_BMP:
		case FILEFORMAT_TGA:
			if ( m_useRLE )
				readScanline_tgaRLE( scanlinebuffer );
			else
				readFully( m_in, scanlinebuffer, m_pitch );
			break;
#ifdef IMG_JPG_SUPPORT
		case FILEFORMAT_JPG:
			readScanline_jpg( scanlinebuffer );
			break;
#endif // IMG_JPG_SUPPORT
		default:
			throwError( IOException( Format("Unsupported image file format while reading {0}", m_in->toString()) ) );
		}

		int j1 = j;
		if ( m_bottomUp )
			j1 = m_height - j - 1;
		uint8_t* dst = reinterpret_cast<uint8_t*>(bits) + j1*pitch;

		if ( fmt.type() == m_fmt.type() )
			memcpy( dst, scanlinebuffer, (m_width*m_fmt.bitsPerPixel()+7)>>3 );
		else
			fmt.copyPixels( dst, palfmt, pal, m_fmt, scanlinebuffer, m_palfmt, &m_colormap[0][0], m_width );
	}
}

void ImageReader::readSurfaceFromSurfaceBuffer( void* bits, int pitch, 
	int w, int h, SurfaceFormat fmt, const void* pal, SurfaceFormat palfmt ) //[TODO ADD] ETC1 RGB 4BPP
{
	assert( m_surfaceIndex >= 0 && m_surfaceIndex < m_surfaceBuffer.size() ); //[NOTE] Assert on line 315
	
	Surface& s = m_surfaceBuffer[m_surfaceIndex];
	assert( s.width == w ); //[NOTE] Assert on line 318
	assert( s.height == h ); //[NOTE] Assert on line 319

	if (m_fmt.type() != SurfaceFormat::SURFACE_ETC1_RGB_4BPP && fmt.type() == m_fmt.type()) //?
	{
		memcpy(bits, &s.data[0], s.data.size());
	}

	fmt.copyPixels( bits, pitch, palfmt, pal,
		m_fmt, &s.data[0], s.width*m_fmt.bitsPerPixel()/8, m_palfmt, m_colormap,
		w, h );

	// iterate to next surface
	m_surfaceIndex++;
	if ( m_surfaceIndex < m_surfaceBuffer.size() )
	{
		m_width = m_surfaceBuffer[m_surfaceIndex].width;
		m_height = m_surfaceBuffer[m_surfaceIndex].height;
	}
}

END_NAMESPACE() // img

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
