#ifndef _GR_CONTEXT_H
#define _GR_CONTEXT_H


#include <gr/Shader.h>
#include <gr/Primitive.h>
#include <img/SurfaceFormat.h>
#include <gr/RenderBatcher.h>
#include <gr/RenderState2D.h>
//#include <io/InputStream.h>
//#include <io/OutputStream.h>
#include <math/float3x4.h>

namespace io
{
class InputStream;
class OutputStream;
enum FileFormat; }

namespace math
{ 
	class float4;
	class float4x4;}

namespace gr
{


class Rect;
class Palette;
class Texture;
class Primitive;
class CubeTexture;
class VertexFormat;
	

/** 
 * Base class for platform dependent rendering device contexts.
 * Manages rendering device state and rendering device dependent 
 * resources like textures and vertex buffers.
 * @ingroup gr
 */
class Context : //39
	public lang::Object
{
public:
	/**
	 * Rendering platform id
	 */
	enum PlatformType //49 | The below to N3D are removed from Fusion.
	{
        /** Platform is GLES1 / OpenGL ES 1.x. */
        PLATFORM_GLES1,
        /** Platform is GLES2 / OpenGL ES 2.x. */
        PLATFORM_GLES2,
        /** Platform is GL1 / OpenGL 1.x. */
        PLATFORM_GL1,
        /** Platform is GL2 / OpenGL 2.x. */
        PLATFORM_GL2,
        /** Platform is DirectX 11. [ADD] */
        PLATFORM_DX11,
        /** Platform is XNA. [ADD] (Used by WP7) */
        PLATFORM_XNA,
#ifdef XFUSION
        /** [ADD] Platform is Exient XGS. [ADD] (Exclusive to Exient fork) */
        PLATFORM_XGS,
#elif defined(FUNFUSION)
        /**[ADD] Platform is Wii. [ADD] (Exclusive to FunLabs fork) */
        PLATFORM_WII,
        /**[ADD] Platform is Wii U. [ADD] (Exclusive to FunLabs fork) */
        PLATFORM_WIIU,
#endif
		/** Number of platform types. */
		PLATFORM_COUNT
	};
	
	/** Resource usage flags. */
	enum UsageFlags //79
	{
		/** Use default options for resource usage. */
		USAGE_DEFAULT			            = 0,
		/** Resource is relatively non-changing (not locked every frame). */
		USAGE_STATIC			            = 2,
		/** Resource is locked frequently (every frame). */
		USAGE_DYNAMIC			            = 4,
        /** Set for texture that needs to be used as render target. */
		USAGE_RENDERTARGET		            = 8, //As of Fusion this was moved from 1 to 8.
        /**  */
		USAGE_RENDERTARGET_NO_ROTATE		= 16,
	};

	/** Screen orientation. */
	enum OrientationType //97
	{
		/** Screen is not rotated. */
		ORIENTATION_0,
		/** Screen is rotated 90 degrees counter-clockwise. */
		ORIENTATION_90,
		/** Screen is rotated 180 degrees counter-clockwise. */
		ORIENTATION_180,
		/** Screen is rotated 270 degrees counter-clockwise. */
		ORIENTATION_270,
	};

	enum Blend //112
	{
		BLEND_AUTO,
		BLEND_ENABLE,
		BLEND_DISABLE,
	};

	/** Helper class for exception-safe usage of beginScene and endScene functions. */
	class RenderScene //128
	{
	public:
		/** Calls beginScene for the context. */
		explicit RenderScene( Context* context );
	
		/** Calls endScene for the context. */
		~RenderScene();
	
	private:
		P(Context) m_context;
	
		RenderScene( const RenderScene& );
		RenderScene& operator=( const RenderScene& );
	};

	/**
	 * Rendering context statistics.
	 * Note that all rendering context implementations might not
	 * update all statistical information.
	 */
	struct Statistics //149
	{
		/** Number of frames rendered. */
		int renderedFrames; //152
		/** Number of lines rendered since last reset. */
		int renderedLines; //154
		/** Number of points rendered since last reset. */
		int renderedPoints; //156
		/** Number of triangles rendered since last reset. */
		int renderedTriangles; //158
		/** Number of primitives rendered since last reset. */
		int renderedPrimitives; //160
        /**  */
		int renderedImages; //162
        /**  */
		int renderedImageFlushes; //164
		/** Allocated texture memory in bytes. */
		int allocatedTextureMemory; //166
		/** Allocated number of textures. */
		int allocatedTextures; //168
        /**  */
		int allocatedImageMemory; //170
		/**  */
		int allocatedImages; //172

		/** Sets all statistics counters to 0. */
		void reset(); //175
	};

	/** Rendering context statistics. */
	Statistics statistics;

	Context(); //187
	~Context(); //188

	/**
	 * Creates context dependent shader by name.
	 * Shader name consists of optional path prefix and
	 * actual shader name following '/' character.
	 * Path prefix is only meaningful if the shader hasn't been
	 * used before and if the platform supports external file base shaders.
	 * Exact meaning of the shader name is platform dependent,
	 * but same names can be used in all platforms.
	 * @param name Shader name.
	 * @param flags Compilation flags. See NS(Shader,Flags).
	 * @exception GraphicsException
	 */
	virtual Shader*						createShader( const std::string& name, int flags=0 ) = 0; //205

	/**
	 * Creates context dependent texture from image file.
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	virtual Texture*					createTexture( const std::string& filename ) = 0; //212

	/**
	 * Creates context dependent texture.
	 * @param width Width of the texture in pixels.
	 * @param height Height of the texture in pixels.
	 * @param mipcount
	 * @param fmt Pixel format of the texture.
	 * @param usageflags Texture usage flags. See UsageFlags.
	 * @exception GraphicsException
	 */
	 
	virtual Texture*					createTexture( int width, int height, int mipcount, const img::SurfaceFormat& fmt, int usageflags ) = 0; //223

	/**
	 * Creates context dependent cube texture from image file.
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	virtual CubeTexture* 				createCubeTexture( const std::string& filename ) = 0; //230
	
	/**
	 * 
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	Image* 								createImagefromBundle( const std::string& filename ); //237
	
	/**
	 * 
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	Image* 								createImageFromAppData( const std::string& filename ); //244
	
	/**
	 * 
	 * @param in Input stream.
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	virtual Image* 						createImage( io::InputStream& in, const std::string& filename ) = 0; //252
	
	/**
	 * 
	 * @param in *.
	 * @param filename Image file name.
	 * @exception IOException
	 * @exception GraphicsException
	 */
	virtual Image* 						createImage( int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage) = 0; //263

	/**
	 * Creates context dependent geometry primitive.
	 * @param prim Primitive type.
	 * @param vf Geometry vertex format.
	 * @param vertices Number of vertices.
	 * @param indices Number of indices.
	 * @param usage Intended usage. Select USAGE_DYNAMIC if the buffer is locked in every frame. Default is USAGE_STATIC.
	 * @exception GraphicsException
	 */
	virtual Primitive* 					createPrimitive( Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices, UsageFlags usage=USAGE_STATIC ) = 0; //274

	/**
	 * Gets context dependent dynamic geometry primitive.
	 * Dynamic primitives need to be re-requested always before rendering.
	 * @param prim Primitive type.
	 * @param vf Geometry vertex format.
	 * @param vertices Number of vertices.
	 * @param indices Number of indices.
	 * @exception GraphicsException
	 */
	virtual Primitive* 					getDynamicPrimitive( Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices ) = 0; //284
	
	
	virtual void						begin2D() = 0; //288
	virtual void						end2D() = 0; //289
	
	/**
	*
	* @param color
	* @param x0
	* @param y0
	* @param x1
	* @param y1
	* @param lineWidth
	*/
	virtual void 						drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth) = 0; //300

