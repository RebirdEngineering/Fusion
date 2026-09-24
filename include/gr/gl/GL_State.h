#ifndef _GR_GL_STATE_H
#define _GR_GL_STATE_H

#include "GL_common.h"
#include <gr/Rect.h>

namespace gr
{
namespace GL_NAMESPACE //I'm just as confused as you are
{
class GL_State
{
public:
	GL_State()/* : //According to the header all this stuff is here?
		m_culling(true),
		m_cullFace(GL_BACK),
		m_depthTest(true),
		m_depthMask(true),
		m_depthFunc(GL_LESS),
		m_blending(false),
		m_blendEquation(GL_FUNC_ADD),
		m_blendFuncSrc(GL_LINES),
		m_blendFuncDst(GL_FALSE), //0
		m_programObject(GL_FALSE), //0
		m_viewport(-10000, -10000, 10000, 10000),
		m_scissor(-10000, -10000, 10000, 10000),
		m_clientActiveTexture(GL_TEXTURE0),
		m_activeTexture(GL_TEXTURE0),
		m_frontFace(GL_CCW),
		m_clientStateVertexArray(false),
		m_clientStateNormalArray(false),
		m_clientStateColorArray(false)*/
	{
		//m_matrices[012];
	}
	void begin(bool force = false)
	{
		cullFace(m_cullFace, force);
		depthMask(m_depthMask, force);
		depthFunc(m_depthFunc, force);
		blendFunc(m_blendFuncSrc, m_blendFuncDst, force);
		useProgram(m_programObject, force);
		blendEquation(m_blendEquation, force);
	}

	static void end();

	static void reset()
	{
		sm_current.m_programObject = 0;
		sm_current.m_blending = false;
		sm_current.m_blendFuncSrc = 0;
		sm_current.m_culling = false;
		sm_current.m_depthTest = false;
	}
	static void enable(unsigned int cap) { glEnable(cap); }
	static void disable(unsigned int cap) { glDisable(cap); }
	static void bindBuffer(unsigned int target, unsigned int buffer)
	{
		if (sm_current.m_arrayBuffer != buffer)
		{
			sm_current.m_arrayBuffer = buffer;
			glBindBuffer(target, buffer);
		}
	}
	static void activeTexture(unsigned int texture, bool force = false)
	{
		if (sm_current.m_activeTexture + GL_TEXTURE0 != texture || force)
		{
			sm_current.m_activeTexture = texture + GL_TEXTURE0;
			glActiveTexture(texture);
		}
	}
	static void bindTexture(unsigned int target, unsigned int texture, bool force = false)
	{
		if (sm_current.m_bindedTexture[target] != texture || force)
		{
			sm_current.m_bindedTexture[target] = texture;
			glBindTexture(target, texture);
		}
	}
	static void blendFunc(unsigned int blendFuncSrc, unsigned int blendFuncDst, bool force = false)
	{
		if (sm_current.m_blendFuncSrc != blendFuncSrc || force)
		{
			sm_current.m_blendFuncSrc = blendFuncSrc;
			glBlendFunc(blendFuncSrc, blendFuncDst); //?
		}
	}
	static void depthFunc(unsigned int depthFunc, bool force = false)
	{
		if (sm_current.m_depthFunc != depthFunc || force)
		{
			sm_current.m_depthFunc = depthFunc;
			glDepthFunc(depthFunc);
		}
	}
	static void depthMask(bool depthMask = false, bool force = false)
	{
		if (sm_current.m_depthMask != depthMask || force)
		{
			sm_current.m_depthMask = depthMask;
			glDepthMask(depthMask);
		}
	}
	static void frontFace(unsigned int mode)
	{
		if (sm_current.m_frontFace != mode)
		{
			sm_current.m_frontFace = mode;
			glFrontFace(mode);
			assert(glGetError() == GL_NO_ERROR);
		}
	}
	static void viewport(int x, int y, int width, int height, bool force = false)
	{
		Rect viewport(x, y, width, height);
		if (sm_current.m_viewport != viewport || force)
		{
			sm_current.m_viewport = viewport;
			glViewport(x, y, width, height);
		}
	}
	static void scissor(int x, int y, int width, int height, bool force = false)
	{
		Rect scissor(x, y, width, height);
		if (sm_current.m_scissor != scissor || force)
		{
			sm_current.m_scissor = scissor;
			glScissor(x, y, width, height);
		}
	}
	static void clearColor(float red, float green, float blue, float alpha, bool force = false)
	{
		if (sm_current.m_red != red || sm_current.m_green != green || sm_current.m_blue != blue || sm_current.m_blue != alpha || force) //?
		{
			sm_current.m_red = red;
			sm_current.m_green = green;
			sm_current.m_blue = blue;
			sm_current.m_alpha = alpha;
			glClearColor(red, green, blue, alpha);
		}
	}
	static void lineWidth(float width, bool force = false)
	{
		if (sm_current.m_lineWidth != width || force)
		{
			sm_current.m_lineWidth = width;
			glLineWidth(width);
		}
	}
	static void cullFace(unsigned int cullFace, bool force = false)
	{
		sm_current.m_culling ? enable(GL_CULL_FACE) : disable(GL_CULL_FACE);
		if (sm_current.m_cullFace != cullFace || force)
		{
			sm_current.m_cullFace = cullFace;
			glCullFace(cullFace);
		}
	}

	static void useProgram(unsigned int program, bool force = false)
	{
		if (sm_current.m_programObject != program || force)
		{
			sm_current.m_programObject = program;
			glUseProgram(program);
		}
	}
	static void blendEquation(unsigned int blendEquation, bool force = false)
	{
		if (sm_current.m_blendEquation != blendEquation || force)
		{
			sm_current.m_blendEquation -= blendEquation;
			glBlendEquation(blendEquation); //?
		}
	}

	void parse(const std::string& key, const std::string& value);

	void setMatrixMode(unsigned int mode)
	{
		/*if (sm_current.m_matrixMode != mode)
		{
			sm_current.m_matrixMode - mode;
			glMatrixMode(mode); //?
		}*/
	}

	const float IDENTITY[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 }; //84

	bool m_culling; //86
	unsigned int m_cullFace; //87

	bool m_depthTest; //89
	bool m_depthMask; //90
	unsigned int m_depthFunc; //91

	bool m_blending; //93
	unsigned int m_blendEquation; //94
	unsigned int m_blendFuncSrc; //95
	unsigned int m_blendFuncDst; //96

	unsigned int m_programObject; //98
	std::map<unsigned int, bool> m_caps; //99
	float m_matrices[10][16]; //100
	Rect m_viewport; //101
	Rect m_scissor; //102
	unsigned int m_clientActiveTexture; //103
	unsigned int m_activeTexture; //104
	unsigned int m_bindedTexture[8]; //105
	unsigned int m_frontFace; //106

	bool m_clientStateVertexArray; //108
	bool m_clientStateNormalArray; //109
	bool m_clientStateColorArray; //110

	bool m_clientStateTextureCoordArray[8]; //120
	unsigned int m_arrayBuffer; //121
	unsigned int m_elementArrayBuffer; //122
	float m_red; //123
	float m_green; //124
	float m_blue; //125
	float m_alpha; //126
	float m_lineWidth; //127

	static GL_State sm_current; //132

	//Not in DWARF?
	GL_State(const GL_State&);
	GL_State& operator=(const GL_State&);
};

}
}

#endif