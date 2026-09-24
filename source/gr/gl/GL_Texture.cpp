#include <gr/gl/GL_common.h>
#include <gr/gl/GL_Texture.h>
#include <gr/gl/GL_Context.h>
#include <gr/gl/GL_State.h>
#include <gr/GraphicsException.h>
#include <lang/Math.h>

USING_NAMESPACE(img)
USING_NAMESPACE(lang)

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE)

static void getGLFormat(SurfaceFormat fmt, GLenum* type, GLenum* format) //17
{
    switch (fmt.type())
    {
    case SurfaceFormat::SURFACE_R8G8B8:				//return;       
    case SurfaceFormat::SURFACE_B8G8R8:				*type = GL_UNSIGNED_BYTE; *format = GL_RGB;
    case SurfaceFormat::SURFACE_A8R8G8B8:			//return;        
    case SurfaceFormat::SURFACE_A8B8G8R8:			*type = GL_UNSIGNED_BYTE; *format = GL_RGBA;
    case SurfaceFormat::SURFACE_R5G6B5:				*type = GL_UNSIGNED_SHORT_5_6_5; *format = GL_RGB;
    case SurfaceFormat::SURFACE_L8:				    *type = GL_UNSIGNED_BYTE; *format = GL_LUMINANCE;
    case SurfaceFormat::SURFACE_A8L8:			    *type = GL_UNSIGNED_BYTE; *format = GL_LUMINANCE_ALPHA;
    case SurfaceFormat::SURFACE_R4G4B4A4:			*type = GL_UNSIGNED_SHORT_4_4_4_4; *format = GL_RGBA;
    case SurfaceFormat::SURFACE_R5G5B5A1:			*type = GL_UNSIGNED_SHORT_5_5_5_1; *format = GL_RGBA;
    case SurfaceFormat::SURFACE_A8:					*type = GL_UNSIGNED_BYTE; *format = GL_ALPHA;
    case SurfaceFormat::SURFACE_PVRTC_RGB_2BPP:		*type = 0; *format = GL_TEXTURE_COMPRESSED & GL_RGB;
    case SurfaceFormat::SURFACE_PVRTC_RGBA_2BPP:	*type = 0; *format = GL_TEXTURE_COMPRESSED & GL_RGBA;
    case SurfaceFormat::SURFACE_PVRTC_RGB_4BPP:	    *type = 0; *format = GL_TEXTURE_COMPRESSED & GL_RGB;
    case SurfaceFormat::SURFACE_PVRTC_RGBA_4BPP:	*type = 0; *format = GL_TEXTURE_COMPRESSED & GL_RGBA;
    default:										assert(!"Trying to create texture with unsupported color format"); throwError(GraphicsException(Format("Unsupported texture format: {0}", fmt.toString()))); break; //73 ABC 1.0.0 + 1.6.3 OSX
    }
}

GL_Texture::GL_Texture(GL_Context* context, int width, int height, int mipcount, int usageflags, SurfaceFormat format) : //122
    m_tex(0),
    m_fbo(0),
    m_depthBuffer(0),
    m_width(width),
    m_height(height),
    m_format(SurfaceFormat::SURFACE_UNKNOWN),
    m_name(),
    m_autoRotate(false),
    m_lock(LOCK_NONE)
{
    allocate(context, width, height, mipcount, format, usageflags);
}

GL_Texture::~GL_Texture() //138
{
    if (m_shadowingTex.m_context->isTextureShadowingEnabled())
        m_shadowingTex.m_context->removeTexture(this);

    deallocate();
}

void GL_Texture::allocate(GL_Context* context, int width, int height, int mipcount, SurfaceFormat format, int usageflags) //144
{
    /*deallocate();

    int fullMips = Math::log(m_width); //148
    assert(mipcount >= 0 && mipcount <= fullMips); //103 of OSX

    GLint maxTexSize; //151
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
    if (maxTexSize < height || maxTexSize < width)
        throwError(GraphicsException(Format("Texture is too large: {0}x{1}, maximum supported size: {2}x{3}", height, width, maxTexSize, maxTexSize))); //154

    bool isRenderTarget = usageflags & Context::USAGE_RENDERTARGET; //156
    assert(!(m_format.compressed() && isRenderTarget)); //117 of OSX
    m_autoRotate = isRenderTarget;
    glGenTextures(1, &m_tex);

    GL_State::activeTexture(GL_TEXTURE0); //168
    GL_State::bindTexture(GL_TEXTURE_2D, m_tex); //169

    GLenum type,glformat; //171
    getGLFormat(m_format, &type, &glformat);

    int minFilterType = fullMips == mipcount ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR; //175

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if ((!width || ((width - 1) & width) != 0 || !height || ((height - 1) & height) != 0))
    {
        if (fullMips >= 1)
            throwError(GraphicsException(Format("Mipmapping is not supported with non power-of-two textures"))); //189

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    

    Math::isPow(); //183

    m_format->compressed();

    GL_State::bindTexture(GL_TEXTURE_2D, 0);
    GL_State::clearColor(1f, 0f, 1f, 0f);

    

    if (m_format.compressed()) //200
    {
        //int mip = //202;

        int w = Math::max(1, ); //205
        int h = Math::max(1, ); //206
    }


    GL_State::bindTexture(GL_TEXTURE_2D, 0); //214

    GL_State::depthMask(-1); //350
    GL_State::clearColor(0.0, 0.0, 0.0, 0.0); //351

    GL_State::depthMask(); //356

    GL_State::bindTexture(GL_TEXTURE_2D, 0); //

    assert(!(mipcount > 1 && isRenderTarget));


    assert(glGetError() == GL_NO_ERROR);










    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);










    assert(glGetError() == GL_NO_ERROR);









    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(complete);
    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);





    assert(glGetError() == GL_NO_ERROR);




    assert(glGetError() == GL_NO_ERROR);


    assert(glGetError() == GL_NO_ERROR);*/
    assert("void GL_Texture::allocate(GL_Context* context, int width, int height, int mipcount, SurfaceFormat format, int usageflags) was not yet decompiled.");
}

