#ifndef _GR_GL_TEXTURE_H
#define _GR_GL_TEXTURE_H

#include "GL_common.h"
#include <gr/Texture.h>
#include <lang/Object.h>

namespace gr
{
namespace GL_NAMESPACE //I'm just as confused as you are
{

class GL_Context;

struct ShadowingTextureData //17
{
public:
	ShadowingTextureData(); //20

	ShadowingTextureData(GL_Context* context, int width, int height, int mipcount, img::SurfaceFormat fmt, int usageflags) : //29
		m_context(context),
		m_width(width),
		m_height(height),
		m_mipcount(mipcount),
		m_fmt(fmt),
		m_usageflags(usageflags)
	{
	}

	GL_Context* m_context; //39
	int m_width; //40
	int m_height; //41
	int m_mipcount; //42
	img::SurfaceFormat m_fmt; //43
	int m_usageflags; //44
};

class ShadowingSurfaceData : public lang::Object
{
public:
	ShadowingSurfaceData(); //51
	ShadowingSurfaceData(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const img::SurfaceFormat& fmt) : //52
		m_x(x),
		m_y(y),
		m_pitch(pitch),
		m_miplevel(miplevel),
		m_w(w),
		m_h(h),
		m_fmt(fmt)
	{
		int dataSize = fmt.getMemoryUsage(w, h);
		m_data.resize(dataSize); //62
		memcpy(&m_data, 0, dataSize); //63
	}

	int m_x; //66
	int m_y; //67
	std::vector<unsigned char> m_data; //68
	int m_pitch; //69
	int m_miplevel; //70
	int m_w; //71
	int m_h; //72
	img::SurfaceFormat m_fmt; //73
};

class GL_Texture :
	public Texture
{
public:
	/**
	 * Initializes the texture.
	 */
	GL_Texture(GL_Context* context, int width, int height, int mipcount, int usageflags, img::SurfaceFormat format); //86

	///
	~GL_Texture(); //89

	void allocate(GL_Context* context, int width, int height, int mipcount, img::SurfaceFormat format, int usageflags); //91

	void deallocate(); //93

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
	void    blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const img::SurfaceFormat& fmt); //107

	/**
	 * Clears texture surface.
	 * Texture must be unlocked before the method is called.
	 */
	void    clear(); //113

	/**
	 * Returns area of the texture surface.
	 */
	Rect    rect() const; //118

	/**
	 * Returns texture top level surface width in pixels.
	 */
	int     width() const; //123

	/**
	 * Returns texture top level surface height in pixels.
	 */
	int     height() const; //128

	/**
	 * 
	 */
	int     pitch() const; //133

	/**
	* Returns surface pixel storage format of this texture.
	*/
	img::SurfaceFormat   format() const; //138

	/**
	 * Returns access to locked data. Requires that texture is locked before calling this.
	 */
	void            getData( void** bits, int* pitch ) const; //143

	/**
	 * 
	 */
	const std::string&            getName() const; //148

	void setName( const std::string& name ); //153

	GLuint tex() const {return m_tex;} //158

	GLuint fbo() const {return m_fbo;} //163

	bool autoRotate() const { return m_autoRotate; } //168

private:
	friend class GL_Context; //Needed if you're making this private!

	GLuint m_tex; //173
	GLuint m_fbo; //174
	GLuint m_depthBuffer; //175
	int m_width; //176
	int m_height; //177
	img::SurfaceFormat m_format; //178
	std::string m_name; //m_name
	bool m_autoRotate; //180
	LockType m_lock; //181
	std::vector<char> m_lockedData; //182

	ShadowingTextureData m_shadowingTex; //184
	std::vector<P(ShadowingSurfaceData)> m_shadowingSurf; //185
	bool m_restoring; //186

	void lock(LockType lock); //188
	void unlock(); //189
	
	GL_Texture(const GL_Texture&); //191
	GL_Texture& operator=(const GL_Texture&); //192
};

}
}

#endif // _GR_GL_TEXTURE_H