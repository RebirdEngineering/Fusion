#include <gr/RenderBatcher.h>
#include <gr/Context.h>

USING_NAMESPACE(math)

BEGIN_NAMESPACE(gr)

RenderBatcher::RenderBatcher(Context* context)
{
	m_type = TYPE_TEX;
	m_context = context;
	m_flushEnabled = true;
}

void RenderBatcher::reset()
{
	m_flushEnabled = false;
	m_verts.clear();
	m_uvs.clear();
	m_colors.clear();
	m_image = 0;
	m_shader = 0;
	m_flushEnabled = true;
}

bool RenderBatcher::isBatchable(Type type, Shader* shader, Image* image, const RenderState2D& state, const NS(math, float4)* colors)
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

void RenderBatcher::enableFlushing(bool enable)
{
	m_flushEnabled = enable;
}

Image* RenderBatcher::getImage()
{
	return m_image;
}

void RenderBatcher::render(Type type, Shader* shader, const float3* vertpos, const float2* uv, const float4* colors, Image* image)
{
	if (type == TYPE_TEX)
		m_context->statistics.renderedImages++;
	if (isBatchable(type, shader, image, m_state, colors))
		flush();
	add(type, shader, vertpos, uv, colors, image);
}

void RenderBatcher::add(Type type, Shader* shader, const float3* vertpos, const float2* uv, const float4* colors, Image* image)
{
	/*if (!m_verts.empty())
	{
		m_type = type;
		m_shader = shader;
		m_image = image;
		int size = m_verts.size();
		memcpy(&m_state, &m_context->getRenderDevice2D(), sizeof(m_state));
		while (m_uvs.begin() != m_uvs.end())
		{
			int size = m_uvs.size();
			m_uvs.resize(size);
			while (m_colors.begin() != m_colors.end())
			{
				int size = m_colors.size();
				m_colors.resize(size);
			}
		}
		
	}*/
}

}