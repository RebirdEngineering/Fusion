#include <gr/dx11/DX11_common.h>
#include <gr/dx11/DX11_Shader.h>
#include <gr/dx11/DX11_Context.h>
#include <gr/GraphicsException.h>
#include <io/BundleInputStream.h>
#include <lang/Log.h>

using namespace io;
using namespace lang;
using namespace math;

namespace gr
{
	DX11_Shader::DX11_Shader(DX11_Context* context, const std::string& name, const std::string& fxfilename, int flags) : //1000C3D0 | TODO
		m_currentTechnique(0),
		m_currentPass(0),
		m_enabled(false),
		m_priority(false),
		m_name(name),
		m_sort(SORT_NONE),
		unk3C(0),
		unk40(0),
		m_context(context)
	{
		//BundleInputStream bis(name);
		//int size = bis.available();

		//std::vector<char> content;
		//void* data = 0;
		//int unk = 0;
		//int unk2 = 0; //?
		//content.resize(size);
		//bis.read(content, bis.available());

		//ShaderInclude incl;
		//incl.name04 = name;

		//ID3DBlob* blob;
		//ID3DBlob* error;

		//D3DCompile(content.data(), size, name.c_str(), 0, &incl, 0, "fx_5_0", 0, 0, &blob, &error);

		//throw GraphicsException(Format("FX file {0} could not be compiled.\n\n{1}", error)); //error msg
		//throw GraphicsException(Format("FX file {0} could not be located.", incl.name04));
		//int srcDataSize = D3DCompile()

		//if (FAILED(D3DX11CreateEffectFromMemory(blob->GetBufferPointer(), blob->GetBufferSize(), 0, context->device(), &unk3C) || !unk3C->IsValid())
			//throw GraphicsException(Format("D3DX11CreateEffectFromMemory failed for file: {0}", incl.name04));

		m_currentTechnique = 0;
		m_enabled = false;
		setTechnique("Default");
	}

	DX11_Shader::~DX11_Shader() //1000C0A0
	{
		if (unk3C)
			unk3C->Release();
	}

	Shader* DX11_Shader::clone() const //1000C770
	{
		return new DX11_Shader(*this);
	}

	void DX11_Shader::setTechnique(const char* name) //1000BD10 | Correct?
	{
		m_currentTechnique = 0;

		if (name != 0)
		{
			ID3DX11EffectTechnique* tech = unk3C->GetTechniqueByName(name);
			unk40 = tech;

			if (tech && tech->IsValid())
			{
				D3DX11_TECHNIQUE_DESC desc;
				unk40->GetDesc(&desc);
				m_enabled = true;
			}
		}

		else
		{
			m_enabled = false;
			setTechnique("Default");
		}
	}

	bool DX11_Shader::hasTechnique(const char* name) //1000BD90 | Correct?
	{
		ID3DX11EffectTechnique* tech = unk3C->GetTechniqueByName(name);
		return tech && tech->IsValid();
	}
	
	void DX11_Shader::setTexture(const char* name, BaseTexture* value) //1000BDE0 | TODO
	{
		//ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		//ID3DX11EffectShaderResourceVariable* shaderRes = var->AsShaderResource();
		//
		//if (shaderRes->IsValid())
		//{
		//	DX11_Texture* v = static_cast<DX11_Texture*>(value);
		//	shaderRes->SetResource(v->);
		//}
	}

	void DX11_Shader::setTexture(ParamType param, BaseTexture* value) //1000BB70
	{
		const char* paramName = Shader::toString(param);
		setTexture(paramName, value);
	}

	void DX11_Shader::setMatrix(const char* name, const float4x4& value) //1000C7E0 | Correct?
	{
		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectMatrixVariable* mtxVar = var->AsMatrix();

		if (mtxVar->IsValid())
			mtxVar->SetMatrix((float*)&value); //?
		else
			LANG_LOG("DX11", LANG_LOG_PRIORITY_ERROR, "MATRIX %s IS NOT VALID", name); //198
	}

