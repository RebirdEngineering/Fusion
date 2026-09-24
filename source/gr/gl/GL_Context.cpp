#include <gr/gl/GL_common.h>
#include <gr/gl/GL_Primitive.h>
#include <gr/gl/GL_Context.h>
#include <gr/gl/GL_Texture.h>
#include <gr/gl/GL_State.h>
#include <gr/gl/GL_Image.h>
#include <img/ImageWriter.h>
#include <lang/Log.h>
#include <io/PathName.h>
#include <io/BundleInputStream.h>
#include <io/FileFormat.h>
#include <img/ImageReader.h>
#include <math/float4x4.h>
#include <gr/GraphicsException.h>
#include <io/FileOutputStream.h>

using namespace lang;
using namespace img;
using namespace math;
using namespace io;

namespace gr
{

namespace GL_NAMESPACE //on iOS and Android, on MacOS, gl1+gl2
{
GL_Context::GL_Context(int w, int h, OrientationType orientation, void (*presentFunc)()) : //107-332 | WIP
    boneworldtm(),
    sortbuffer(),
    m_dynamicPrimitives(),
    m_projtm(1.f),
    m_viewtm(1.f),
    m_modelviewtm(1.f),
    m_customModelTM(1.f),
    m_viewport(-32000, -32000, -32000, -32000),
    m_width(w),
    m_height(h),
    m_windingOrder(GL_CW),
    m_customModelTMEnabled(false),
    m_sort(Shader::SORT_NONE),
    m_orientation(orientation),
    m_renderTarget(0),
    m_time(0.f),
    m_fovScaleBias(1.f, 0.f),
    m_plainShader(0),
    m_spriteAlphaShader(0),
    m_presentFunc(presentFunc)
{
    //setOrthographicProjection();
    //setViewTransform();


    LANG_LOG_DEBUG("GL", LANG_LOG_PRIORITY_INFO, "Vendor: %s", getGraphicsDriverVendor()); //In MacOS 3.0.0 this moved to log::log | 228 (OSX ABC 3.0.1, OSX ABS 3.1.1)
    LANG_LOG_DEBUG("GL", LANG_LOG_PRIORITY_INFO, "Renderer: %s", getGraphicsDriverRenderer()); //229 (OSX ABC 3.0.1, OSX ABS 3.1.1)
    LANG_LOG_DEBUG("GL", LANG_LOG_PRIORITY_INFO, "Version: %s", getGraphicsDriverVersion()); //230 (OSX ABC 3.0.1, OSX ABS 3.1.1)

#ifdef PLATFORM_WIN32 || defined(PLATFORM_OSX)
    GLenum error = glewInit();
    if (!error)
        throwError(GraphicsException(Format("glewInit failed! Reason: {0}", *glewGetErrorString(error))));

#ifdef GL1
    if (!GLEW_VERSION_1_3)
        throwError(GraphicsException(Format("OpenGL 1.3 is not supported"))); //Only on PC and Mac
#elif GL2
    if (!GLEW_VERSION_2_0)
        throwError(GraphicsException(Format("OpenGL 2.0 is not supported"))); //Only on PC and Mac

    //const GLubyte* langVer = glGetString(GL_SHADING_LANGUAGE_VERSION);
    //std::string shadingLangVer = string::split(".", langVer);

    //if (atoi(shadingLangVer) <= 0 || atoi(shadingLangVer) == 1 && atoi(shadingLangVer) <= 19)
        //throwError(GraphicsException(Format("GLSL 1.20 is not supported")));
#endif
#endif

    GL_State::frontFace(GL_CW); //324

    GL_State state; //328
    state.enable(GL_DEPTH_TEST);
    state.begin(true);
    setViewport(Rect(width(), height()));

    //assert(glGetError() == GL_NO_ERROR); //Line 167 in GL_Context (MacOS 1.0.0)

    //assert(glGetError() == GL_NO_ERROR); //Line 174 in GL_Context (MacOS 1.0.0)
    
    //Win, OSX only.


    //throwError( GraphicsException( Format("eglGetDisplay() failed")));
    //throwError( GraphicsException( Format("eglInitialize() failed, eglGetError: {0,x}", eglGetError())));
    //eglBindAPI(EGL_OPENGL_ES_API);
}

GL_Context::~GL_Context() //336
{
    m_batcher->reset(); //337

    m_plainShader = 0; //339
    m_plainAlphaShader = 0; //340
    m_spriteShader = 0; //341
    m_spriteAlphaShader = 0; //342
    m_dynamicPrimitives.clear(); //343
    m_uniqueShaders.clear(); //344
}

void GL_Context::createBackBuffer() //Bada, BB10, Maemo
{
}

void GL_Context::releaseBackBuffer()
{
}

static SurfaceFormat convertToCompatibleSurfaceFormat(const SurfaceFormat& fmt) //515
{
    switch (fmt.m_type)
    {
    case SurfaceFormat::SURFACE_R8G8B8: return SurfaceFormat(SurfaceFormat::SURFACE_B8G8R8);
    case SurfaceFormat::SURFACE_A8R8G8B8:
    case SurfaceFormat::SURFACE_P4: 
    case SurfaceFormat::SURFACE_P8: return SurfaceFormat(SurfaceFormat::SURFACE_A8B8G8R8);
    case SurfaceFormat::SURFACE_ETC1_RGB_4BPP: !GL_Context::isExtensionSupported("GL_OES_compressed_ETC1_RGB8_texture") ? fmt : SurfaceFormat(SurfaceFormat::SURFACE_R5G6B5);
    default: return fmt;
    }
}

Shader* GL_Context::createShader(const std::string& name, int flags) //542
{
    PathName pathname(name); //545
    std::string basename = pathname.basename(); //546

    GL_Shader* shader = m_uniqueShaders[basename]; //548
    if (shader)
        return shader->clone();

    shader = new GL_Shader(this, basename, PathName(pathname.parent().toString(), basename + ".fx").toString(), flags); //552
    m_uniqueShaders[basename] = shader; //553
    return shader;    
}

Texture* GL_Context::createTexture(const std::string& filename) //565
{
    P(InputStream) in = new BundleInputStream(filename); //568
    P(ImageReader) rd = new ImageReader(in, guessFileFormat(filename)); //569
    int w = rd->surfaceWidth(); //570
    int h = rd->surfaceHeight(); //571
    SurfaceFormat fmt = rd->format(); //572
    
    Texture* tex = createTexture(w, h, rd->mipLevels() - 1, fmt, USAGE_STATIC); //575
    tex->setName(filename);
    SurfaceFormat texfmt = tex->format(); //577

    LANG_LOG_DEBUG("GL", LANG_LOG_PRIORITY_INFO, "Loading texture %s: %dx%d %s (as %s) mips: %d'", filename, w, h, fmt.toString(), texfmt.toString(), rd->mipLevels() - 1); //521 (OSX ABC 3.0.1, OSX ABS 3.1.1)

    for (int mipLevel = 0; mipLevel < rd->mipLevels(); mipLevel++) //581
    {
        w = rd->surfaceWidth();
        h = rd->surfaceHeight();

        std::vector<uint8_t> texData; //586
        int dataSize = fmt.getMemoryUsage(w, h); //587

        int pitch = fmt.getMemoryUsage(w, 1); //590
        rd->readSurface(&texData, pitch, w, h, texfmt, 0, SurfaceFormat()); //Correct?
        tex->blt(0, 0, &texData, pitch, mipLevel, w, h, texfmt);

        if (mipLevel >= 1)
            statistics.allocatedTextureMemory += dataSize;
    }

    return tex;
}

Texture* GL_Context::createTexture(int width, int height, int mipcount, const img::SurfaceFormat& fmt, int usageflags) //602
{
    GL_Texture* tex = new GL_Texture(this, width, height, mipcount, usageflags, convertToCompatibleSurfaceFormat(fmt)); //604 | Defined twice in DWARF?
    statistics.allocatedTextures++;
    statistics.allocatedTextureMemory += fmt.getMemoryUsage(width, height);
    if (isTextureShadowingEnabled())
        m_textures.push_back(tex); //608
    return tex;
}

CubeTexture* GL_Context::createCubeTexture(const std::string& filename) //612
{
    throwError(GraphicsException(Format("Cube textures not supported"))); //614
    return 0;
}

Image* GL_Context::createImage(InputStream& in, const std::string& filename) //617
{
    P(InputStream) inPtr = new InputStream(in); //620
    P(ImageReader) rd = new ImageReader(inPtr, guessFileFormat(filename)); //621
    int w = rd->surfaceWidth(); //622
    int h = rd->surfaceHeight(); //623
    SurfaceFormat fmt = rd->format(); //624
    
    Image* img = createImage(w, h, rd->mipLevels() - 1, fmt, USAGE_STATIC); //627
    img->getTexture()->setName(filename);
    SurfaceFormat imgfmt = img->format(); //629
    LANG_LOG_DEBUG("GL", LANG_LOG_PRIORITY_INFO, "Loading image %s: %dx%d %s (as %dx%d %s) mips: %d", filename, w, h, fmt.toString(), imgfmt.toString(), rd->mipLevels() - 1 ); //573 (ABC OSX, ABS 3.1.1 OSX)

    for (int mipLevel = 0; mipLevel < rd->mipLevels(); mipLevel++) //633
    {
        w = rd->surfaceWidth();
        h = rd->surfaceHeight();

        std::vector<uint8_t> imgdata(w * h); //638 //imgdata.resize(w * h); //?
        int dataSize = imgfmt.getMemoryUsage(w, h); //639

        int pitch = imgfmt.getMemoryUsage(w, 1); //642
        rd->readSurface(&imgdata, pitch, w, h, imgfmt, 0, SurfaceFormat());
        img->blt(0, 0, &imgdata, pitch, mipLevel, w, h, imgfmt);

        if (mipLevel >= 1)
            statistics.allocatedImageMemory += dataSize;
    }

    return img;
}

Image* GL_Context::createImage(int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage) //654
{
    Image* img = new GL_Image(this, width, height, mipcount, usage, convertToCompatibleSurfaceFormat(fmt), false); //656
    statistics.allocatedImages++;
    statistics.allocatedImageMemory += img->format().getMemoryUsage(width, height);
    return img;
}

Image* GL_Context::createFlippedImage(int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage) //662
{
    Image* img = new GL_Image(this, width, height, mipcount, usage, convertToCompatibleSurfaceFormat(fmt), true); //664
    statistics.allocatedImages++;
    statistics.allocatedImageMemory += img->format().getMemoryUsage(width, height);
    return img;
}

Primitive* GL_Context::createPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices, UsageFlags usage) //670
{
    return new GL_Primitive(this, prim, vf, vertices, indices, usage);
}

Primitive* GL_Context::getDynamicPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices) //675
{
    for (size_t i = 0; i < m_dynamicPrimitives.size(); ++i) //677
    {
        Primitive* p = m_dynamicPrimitives[i]; //679
        if (p->vertexFormat() == vf &&
            p->type() == prim &&
            p->vertices() >= vertices &&
            p->indices() >= indices)
        {
            return p;
        }
    }
    m_dynamicPrimitives.push_back(new GL_Primitive(this, prim, vf, (vertices + 31) & ~31, (indices + 31) & ~31, Context::USAGE_DYNAMIC));
    return m_dynamicPrimitives.back(); //691
}

