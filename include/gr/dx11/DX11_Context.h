#ifndef _GR_DX11_CONTEXT_H
#define _GR_DX11_CONTEXT_H


#include "DX11_common.h"
#include "DX11_Shader.h"
#include "DX11_Primitive.h"
#include "DX11_Texture.h"
#include <gr/Context.h>
#include <io/PathName.h>
#include <img/SurfaceFormat.h>
#include <math/float4x4.h>

namespace framework
{
    class VisualStudioLogger;
}

namespace gr
{

class DX11_Context : //0x350 bytes.
    public Context
{
public:
    /**
     * Initializes the device object that renders to current active window.
     * @param hwnd
     * @param orientation
     */
    DX11_Context(HWND hwnd, OrientationType orientation); //( int w, int h, OrientationType orientation, void* presentFunc ); | 10007950

    ~DX11_Context();

    /**
     * Creates context dependent shader by name.
     * Exact meaning of the shader name is platform dependent,
     * but same names can be used in all platforms.
     * @exception GraphicsException
     */
    Shader* createShader(const std::string& name, int flags);

    /**
     * Creates context dependent texture from image file.
     * @param filename Image file name.
     * @exception IOException
     * @exception GraphicsException
     */
    Texture* createTexture(const std::string& filename);

    /**
     * Creates context dependent texture.
     * @param width Width of the texture in pixels.
     * @param height Height of the texture in pixels.
     * @param mipcount
     * @param fmt Pixel format of the texture.
     * @param usageflags Texture usage flags. See UsageFlags.
     * @exception GraphicsException
     */
    Texture* createTexture(int width, int height, int mipcount, const img::SurfaceFormat& fmt, int usageflags);

    /**
     * Creates context dependent cube texture from image file.
     * @param filename Image file name.
     * @exception IOException
     * @exception GraphicsException
     */
    CubeTexture* createCubeTexture(const std::string& filename);

    Image* createImage(io::InputStream& in, const std::string& filename);

    Image* createImage(int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage);

    /**
     * Creates context dependent geometry primitive.
     */
    Primitive* createPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices, UsageFlags usage);

