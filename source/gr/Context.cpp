#include <gr/Context.h>
#include <io/BundleInputStream.h>

USING_NAMESPACE(io)

BEGIN_NAMESPACE(gr)

const char* const PLATFORM_NAME[] = //8
{
    "gles1",
    "gles2",
    "gl1",
    "gl2",
    "dx11",
    "xna"
};

const char* const PLATFORM_DESC[] = //[NOTE] DirectX to Nokia N3D are deprecated | Not in iOS builds?
{
    "OpenGL ES 1.1",
    "OpenGL ES 2.0",
    "OpenGL 1.4",
    "OpenGL 2.0",
    "DirectX 11",
    "XNA (Interop)"
};


Context::RenderScene::RenderScene( Context* context ) : //32
	m_context( context )
{
	m_context->beginScene();
}
	
Context::RenderScene::~RenderScene()
{
	m_context->endScene();
}

void Context::Statistics::reset()
{
	memset( this, 0, sizeof(Statistics) );
}

Context::Context()
{
	m_batcher = 0;
	m_useTextureShadowing = false;
	m_batcher = new RenderBatcher(this); //51
	statistics.reset(); //52
}

Context::~Context()
{
}

float Context::aspect() const
{
	assert(width() > 0); //Line 59
	assert(height() > 0); //Line 60
	return (float)width() / (float)height();
}

const char*	Context::getString( PlatformType platform )
{
	assert( (int)platform >= 0 && (int)platform < int(sizeof(PLATFORM_NAME)/sizeof(PLATFORM_NAME[0])) ); //Assert on line 66
	return PLATFORM_NAME[platform];
}

const char*	Context::getDescription( PlatformType platform )
{
	assert( (int)platform >= 0 && (int)platform < int(sizeof(PLATFORM_DESC)/sizeof(PLATFORM_DESC[0])) );
	return PLATFORM_DESC[platform];
}

const char* Context::platformString() const
{
	assert( (int)platform() >= 0 && (int)platform() < int(sizeof(PLATFORM_NAME)/sizeof(PLATFORM_NAME[0])) ); //Assert on line 78
	return PLATFORM_NAME[platform()];
}

void Context::transformPointToScreen(int& x, int& y) const //Correct?
{
	switch (orientation())
	{
	case ORIENTATION_180: x -= width(); y -= height(); break;
	case ORIENTATION_270: x -= width(); y = x; break;
	case ORIENTATION_90: x = y; y -= height(); break;
	}
}

void Context::setWireframeEnabled( bool /*enabled*/ )
{
}

bool Context::isTextureShadowingEnabled() const
{
	return m_useTextureShadowing;
}

Image* Context::createImagefromBundle(const std::string& filename) //121
{
	BundleInputStream inputStream(filename); //123
	return createImage(inputStream, filename);
}

END_NAMESPACE() // gr

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