void GL_Context::end2D()
{
}

void GL_Context::begin2D()
{
}

bool cullScreen(const float3* vertpos, int size = 0) //697
{
    float minx = 3.4028e38; //702
    float miny = 3.4028e38; //700
    float maxx = -3.4028e38; //701
    float maxy = -3.4028e38; //702
    for (int i = 0; i < size; i++) //703
    {
        minx = fminf(vertpos->x - 1, minx);
        miny = fminf(vertpos->y - 1, miny);
        maxx = fmaxf(vertpos->x - 1, maxx);
        maxy = fmaxf(vertpos->y - 1, maxy);
        //? += 3;
    }

    return minx >= 1.0 && miny >= 1.0 && maxx < 1.0 && maxy < 1.0;
}

void GL_Context::drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth) //724
{
    /*float2 delta; //726

    float2 offset = m_renderState2D.getTranslation(); //732
    float2 scale = m_renderState2D.getScale(); //733
    float2 pivot = m_renderState2D.getRotationPivot(); //734
    float2 col0; //735
    float2 col1; //736

    float ex; //738
    float ey; //739
    float tx; //740
    float ty; //741
    float proj00 = viewport().width(); //742
    float proj11 = viewport().height(); //743

    //float2 linepos[]; //745

    // = normalize(//753 
    // *= //754

    float2 d; //759
    //float2 v = normalize(); //760

    int width = m_renderTarget->width(); //762
    int height = m_renderTarget->height(); //763

    float2 ext; //768

    if (cullScreen(vertpos, sizeof(vertpos))) //786
        return;

    float3 vertpos[4]; //791

    //getColorF(color, ?) //793

    //m_batcher->render(TYPE_LINE, )//801
    //m_renderState2D.getAlpha()//802

    /*const int CIRCLE_SEGMENTS = 32; //885
    const int DELTA2 = 0.125;
    const int NUM_VERTS = 64; //887
    float3 vertices[NUM_VERTS];
    float4 colors[];
    float colorf[];
    float proj11;
    float radiusX;
    float radiusY;*/
    assert("gr::GL_NAMESPACE::GL_Context::drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth) was not yet decompiled.");
}

