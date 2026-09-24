#include <gr/gl/GL_common.h>
#include <gr/gl/GL_Primitive.h>
#include <gr/gl/GL_State.h>
#include <gr/gl/GL2_Shader.h>
#include <gr/gl/GL_Context.h>
#include <gr/gl/GL2_Shader_Platform.h>

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE)

static bool s_hasVBOsupport = false; //19

GL_Primitive::GL_Primitive(GL_Context* context, PrimType prim, const VertexFormat& vf, int vertices, int indices, Context::UsageFlags usage) : //21-49
	m_context(context),
	m_fx(0),
	m_prim(prim),
	m_lock(LOCK_NONE),
	m_usage(usage),
	m_ibuffer(0)
{
	if (context->isExtensionSupported("GL_ARB_vertex_buffer_object"))
		s_hasVBOsupport = true;
	else
	{
		s_hasVBOsupport = context->isExtensionSupported("GL_OES_vertex_buffer_object");
		if (!s_hasVBOsupport)
			m_usage = Context::USAGE_DYNAMIC;
	}

	for (int i = 0; i < MAX_VBUFFERS; i++) //40
		m_vbuffers[i] = 0;

	VertexFormat validvf = vf; //44
	validvf.setAlignEach(4);
	setFormat(validvf, vertices, indices);
}

GL_Primitive::~GL_Primitive()
{
	deallocate(); //53
}

void GL_Primitive::setShader(Shader* fx) //56
{
	m_fx = static_cast<GL_Shader*>(fx); //58
}

Shader* GL_Primitive::shader() const
{
	return m_fx; //63
}

int GL_Primitive::getGLDataType(VertexFormat::DataType dt) const //66
{
	VertexFormat::DataFormat df = vf().getDataFormat(dt); //68
	int bytes = vf().getDataSize(df) / vf().getDataDim(df); //69
	assert(bytes >= 1 && bytes <= 4 && bytes != 3); //58 ABC 1.0.0 OSX

	switch (bytes)
	{
	case 4: return GL_FLOAT;
	case 2: return GL_SHORT;
	case 1: return GL_BYTE;
	}
	return 0;
}

bool enableClientState(VertexFormat::DataType dt) //127
{
	GL_Shader_Platform* shader = GL_Shader_Platform::sm_currentPlatformShader; //150
	if (shader->m_attribIndex[dt] != -1)
	{
		glEnableVertexAttribArray(shader->m_attribIndex[dt]);
		return true;
	}

	return false;
}

void disableClientState(VertexFormat::DataType dt) //161
{
	GL_Shader_Platform* shader = GL_Shader_Platform::sm_currentPlatformShader; //170

	if (shader->m_attribIndex[dt] == -1)
		glDisableVertexAttribArray(shader->m_attribIndex[dt]);
}

