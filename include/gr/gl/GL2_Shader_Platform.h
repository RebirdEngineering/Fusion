#ifndef _GR_GL_GL2_SHADERPLATFORM_H
#define _GR_GL_GL2_SHADERPLATFORM_H

#include "GL_common.h"
#include <gr/Shader.h>

//Not on OGL1

BEGIN_NAMESPACE(math) 
	class float4x4;END_NAMESPACE()

BEGIN_NAMESPACE(gr)

BEGIN_NAMESPACE(GL_NAMESPACE)

class GL_Texture;

class GL_Shader_Platform : //23
	public lang::Object
{
public:
	GL_Shader_Platform(); //27

	~GL_Shader_Platform(); //30

	unsigned int compileVertexShader( const std::vector<char>& vertexShaderData, const std::string& filename ); //36

	unsigned int compilePixelShader( const std::vector<char>& pixelShaderData, const std::string& filename); //42

	void createShaderProgram( unsigned int vertexShader, unsigned int pixelShader ); //47

	void setVertexShader( unsigned int vertexShader ); //52

	void setPixelShader( unsigned int pixelShader); //57

	void setProgramObject( unsigned int programObject ); //62

	void     begin(); //67

    void    end(); //72

	/**
     * Sets shader float parameter.
     */
    void    setFloat( Shader::ParamType param, float value ); //77
 
    /**
     * Sets custom float parameter which is not defined in ParamType.
     */
    void    setFloat( const char* name, float value ); //82

    /**
     * Sets custom float parameter which is not defined in ParamType.
     */
    void    setFloat( int handle, float value ); //87

	/**
     * Sets shader 4-vector parameter.
     */
    void    setVector( Shader::ParamType param, const NS(math,float4)& value ); //92
 
    /**
     * Sets custom shader 4-vector parameter which is not defined in ParamType.
     */
    void    setVector( const char* name, const NS(math,float4)& value ); //97

    /**
     * Sets custom shader 4-vector parameter which is not defined in ParamType.
     */
    void    setVector( int handle, const NS(math,float4)& value ); //102

	/**
     * Sets shader 4x4 matrix parameter.
     */
    void    setMatrix(Shader::ParamType param, const NS(math,float4x4)& value ); //107
 
    /**
     * Sets custom shader 4x4 matrix parameter which is not defined in ParamType.
     */
    void    setMatrix( const char* name, const NS(math,float4x4)& value ); //112

    /**
     * Sets custom shader 4x4 matrix parameter which is not defined in ParamType.
     */
    void    setMatrix( int handle, const NS(math,float4x4)& value ); //117

    /**
     * Sets shader 4x4 matrix array parameter.
     */
    void	setMatrixArray(Shader::ParamType param, NS(math, float4x4)* values, int count); //122

    /**
     * Sets shader 4x4 matrix array parameter.
     */
    void    setMatrixArray( const char* name, NS(math,float4x4)* values, int count ); //127

    /**
     * Sets shader 4x4 matrix array parameter.
     */
    void    setMatrixArray(int handle, NS(math, float4x4)* values, int count); //132

    /**
     * Sets shader texture parameter.
     */
    void	setTexture(Shader::ParamType param, GL_Texture* tex, int texturingUnit); //137

    /**
    * Sets custom shader texture parameter which is not defined in ParamType.
    */
    void    setTexture( int handle, GL_Texture* tex, int texturingUnit ); //142
 
    /**
     * Sets custom shader texture parameter which is not defined in ParamType.
     */
    void    setTexture( const char* name, GL_Texture* tex, int texturingUnit); //147

    /**
     * Gets shader float parameter or 0 if texture not set.
     */
    float           getFloat( int handle ); //152

    /**
     * Gets shader float parameter or 0 if texture not set.
     */
    float           getFloat( const char* name ); //157

    /**
     * Gets shader vector parameter or 0 if texture not set.
     */
    NS(math,float4) getVector( int handle ); //162

    /**
     * Gets shader vector parameter or 0 if texture not set.
     */
    NS(math,float4) getVector( const char* name ); //167

    /**
     * Gets shader matrix parameter or 0 if texture not set.
     */
    NS(math,float4x4)   getMatrix( int handle ); //172

    /**
     * Gets shader matrix parameter or 0 if texture not set.
     */
    NS(math,float4x4)   getMatrix( const char* name ); //177

    /**
     * Gets shader texture parameter or 0 if texture not set.
     */
    BaseTexture*    getTexture( int handle ); //182

    /**
     * Gets shader texture parameter or 0 if texture not set.
     */
    BaseTexture*    getTexture( const char* name ); //187

    unsigned int    getProgramObject() const; //192
    unsigned int m_attribIndex[12]; //194

    static GL_Shader_Platform* sm_currentPlatformShader; //196

private:
	std::string m_name; //199
	unsigned int m_vertexShader; //200
	unsigned int m_pixelShader; //201
	unsigned int m_programObject; //202

	std::vector<std::pair<int, std::string>> m_uniforms; //204

	std::map<unsigned int, float> m_floats; //206
	std::map<unsigned int, math::float4> m_vectors; //207
	std::map<unsigned int, math::float4x4> m_matrices; //208
	std::map<unsigned int, unsigned int> m_texturingUnit; //209

    int    getHandle(const char* name); //215
    int    getHandle(Shader::ParamType param); //216
};

}
}

#endif