void GL_Context::drawLine2D(unsigned int color, int* vertices, int count, int lineWidth) //806
{
    //Some assert?
}

void GL_Context::drawCircle2D(unsigned int color, int x, int y, int radius, int lineWidth) //811
{
    //Some assert?
}

void GL_Context::fillTriangle2D(unsigned int color, int x0, int y0, int x1, int y1, int x2, int y2) //816
{
    //Some assert?
}

void GL_Context::fillRect2D(unsigned int color, int x, int y, int w, int h, Blend blend) //821
{
    /*float2 offset = m_renderState2D.getTranslation(); //825
    float2 scale = m_renderState2D.getScale(); //826
    float2 pivot = m_renderState2D.getRotationPivot(); //827
    float2 col0; //828
    float2 col1; //829

    float ex; //831
    float ey; //832
    float tx; //833
    float ty; //834
    float proj00 = viewport().width();  //835
    float proj11 = viewport().height(); //836
    float3 vertpos[4]; //838

    if (cullScreen(vertpos, 4)) //854
    {
    }

    float4 colors[]; //859
    float colorf[]; //860
    getColorF(color, colorf); //861

    Shader* shader; //869

    //m_renderState2D.getAlpha(); //871

    shader = getPlainAlphaShader();
    
    m_batcher->render(RenderBatcher::TYPE_PLAIN, shader, vertpos, 0, colors, 0); //877*/

    assert("gr::GL_NAMESPACE::GL_Context::fillRect2D(unsigned int color, int x, int y, int w, int h, gr::Context::Blend blend) was not yet decompiled.");
}