	virtual void 						drawLine2D(unsigned int color, int* vertices, int count, int lineWidth) = 0; //309 | Recovered parameters from ABFM.
	
	/**
	*
	* @param color
	* @param x0
	* @param y0
	* @param x1
	* @param y1
	*/
	virtual void 						drawCircle2D(unsigned int color, int x0, int y0, int x1, int y1) = 0; //319
	
	/**
	*
	* @param color
	* @param x0
	* @param y0
	* @param x1
	* @param y1
	* @param x2
	* @param y2
	*/
	virtual void 						fillTriangle2D(unsigned int color, int x0, int y0, int x1, int y1, int x2, int y2) = 0; //331
	
	/**
	*
	* @param color
	* @param x0
	* @param y0
	* @param x1
	* @param y1
	* @param blend
	*/
	virtual void 						fillRect2D(unsigned int color, int x0, int y0, int x1, int y1, Blend blend) = 0; //342
	
	/**
	*
	* @param color
	* @param x
	* @param y
	* @param radius
	*/
	virtual void 						fillCircle2D(unsigned int color, int x, int y, int radius) = 0; //351
	
	/**
	* @param image
	* @param scaleBias
	* @param x0
	* @param y0
	* @param x1
	* @param y1
	* @param x2
	* @param y2
	* @param radius
	*/
	virtual void 						texturizeTriangle2D(Image* Image, const math::float4& scaleBias, int x0, int y0, int x1, int y1, int x2, int y2) = 0; //364
	
