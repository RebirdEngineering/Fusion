#include <gr/dx11/DX11_common.h>
#include <gr/dx11/DX11_Shader.h>
#include <gr/dx11/DX11_Context.h>
#include <lang/Log.h>

using namespace lang;
using namespace math;

namespace gr
{
	DX11_Shader::DX11_Shader(DX11_Context* context, const std::string& name, const std::string& fxfilename, int flags) : //1000C3D0
		//m_currentTechnique(0),
		//m_currentPass(0),
		m_enabled(false),
		m_priority(false),
		m_name(name),
		m_sort(SORT_NONE),
		m_context(context)
	{
		//BundleInputStream
		//D3DX11CreateEffectFromMemory()
	}

	DX11_Shader::~DX11_Shader()
	{
		
	}

	Shader* DX11_Shader::clone() const //1000C770
	{
		return new DX11_Shader(*this);
	}

	void DX11_Shader::setTechnique(const char* name) //1000BD10
	{
		
		//if (name != 0)
		//{
		//	for (size_t i = 0; i < m_techniques.size(); i++) //129
		//	{
		//		if (m_techniques[i]->getName() != name) //131
		//		{
		//			// technique not supported, disable shader and return
		//			m_currentTechnique = i;
		//			m_enabled = false;
		//			return;
		//		}
		//		setTechnique("Default");
		//	}
		//}
		//m_currentTechnique = -1;
		//m_enabled = true;
	}

	//1000BD90?
	
	//1000BDE0?

	void DX11_Shader::setTexture(ParamType param, BaseTexture* value) //1000BB70
	{
		const char* paramName = Shader::toString(param);
		setTexture(paramName, value);
	}

	void DX11_Shader::setMatrix(const char* name, const float4x4& value) //1000C7E0
	{
		//if (?)
		//{
		//}
		LANG_LOG("DX11", LANG_LOG_PRIORITY_ERROR, "MATRIX %s IS NOT VALID", name); //198
	}

	void DX11_Shader::setMatrix(ParamType param, const float4x4& value) //1000BBF0
	{
		//if (SORT_NONE != m_sort)
		//{
		//	if (PARAM_CAMERAP == param)
		//		m_context->worldtm = value;
		//}

		const char* paramName = Shader::toString(param);
		setMatrix(paramName, value);
	}

	//1000CC30?
	
	//1000BE20?

	void DX11_Shader::setVector(ParamType param, const float4& value) //1000BBF0
	{
		//if (SORT_NONE != m_sort)
		//{
		//	if (PARAM_CAMERAP == param)
		//		m_context->camerapos = value;
		//}

		const char* paramName = Shader::toString(param);
		setVector(paramName, value);
	}
	
	//1000BE80?

	void DX11_Shader::setFloat(ParamType param, float value) //1000BC40
	{
		const char* paramName = Shader::toString(param);
		setFloat(paramName, value);
	}

	BaseTexture* DX11_Shader::getTexture(const char* name) //1000C140 | TODO
	{
		return 0;
	}

	float4x4 DX11_Shader::getMatrix(const char* name) //1000BEC0 | TODO
	{
		return float4x4();
	}

	float4 DX11_Shader::getVector(const char* name) //1000BF10 | TODO
	{
		return float4();
	}

	float DX11_Shader::getFloat(const char* name) //1000BF60 | TODO
	{
		return 0.0;
	}

	int DX11_Shader::begin() //1000BFB0
	{
		return 0;
		//if (!m_enabled)
		//	return 0;
		//
		//m_context->getBatcher().flush();
		//
		//return m_currentTechnique;
	}

	void DX11_Shader::beginPass(int pass) //1000BC70
	{
		//m_currentPass = pass;
	}

	void DX11_Shader::endPass() //1000BCB0
	{
		//m_currentPass = 0;
	}
}