void GL_Primitive::render()
{
	/*
	//shader()-> 221

	int tricount = triangleListSize(); //223
	if (tricount > 0)
	{
		Lock lk(this, LOCK_READWRITE); //226

		switch (shader()->sort()) //228
		{
		case Shader::SORT_OUTSIDEIN:
			sortOutsideIn(m_context->sortbuffer);
			break;

		case Shader::SORT_INSIDEOUT:
			sortInsideOut(m_context->sortbuffer);
			break;

		case Shader::SORT_FRONTTOBACK:
			sortFrontToBack(m_context->camerapos.xyz(), m_context->worldtm, m_context->boneworldtm.data(), m_context->boneworldtm.size(), m_context->sortbuffer);
			break;

		case Shader::SORT_BACKTOFRONT:
			sortBackToFront(m_context->camerapos.xyz(), m_context->worldtm, m_context->boneworldtm.data(), m_context->boneworldtm.size(), m_context->sortbuffer);
			break;
		}
	}

	if (m_usage == Context::USAGE_DYNAMIC)
		GL_State::bindBuffer(GL_ARRAY_BUFFER, 0); //256

	else if (m_interleaved)
		GL_State::bindBuffer(GL_ARRAY_BUFFER, m_vbuffers[0]); //260

	uint8_t* begin = 0; //265
	VertexFormat vf = vertexFormat(); //266
	//VertexFormat::DataType dt = ; //267

	//enableClientState(dt); //269

	int pitch; //271
	uint8_t* data; //272

	GL_State::bindBuffer(GL_ARRAY_BUFFER, m_vbuffers[dt]); //286


	getGLDataType(); //292

	GL_State::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibuffer); //335

	uint16_t* data; //337

	int pitch; //340

	int icount = indexBegin(); //344

	vertexBegin(); //348
	indexBegin(); //349

	GL_State::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //355

	int vcount = vertexBegin(); //357

	VertexFormat::DataType dt; //372

	if (vertexFormat().hasData(dt)) //374
		disableClientState(dt);


	/*
	assert(shader()); //87 ABC 1.0.0 OSX

	if (!GL_Shader_Platform::sm_currentPlatformShader)
		assert(shader); //90 ABC 1.0.0 OSX



	//Shader* shader = m_fx;

	//shader-> //221
	
	//int tricount = triangleListSize(); //223

	Lock lk(this, LOCK_READWRITE); //226

	m_fx->sort();*/

	

	/*
	if (tricount > 0) // don't sort lines, strips or fans
	{
		Lock lk(this, LOCK_READWRITE);
	}

	switch (m_fx->sort())
	{
	case Shader::SORT_OUTSIDEIN:
		sortOutsideIn(m_context->sortbuffer);
		break;

	case Shader::SORT_INSIDEOUT:
		sortInsideOut(m_context->sortbuffer);
		break;

	case Shader::SORT_FRONTTOBACK:
		sortFrontToBack(m_context->camerapos.xyz(), m_context->worldtm, m_context->boneworldtm.begin(), m_context->boneworldtm.size(), m_context->sortbuffer);
		break;

	case Shader::SORT_BACKTOFRONT:
		sortBackToFront(m_context->camerapos.xyz(), m_context->worldtm, m_context->boneworldtm.begin(), m_context->boneworldtm.size(), m_context->sortbuffer);
		break;
	}

	if (s_hasVBOsupport)
	{
		if (m_usage != Context::UsageFlags::USAGE_DYNAMIC && m_interleaved)
		{
			if (GL_State::sm_current.m_arrayBuffer != m_vbuffers[0])
			{
				GL_State::sm_current.m_arrayBuffer = m_vbuffers[0];
				glBindBuffer(GL_ARRAY_BUFFER, GL_State::sm_current.m_arrayBuffer);
			}
			else
			{
			}
		}
		else if (GL_State::sm_current.m_arrayBuffer)
		{
			GL_State::sm_current.m_arrayBuffer = 0;
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	VertexFormat vf = ; //266
	uint8_t* begin; //265

	GLenum glmode = GL_NONE; //319

	VertexFormat::DataType dt = vf.getDataFormat(); /267

	enableClientState(dt);

	int pitch;

	assert(glGetError() == GL_NO_ERROR); //Line 127
	assert(glGetError() == GL_NO_ERROR); //Line 132
	assert(glGetError() == GL_NO_ERROR); //Line 142
	assert(glGetError() == GL_NO_ERROR); //Line 160
	assert(glGetError() == GL_NO_ERROR); //Line 168
	//switch
	//default: assert(false); //Line 181
	assert(glGetError() == GL_NO_ERROR); //Line 188
	assert(glGetError() == GL_NO_ERROR); //Line 199
	assert(glGetError() == GL_NO_ERROR); //Line 211
	assert(glGetError() == GL_NO_ERROR); //Line 224
	*/

	assert("void GL_Primitive::render() was not yet decompiled.");
}

GL_Primitive::PrimType GL_Primitive::type() const
{
	return m_prim;
}

void GL_Primitive::allocate(const VertexFormat& vf, int vertices, int indices) //386
{
	DIPrimitive::allocate(vf, vertices, indices);

	if (m_usage == Context::USAGE_DYNAMIC)
		return;

	if (indices > 0)
	{
		glGenBuffers(1, &m_ibuffer);
		assert(glGetError() == GL_NO_ERROR); //245 ABC 1.0.0 OSX
		assert(m_ibuffer != INVALID_BUFFER); //246 ABC 1.0.0 OSX
	}

	if (m_interleaved)
	{
		glGenBuffers(1, m_vbuffers);
		assert(glGetError() == GL_NO_ERROR); //252 ABC 1.0.0 OSX
		assert(m_vbuffers[0] != INVALID_BUFFER); //253 ABC 1.0.0 OSX
	}

	else
	{
		for (int i = VertexFormat::DT_POSITION; i < VertexFormat::DT_SIZE; i++) //409
		{
			VertexFormat::DataType dt = (VertexFormat::DataType)(i); //411
			if (vf.hasData(dt)) //413
			{
				glGenBuffers(1, &m_vbuffers[i]);
				assert(glGetError() == GL_NO_ERROR); //264 ABC 1.0.0 OSX
				assert(m_vbuffers[0] != INVALID_BUFFER); //265 ABC 1.0.0 OSX

				m_vbuffers[i]++;
			}
		}
	}
}

