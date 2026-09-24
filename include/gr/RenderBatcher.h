#ifndef _GR_RENDERBATCHER_H
#define _GR_RENDERBATCHER_H

#include <lang/Object.h>
#include <gr/Image.h>
#include <gr/RenderState2D.h>

namespace math
{
	class float2;
	class float3;
	class float4;
}

namespace gr
{
	class Context;
	//class Image;
	class Shader;

class RenderBatcher :
	public lang::Object
{
public:
	enum Type
	{
		TYPE_LINE,
		TYPE_PLAIN,
		TYPE_TEX,
	};
	RenderBatcher(Context* context);

	void render(Type type, Shader* shader, const math::float3* vertpos, const math::float2* uv, const math::float4* colors, Image* image);
	void flush();
	void enableFlushing(bool enable);
	void reset();
	Image* getImage();
private:
	RenderState2D m_state;
	Type m_type;
	Context* m_context;
	P(Image) m_image;
	P(Shader) m_shader;
	std::vector<math::float3> m_verts;
	std::vector<math::float2> m_uvs;
	std::vector<math::float4> m_colors;
	bool m_flushEnabled;
	void add(Type type, Shader* shader, const math::float3* vertpos, const math::float2* uv, const math::float4* colors, Image* image);
	bool isBatchable(Type type, Shader* shader, Image* image, const RenderState2D& state, const math::float4* colors);
};

}

#endif