void GL_Context::fillCircle2D(unsigned int color, int x, int y, int radius) //882 | Blank on Meego.
{
    /*static const int CIRCLE_SEGMENTS = 32; //885
    static const int DELTA2 = 0.125; //886
    static const int NUM_VERTS = 64; //887

    float2 offset = m_renderState2D.getTranslation(); //891
    float2 scale = m_renderState2D.getScale(); //892
    float2 pivot = m_renderState2D.getRotationPivot(); //893
    float2 col0; //894
    float2 col1; //895

    float tx; //897
    float ty; //898
    float proj00 = m_viewport.width(); //899
    float proj11 = m_viewport.height(); //900

    float3 center; //902

    float radiusX; //905
    float radiusY; //906

    float3 vertices[NUM_VERTS]; //908
    float4 colors[16]; //909
    float colorf[16]; //910

    getColorF(color, colorf);

    for (int i = 0; i < NUM_VERTS; i++)
    {
        int idxbase; //917

        //float3+ //919
        //float3+ //920
        //float3+ //921
    }
    
    float angle[]; //914


    cullScreen(vertices, 4); //933

    for (int i = 0; i < 4; i++) //938
    {
        m_batcher->render(RenderBatcher::TYPE_PLAIN, shader, vertpos, 0, colors, 0);
        m_renderState2D.getAlpha();
    }*/
    assert("gr::GL_NAMESPACE::GL_Context::fillCircle2D(unsigned int color, int x, int y, int radius) was not yet decompiled.");
}

void GL_Context::texturizeTriangle2D(Image* image, const float4& scaleBias, int x0, int y0, int x1, int y1, int x2, int y2) //946
{
    //Some assert?
}

