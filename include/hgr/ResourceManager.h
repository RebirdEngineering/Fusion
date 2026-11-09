#ifndef _HGR_RESOURCEMANAGER_H
#define _HGR_RESOURCEMANAGER_H

#include <lang/Object.h>

namespace gr
{
	class Shader;
	class Context;
	class Texture;
	class CubeTexture;
}

namespace hgr
{

class ParticleSystem;

/**
 * Abstract base class for managing and sharing rendering resources.
 *
 * @ingroup hgr
 */
class ResourceManager : //21
	public lang::Object
{
public:
	/**
	 * Gets shader by name.
	 * @param name (Base) name of the shader.
	 * @param flags Shader compilation flags. See NS(Shader,Flags).
	 * @exception Exception
	 */
	virtual gr::Shader*			getShader( const std::string& name, int flags ) = 0; //31

	/** 
	 * Gets texture by filename. 
	 * @param name Name of the texture.
	 * @exception Exception
	 */
	virtual gr::Texture*		getTexture( const std::string& filename ) = 0; //38

	/** 
	 * Gets cube texture by filename. 
	 * @param name Name of the texture.
	 * @exception Exception
	 */
	virtual gr::CubeTexture*	getCubeTexture( const std::string& filename ) = 0; //45


	/** 
	 * Gets particle system by filename. 
	 * @param name Name of the particle system.
	 * @exception Exception
	 */
	virtual ParticleSystem*		getParticleSystem( const std::string& filename, //55
									const std::string& texturepath="",
									const std::string& shaderpath="" ) = 0;
#endif
};


} // hgr


#endif // _HGR_RESOURCEMANAGER_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
