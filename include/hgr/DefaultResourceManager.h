#ifndef _HGR_DEFAULTRESOURCEMANAGER_H
#define _HGR_DEFAULTRESOURCEMANAGER_H

#include <gr/Texture.h>
#include <gr/CubeTexture.h>
#ifndef HGR_NOPARTICLES
#include <hgr/ParticleSystem.h>
#endif
#include <hgr/ResourceManager.h>

namespace gr
{
	class Context;
	class Texture;
}

namespace hgr { 

class ParticleSystem;

/**
 * Default rendering resource manager.
 *
 * Manages resources in following way:
 * <ul>
 * <li>Shares texture by matching pathname (i.e. C:/mydata/tex.bmp != C:/tex.bmp)
 * <li>Shares particles by matching basename (i.e. C:/flare.prs == C:/data/flare.prs)
 * <li>Shaders are not shared (i.e. C:/my.fx != C:/my.fx)
 * </ul>
 *
 * @ingroup hgr
 */
class DefaultResourceManager : //35 | THIS IS REALLY ONLY HERE SINCE GAMELUA USES IT'S STRUCT
	public ResourceManager
{
public:
	/**
	 * Creates resource manager using specified rendering context.
	 */
	explicit DefaultResourceManager( gr::Context* context ); //42

	~DefaultResourceManager(); //44

	/**
	 * Gets shader by name.
	 * @exception Exception
	 */
	gr::Shader*		getShader( const std::string& name, int flags ); //50

	/** 
	 * Gets texture by filename. Note that basenames need to be unique!
	 * @exception Exception
	 */
	gr::Texture*		getTexture( const std::string& filename ); //56

	/** 
	 * Gets cube texture by filename. 
	 * @exception Exception
	 */
	gr::CubeTexture*	getCubeTexture( const std::string& filename ); //62

	/** 
	 * Gets particle system by filename. 
	 * @exception Exception
	 */
	ParticleSystem*		getParticleSystem( const std::string& filename,
							const std::string& texturepath,
							const std::string& shaderpath ); //68

	bool isTextureCached(const std::string& filename); //75 | Recovered param from ABFM

	/**
	 * Finds texture resources below specific path.
	 * @param pathfilter Path to find resource from, e.g. D:/data/*
	 */
	void				findTextureResources( const std::string& pathfilter ); //81

	void getTextureResources(const io::PathName& path, const std::string& file); //89 | Recovered params from ABFM

	/*
	*
	*/
	void getTextureResourcesFromBundleIndex(const std::string& searchPath, io::FileBundle bm); //94

	/**
	 * Replaces texture file extension with specified string.
	 * Can be used for example to load platform-specific texture files 
	 * when scenes have been exported with generic files.
	 * @param newsuffix New file name extension for textures, dot included.
	 */
	void				replaceTextureExtension( const std::string& newsuffix ); //102

	/**
	 * Releases textures which have no (external) references left.
	 * @return Number of surface memory bytes released.
	 */
	int					releaseUnusedTextures(); //108

	/**
	 * Returns active resource manager.
	 */
	static ResourceManager* get( gr::Context* context ); //113

	/**
	 * Sets active resource manager.
	 */
	static void				set( ResourceManager* res ); //118

private:
	class TextureResource //121
	{
	public:
		P(gr::Texture)	texture; //124
		std::string		filename; //125
	};

	std::string		m_textureExtension; //128
	P(gr::Context)																				m_context; //129
	std::map<std::string, TextureResource>			m_textures; //130
	std::map<std::string, P(gr::CubeTexture)>		m_cubeTextures; //131
#ifndef HGR_NOPARTICLES
	std::map<std::string, P(hgr::ParticleSystem)>	m_particles; //133
#endif

	std::string		getTextureSystemFilename( const std::string& filename ); //136


	DefaultResourceManager( const DefaultResourceManager& ); //138
	DefaultResourceManager& operator=( const DefaultResourceManager& ); //139
};


} // hgr


#endif // _HGR_DEFAULTRESOURCEMANAGER_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
