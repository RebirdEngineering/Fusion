#ifndef _GR_GL_CONTEXT_H
#define _GR_GL_CONTEXT_H

#include "GL_common.h"
#include "GL_Primitive.h" //?
//#include "GL_State.h" //?
//#include "GL_Texture.h" //?

#include <gr/Context.h>
#include <gr/impl/SortBuffer.h>
#include <img/SurfaceFormat.h>

namespace gr
{

namespace GL_NAMESPACE //I'm just as confused as you are, Android and iOS use this

{

//class GL_Primitive;
class GL_Texture;
class GL_State;

class GL_Context : //33
	public Context
{
public:
    /**
     * Initializes the device object that renders to current active window.
     * @param w Width of the frame buffer.
     * @param h Height of the frame buffer.
     * @param orientation 
     * @param presentFunc
     */
    GL_Context(int w, int h, OrientationType orientation, void (*presentFunc)()); //( int w, int h, OrientationType orientation, void* presentFunc ); //45

    ~GL_Context(); //60

    void createBackBuffer(); //62
    void releaseBackBuffer(); //63

    /**
     * Creates context dependent shader by name.
     * Exact meaning of the shader name is platform dependent,
     * but same names can be used in all platforms.
     * @exception GraphicsException
     */
    Shader* createShader( const std::string& name, int flags ); //80

    /**
     * Creates context dependent texture from image file.
     * @param filename Image file name.
     * @exception IOException
     * @exception GraphicsException
     */
    Texture* createTexture( const std::string& filename ); //87

    /**
     * 
     */
    Texture* createTexture( int width, int height, int mipcount, const img::SurfaceFormat& fmt, int usageflags ); //98

    /**
     * Creates context dependent cube texture from image file.
     * @param filename Image file name.
     * @exception IOException
     * @exception GraphicsException
     */
    CubeTexture* createCubeTexture( const std::string& filename ); //105

    Image* createImage( io::InputStream& in, const std::string& filename ); //113

    Image* createImage( int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage ); //124

    Image* createFlippedImage( int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage ); //135

    /**
     * Creates context dependent geometry primitive.
     */
    Primitive*  createPrimitive( Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices, UsageFlags usage ); //146

    /**
     * Gets context dependent dynamic geometry primitive.
     */
    Primitive*  getDynamicPrimitive( Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices ); //156

    void    begin2D(); //160
    void    end2D(); //161

    void    drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth); //172

    void    drawLine2D(unsigned int color, int* vertices, int count, int lineWidth); //181 | Recovered param names from ABFM

    void    drawCircle2D(unsigned int color, int x, int y, int radius, int lineWidth); //191 | Recovered param names from ABFM

    void    fillTriangle2D(unsigned int color, int x0, int y0, int x1, int y1, int x2, int y2); //203 | Recovered param names from ABFM

    void    fillRect2D(unsigned int color, int x, int y, int w, int h, Blend blend); //213

    void    fillCircle2D(unsigned int color, int x, int y, int radius); //222

    void    texturizeTriangle2D(Image* image, const math::float4& scaleBias, int x0, int y0, int x1, int y1, int x2, int y2); //235 | Recovered param names from ABFM

    void    texturizeRect2D(Image* image, const math::float4& scalebias, int x, int y, int width, int height); //246 | Recovered param names from ABFM

    void    texturizeCircle2D(Image* image, const math::float4& scalebias, int x, int y, int radius); //256 | Recovered param names from ABFM

    std::string  getGraphicsDriverVendor(); //263

    std::string  getGraphicsDriverVersion(); //268

    std::string  getGraphicsDriverRenderer(); //273

    RenderState2D&  getRenderState2D(); //278

    /**
     * Returns current active viewport of the device.
     */
    const Rect& viewport() const; //283

    /**
     * Returns surface format of the back buffer.
     */
    img::SurfaceFormat   surfaceFormat() const; //288

    /**
     * Returns screen buffer width.
     */
    int         width() const; //293

    /**
     * Returns screen buffer height.
     */
    int         height() const; //298

    float         time() const; //304

    const math::float3x4&         customModelTransform() const; //309

    bool          customModelTransformEnabled() const; //314

    /**
     * Returns view->screen transformation (including screen transform).
     */
    const math::float4x4& projectionTransform() const; //319

    const math::float4x4& viewTransform() const; //32

    const math::float2& getFovScaleBias() const; //328

    PlatformType    platform() const; //333

    OrientationType    orientation() const; //338

    /**
     * Returns true if device can be used for rendering.
     * Call once per frame before using device for rendering.
     */
    bool        ready() const; //344

    const std::string& shaderPath() const; //349

    void        setRenderState2D( const RenderState2D& state ); //357

    /**
     * Sets viewport on active render target.
     */
    void        setViewport( const Rect& rect ); //362

