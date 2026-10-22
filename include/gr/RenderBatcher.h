#ifndef _GR_RENDERBATCHER_H
#define _GR_RENDERBATCHER_H

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

class RenderBatcher : //15
	public lang::Object
{
public:
	enum Type { TYPE_LINE, TYPE_PLAIN, TYPE_TEX, }; //19

	RenderBatcher(Context* context); //23

	void render(Type type, Shader* shader, const math::float3* vertpos, const math::float2* uv, const math::float4* colors, Image* image); //25
	void flush(); //26
	void enableFlushing(bool enable); //27
	void reset(); //28
	Image* getImage(); //29

private:
	RenderState2D m_state; //32
	Type m_type; //33
	Context* m_context; //34
	P(Image) m_image; //35
	P(Shader) m_shader; //36
	std::vector<math::float3> m_verts; //37
	std::vector<math::float2> m_uvs; //38
	std::vector<math::float4> m_colors; //39
	bool m_flushEnabled; //40

	void add(Type type, Shader* shader, const math::float3* vertpos, const math::float2* uv, const math::float4* colors, Image* image); //42
	bool isBatchable(Type type, Shader* shader, Image* image, const RenderState2D& state, const math::float4* colors); //43
};

}

#endif