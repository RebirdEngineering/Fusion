#ifndef _GR_GL_PRIMITIVE_H
#define _GR_GL_PRIMITIVE_H


#include <gr/Shader.h>
#include <gr/Context.h>
#include <gr/VertexFormat.h>
#include <gr/impl/DIPrimitive.h>
#include <math/float4.h>
#include "GL_common.h"

#define INVALID_BUFFER 0 //According to assert

BEGIN_NAMESPACE(math) 
	class float4;END_NAMESPACE()

BEGIN_NAMESPACE(gr)

class Shader;

BEGIN_NAMESPACE(GL_NAMESPACE)

class GL_Shader;
class GL_Context;

/**
 * 
 */
class GL_Primitive : //19
    public DIPrimitive
{
public:
    enum Constants { MAX_VBUFFERS = 12 };

    GL_Primitive(GL_Context* context, PrimType prim, const VertexFormat& vf, int vertices, int indices, Context::UsageFlags usage); //28

    ~GL_Primitive(); //30

    void    setShader(Shader* fx); //32

    /**
     * Renders the primitive.
     */
    void    render(); //37

    /**
     * Sets shader to be used while rendering the primitive.
     */
    Shader* shader() const; //42

    /**
     * Returns primitive type.
     */
    PrimType        type() const; //47

    /**
     * Returns number of triangles the primitive has in triangle list.
     * NOTE: Only indexed and non-indexed triangle lists are counted,
     * i.e. triangle strips, triangle fans and lines return 0 as triangle list size.
     */
    int     triangleListSize() const { return m_prim != PRIM_TRI ? 0 : (indexCount() > 0 ? indexCount() / 3 : vertexCount() / 3); } //54


private:
    GL_Context* m_context; //57
    P(GL_Shader) m_fx; //58
    GLuint m_ibuffer; //59
    GLuint m_vbuffers[MAX_VBUFFERS]; //60
    PrimType m_prim; //61
    LockType m_lock; //62
    int m_usage; //63

    void    allocate(const VertexFormat& vf, int vertices, int indices); //65
    void    deallocate(); //66
    void        getVertexDataPtr(VertexFormat::DataType dt, uint8_t** data, int* pitch); //67
    void        getIndexDataPtr(uint16_t** data, int* indexsize); //68

    void        lock(LockType lock); //70
    void        unlock(); //71

    void drawPrimitive(int, int); //73
    void drawIndexedPrimitive(int, int); //74

    int getGLDataType(VertexFormat::DataType dt) const; //76

    GL_Primitive(const GL_Primitive&); //78
    GL_Primitive& operator=(const GL_Primitive&); //79
};

} // gr
} // gles2

#endif