	/**
	* 
	* @param image
	* @param scaleBias
	* @param x
	* @param y
	* @param width
	* @param height
	*/
	virtual void 						texturizeRect2D(Image* image, const math::float4& scaleBias, int x, int y, int width, int height) = 0; //375
	
	/**
	* 
	* @param image
	* @param scaleBias
	* @param x
	* @param y
	* @param radius
	*/
	virtual void 						texturizeCircle2D(Image* image, const math::float4& scalebias, int x, int y, int radius) = 0; //385
	
	virtual std::string 			getGraphicsDriverVendor() = 0; //392
	
	/*
	* 
	*/
	virtual std::string 			getGraphicsDriverVersion() = 0; //397
	
	/*
	*
	*/
	virtual std::string 			getGraphicsDriverRenderer() = 0; //402
	
	/*
	*
	*/
	virtual RenderState2D&				getRenderState2D() = 0; //407
	
	/**
	 * Returns current active viewport of the device.
	 */
	virtual const Rect&					viewport() const = 0; //412

	/**
	 * Returns surface format of the back buffer. [NOTE CHANGED TO UPPERCASE]
	 */
	virtual img::SurfaceFormat				SurfaceFormat() const = 0; //417
	
	/**
	 * Returns screen buffer width.
	 */
	virtual int							width() const = 0; //422

	/**
	 * Returns screen buffer height.
	 */
	virtual int							height() const = 0; //427
	
	virtual float						time() const = 0; //433
	
	/*
	* 
	*/
	virtual const math::float3x4&		customModelTransform() const = 0; //438

	/*
	*
	*/	
	virtual bool						customModelTransformEnabled() const = 0; //443
	
	/**
	 * Returns view->screen transformation (including screen transform).
	 */
	virtual const math::float4x4&	projectionTransform() const = 0; //448
	
	virtual const math::float4x4&	viewTransform() const = 0; //450
	
	virtual const math::float2& 				getFovScaleBias() const = 0; //457
	
	/**
	 * Returns platform id.
	 */
	virtual PlatformType				platform() const = 0; //462

	/**
	 * Returns screen orientation. Default is ORIENTATION_0.
	 */
	virtual OrientationType				orientation() const = 0; //467
	
	/**
	 * Returns true if device can be used for rendering.
	 * Call once per frame before using device for rendering.
	 */
	virtual bool						ready() const = 0; //473
	
	/**
	 * 
	 */
	virtual const std::string&	    shaderPath() const = 0; //478
	
	/**
	 * 
	 */
	virtual void						setRenderState2D(const RenderState2D& state) = 0; //486
	
	/** 
	 * Sets viewport on active render target.
	 */
	virtual void						setViewport( const Rect& rect ) = 0; //491
	
	/**
	 * 
	 */
	virtual void						setClipRect( const Rect& rect ) = 0; //496
	
	/**
	 * Sets render target. Render target texture must be created with USAGE_RENDERTARGET
	 * flag set.
	 * @param dst Render target texture or 0 if back buffer should be re-activated.
	 */
	virtual void						setRenderTarget( Texture* dst ) = 0; //503
	
	/** 
	 * Sets wireframe rendering enabled/disabled. Debug usage only.
	 * Note that all platform might not support this function (nothing happens).
	 */
	virtual void						setWireframeEnabled( bool enabled ); //509
	
	 /**
	 * 
	 * @param orientation
	 */
	virtual void						setOrientation( OrientationType orientation ) = 0; //516
	
	/** 
	 *
	 * @param scalebias
	 */
	virtual void						setFovScaleBias( const math::float2& scalebias ) = 0; //523
	
	/** 
	 * 
	 * @param customtm
	 */
	virtual void						setCustomModelTransform( const math::float3x4& customtm) = 0; //531
    
    /** 
	 * 
	 * @param enable
	 */
	virtual void						setCustomModelTransformEnabled( bool enable) = 0; //537