void GL_Primitive::deallocate() 
{
	if (m_usage == Context::USAGE_DYNAMIC)
		return;

	if (m_ibuffer)
	{
		glDeleteBuffers(1, &m_ibuffer);
		assert(glGetError() == GL_NO_ERROR); //281 ABC 1.0.0 OSX
		m_ibuffer = 0;
	}

	if (m_interleaved)
	{
		glDeleteBuffers(1, m_vbuffers);
		assert(glGetError() == GL_NO_ERROR); //288 ABC 1.0.0 OSX
		m_vbuffers[0] = 0;
	}

	else
	{
		for (int i = 0; i < MAX_VBUFFERS; i++) //445
		{
			if (m_vbuffers[i])
			{
				glDeleteBuffers(1, &m_vbuffers[i]);
				assert(glGetError() == GL_NO_ERROR); //298 ABC 1.0.0 OSX
				m_vbuffers[i] = 0;
			}
		}
	}
}

void GL_Primitive::getVertexDataPtr(VertexFormat::DataType dt, uint8_t** data, int* pitch) //457
{
	DIPrimitive::getVertexDataPtr(dt, data, pitch);
}

void GL_Primitive::getIndexDataPtr(uint16_t** data, int* indexsize) //462
{
	DIPrimitive::getIndexDataPtr(data, indexsize);
}

void GL_Primitive::lock(LockType lock) //467
{
	m_lock = lock;
}

void GL_Primitive::unlock()
{
	if (m_usage == Context::USAGE_DYNAMIC && (m_lock & LOCK_WRITE))
		m_lock = LOCK_NONE;

	int vertices = vertexCount(); //481
	int indices = indexCount(); //482, inline call not in DWARF?
	VertexFormat vf = vertexFormat(); //483

	if ((m_lock & LOCK_VERTEXONLY_FLAG) == 0 && m_ibuffer)
	{
		uint16_t* data; //487
		int pitch; //488
		getIndexDataPtr(&data, &pitch);

		GL_State::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibuffer); //491
		assert(glGetError() == GL_NO_ERROR); //340 ABC 1.0.0 OSX
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pitch * indices, data, GL_STATIC_DRAW_ARB);

		assert(glGetError() == GL_NO_ERROR); //343 ABC 1.0.0 OSX
		GL_State::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //497

		assert(glGetError() == GL_NO_ERROR); //346 ABC 1.0.0 OSX
	}

	if (m_interleaved)
	{
		VertexFormat::DataType dt; //504
		for (int i = VertexFormat::DT_POSITION; i < VertexFormat::DT_SIZE; i++) //505
		{
			dt = (VertexFormat::DataType)(i);
			if (vf.hasData(dt))
			{
				uint8_t* data; //512
				int pitch;
				getVertexDataPtr(dt, &data, &pitch);

				GL_State::bindBuffer(GL_ARRAY_BUFFER, m_vbuffers[i]); //516
				assert(glGetError() == GL_NO_ERROR); //365 ABC 1.0.0 OSX

				glBufferData(GL_ELEMENT_ARRAY_BUFFER, pitch * indices, data, GL_STATIC_DRAW);
				assert(glGetError() == GL_NO_ERROR); //368 ABC 1.0.0 OSX
				GL_State::bindBuffer(GL_ARRAY_BUFFER, 0); //522
			}
		}
	}
	else
	{
		for (int i = VertexFormat::DT_POSITION; i != VertexFormat::DT_SIZE; i++) //527
		{
			VertexFormat::DataType dt = (VertexFormat::DataType)(i); //529
			if (vf.hasData(dt)) //530
			{
				uint8_t* data; //532
				int pitch; //533
				getVertexDataPtr(dt, &data, &pitch);

				GL_State::bindBuffer(GL_ARRAY_BUFFER, m_vbuffers[i]); //536
				assert(glGetError() == GL_NO_ERROR); //385 ABC 1.0.0 OSX
				glBufferData(GL_ARRAY_BUFFER, pitch * indices, data, GL_STATIC_DRAW);

				assert(glGetError() == GL_NO_ERROR); //388 ABC 1.0.0 OSX
				GL_State::bindBuffer(GL_ARRAY_BUFFER, 0); //542

				assert(glGetError() == GL_NO_ERROR); //391 ABC 1.0.0 OSX
			}
		}
	}

	m_lock = LOCK_NONE;
}

}
}