    void        setClipRect( const Rect& rect ); //364

    /**
     * Sets render target. Render target texture must be created with USAGE_RENDERTARGET
     * flag set.
     * @param dst Render target texture or 0 if back buffer should be re-activated.
     */
    void        setRenderTarget( Texture* dst ); //374

    /**
     * Sets wireframe rendering enabled/disabled. Debug usage only.
     * Note that all platform might not support this function (nothing happens).
     */
    void        setWireframeEnabled( bool enabled ); //380

    void        setOrientation( OrientationType orientation ); //387

    void        setFovScaleBias( const math::float2& ); //394

    void        setCustomModelTransform( const math::float3x4& customtm ); //402

    void        setCustomModelTransformEnabled( bool enable ); //408

    /**
     * Sets perspective projection.
     * @param hfov Horizontal field-of-view
     * @param front Front/near plane distance
     * @param back Back/far plane distance
     * @param aspect Viewport aspect ratio (w/h)
     */
    void        setPerspectiveProjection( float aspect, float fov, float front, float back ); //417

    /**
     * Sets orthographic projection.
     */
    void        setOrthographicProjection(); //422

    void        setProjection( const math::float4x4& ); //428

    void        setViewTransform( const math::float4x4& ); //430

    void        setTime( float ); //435

    void        setShaderPath( const std::string& path); //440

    void        reset( int w, int h ); //447

    /**
     * Called before beginning scene rendering.
     * Don't use this directly, but exception-safe RenderScene wrapper instead.
     */
    void        beginScene(); //453

    /**
     * Called after scene rendering.
     * Don't use this directly, but exception-safe RenderScene wrapper instead.
     */
    void        endScene(); //459

    void        reloadShaders(); //465

    /**
     * Swaps back buffer to screen and clears viewport.
     */
    virtual void        present(); //470

    /**
     * Clears viewport on active render target.
     * Don't need to be called for back buffer since present() takes care of this.
     */
    virtual void        clear(unsigned int color, bool clearColor, bool clearDepth, bool clearStencil); //479

    /**
     * Captures back buffer contents to a file.
     * @param namefmt printf compatible format string of output file name.
     * @exception GraphicsException
     * @exception IOException
     */
    void        capture( const std::string& namefmt ); //486

    void        capture( io::OutputStream& out, io::FileFormat ff ); //494

    P(Image)    capture( P(Image) image ); //501

    void        flipWindingOrder(); //506

    void        hibernateContext(); //511

    void        resumeContext(); //516

    void        flush(); //521

    Shader*     getPlainShader() { return m_plainShader; }; //574

    Shader*     getPlainAlphaShader() { return m_plainAlphaShader; } //581

    Shader*     getSpriteShader() {return m_spriteShader;} //588

    Shader*     getSpriteAlphaShader() {return m_spriteAlphaShader;} //595

    void        removeTexture(Texture* tex); //601

    void        saveCachedState( const std::string& name ); //606

    void        restoreCachedState( const std::string& name ); //612

    void        resetCachedState( ); //617

    void        getColorF( int color, float* colorf ); //623

    static bool        isExtensionSupported( const char* extension ); //629

    /** Transform buffer for transformations needed in polygon sorting. */
    std::vector<math::float4x4> boneworldtm; //635

    /** Cached model-world transform, used for sorting. */
    math::float4x4					worldtm; //638

    /** Cached world space camera position, used for sorting. */
    math::float4					camerapos; //641

    /** Temporary buffer for polygon sorting. */
    SortBuffer						sortbuffer; //644

private:
    //friend class GL_Texture;
    std::map<std::string, P(GL_Shader)> m_uniqueShaders; //650
    std::vector<P(GL_Primitive)> m_dynamicPrimitives; //651
    std::map<std::string, GL_State> m_stateStorage; //652

    RenderState2D m_renderState2D; //654
    math::float4x4 m_projtm; //655
    math::float4x4 m_viewtm; //656
    math::float4x4 m_modelviewtm; //657
    math::float3x4 m_customModelTM; //658
    Rect m_viewport; //659
    int m_width; //660
    int m_height; //661
    int m_windingOrder; //662
    bool m_customModelTMEnabled; //663
    Shader::SortType m_sort; //664
    OrientationType m_orientation; //665
    GL_Texture* m_renderTarget; //666
    float m_time; //667
    math::float2 m_fovScaleBias; //668
    std::string m_shaderPath; //669
    P(Shader) m_plainShader; //670
    P(Shader) m_plainAlphaShader; //671
    P(Shader) m_spriteShader; //672
    P(Shader) m_spriteAlphaShader; //673
    std::vector<GL_Texture*> m_textures; //674

    void (*m_presentFunc)(); //void m_presentFunc(void); //688 | ?
};

}
}

#endif