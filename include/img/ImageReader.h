#ifndef _IMG_IMAGEREADER_H
#define _IMG_IMAGEREADER_H


#include <io/FileFormat.h> //Move
#include <io/ByteArrayInputStream.h>
#include <lang/Object.h>
#include <img/SurfaceFormat.h>

namespace img
{


/**
 * Low level image file reader.
 * @ingroup img
 */
class ImageReader :
	public lang::Object
{	
public:

	ImageReader();

	/**
	 * Starts reading image file using specified format.
	 * Note that ImageReader does not add a reference to InputStream,
	 * so you must make sure InputStream exists as long as the image is read from it.
	 * @exception IOException
	 */
	ImageReader( P(io::InputStream) in, io::FileFormat filefmt );

	///
	~ImageReader();

	/**
	 * Reads data of current active surface and iterates reading to next surface.
	 *
	 * Iteration order for cubemaps:
	 * <ol>
	 * <li>All mipmaps for +X surface
	 * <li>All mipmaps for -X surface
	 * <li>All mipmaps for +Y surface
	 * <li>All mipmaps for -Y surface
	 * <li>All mipmaps for +Z surface
	 * <li>All mipmaps for -Z surface
	 * <li>...
	 * </ol>
	 *
	 * @exception IOException
	 */
	void 				readSurface( void* bits, int pitch, int w, int h, SurfaceFormat fmt,
							const void* pal, SurfaceFormat palfmt );
	
	/**
	 * Returns total number of surfaces to be read.
	 * This includes all mipmap levels too,
	 * i.e. for cubemap with three mipmap levels surfaces() will be 18.
	 */
	int					surfaces() const;

	/**
	 * Returns index of current surface being read.
	 */
	int					surfaceIndex() const;

	/**
	 * Returns true if the image is cube map.
	 */
	bool				cubeMap() const;

	/**
	 * Returns number of mipmap levels in image.
	 * Minimum returned value is 1 (this level).
	 */
	int					mipLevels() const;

	/**
	 * Returns pixel format of the image.
	 */
	SurfaceFormat	format() const;

	/**
	 * Returns pointer to palette data if any.
	 * Palette data is file format dependent.
	 * @return 0 if no palette.
	 */
	const void*			paletteData() const;

	/**
	 * Returns pixel format of the palette if any.
	 * @return SURFACE_UNKNOWN if palette data format is non-standard.
	 */
	SurfaceFormat	paletteFormat() const;
	
	/**
	 * Returns width of current active surface in pixels.
	 */
	int					surfaceWidth() const;
	
	/**
	 * Returns height of current active surface in pixels.
	 */
	int					surfaceHeight() const;

	/**
	 * Returns true if color keying is enabled for this image.
	 */
	bool				colorKeyEnabled() const			{return m_colorKeyEnabled;}

	/*
	 * Reads Little-Endian 16-bit Unsigned Integer.
	 */
	static uint16_t		getUInt16LE( const void* data, int offset );

	/*
	 * Reads Little-Endian 32-bit Unsigned Integer.
	 */
	static uint32_t		getUInt32LE( const void* data, int offset );

private:
	class Surface
	{
	public:
		std::vector<uint8_t>	data;
		int						width;
		int						height;
	};

	P(io::InputStream)			m_in; //Ptr now
	
	int								m_width;
	int								m_height;
	int								m_bitsPerPixel;
	int								m_pitch;
	int								m_mipLevels;
	int								m_surfaces;
	int								m_surfaceIndex;
	uint8_t							m_colormap[256][4];
	std::vector<uint8_t>			m_scanlinebuffer;
	SurfaceFormat					m_fmt;
	SurfaceFormat					m_palfmt;
	io::FileFormat						m_filefmt; //Moved to io/FileFormat.h
	bool							m_bottomUp;
	bool							m_useRLE;
	bool							m_cubeMap;
	bool							m_colorKeyEnabled;
	uint32_t						m_ffbuffer[200]; // file format specific buffer
	std::vector<Surface>			m_surfaceBuffer;
    io::ByteArrayInputStream			m_byteBuf; //Add
    std::vector<uint8_t> 			m_tempBuffer; //Add

	static void			readFully( P(io::InputStream) in, void* buf, int bytes );
	static void			readColorMap( P(io::InputStream) in, int entrysize, int entries, uint8_t* colormap );

    void	readHeader_pvr();
	void	readHeader_bmp();
	void	readHeader_tga();
	void	readHeader_jpg();
	void	readHeader_png();
    void	readHeader_webp();
	void 	readSurface_jpg( void* bits, int pitch, int w, int h, SurfaceFormat fmt, const void* pal, SurfaceFormat palfmt );
	void 	readSurfaceFromSurfaceBuffer( void* bits, int pitch, int w, int h, SurfaceFormat fmt, const void* pal, SurfaceFormat palfmt );
	void 	readScanlines( void* bits, int pitch, int w, int h, SurfaceFormat fmt, const void* pal, SurfaceFormat palfmt );
	void	readScanline_jpg( void* buffer );
	void	readScanline_tgaRLE( uint8_t* buffer );
	void	finish_jpg();

	ImageReader( const ImageReader& );
	ImageReader& operator=( const ImageReader& );
};


} // img


#endif // _IMG_IMAGEREADER_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
