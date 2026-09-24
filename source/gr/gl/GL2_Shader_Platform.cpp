#include <gr/gl/GL_common.h>
#include <gr/gl/GL2_Shader_Platform.h>
#include <gr/gl/GL_State.h>
#include <gr/gl/GL_Texture.h>
#include <gr/VertexFormat.h>
#include <gr/GraphicsException.h>
#include <math/float4x4.h>

using namespace lang;
using namespace math;

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE)

GL_Shader_Platform::GL_Shader_Platform() :
	m_vertexShader(0),
	m_programObject(0)
{
}

GL_Shader_Platform::~GL_Shader_Platform() //-61
{
	if (m_vertexShader)
	{
		if (m_programObject)
			glDetachShader(m_programObject, m_vertexShader);
		glDeleteShader(m_vertexShader);
	}

	if (m_vertexShader)
	{
		if (m_programObject)
			glDetachShader(m_programObject, m_pixelShader);
		glDeleteShader(m_pixelShader);
	}

	if (m_programObject)
		glDeleteProgram(m_programObject);

	m_texturingUnit.clear();
	m_matrices.clear();
	m_vectors.clear();
	m_floats.clear();
	m_uniforms.clear();
}

unsigned int GL_Shader_Platform::compileVertexShader(const std::vector<char>& vertexShaderData, const std::string& filename) //63-98
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); //66
	assert(glGetError() == GL_NO_ERROR); //60 ABC 1.0.0 OSX

	const char* data = vertexShaderData.data(); //70
	
	int length = vertexShaderData.size(); //72

	glShaderSource(vertexShader, 1, &data, &length);
	assert(glGetError() == GL_NO_ERROR); //67 ABC 1.0.0 OSX

	glCompileShader(vertexShader);
	assert(glGetError() == GL_NO_ERROR); //71 ABC 1.0.0 OSX

	GLint bShaderCompleted; //81

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &bShaderCompleted);
	assert(glGetError() == GL_NO_ERROR); //76 ABC 1.0.0 OSX
	if (!bShaderCompleted)
	{
		int i32InfoLogLength, i32CharsWritten; //87
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		char* pszInfoLog; //90
		glGetShaderInfoLog(vertexShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		Format message("Failed to compile vertex shader: {0}\n\n{1}", filename, pszInfoLog); //94
		throwError(GraphicsException(message));
	}
	return vertexShader;
}

unsigned int GL_Shader_Platform::compilePixelShader(const std::vector<char>& pixelShaderData, const std::string& filename) //100-137
{
	unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER); //103
	assert(glGetError() == GL_NO_ERROR); //97 ABC 1.0.0 OSX

	const char* data = pixelShaderData.data(); //107

	int length = pixelShaderData.size(); //109

	glShaderSource(pixelShader, 1, &data, &length);
	assert(glGetError() == GL_NO_ERROR); //104 ABC 1.0.0 OSX

	glCompileShader(pixelShader);
	assert(glGetError() == GL_NO_ERROR); //108 ABC 1.0.0 OSX

	GLint bShaderCompleted = 0; //118

	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &bShaderCompleted);
	assert(glGetError() == GL_NO_ERROR); //113 ABC 1.0.0 OSX

	if (bShaderCompleted == GL_FALSE)
	{
		int i32InfoLogLength, i32CharsWritten; //125
		glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

		char* pszInfoLog; //129
		glGetShaderInfoLog(pixelShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		Format message("Failed to compile fragment shader: {0}\n\n{1}", filename, pszInfoLog); //131

		throwError(GraphicsException(message)); //133
	}
	return pixelShader;
}