void GL_Context::texturizeRect2D(Image* image, const float4& scalebias, int x, int y, int width, int height) //951
{
    //Some assert?
}

void GL_Context::texturizeCircle2D(Image* image, const float4& scalebias, int x, int y, int radius) //956
{
    //Some assert?
}

std::string GL_Context::getGraphicsDriverVendor()
{
    const GLubyte* vendor = glGetString(GL_VENDOR); //368
    return (std::string&)vendor;
}

std::string GL_Context::getGraphicsDriverVersion()
{
    const GLubyte* vendor = glGetString(GL_VERSION); //374 | Why vendor, something tells us you copied code
    return (std::string&)vendor;
}

std::string GL_Context::getGraphicsDriverRenderer()
{
    const GLubyte* vendor = glGetString(GL_RENDERER); //380 | Again wow
    return (std::string&)vendor;
}

RenderState2D& GL_Context::getRenderState2D()
{
    return m_renderState2D;
}

const Rect& GL_Context::viewport() const
{
    return m_viewport;
}

SurfaceFormat GL_Context::surfaceFormat() const
{
    return SurfaceFormat::SURFACE_B8G8R8;
}

int GL_Context::width() const
{
    return m_width;
}

int GL_Context::height() const
{
    return m_height;
}

float GL_Context::time() const
{
    return m_time;
}

const float3x4& GL_Context::customModelTransform() const
{
    return m_customModelTM;
}

bool GL_Context::customModelTransformEnabled() const
{
    return m_customModelTMEnabled;
}

const float4x4& GL_Context::projectionTransform() const
{
    return m_projtm;
}

const float4x4& GL_Context::viewTransform() const
{
    return m_viewtm;
}

const float2& GL_Context::getFovScaleBias() const
{
    return m_fovScaleBias;
}

Context::PlatformType GL_Context::platform() const
{
    return PLATFORM_GLES2; //on iOS
}

Context::OrientationType GL_Context::orientation() const
{
    return m_orientation;
}

bool GL_Context::ready() const
{
    return true;
}

const std::string& GL_Context::shaderPath() const
{
    return m_shaderPath;
}

void GL_Context::setRenderState2D(const RenderState2D& state) //1052
{
    m_renderState2D = state;
}

void GL_Context::setViewport(const Rect& rect) //1057
{
    m_batcher->flush(); //1059

    m_viewport = rect;

    if (m_renderTarget)
        GL_State::viewport(rect.left(), m_renderTarget->height() - rect.bottom(), rect.width() + rect.left(), rect.height() + m_renderTarget->height() - rect.bottom()); //1065
    else
        GL_State::viewport(rect.left(), m_height - rect.bottom(), rect.width(), rect.height() + m_height - rect.bottom()); //1069

    //assert(glGetError() == GL_NO_ERROR); //restore?
}

void GL_Context::setClipRect(const Rect& rect) //1075
{
    m_batcher->flush(); //1077
    GL_State::enable(GL_SCISSOR_TEST);

    if (m_renderTarget)
        GL_State::scissor(rect.left(), m_renderTarget->height() - rect.bottom(), rect.width() + rect.left(), rect.height() + m_renderTarget->height() - rect.bottom()); //1083
    else
        GL_State::scissor(rect.left(), m_height - rect.bottom(), rect.width(), rect.height() + m_height - rect.bottom()); //1087

    //assert(glGetError() == GL_NO_ERROR); //Line 995
}

void GL_Context::setRenderTarget(Texture* dst) //1093 | TODO
{
    //assert(glGetError() == GL_NO_ERROR); //Line 724
    m_batcher->flush(); //1095

    float4x4 invy(1.0); //1108
    invy *= projectionTransform();

    flipWindingOrder();

    m_renderTarget = (GL_Texture*)dst;

    unsigned int target; //1117
    unsigned int newWidth = dst ? dst->width() : width(); //1122
    unsigned int newHeight = dst ? dst->height() : height(); //1123

    glBindFramebuffer(GL_FRAMEBUFFER, m_renderTarget->fbo()); //1127

    setViewport(Rect(0, 0, newWidth, newHeight));
}

