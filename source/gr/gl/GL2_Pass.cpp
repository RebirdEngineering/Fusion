#include <gr/gl/GL2_Pass.h>
#include <gr/gl/GL2_Shader_Platform.h>

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE)

GL_Pass::GL_Pass(const std::string& name) : //12-16
	m_name(name),
	m_platformShader(0)
{
	m_platformShader = new GL_Shader_Platform(); //15
}

GL_Pass::GL_Pass(const GL_Pass& other) //18
{
	*this = other;
}

GL_Pass::~GL_Pass() //23
{
}

GL_Pass* GL_Pass::clone() const
{
	return new GL_Pass(m_name);
}

void GL_Pass::addProperty(const std::string& key, const std::string& value) //35
{
	m_state.parse(key, value);
}

GL_Shader_Platform* GL_Pass::getPlatformShader()
{
	return m_platformShader;
}

GL_State& GL_Pass::getState()
{
	return m_state;
}

void GL_Pass::begin()
{
	m_platformShader->begin(); //m_state.begin(); underneath?
}

void GL_Pass::end()
{
	m_platformShader->end(); //49
}

}
}