void GL_Shader_Platform::createShaderProgram(unsigned int vertexShader, unsigned int pixelShader) //139
{
	GLuint programObject = glCreateProgram(); //142
	assert(glGetError() == GL_NO_ERROR); //136 ABC 1.0.0 OSX

	glAttachShader(programObject, pixelShader);
	assert(glGetError() == GL_NO_ERROR); //140 ABC 1.0.0 OSX

	glAttachShader(programObject, vertexShader);
	assert(glGetError() == GL_NO_ERROR); //143 ABC 1.0.0 OSX

	GLint bLinked; //157
	glLinkProgram(programObject);
	assert(glGetError() == GL_NO_ERROR); //147 ABC 1.0.0 OSX

	glGetProgramiv(programObject, GL_LINK_STATUS, &bLinked);
	assert(glGetError() == GL_NO_ERROR); //152 ABC 1.0.0 OSX

	if (!bLinked)
	{
		int i32InfoLogLength, i32CharsWritten; //163
		glGetProgramiv(pixelShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog; //165

		glGetShaderInfoLog(pixelShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		Format message("Failed to link shader!\n\n{0}", pszInfoLog); //167

		throwError(GraphicsException(message)); //169
	}

	GLint valid; //174
	glValidateProgram(programObject);
	glGetProgramiv(programObject, GL_VALIDATE_STATUS, &valid);
	assert(valid == GL_TRUE); //169 ABC 1.0.0 OSX

	memset(m_attribIndex, 255, sizeof(m_attribIndex));
	for (int i = 0; i < VertexFormat::DT_SIZE; i++) //178
	{
		VertexFormat::DataType dt = VertexFormat::DataType(i); //211
		m_attribIndex[i] = glGetAttribLocation(programObject, VertexFormat::toString(dt));
	}

	int activeUniformCount; //217
	glGetProgramiv(programObject, GL_ACTIVE_UNIFORMS, &activeUniformCount);
	for (int i = 0; i < activeUniformCount; i++) //219
	{
		int size; //221
		unsigned int type; //222
		int length; //223
		char name[32]; //224

		char* end; //237

		glGetActiveUniform(programObject, i, sizeof(name), &length, &length, 0, name);
		assert(length); //220 ABC 1.0.0 OSX
		assert(glGetError() == GL_NO_ERROR); //221 ABC 1.0.0 OSX
		glGetUniformLocation(programObject, strchr(end, '['));
		//m_uniforms.push_back(m_uniforms[i]);//?
	}
	m_programObject = programObject;
}

void GL_Shader_Platform::setVertexShader(unsigned int vertexShader) //250
{
	m_vertexShader = vertexShader;
}

void GL_Shader_Platform::setPixelShader(unsigned int pixelShader) //256
{
	m_pixelShader = pixelShader;
}

void GL_Shader_Platform::setProgramObject(unsigned int programObject)
{
	m_programObject = programObject;
}

void GL_Shader_Platform::begin()
{
	sm_currentPlatformShader = this;
}

void GL_Shader_Platform::end()
{
	sm_currentPlatformShader = 0;
}

void GL_Shader_Platform::setFloat(Shader::ParamType param, float value)
{
	setFloat(param, value);
}

void GL_Shader_Platform::setFloat(const char* name, float value) //303
{
	int handle = getHandle(name); //305
	setFloat(handle, value);
}

void GL_Shader_Platform::setFloat(int handle, float value) //309
{
	if (handle == -1)
		return;

	m_floats[handle] = value;
	glUniform1f(handle, value);
	assert(glGetError() == GL_NO_ERROR); //309 ABC 1.0.0 OSX
}

void GL_Shader_Platform::setVector(Shader::ParamType param, const float4& value)
{
	setVector(Shader::toString(param), value);
}

void GL_Shader_Platform::setVector(const char* name, const float4& value) //331
{
	int handle = getHandle(name); //333
	setVector(handle, value);
}

void GL_Shader_Platform::setVector(int handle, const float4& value) //337
{
	if (handle == -1)
		return;

	m_vectors[handle] = value;
	glUniform4f(handle, value.x, value.y, value.z, value.w);
	assert(glGetError() == GL_NO_ERROR); //337 ABC 1.0.0 OSX
}

void GL_Shader_Platform::setMatrix(Shader::ParamType param, const float4x4& value)
{
	setMatrix(Shader::toString(param), value);
}

void GL_Shader_Platform::setMatrix(const char* name, const float4x4& value) //359
{
	int handle = getHandle(name); //361
	setMatrix(handle, value);
}

void GL_Shader_Platform::setMatrix(int handle, const float4x4& value) //365
{
	if (handle == -1)
		return;
	float4x4 transposed = value.transpose(); //375

	glUniformMatrix4fv(handle, 1, 0, (GLfloat*)&transposed); //?
	assert(glGetError() == GL_NO_ERROR); //367 ABC 1.0.0 OSX
}

void GL_Shader_Platform::setMatrixArray(Shader::ParamType param, float4x4* value, int count)
{
	setMatrixArray(Shader::toString(param), value, count);
}

void GL_Shader_Platform::setMatrixArray(const char* name, float4x4* values, int count) //389
{
	int handle = getHandle(name); //391
	setMatrixArray(handle, values, count);
}

void GL_Shader_Platform::setMatrixArray(int handle, float4x4* values, int count) //395
{
	if (handle == -1)
		return;

	glUniformMatrix4fv(handle, count, false, (GLfloat*)&values); //?
	assert(glGetError() == GL_NO_ERROR); //381 ABC 1.0.0 OSX
}

void GL_Shader_Platform::setTexture(Shader::ParamType param, GL_Texture* tex, int texturingUnit) //Backported from ABFM
{
	setTexture(Shader::toString(param), tex, texturingUnit); //TODO
}

void GL_Shader_Platform::setTexture(const char* name, GL_Texture* tex, int texturingUnit) //412
{
	int handle = getHandle(name); //414
	setTexture(handle, tex, texturingUnit);
}

void GL_Shader_Platform::setTexture(int handle, GL_Texture* tex, int texturingUnit) //418
{
	if (handle == -1)
		return;

	GL_State::activeTexture(tex->tex()); //423
	GL_State::bindTexture(GL_TEXTURE_2D, tex->tex()); //424
	glUniform1i(handle, texturingUnit);
}

float GL_Shader_Platform::getFloat(int handle)
{
	float value = 0.0f;
	if (handle != 0)
		glGetUniformfv(m_programObject, handle, &value);
	return value;
}

float GL_Shader_Platform::getFloat(const char* name)
{
	int handle = getHandle(name);
	return getFloat(handle);
}

float4 GL_Shader_Platform::getVector(int handle)
{
	float4 value(0, 0, 0, 0);
	if (handle != 0)
		glGetUniformfv(m_programObject, handle, (GLfloat*)&value); //?
	return value;
}

float4 GL_Shader_Platform::getVector(const char* name)
{
	int handle = getHandle(name);
	return getVector(handle);
}

float4x4 GL_Shader_Platform::getMatrix(int handle)
{
	float4x4 value( 0.f );
	if (handle != 0)
		glGetUniformfv(m_programObject, handle, (GLfloat*)&value); //?
	return value.transpose();
}

float4x4 GL_Shader_Platform::getMatrix(const char* name)
{
	int handle = getHandle(name);
	return getMatrix(handle);
}

BaseTexture* GL_Shader_Platform::getTexture(int handle)
{
	return 0; //Unimplemented.
}

BaseTexture* GL_Shader_Platform::getTexture(const char* name)
{
	return 0; //Unimplemented.
}

unsigned int GL_Shader_Platform::getProgramObject() const
{
	return m_programObject;
}

int GL_Shader_Platform::getHandle(const char* name) //484
{
	int size = m_uniforms.size(); //486

	for (int i = 0; i < size; i++) //488
	{
		if (m_uniforms[i].second == name)
			return m_uniforms[i].first;
	}

	return 0;
}

int GL_Shader_Platform::getHandle(Shader::ParamType param)
{
	return getHandle(Shader::toString(param));
}

}
}