    /**
     * Gets context dependent dynamic geometry primitive.
     */
    Primitive* getDynamicPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices);

    void    begin2D();
    void    end2D();

    void    drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth);

    void    drawLine2D(unsigned int color, int* vertices, int count, int lineWidth); //Recovered param names from ABFM

    void    drawCircle2D(unsigned int color, int x, int y, int radius, int lineWidth); //Recovered param names from ABFM

    void    fillTriangle2D(unsigned int color, int x0, int y0, int x1, int y1, int x2, int y2); //Recovered param names from ABFM

    void    fillRect2D(unsigned int color, int x, int y, int w, int h, Blend blend);

    void    fillCircle2D(unsigned int color, int x, int y, int radius);

    void    texturizeTriangle2D(Image* image, const math::float4& scaleBias, int x0, int y0, int x1, int y1, int x2, int y2); //Recovered param names from ABFM

    void    texturizeRect2D(Image* image, const math::float4& scalebias, int x, int y, int width, int height); //Recovered param names from ABFM

    void    texturizeCircle2D(Image* image, const math::float4& scalebias, int x, int y, int radius); //Recovered param names from ABFM

    std::string  getGraphicsDriverVendor();

    std::string  getGraphicsDriverVersion();

    std::string  getGraphicsDriverRenderer();

    RenderState2D& getRenderState2D();

    /**
     * Returns current active viewport of the device.
     */
    const Rect& viewport() const;

    /**
     * Returns surface format of the back buffer. [NOTE CHANGED TO UPPERCASE]
     */
    img::SurfaceFormat   SurfaceFormat() const;

    /**
     * Returns screen buffer width.
     */
    int         width() const;

    /**
     * Returns screen buffer height.
     */
    int         height() const;

    float         time() const;

    const math::float3x4& customModelTransform() const;

    bool          customModelTransformEnabled() const;

    /**
     * Returns view->screen transformation (including screen transform).
     */
    const math::float4x4& projectionTransform() const;

    const math::float4x4& viewTransform() const;

    const math::float2& getFovScaleBias() const;

    PlatformType    platform() const;

    OrientationType    orientation() const;

    /**
     * Returns true if device can be used for rendering.
     * Call once per frame before using device for rendering.
     */
    bool        ready() const;

    const std::string& shaderPath() const;

    void        setRenderState2D(const RenderState2D& state);

    /**
     * Sets viewport on active render target.
     */
    void        setViewport(const Rect& rect);

    void        setClipRect(const Rect& rect);

    /**
     * Sets render target. Render target texture must be created with USAGE_RENDERTARGET
     * flag set.
     * @param dst Render target texture or 0 if back buffer should be re-activated.
     */
    void        setRenderTarget(Texture* dst);

    /**
     * Sets wireframe rendering enabled/disabled. Debug usage only.
     * Note that all platform might not support this function (nothing happens).
     */
    void        setWireframeEnabled(bool enabled);

    void        setOrientation(OrientationType orientation);

    void        setFovScaleBias(const math::float2& scalebias);

    void        setCustomModelTransform(const math::float3x4& customtm);

    void        setCustomModelTransformEnabled(bool enable);

    /**
     * Sets perspective projection.
     * @param hfov Horizontal field-of-view
     * @param front Front/near plane distance
     * @param back Back/far plane distance
     * @param aspect Viewport aspect ratio (w/h)
     */
    void        setPerspectiveProjection(float aspect, float fov, float front, float back);

    /**
     * Sets orthographic projection.
     */
    void        setOrthographicProjection();

    void        setProjection(const math::float4x4& projtm);

    void        setViewTransform(const math::float4x4& viewtm);

    void        setTime(float time);

    void        setShaderPath(const std::string& path);

    void        reset(int w, int h);

    /**
     * Called before beginning scene rendering.
     * Don't use this directly, but exception-safe RenderScene wrapper instead.
     */
    void        beginScene();

    /**
     * Called after scene rendering.
     * Don't use this directly, but exception-safe RenderScene wrapper instead.
     */
    void        endScene();

    void        reloadShaders();

    /**
     * Swaps back buffer to screen and clears viewport.
     */
    void        present();

    /**
     * Clears viewport on active render target.
     * Don't need to be called for back buffer since present() takes care of this.
     */
    void        clear(unsigned int color, bool clearColor, bool clearDepth, bool clearStencil);

    /**
     * Captures back buffer contents to a file.
     * @param namefmt printf compatible format string of output file name.
     * @exception GraphicsException
     * @exception IOException
     */
    void        capture(const std::string& namefmt);

    void        capture(io::OutputStream& out, io::FileFormat ff);

    P(Image)    capture(P(Image) image);

    void        flipWindingOrder();

    void        hibernateContext();

    void        resumeContext();

    void        flush();

    Shader*     getPlainShader() //10003650
    {
        if (!m_plainShader)
            m_plainShader = createShader(io::PathName(shaderPath(), "2d-vertexcolor").toString(), 0);
        return m_plainShader;
    };

    Shader*     getPlainAlphaShader() //10003760
    {
        if (!m_plainAlphaShader)
            m_plainAlphaShader = createShader(io::PathName(shaderPath(), "2d-vertexcolor-alpha").toString(), 0);
        return m_plainAlphaShader;
    }

    Shader*     getSpriteShader() //10003870
    {
        if (!m_spriteShader)
            m_spriteShader = createShader(io::PathName(shaderPath(), "2d-sprite").toString(), 0);
        return m_spriteShader;
    }

    Shader*     getSpriteAlphaShader() //10003980
    {
        if (!m_spriteAlphaShader)
            m_spriteAlphaShader = createShader(io::PathName(shaderPath(), "2d-sprite-alpha").toString(), 0);
        return m_spriteAlphaShader;
    }

    void        saveCachedState(const std::string& name);

    void        restoreCachedState(const std::string& name);

    void        resetCachedState();

    void getColorF(int color, float* colorf); //Assuming via GLES2

    void*       getBackbuffer();

    ID3D11Device* device() { return m_device; } //Unofficial name, assuming from KA3D DX9. | 10002020 | device

    ID3D11DeviceContext* deviceContext() { return pid3d11devicecontext320; } //sub_10002030 | Unofficial name.

protected:

