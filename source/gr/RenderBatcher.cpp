#include <gr/RenderBatcher.h>
#include <gr/Texture.h>
#include <gr/Context.h>

USING_NAMESPACE(math)

BEGIN_NAMESPACE(gr)

RenderBatcher::RenderBatcher(Context* context) //10
{
	m_type = TYPE_TEX;
	m_context = context;
	m_flushEnabled = true;
}

void RenderBatcher::enableFlushing(bool enable) //19
{
	m_flushEnabled = enable;
}

Image* RenderBatcher::getImage()
{
	return m_image; //26
}

void RenderBatcher::render(Type type, Shader* shader, const float3* vertpos, const float2* uv, const float4* colors, Image* image) //29
{
	if (type == TYPE_TEX)
		m_context->statistics.renderedImages++;

	if (isBatchable(type, shader, image, m_state, colors)) //34
		flush();

	add(type, shader, vertpos, uv, colors, image);
}

void RenderBatcher::add(Type type, Shader* shader, const float3* vertpos, const float2* uv, const float4* colors, Image* image) //40 | Correct?
{
	if (!m_verts.empty()) //42
	{
		m_type = type; //44
		m_shader = shader; //45
		m_image = image; //46
		memcpy(&m_state, &m_context->getRenderState2D(), sizeof(m_state)); //47
	}

	if (type == TYPE_LINE)
	{
		int size = m_verts.size(); //52 | Correct
		m_verts.resize(size); //53
		m_verts[0] = vertpos[0]; //54
		m_verts[1] = vertpos[1]; //55

		if (uv)
		{
			int size = m_uvs.size(); //59 | Correct
			m_uvs.resize(size); //60
			m_uvs[0] = uv[0]; //61
			m_uvs[1] = uv[1]; //62
		}

		if (colors)
		{
			int size = m_colors.size(); //68
			m_colors.resize(size); //69
			m_colors[0] = colors[0]; //70
			m_colors[1] = colors[1]; //71
		}
	}
	else
	{
		int size = m_verts.size(); //76 | Correct
		m_verts.resize(size); //77
		m_verts[0] = vertpos[0]; //78
		m_verts[1] = vertpos[1]; //79
		m_verts[2] = vertpos[2]; //80
		m_verts[3] = vertpos[3]; //81
		m_verts[4] = vertpos[4]; //82
		m_verts[5] = vertpos[5]; //83

		if (uv)
		{
			int size = m_uvs.size(); //87 | Correct
			m_uvs.resize(size); //88
			m_uvs[0] = uv[0]; //89
			m_uvs[1] = uv[1]; //90
			m_uvs[2] = uv[2]; //91
			m_uvs[3] = uv[3]; //92
			m_uvs[4] = uv[4]; //93
			m_uvs[5] = uv[5]; //94

			if (colors)
			{
				int size = m_colors.size(); //99
				m_colors.resize(size); //100
				m_colors[0] = colors[0]; //101
				m_colors[1] = colors[1]; //102
				m_colors[2] = colors[2]; //103
				m_colors[3] = colors[3]; //104
				m_colors[4] = colors[4]; //106
				m_colors[5] = colors[5]; //106
			}
		}
	}
}

void RenderBatcher::flush()
{
	if (m_flushEnabled && (m_image || m_shader)) //114
	{
		if (m_type == TYPE_TEX)
			m_context->statistics.renderedImageFlushes++; //118

		enableFlushing(false); //120

		VertexFormat vf; //122
		vf.addPosition(VertexFormat::DF_V3_32); //123
		if (!m_uvs.empty()) vf.addTextureCoordinate(VertexFormat::DF_V2_32); //124
		if (!m_colors.empty()) //125
		{
			vf.addDiffuse(m_context->platform() == Context::PLATFORM_DX11 || Context::PLATFORM_XNA ? VertexFormat::DF_V4_32 : VertexFormat::DF_V4_8);
		}

		Primitive* prim = m_context->getDynamicPrimitive(m_type == RenderBatcher::TYPE_LINE ? Primitive::PRIM_LINE : Primitive::PRIM_TRI, vf, m_verts.size(), 0); //132

		ContextObject::Lock(prim, ContextObject::LOCK_WRITE); //137
		prim->setVertexData(VertexFormat::DT_POSITION, 0, &m_verts, VertexFormat::DF_V3_32, m_verts.size()); //138
		if (!m_uvs.empty()) //139
			prim->setVertexData(VertexFormat::DT_TEX0, 0, &m_verts, VertexFormat::DF_V2_32, m_uvs.size()); //140
		if (!m_colors.empty()) //141
			prim->setVertexData(VertexFormat::DT_DIFFUSE, 0, &m_verts, VertexFormat::DF_V4_32, m_colors.size()); //142

		prim->setVertexRangeBegin(0); //144
		prim->setVertexRangeEnd(m_verts.size()); //145

		m_context->setClipRect(m_state.getClip()); //150

		m_shader->setFloat("ALPHA_FACTOR", m_state.getAlpha()); //153
		m_shader->setFloat("COLOR_SATURATION", m_state.getSaturation()); //154
		if (m_image) //155
			m_shader->setTexture("BASEMAP", m_image->getTexture()); //156
		prim->setShader(m_shader); //157

		Shader::Begin use(m_shader); //162

		float4x4 worldtm = m_state.getWorldTransform(); //164
		float4x4 viewtm = m_context->viewTransform(); //165
		float4x4 projtm = m_context->projectionTransform(); //166
		float4x4 totaltm = (projtm * viewtm) * viewtm; //167 (Correct?)

		m_shader->setMatrix(Shader::PARAM_WORLDTM, worldtm); //169
		m_shader->setMatrix(Shader::PARAM_VIEWTM, viewtm); //170
		m_shader->setMatrix(Shader::PARAM_PROJTM, projtm); //171
		m_shader->setMatrix(Shader::PARAM_TOTALTM, totaltm); //172

		for (int i = 0; i < use.passes(); i++) //174
		{
			Shader::Pass pass(m_shader, i); //176
			prim->render(); //177
		}

		reset(); //182

		enableFlushing(true); //184
	}
}

bool RenderBatcher::isBatchable(Type type, Shader* shader, Image* image, const RenderState2D& state, const float4* colors) //187
{
	if (m_verts.begin() != m_verts.end())
	{
		if (m_image != image || m_shader != shader || m_type != type || m_state.m_clip != state.m_clip || m_state.m_alpha != state.getAlpha())
			return true;
		if (colors)
			return true;
	}
	return false;
}

void RenderBatcher::reset()
{
	enableFlushing(false); //222
	m_verts.clear(); //223
	m_uvs.clear(); //224
	m_colors.clear(); //225
	m_image = 0; //226
	m_shader = 0; //227
	enableFlushing(true); //228
}

}