void GL_Texture::deallocate()
{
    /*int texUnits; //378
    if (m_tex)
    {
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texUnits);
        for (int i = 0; i < texUnits+8; i++) //382
        {
            GL_State::activeTexture(i); //384
            GL_State::bindTexture(GL_TEXTURE_2D, 0); //385
            glDeleteTextures(1, &m_tex);
        }
    }

    if (m_depthBuffer)
    {
        glDeleteRenderbuffers(1, &m_depthBuffer);
        m_depthBuffer = 0;
    }

    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }

    glFinish();*/

    //assert(glGetError() == GL_NO_ERROR); //210
    //
    //
    //
    //
    //
    //
    //assert(glGetError() == GL_NO_ERROR); //217
    //
    //
    //
    //
    //
    //
    //assert(glGetError() == GL_NO_ERROR); //224
    
    //glFinish();

    assert("void GL_Texture::deallocate() is not yet decompiled.");
}

void GL_Texture::blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const SurfaceFormat& fmt) //443 TODO
{
    assert(pitch * 8 >= w * fmt.bitsPerPixel()); //233 (ABC OSX 1.0.0)
    assert(x >= 0); //234 (ABC OSX 1.0.0)
    assert(y >= 0); //235 (ABC OSX 1.0.0)
    assert(w >= 0); //236 (ABC OSX 1.0.0)
    assert(h >= 0); //237 (ABC OSX 1.0.0)
    assert(x + w <= width()); //237 (ABC OSX 1.0.0)
    assert(y + h <= height()); //238 (ABC OSX 1.0.0)
    //Palette is obsoleted.
    assert(fmt == m_format); //240 (ABC OSX 1.0.0)

    if (m_shadowingTex.m_context->isTextureShadowingEnabled())
        m_shadowingSurf.push_back(new ShadowingSurfaceData(x, y, data, pitch, miplevel, w, h, fmt));

    GL_State::activeTexture(GL_TEXTURE0); //459
    GL_State::bindTexture(GL_TEXTURE_2D, m_tex); //460

    GLenum type, glformat; //462
    getGLFormat(fmt, &type, &glformat);

    if (fmt.compressed()) //465
    {
        glCompressedTexImage2D(GL_TEXTURE_2D, miplevel, glformat, w, h, 0, fmt.getMemoryUsage(w, h), data);
        assert(glGetError() == GL_NO_ERROR); //258 (ABC OSX 1.0.0)
    }

    else
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        assert(glGetError() == GL_NO_ERROR); //264 (ABC OSX 1.0.0)

        glTexSubImage2D(GL_TEXTURE_2D, miplevel, x, y, w, h, glformat, type, data);
        assert(glGetError() == GL_NO_ERROR); //268
    }

    glFlush();

    GL_State::bindTexture(GL_TEXTURE_2D, 0); //484
}

void GL_Texture::clear()
{
    assert(!"Not implemented!"); //278
}

Rect GL_Texture::rect() const
{
    return Rect(m_width, m_height);
}

int GL_Texture::width() const
{
    return m_width;
}

int GL_Texture::height() const
{
    return m_height;
}

int GL_Texture::pitch() const
{
    return m_format.getMemoryUsage(m_width, m_height);
}

SurfaceFormat GL_Texture::format() const
{
    return m_format;
}

void GL_Texture::lock(LockType lock) //517
{
    if (lock != LOCK_READ)
        throwError(Exception(Format("Only LOCK_READ is supported when locking texture"))); //520

    m_lock = LOCK_READ;
}

void GL_Texture::unlock()
{
    m_lockedData.swap(m_lockedData); //536 | ?
    m_lock = LOCK_NONE; //537
}

void GL_Texture::getData(void** bits, int* pitch) const //540
{
    assert(!"Not implemented!"); //316
    throwError(Exception(Format("Texture readback is not supported by OpenGL ES"))); //543
}

const std::string& GL_Texture::getName() const
{
    return m_name;
}

void GL_Texture::setName(const std::string& name) //559
{
    m_name = name; //561
}

/*
void gl2::GL_Texture::getData( void** bits, int* pitch ) const
{
    if (locked() == LOCK_NONE)
    {
        throwError(Exception(Format("Texture must be locked with LOCK_READ before getData() can be called")));
    }
    //?
    *bits = m_lockedRect.pBits;
	*pitch = m_lockedRect.Pitch;
}*/

/*
void gl2::GL_Texture::allocate( int width, int height, int mipcount, int usageflags, GL_Context*, SurfaceFormat )
{
    throwError(GraphicsException(Format("Texture is too large: {0}x{1}, maximum supported size: {2}x{3}")));
}


void gl2::parseValue(String *value, char name, unsigned int values)
{
    throwError(GraphicsException(Format("Unsupported value {0}")));
}


void gl2::parseBoolean(String *value)
{
    if (value == "TRUE")
    {
        return 1;
    }
    if (value == "FALSE")
    {
        return 0;
    }
    else
    {
        throwError(GraphicsException(Format("Unsupported value {0}"), value));
    }
}*/

}
}