	void DX11_Shader::setMatrix(ParamType param, const float4x4& value) //1000BBA0
	{
		if (SORT_NONE != m_sort)
		{
			if (PARAM_CAMERAP == param)
				m_context->worldtm = value;
		}

		const char* paramName = toString(param);
		setMatrix(paramName, value);
	}
	
	void DX11_Shader::setMatrixArray(ParamType param, float4x4** values, int count) //1000CC30 | Correct?
	{
		if (SORT_NONE != m_sort && PARAM_BONEWORLDTM == param)
		{
			if (SORT_INSIDEOUT != m_sort)
			{
				m_context->boneworldtm.resize(count);
				for (int i = 0; i < m_context->boneworldtm.size(); ++i)
					m_context->boneworldtm[i] = *values[i];
			}
		}

		ID3DX11EffectVariable* var = unk3C->GetVariableByName(toString(param));
		ID3DX11EffectMatrixVariable* elem = var->AsMatrix();

		if (elem->IsValid())
			elem->SetMatrixArray((float*)&values, 0, count);
	}

	void DX11_Shader::setVector(const char* name, const float4& value) //1000BE20 | Correct?
	{
		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectVectorVariable* elem = var->AsVector();

		if (elem->IsValid())
			elem->SetFloatVector((float*)&value);
	}

	void DX11_Shader::setVector(ParamType param, const float4& value) //1000BBF0
	{
		if (SORT_NONE != m_sort)
		{
			if (PARAM_CAMERAP == param)
				m_context->camerapos = value;
		}

		const char* paramName = toString(param);
		setVector(paramName, value);
	}
	
	void DX11_Shader::setFloat(const char* name, float value) //1000BE80 | Correct?
	{
		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectScalarVariable* elem = var->AsScalar();

		if (elem->IsValid())
			elem->SetFloat(value);
	}

	void DX11_Shader::setFloat(ParamType param, float value) //1000BC40
	{
		const char* paramName = Shader::toString(param);
		setFloat(paramName, value);
	}

	BaseTexture* DX11_Shader::getTexture(const char* name) //1000C140 | TODO
	{
		BaseTexture* foundtex = 0;
		//
		return foundtex;
	}

	float4x4 DX11_Shader::getMatrix(const char* name) //1000BEC0 | Correct?
	{
		float4x4 value(1.f);

		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectMatrixVariable* mtx = var->AsMatrix();

		if (mtx->IsValid())
			mtx->GetMatrix((float*)&value);

		return value;
	}

	float4 DX11_Shader::getVector(const char* name) //1000BF10 | Correct?
	{
		float4 value(0, 0, 0, 0);

		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectVariable* elem = var->AsVector();

		if (elem->IsValid())
			elem->AsVector()->GetFloatVector((float*)&value);

		return value;
	}

	float DX11_Shader::getFloat(const char* name) //1000BF60 | Correct?
	{
		float value(0.f);
		ID3DX11EffectVariable* var = unk3C->GetVariableByName(name);
		ID3DX11EffectScalarVariable* scalar = var->AsScalar();

		if (scalar->IsValid())
			return scalar->GetFloat(&value);

		return value;
	}

	int DX11_Shader::begin() //1000BFB0
	{
		if (!m_enabled)
			return 0;
		
		m_context->getBatcher().flush();
		
		return m_currentTechnique;
	}

	void DX11_Shader::beginPass(int pass) //1000BC70 | Correct?
	{
		m_currentPass = pass;

		ID3DX11EffectPass* effectPass = unk40->GetPassByIndex(pass);
		ID3D11DeviceContext* deviceContext = m_context->deviceContext();
		
		effectPass->Apply(0, deviceContext);
	}

	void DX11_Shader::endPass() //1000BCB0
	{
		m_currentPass = 0;
	}
}