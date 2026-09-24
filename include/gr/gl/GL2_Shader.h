#ifndef _GR_GL2_SHADER_H
#define _GR_GL2_SHADER_H


#include "GL_common.h"
#include <gr/Shader.h>

namespace math
{
    class float4x4; }


namespace gr
{

class BaseTexture;

namespace GL_NAMESPACE
{

class GL_Context;
class GL_Technique;
class GL_Pass;


/**
 * 
 */
class GL_Shader :
    public Shader
{
public:
    /**
     * Initializes the shader from fx file source code.
     * @param context Rendering context.
     * @param name Name of the shader.
     * @param filename 
     * @param flags Compilation flags. See NS(Shader,Flags).
     */
    explicit GL_Shader(GL_Context* context, const std::string& name, const std::string& filename, int flags); //38

    ///
    ~GL_Shader(); //41

    /**
     * Returns clone of this shader.
     * All parameters are unique to each clone, but code
     * and other constants are shared.
     */
    Shader* clone() const; //48

    /**
     * Called after reseting device.
     */
    void    reset(); //53

    /**
     * 
     * 
     * @param technique 
     */
    void    addTechnique( GL_Technique* technique ); //59

    /**
     *
     *
     * @param key
     * @param value
     */
    void    addProperty(const std::string& key, const std::string& value); //67

    /**
     * Sets rendering technique to be used when rendering objects using this shader.
     * If the requested technique is not supported, the shader is disabled.
     * @param name Name of the rendering technique to be set. Pass 0 or empty string to restore default technique.
     */
    void    setTechnique(const char* name); //77

    /**
     * 
     * 
     * @param name 
     */
    bool    hasTechnique(const char* name); //82

    /**
     * Sets shader texture parameter.
     */
    void    setTexture(ParamType param, BaseTexture* value); //87

    /**
     * Sets custom shader texture parameter which is not defined in ParamType.
     */
    void    setTexture(const char* name, BaseTexture* value); //92

    /**
     * Sets shader 4x4 matrix parameter.
     */
    void    setMatrix(ParamType param, const NS(math, float4x4)& value); //97

    /**
     * Sets custom shader 4x4 matrix parameter which is not defined in ParamType.
     */
    void    setMatrix(const char* name, const NS(math, float4x4)& value); //102

    /**
     * Sets shader 4x4 matrix array parameter.
     */
    void    setMatrixArray(ParamType param, NS(math, float4x4)** value, int count); //107

    /**
     * Sets shader 4x4 matrix array parameter.
     */
    void    setMatrixArray(const char* name, NS(math, float4x4)** values, int count); //112

    /**
     * Sets shader 4-vector parameter.
     */
    void    setVector(ParamType param, const NS(math, float4)& value); //117

    /**
     * Sets custom shader 4-vector parameter which is not defined in ParamType.
     */
    void    setVector(const char* name, const NS(math, float4)& value); //122

    /**
     * Sets shader float parameter.
     */
    void    setFloat(ParamType param, float value); //127

    /**
     * Sets custom float parameter which is not defined in ParamType.
     */
    void    setFloat(const char* name, float value); //132

    /**
     * Gets shader texture parameter or 0 if texture not set.
     */
    BaseTexture* getTexture(const char* name); //137

    /**
     * Gets shader matrix parameter or 0 if texture not set.
     */
    NS(math, float4x4)   getMatrix(const char* name); //142

    /**
     * Gets shader vector parameter or 0 if texture not set.
     */
    NS(math, float4) getVector(const char* name); //147

    /**
     * Gets shader float parameter or 0 if texture not set.
     */
    float           getFloat(const char* name); //152

    /**
	 * Begins rendering geometry using the shader.
	 * Prefer not using this method directly, but use Begin helper class instead.
	 * Rendering sequence:
	 * <ol>
	 * <li>First call NS(Shader,begin)() for the shader before rendering any geometry
	 * <li>Set shader parameters which need to be updated every frame, like transforms.
	 * <li>Call NS(Shader,beginPass)(0) to start rendering geometry using the first pass of the shader.
	 * <li>Call render() for each primitive to be rendered.
	 * <li>Call NS(Shader,endPass)() to stop rendering using this pass of the shader.
	 * <li>Loop to NS(Shader,beginPass)(i) for other passes, as many times as return value of begin() specified.
	 * <li>End rendering by calling NS(Shader,end)() for the shader.
	 * @return Number of passes to be rendered. 0 if shader is disabled.
	 */
    int     begin(); //169

    /**
     * Begins rendering using specified pass. See begin() for description
     * of the rendering sequence.
     */
    void    beginPass(int pass); //175

    /**
     * Ends rendering using specified pass. See begin() for description
     * of the rendering sequence.
     */
    void    endPass(); //181

    /**
     * Ends rendering using this shader. See begin() for description
     * of the rendering sequence.
     */
    void    end(); //187

    /**
     * Sets name of the shader.
     */
    void    setName(const std::string& name); //192

    /**
     * @param path
     */
    void    setFilePath(const std::string& path); //197

    /**
     * Sets shader sorting mode.
     */
    void    setSort(SortType sort); //202

    /**
     * Returns priority of the shader.
     * Higher priority shaders need to be rendered before lower priority ones.
     * Default priority is 0. Priorities can be negative.
     */
    int     priority() const; //211

    /**
     * Returns preferred sort mode of the shader.
     * Default sort mode is SORT_NONE.
     */
    SortType sort() const; //217

    /**
     * Returns true if the shader is enabled.
     */
    bool    enabled() const; //222

    /**
     * Returns name of the shader.
     */
    const std::string& name() const; //227

    /**
     * 
     */
    void reload(GL_Context* context); //232 | Recovered param name from ABFM

private:
    GL_Context*         m_context; //235
    std::vector<P(GL_Technique)>    m_techniques; //236
    std::string         m_name; //237
    std::string         m_filePath; //238
    int                 m_flags; //239
    SortType            m_sort; //240
    int8_t              m_priority; //241
    int8_t              m_currentTechnique; //242
    GL_Pass*            m_currentPass; //243
    bool                m_enabled; //244

    std::vector<std::pair<std::string, float>>            m_floats; //246
    std::vector<std::pair<std::string, math::float4>>           m_vectors; //247
    std::vector<std::pair<std::string, math::float4x4>>           m_matrices; //248
    std::vector<std::pair<std::string, std::vector<math::float4x4>>>         m_matrixArrays; //249
    std::vector<std::pair<std::string, BaseTexture*>>         m_textures; //250

    void                validateHandles(); //252

    GL_Shader(const GL_Shader&);
    GL_Shader& operator=(const GL_Shader&);
};

}
}


#endif // _GR_GL2_SHADER_H