private:

    std::vector<math::float4x4> boneworldtm; //0x40
    math::float4 camerapos; //0x50
    math::float4x4 worldtm; //0x60
    SortBuffer sortbuffer; //0xA0
    framework::VisualStudioLogger* visualstudiologgerB8; //0xB8
    std::vector<math::float4x4> unkBC; //0xBC
    std::vector<P(DX11_Primitive)> m_dynamicPrimitives; //0xCC
    RenderState2D m_renderState2D; //0xDC
    math::float4x4 m_projtm; //0x178
    math::float4x4 m_viewtm; //0x1B8
    math::float4x4 m_modelviewtm; //0x1F8
    math::float4x4 unk238; //0x238
    math::float3x4 m_customModelTM; //0x238
    Rect m_viewport; //0x2A8
    int m_width; //0x2B8
    int m_height; //0x2BC
    int m_windingOrder; //0x2C0
    bool m_customModelTMEnabled; //0x2C4
    Shader::SortType m_sort; //0x2C8
    OrientationType m_orientation; //0x2CC
    Texture* m_renderTarget; //0x2D0
    float m_time; //0x2D4
    math::float2 m_fovScaleBias; //0x2D8
    std::string m_shaderPath; //0x2E0
    P(Shader) m_plainShader; //0x2FC
    P(Shader) m_plainAlphaShader; //0x300
    P(Shader) m_spriteShader; //0x304
    P(Shader) m_spriteAlphaShader; //0x308
    std::vector<DX11_Texture*> m_textures; //0x30C
    ID3D11Device* m_device; //0x31C
    ID3D11DeviceContext* pid3d11devicecontext320; //0x320
    IDXGISwapChain* pidxgiswapchain324; //0x324
    ID3D11RenderTargetView* pid3d11rendertargetview328; //0x324
    DXGI_FORMAT dxgi_format32C; //0x32C
    DX11_Texture* unk330; //0x330
    DX11_Texture* unk334; //0x334
    ID3D11RenderTargetView* pid3d11rendertargetview338; //0x338
    ID3D11DepthStencilView* pid3d11depthstencilview33C; //0x33C
    std::map<std::string, P(DX11_Shader)> m_uniqueShaders; //0x340

    void createSwapChain(HWND hwnd);

	/*
  _DWORD dword40;
  _DWORD dword44;
  _DWORD dword48;
  _BYTE gap4C[112];
  _DWORD dwordBC;
  _DWORD dwordC0;
  _DWORD dwordC4;
  _BYTE gapC8[4];
  _DWORD dwordCC;
  _DWORD dwordD0;
  _DWORD dwordD4;
  _BYTE gapD8[4];
  gr::RenderState2D gr__renderstate2dDC; //0x2DDC
  float float178;
  _BYTE gap17C[60];
  float float1B8;
  _BYTE gap1BC[60];
  float float1F8;
  _BYTE gap1FC[60];
  float float238;
  _BYTE gap23C[108];
  gr::Rect gr__rect2A8;
  _DWORD dword2B8;
  _DWORD dword2BC;
  _BYTE gap2C0[4];
  _WORD word2C4;
  _DWORD dword2C8;
  _DWORD dword2CC;
  _DWORD dword2D0; //function call
  float float2D4;
  float float2D8;
  float float2DC;
  _BYTE byte2E0;
  _BYTE gap2E1[15];
  _DWORD dword2F0;
  _DWORD dword2F4;
  _BYTE gap2F8[4];
  _DWORD dword2FC;
  _DWORD dword300;
  _DWORD dword304;
  _DWORD dword308;
  _DWORD dword30C;
  _DWORD dword310;
  _DWORD dword314;
  _BYTE gap318[4];
  ID3D11Device *m_device;
  ID3D11DeviceContext *pid3d11devicecontext320;
  _DWORD dword324;
  _DWORD dword328;
  _DWORD dword32C;
  _DWORD dword330;
  _DWORD dword334;
  _DWORD dword338;
  _DWORD dword33C;
  _BYTE gap340[4];
  _DWORD dword344;
  _DWORD dword348;
	*/

	DX11_Context(const DX11_Context&);
	DX11_Context& operator=(const DX11_Context&);
};


} // gr


#endif // _GR_DX11_CONTEXT_H