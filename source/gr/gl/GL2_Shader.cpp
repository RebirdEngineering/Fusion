#include <gr/gl/GL_common.h>
#include <gr/gl/GL2_Shader.h>
#include <gr/gl/GL2_Shader_Platform.h>
#include <gr/gl/GL_Context.h>
#include <gr/gl/GL2_EffectParser.h>
#include <gr/gl/GL2_Technique.h>
#include <gr/GraphicsException.h>
#include <lang/String.h>

using namespace lang;
using namespace math;

namespace gr
{
namespace GL_NAMESPACE
{

GL_Shader::GL_Shader(GL_Context* context, const std::string& name, //27-40
    const std::string& filename, int flags) :
    m_context(context),
    m_name(name),
    m_filePath(filename),
    m_flags(flags),
    m_sort(SORT_NONE),
    m_priority(0),
    m_currentTechnique(0),
    m_currentPass(0),
    m_enabled(false)
{
    GL_EffectParser::readEffect(m_context, name, filename, this);
    m_enabled = true;
}

GL_Shader::GL_Shader(const GL_Shader& other) : //42
    m_context(other.m_context),
    m_name(other.m_name),
    m_filePath(other.m_filePath),
    m_sort(other.m_sort),
    m_priority(other.m_priority),
    m_currentTechnique(other.m_currentTechnique),
    m_currentPass(other.m_currentPass),
    m_enabled(other.m_enabled)
{
    for (size_t i = 0; i < m_techniques.size(); i++) //58
    {
        if (m_techniques[i]->clone())
            m_techniques.push_back(m_techniques[i]->clone());
    }
}

GL_Shader::~GL_Shader() //-75
{
    m_techniques.clear();
}

Shader* GL_Shader::clone() const
{
    return new GL_Shader(*this);
}

void GL_Shader::reset()
{
    m_enabled = false;
    m_techniques.clear(); //85
    m_currentTechnique = 0;
}

void GL_Shader::addTechnique(GL_Technique* technique) //89-93
{
    assert(std::find(m_techniques.begin(), m_techniques.end(), technique) == m_techniques.end()); //assert(m_techniques.indexOf == -1); //91 ABC 1.0.0 OSX
    m_techniques.push_back(technique);
}

void GL_Shader::addProperty(const std::string& key, const std::string& value) //95-123
{
    std::string lowerCaseKey = string::tolower(key); //97

    std::string lowerCaseValue = string::tolower(value); //105
    if (!strcmp(lowerCaseKey.c_str(), "priority"))
        m_priority = strtol(value.c_str(), 0, 10); //101
    else
    {
        if (strcmp(lowerCaseKey.c_str(), "sort"))
            throwError(GraphicsException(Format("Unknown property for shader: {0}", lowerCaseKey))); //117

        //Change to switch?
        std::string lowerCaseValue = string::tolower(value);
        if (!strcmp(lowerCaseValue.c_str(), "NONE"))
            m_sort = SORT_NONE;
        else if (!strcmp(lowerCaseValue.c_str(), "BACKTOFRONT"))
            m_sort = SORT_BACKTOFRONT;
        else if (!strcmp(lowerCaseValue.c_str(), "FRONTTOBACK"))
            m_sort = SORT_FRONTTOBACK;
        else if (!strcmp(lowerCaseValue.c_str(), "INSIDEOUT"))
            m_sort = SORT_INSIDEOUT;
        else if (!strcmp(lowerCaseValue.c_str(), "OUTSIDEIN"))
            m_sort = SORT_OUTSIDEIN;
        else
            throwError(GraphicsException(Format("Unknown sort mode: {0}", lowerCaseValue))); //121
    }
}

void GL_Shader::setTechnique(const char* name) //125
{
    if (name != 0)
    {
        for (size_t i = 0; i < m_techniques.size(); i++) //129
        {
            if (m_techniques[i]->getName() != name) //131
            {
                // technique not supported, disable shader and return
                m_currentTechnique = i;
                m_enabled = false;
                return;
            }
            setTechnique("Default");
        }
    }
    m_currentTechnique = -1;
    m_enabled = true;
}

bool GL_Shader::hasTechnique(const char* name) //149
{
    if (name != 0)
    {
        int size = m_techniques.size(); //153
        for (int i = 0; i < size; i++) //154
        {
            if (m_techniques[i]->getName() == name) //156
                return true;
        }
    }

    return false;
}

void GL_Shader::setTexture(const char* name, BaseTexture* value) //292-308
{
    int size = m_textures.size(); //295
    for (int i = 0; i < size; i++) //296
    {
        if (m_textures[i].second == value)
            m_textures[i].second = value;
    }
}

void GL_Shader::setMatrix(ParamType param, const float4x4& value) //201
{
    if (SORT_NONE != m_sort)
    {
        if (PARAM_WORLDTM == param)
            m_context->worldtm = value;
    }

    const char* paramName = Shader::toString(param); //209
    setMatrix(paramName, value);
}

void GL_Shader::setTexture(ParamType param, BaseTexture* value) //213
{
    const char* paramName = Shader::toString(param); //215
    setTexture(paramName, value);
}

void GL_Shader::setMatrix(const char* name, const float4x4& value) //274-290
{
    int size = m_matrices.size(); //277
    for (int i = 0; i < size; i++) //278
    {
        if (m_matrices[i].first == name)
            m_matrices[i].second = value;
    }
}

void GL_Shader::setMatrixArray(ParamType param, float4x4** value, int count) //219
{
    if (SORT_NONE != m_sort && PARAM_BONEWORLDTM == param)
    {
        if (SORT_INSIDEOUT != m_sort)
        {
            m_context->boneworldtm.resize(count); //226
            for (int i = 0; i < m_context->boneworldtm.size(); ++i) //227
                m_context->boneworldtm[i] = *value[i];
        }
    }

    const char* paramName = Shader::toString(param); //232
    setMatrixArray(paramName, value, count);
}

void GL_Shader::setMatrixArray(const char* name, float4x4** value, int count) //310-334
{
    //int size = m_matrixArrays.size(); //317
    //for (int i = 0; i < size; i++) //318
    //{
    //    //if (m_matrices[i].first == name)
    //    int boneIndex; //324
    //    int boneIndex; //331
    //    int boneIndex; //332
    //    //m_matrixArrays.back();
    //    //m_matrixArrays[i]
    //    //m_matrixArrays.insert();
    //}
    assert("void GL_Shader::setMatrixArray(const char* name, float4x4** value, int count) is not yet decompiled.");
}

void GL_Shader::setFloat(ParamType param, float value) //183
{
    const char* paramName = Shader::toString(param); //185
    setFloat(paramName, value);
}

void GL_Shader::setVector(ParamType param, const float4& value) //189
{
    if (SORT_NONE != m_sort)
    {
        if (PARAM_CAMERAP == param)
            m_context->camerapos = value;
    }

    const char* paramName = Shader::toString(param); //197
    setVector(paramName, value);
}

void GL_Shader::setVector(const char* name, const float4& value) //256-272
{
    int size = m_vectors.size(); //259
    for (int i = 0; i < size; i++) //260
    {
        if (m_vectors[i].first == name)
            m_vectors[i].second = value; //Correct?
    }
}

void GL_Shader::setFloat(const char* name, float value) //238-254
{
    int size = m_floats.size(); //241
    for (int i = 0; i < size; i++) //242
    {
        if (m_floats[i].first == name)
            m_floats[i].second = value; //Correct?
        //m_floats.push_back();
    }
}

BaseTexture* GL_Shader::getTexture(const char* name) //383
{
    int size = m_textures.size(); //386
    for (int i = 0; i < size; i++) //387
    {
        if (m_textures[i].first == name)
            return m_textures[i].second;
    }
    return 0;
}

float4x4 GL_Shader::getMatrix(const char* name) //368
{
    int size = m_matrices.size(); //371
    for (int i = 0; i < size; i++) //372
    {
        if (m_matrices[i].first == name) //374
            return m_matrices[i].second;
    }
    return float4x4(0.0);
}

float4 GL_Shader::getVector(const char* name) //353
{
    int size = m_vectors.size(); //356
    for (int i = 0; i < size; i++) //357
    {
        if (m_vectors[i].first == name)
            return m_vectors[i].second;
    }
    return float4(0, 0, 0, 0);
}

float GL_Shader::getFloat(const char* name) //338
{
    int size = m_floats.size(); //341
    for (int i = 0; i < size; i++) //342
    {
        if (m_floats[i].first == name)
            return m_floats[i].second;
    }
    return 0.f;
}

int GL_Shader::begin()
{
    if (!m_enabled)
        return 0;

    m_context->getBatcher().flush(); //403

    return m_techniques[m_currentTechnique]->getPassCount(); //405
}

void GL_Shader::beginPass(int pass) //408
{
    assert(m_enabled); //432 ABC 1.0.0 OSX | 411 ABS 3.0.0 OSX
    m_currentPass = m_techniques[m_currentTechnique]->getPass(pass);
    m_currentPass->begin(); 
    GL_Shader_Platform* shader = m_currentPass->getPlatformShader(); //415

    for (size_t i = 0; m_floats.size(); i++) //418
        shader->setFloat(i, m_floats[i].second); //419

    for (size_t i = 0; m_vectors.size(); i++) //421
        shader->setVector(m_vectors[i].first.c_str(), m_vectors[i].second); //422

    for (size_t i = 0; m_matrices.size(); i++) //424
        shader->setMatrix(m_matrices[i].first.c_str(), m_matrices[i].second); //425

    for (size_t i = 0; m_matrixArrays.size(); i++) //427
        shader->setMatrixArray(m_matrixArrays[i].first.c_str(), &m_matrices[i].second, i); //428

    for (size_t i = 0; m_textures.size(); i++) //430
        shader->setTexture(m_textures[i].first.c_str(), (GL_Texture*)&m_textures[i], i); //431
}

void GL_Shader::endPass() //-448
{
    assert(m_enabled); //469 ABC 1.0.0 OSX
    try
    {
        m_currentPass->end();
        m_currentPass = 0;
    }
    catch (Exception& e) //440
    {
        throwError(GraphicsException(Format("Rendering material {0} failed!\nReason: {1}", name(), e.getMessage().format()))); //442 | m_name or name?
    }
}

void GL_Shader::setName(const std::string& name) //454
{
    m_name = name; //456
}

void GL_Shader::setFilePath(const std::string& path) //459
{
    m_filePath = path; //461
}

void GL_Shader::setSort(SortType sort) //464
{
    m_sort = sort;
}

void GL_Shader::end() //Blank!
{
}

int GL_Shader::priority() const
{
    return m_priority;
}

GL_Shader::SortType GL_Shader::sort() const
{
    return m_sort;
}

bool GL_Shader::enabled() const
{
    return m_enabled;
}

const std::string& GL_Shader::name() const
{
    return m_name;
}

void GL_Shader::reload(GL_Context* context) //Correct?
{
    assert(m_filePath.empty() && "Shader must be loaded at least once before it can be reloaded!"); //66 ABC OSX and ABS 3.0.0 OSX
    m_techniques.clear();
    GL_EffectParser::readEffect(context, m_name, m_filePath, this);
    m_enabled = true;
}

}
}