void GL_Context::setWireframeEnabled(bool enabled) //1154 | No code.
{
}

void GL_Context::setOrientation(OrientationType orientation) //1158
{
    m_orientation = orientation;
}

void GL_Context::setFovScaleBias(const float2& scalebias) //1158
{
    m_fovScaleBias = scalebias;
}

void GL_Context::setCustomModelTransform(const float3x4& customtm) //1166
{
    m_customModelTM = customtm;
}

void GL_Context::setCustomModelTransformEnabled(bool enabled) //1171
{
    m_customModelTMEnabled = enabled;
}

void GL_Context::setPerspectiveProjection(float aspect, float fov, float front, float back) //1181
{
    float4x4 tm(m_projtm); //1183
    tm.setPerspectiveProjection(aspect, fov, front, back);
}

void GL_Context::setOrthographicProjection()
{
    setProjection(float4x4(1.f));
}

void GL_Context::setProjection(const float4x4& projtm) //1193
{
    assert(glGetError() == GL_NO_ERROR);
    m_projtm = projtm;
    if (m_renderTarget)
    {
        float4x4 invy(1.0f); //1198
        invy *= m_projtm; //?
    }
}

void GL_Context::setViewTransform(const float4x4& viewtm) //1209
{
    m_viewtm = viewtm;
}

void GL_Context::setTime(float time) //1214
{
    m_time = time;
}

void GL_Context::setShaderPath(const std::string& path) //1219
{
    m_shaderPath = path; //1221
}

void GL_Context::reset(int w, int h) //1227 | Correct?
{
    if (m_width == w || m_height == h)
        return;

    m_width = w;
    m_height = h;

    setViewport(Rect(0, 0, width(), height()));
}

void GL_Context::beginScene()
{

}

void GL_Context::endScene()
{

}

void GL_Context::reloadShaders()
{

}

void GL_Context::present()
{
    m_batcher->flush(); //1262
    m_presentFunc();
}

void GL_Context::clear(unsigned int color, bool clearColor, bool clearDepth, bool clearStencil) //1291
{
    setClipRect(m_renderState2D.getClip()); //1293

    unsigned int clearFlags; //1295

    if (clearColor)
    {
        float colorf[4]; //1299
        getColorF(color, colorf); //1300

        GL_State::clearColor(colorf[0], colorf[1], colorf[2], colorf[3]); //1304
        clearFlags = GL_COLOR_BUFFER_BIT;
    }

    if (clearDepth)
    {
        GL_State::depthMask(-1); //1310
        clearFlags |= GL_DEPTH_BUFFER_BIT;
    }

    if (clearStencil)
        clearFlags |= GL_STENCIL_BUFFER_BIT;

    if (clearFlags)
    {
        glClear(clearFlags);
        GL_State::depthMask(false); //1335
    }

    //assert(glGetError() == GL_NO_ERROR); //Line 909


    //assert(glGetError() == GL_NO_ERROR); //Line 912


    //assert(glGetError() == GL_NO_ERROR); //Line 915
}

void GL_Context::capture(const std::string& filename) //1338
{
    FileOutputStream out(filename); //1350
    FileFormat ff = guessFileFormat(filename); //1341
    capture(out, ff);
}

void GL_Context::capture(OutputStream& out, FileFormat ff) //1345 | TODO
{
    /*m_batcher->flush(); //1347

    int width = m_renderTarget ? m_renderTarget->width() : m_width; //1349
    int height = m_renderTarget ? m_renderTarget->height() : m_height; //1350

    std::vector<unsigned int> data; //1352
    std::vector<unsigned int> reserved; //1353

    glReadPixels(m_viewport.left(), height - m_viewport.bottom(), width, height, GL_RGBA, GL_UNSIGNED_BYTE, &data); //1356

    int pitch; //1360
    //for (int y = 0; y <; //1361

    ImageWriter::write(out, ff, &data, width, height, SurfaceFormat::SURFACE_A8B8G8R8, SurfaceFormat::SURFACE_A8B8G8R8);*/
    assert("void gr::GL_NAMESPACE::GL_Context::capture(OutputStream& out, FileFormat ff) was not yet decompiled.");
}