	/**
	 * Sets perspective projection.
	 * @param hfov Horizontal field-of-view
	 * @param front Front/near plane distance
	 * @param back Back/far plane distance
	 * @param aspect Viewport aspect ratio (w/h)
	 */
	virtual void						setPerspectiveProjection( float hfov, float front, float back, float aspect ) = 0; //546

	/**
	 * Sets orthographic projection.
	 */
	virtual void						setOrthographicProjection( ) = 0; //551
    
    /** 
	 * 
	 * @param projtm
	 */
	virtual void						setProjection( const math::float4x4& projtm) = 0; //557
    
	virtual void						setViewTransform( const math::float4x4& viewtm) = 0; //559
    
    /** 
	 * 
	 */
	virtual void						setTime( float time) = 0; //563
    
    /** 
	 * 
	 */
	virtual void						setShaderPath( const std::string& path) = 0; //569
    
    /** 
	 * Not in ABSW XGS fork
	 * @param w
	 * @param h
	 */
    virtual void						reset(int w, int h) = 0; //576
    
    /** 
	 * Called before beginning scene rendering.
	 * Don't use this directly, but exception-safe NS(Context,RenderScene) wrapper instead.
	 */
	virtual void						beginScene() = 0; //582
    
    /** 
	 * Called after scene rendering.
	 * Don't use this directly, but exception-safe NS(Context,RenderScene) wrapper instead.
	 */
	virtual void						endScene() = 0; //588
    
    /** 
	 * 
	 */
	virtual void						reloadShaders() = 0; //594
	
	/** 
	 * Swaps back buffer to screen and clears viewport.
	 */
	virtual void						present( ) = 0; //599
	
	/** 
	 * Clears viewport on active render target.
	 * Don't need to be called for back buffer since present() takes care of this.
	 * @param color 32-bit ARGB color
	 * @param clearColor 
	 * @param clearDepth 
	 * @param clearStencil 
	 */
    virtual void						clear( unsigned int color=0, bool clearColor=false, bool clearDepth=false, bool clearStencil=false ) = 0; //608

	/**
	 * @param namefmt printf compatible format string of output file name.
	 * @exception GraphicsException
	 * @exception IOException
	 */
	virtual void				capture( const std::string& namefmt ) = 0; //615
    
    /**
	 * Not in ABSW Console fork
	 * @param out
	 * @param ff
	 */
	virtual void				capture(NS(io, OutputStream)&out, NS(io,FileFormat) ff ) = 0; //623
    
    /**
	 * Not in ABSW Console fork
	 * @param image
	 */
	virtual P(Image)		capture(P(Image) image) = 0; //630
    
    /**
	 * [ADD]
	 */
	virtual void				flipWindingOrder( ) = 0; //635
    
    /**
	 * [ADD]
	 */
	virtual void				flush() = 0; //640
    
    /**
	 * 
	 */
	virtual void				hibernateContext(); //645
    
    /**
	 *
	 */
	virtual void				resumeContext(); //650
    
    /**
	 * @param name
	 */
	virtual void				saveCachedState( const std::string& name ); //655
    
    /**
	 * 
	 * @param name
	 */
	virtual void				restoreCachedState( const std::string& name ); //661
    
    /**
	 *
	 */
	virtual void				resetCachedState(); //666
	
	/**
	 * Returns screen buffer width divided by height.
	 */
	float						aspect() const; //675

	/**
	 * Returns platform string id.
	 */
	const char*					platformString() const; //680
    
    /**
	 *
	 */
	void						transformPointToScreen( int& x, int& y ) const; //685 | Recover from ABFM (and also by proxy game::BitmapFont & game::CompospriteSet)
    
     /**
	 *
	 */
	void						enableTextureShadowing( bool ) const; //690
	
	/**
	 *
	 */
	bool						isTextureShadowingEnabled( ) const; //695
	
	/**
	 * Returns platform string id (max 3 characters).
	 */
	static const char*			getString( PlatformType platform ); //700

	/**
	 * Returns platform description (can be used for in UIs etc).
	 */
	static const char*			getDescription( PlatformType platform ); //705
    
    /**
	 *
	 */
	static RenderBatcher&				getBatcher(); //710
    
    /**
	 *
	 */
	virtual void*				getBackbuffer(); //712
	
protected:
	P(RenderBatcher) 	m_batcher; //715

private:
	Context( const Context& ); //718
	Context& operator=( const Context& ); //719

	bool 						m_useTextureShadowing; //721
};


} // gr


#endif // _GR_CONTEXT_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
