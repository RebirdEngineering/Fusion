#ifndef _GR_DX11_TEXTURE_H
#define _GR_DX11_TEXTURE_H

#include "DX11_common.h"
#include <gr/Texture.h>

namespace gr
{

class DX11_Context;

class DX11_Texture : //0x4C bytes.
	public Texture
{
public:
	/**
	 * Initializes the texture.
	 */
	DX11_Texture(DX11_Context* context, int width, int height, int mipcount, int usageflags, img::SurfaceFormat format);

	///
	~DX11_Texture();

	void allocate(DX11_Context* context, int width, int height, int mipcount, img::SurfaceFormat format, int usageflags);

	void deallocate();

	/**
	 * Sets all pixels of this texture image.
	 * Texture must be unlocked before the method is called.
	 * @param x Destination offset x.
	 * @param y Destination offset y.
	 * @param data Pointer to source image data.
	 * @param pitch Distance in bytes from start of source image scanline to start of next scanline.
	 * @param miplevel
	 * @param w Width of source image in pixels.
	 * @param h Height of source image in pixels.
	 * @param fmt Pixel format of source image.
	 */
	void    blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const img::SurfaceFormat& fmt);

	/**
	 * Clears texture surface.
	 * Texture must be unlocked before the method is called.
	 */
	void    clear();

	/**
	 * Returns area of the texture surface.
	 */
	Rect    rect() const;

	/**
	 * Returns texture top level surface width in pixels.
	 */
	int     width() const;

	/**
	 * Returns texture top level surface height in pixels.
	 */
	int     height() const;

	/**
	 * 
	 */
	int     pitch() const;

	/**
	* Returns surface pixel storage format of this texture.
	*/
	img::SurfaceFormat   format() const;

	/**
	 * Returns access to locked data. Requires that texture is locked before calling this.
	 */
	void            getData( void** bits, int* pitch ) const;

	/**
	 * 
	 */
	const std::string&            getName() const;

	void setName( const std::string& name );

private:
	friend class DX11_Context; //Needed if you're making this private!

	/*
	* _DWORD dword10;
	  _DWORD dword14;
	  _DWORD dword18;
	  _BYTE byte1C;
	  _BYTE gap1D[15];
	  _DWORD dword2C;
	  _DWORD dword30;
	  _BYTE gap34[4];
	  _BYTE byte38;
	  _DWORD dword3C;
	  _DWORD dword40;
	  _DWORD dword44;
	  _DWORD dword48;
	*/
	
	int m_width; //0x10
	int m_height; //0x14
	img::SurfaceFormat m_format; //0x18
	std::string m_name; //0x1C

	/*int m_mipcount;
	int dword18;
	bool byte1C;
	bool gap1D[15];
	int dword2C;
	int dword30;
	bool gap34[4];
	bool byte38;
	int dword3C;
	int dword40;
	int dword44;
	int dword48;*/

	void lock(LockType lock);
	void unlock();
	
	DX11_Texture(const DX11_Texture&);
	DX11_Texture& operator=(const DX11_Texture&);
};

}

#endif // _GR_DX11_TEXTURE_H