P(Image) GL_Context::capture(P(Image) image) //1368 | TODO
{
    m_batcher->flush(); //1370

    int width = m_renderTarget ? m_renderTarget->width() : m_width; //1372
    int height = m_renderTarget ? m_renderTarget->height() : m_height; //1373

    if (!image) //1376
        image = createFlippedImage(width, height, 0, surfaceFormat(), Context::USAGE_DEFAULT); //1377

    if (image->width() != width || image->height() != height) //1379
        throwError(Exception(Format("Wrong size capture target image"))); //1380

    int textureWidth = image->getTexture()->width(); //1382
    int textureHeight = image->getTexture()->height(); //1383
   
    GL_Texture* texture = (GL_Texture*)image->getTexture(); //1386
    GL_State::bindTexture(GL_TEXTURE_2D, texture->tex()); //1387
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, textureWidth, textureHeight, 0);

    return image; //1390
}

void GL_Context::flipWindingOrder()
{
    m_batcher->flush(); //1395

    GL_State::frontFace(m_windingOrder = GL_CCW ? GL_CW : GL_CCW); //1397 | Correct?
}

void GL_Context::hibernateContext() //Correct?
{
    if (isTextureShadowingEnabled()) //1405
    {
        for (size_t i = 1; i < 7; i++) //1407
        {
            GL_State::activeTexture(GL_TEXTURE0 + i); //1409
            GL_State::bindTexture(GL_TEXTURE_2D, i); //1410
        }

        for (size_t i = 0; i < m_textures.size(); i++) //1420
            m_textures[i]->deallocate();

        glFinish();
    }
}

void GL_Context::resumeContext()
{
    if (isTextureShadowingEnabled())
    {
        for (size_t i = 0; i < m_textures.size(); i++) //1441
        {
            ShadowingTextureData& tex = m_textures[i]->m_shadowingTex; //1443
            m_textures[i]->allocate(tex.m_context, tex.m_width, tex.m_width, tex.m_mipcount, tex.m_fmt, tex.m_usageflags);

            for (size_t j = 0; j < m_textures[i]->m_shadowingSurf.size(); j++) //1446
            {
                m_textures[i]->m_restoring = true;
                ShadowingSurfaceData* surf = m_textures[i]->m_shadowingSurf[j]; //1449

                m_textures[i]->blt(surf->m_x, surf->m_y, surf->m_data.data(), surf->m_pitch, surf->m_miplevel, surf->m_w, surf->m_w, surf->m_fmt); //1451
                m_textures[i]->m_restoring = false;
            }
        }
        glFinish();
    }
}

void GL_Context::flush()
{
    m_batcher->flush(); //1461
}

void GL_Context::removeTexture(Texture* tex) //1464
{
    for (int i = 0; i < m_textures.size(); i++) //1466
    {
        if (m_textures[i] == tex)
            delete m_textures[i]; //?
    }
}

void GL_Context::saveCachedState(const std::string& name) //1475
{
    m_stateStorage[name] = GL_State::sm_current; //1477
}

void GL_Context::restoreCachedState(const std::string& name) //1480
{
    if (&m_stateStorage.find(name)) //1482
        m_stateStorage[name] = GL_State::sm_current; //1483
}

void GL_Context::resetCachedState()
{
    GL_State::reset();
}

void GL_Context::getColorF(int color, float* colorf) //1491
{
    SurfaceFormat fmt(SurfaceFormat::SURFACE_A32B32G32R32F); //1493
    fmt.copyPixels(colorf, SurfaceFormat(), 0, SurfaceFormat::SURFACE_A8R8G8B8, this, SurfaceFormat(), 0, 1);
}

bool GL_Context::isExtensionSupported(const char* extension) //1497
{
   /* if (strchr(extension, ' ') || !extension)
        return false;
    
    const GLubyte* extensions = glGetString(GL_EXTENSIONS); //1502
    //const GLubyte* start = //1503;
    //GLbyte* where, terminator = m_stateStorage.find(); //1504
    if (!strstr((char*)extensions, extension))
        return false;
    {
        //GLbyte* where,terminator = m_stateStorage.find();
    }
    return true;
    */
    assert("bool gr::GL_NAMESPACE::GL_Context::isExtensionSupported(const char* extension) is not yet decompiled. Returning false.");
    return false;
}

}
}