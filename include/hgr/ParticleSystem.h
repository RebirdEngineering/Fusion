#ifndef _HGR_PARTICLESYSTEM_H
#define _HGR_PARTICLESYSTEM_H
#ifndef HGR_NOPARTICLES

#include <gr/Primitive.h>
#include <hgr/Visual.h>
#include <hgr/impl/ParticleSystem_Integral.h>

namespace gr
{
	class Shader;
	class Texture;
}

namespace io
{ 
	class PropertyParser;
	class InputStream;
	class OutputStream;
}

namespace lua
{ 
	class LuaTable;
}

namespace hgr
{

class Camera;
class ResourceManager;

/**
 * Particle effect. Can be created directly or from Lua script.
 * 
 * Key features:
 * <ul>
 * <li>Variable number of emitters / single system
 * <li>Variable number of particles / emitter
 * <li>All properties can have different random variable value distribution
 * <li>Elastic, scaling, rotating etc. particle sprites are supported.
 * <li>Per particle transparency, color and animation texture frame are supported.
 * <li>Particles can use also user defined shaders.
 * </ul>
 *
 * Particle systems are heavily based on concept of 'domains'.
 * It is a bit abstract, but understanding it is essential
 * for effective usage of the particle systems. On the benefit
 * side once you understand it, using the particle systems
 * becomes very intuitive and orthogonal, as nearly all properties
 * of particle systems are simple defined by setting
 * appropriate value domains for each property.
 *
 * 'Domains' are source ranges for various random
 * values needed by particle systems.
 * Domains can be sources for scalar values, 
 * 2D and 3D vectors used in the simulation.
 *
 * For example by saying that some particle effect has
 * particle initial position domain set as 'Sphere with
 * radius 4' means that the initial positions of new 
 * particles are randomized inside sphere which has radius 4.
 * If in turn the particle initial velocity domain
 * is set as Point {-50,0,0} then all particles get
 * initial velocity of -50 along negative X-axis.
 *
 * With various domains it is easy to make pretty much
 * any kind of particle effect. For example rain
 * could be done by setting position box above sky,
 * and then velocity Point(0,-1,0) and Gravity=-9.8.
 * In addition, ParticleSpriteElasticity could be
 * set above 0 (say, 0.1) to stretch particle bitmap
 * along movement speed - the system is very flexible.
 *
 * @ingroup hgr
 */
class ParticleSystem : //74
	public NS(hgr,Visual)
{
public:
	/**
	 * Kill mode describes how max count limit is maintained.
	 */
	enum KillType //81
	{
		/** No items are killed when max limit is reached. */
		KILL_NONE,
		/** Oldest item is killed when max limit is reached. */
		KILL_OLDEST,
		/** Random item is killed when max limit is reached. */
		KILL_RANDOM,
		/** Number of kill modes. */
		KILL_COUNT
	};

	/** 
	 * View mode of particle sprites.
	 * View mode defines how particles are rotated when camera is tilted.
	 */
	enum ViewType //97
	{
		/**
		 * Particles are facing to camera and bitmaps Y-axis points up in camera space.
		 */
		VIEW_CAMERAUP,
		/**
		 * Particles are facing to camera and bitmaps Y-axis points up in world space.
		 */
		VIEW_WORLDUP,
		/**
		 * Number of view modes.
		 */
		VIEW_COUNT
	};

	/** 
	 * Animation type of particle texture.
	 * Defines how texture frames change over life time of particle effect.
	 */
	enum AnimationType //117
	{
		/**
		 * Animation frames are used as normal animation sequence.
		 * Framerate defines how often frame is changed to next one.
		 */
		ANIM_LOOP,
		/**
		 * Animation frames are used by particle life time.
		 * Framerate does not affect any way.
		 */
		ANIM_LIFE,
		/**
		 * Animation frames are used randomly.
		 * Framerate defines how often frame is randomized.
		 */
		ANIM_RANDOM,
		/**
		 * Number of animation types.
		 */
		ANIM_COUNT
	};

	/**
	 * Description of a particle system.
	 * Description objects are shared between all instances
	 * of the same particle effect.
	 * Normally this class is not used directly by the user as
	 * particle systems are loaded from scripts.
	 */
	class Description : //147
		public lang::Object
	{
	public:
		enum
		{
			/** Absolute maximum limit for number of particles. */ 
			MAX_PARTICLES_LIMIT = 65535/6 
		};

		/** Maximum number of simultaneous emissions. */
		int					systemMaxEmissions; //158

		/** Value domain for number of new emissions / second random (scalar) variable. */
		math::Domain		systemRate; //161

		/** Value domain for system stop time random (scalar) variable. */
		math::Domain		systemStopTime; //164

		/** Value domain for system life time random (scalar) variable. */
		math::Domain		systemLifeTime; //167

		/** Maximum number of particles. See MAX_PARTICLES_LIMIT. */
		int					emissionMaxParticles; //170

		/** Value domain for emission rate random (scalar) variable. */
		math::Domain		emissionRate; //173

		/** Value domain for emission stop time random (scalar) variable. */
		math::Domain		emissionStopTime; //176

		/** Value domain for emission life time random (scalar) variable. */
		math::Domain		emissionLifeTime; //189

		/** Value domain for emission pivot random (3-vector) variable. */
		math::Domain		emissionPosition; //182

		/** Value domain for particle life time random (scalar) variable. */
		math::Domain		particleLifeTime; //185
		
		/** Value domain for particle start velocity random (3-vector) variable. */
		math::Domain		particleStartVelocity; //188
		
		/** Value domain for particle start position random (3-vector) variable. */
		math::Domain		particleStartPosition; //191
		
		/** Value domain for particle start size random (scalar) variable. */
		math::Domain		particleStartSize; //194
		
		/** Value domain for particle end size random (scalar) variable. */
		math::Domain		particleEndSize; //197
		
		/** Value domain for particle start transparency random (scalar) variable. 1 is opaque. */
		math::Domain		particleStartAlpha; //200
		
		/** Value domain for particle end transparency random (scalar) variable. 1 is opaque. */
		math::Domain		particleEndAlpha; //203
		
		/** Value domain for particle start color random (3-vector) variable. (1,1,1) is white. */
		math::Domain		particleStartColor; //206
		
		/** Value domain for particle end color random (3-vector) variable. (1,1,1) is white. */
		math::Domain		particleEndColor; //209
		
		/** 
		 * Value domain for particle elasticity random (scalar) variable. 
 		 * Good values 0-0.2, but out-of-range values can create interesting effects. 
		 */
		math::Domain		particleSpriteElasticity; //215
		
		/** Value domain for particle sprite start rotation (radians) random (scalar) variable. */
		math::Domain		particleSpriteRotation; //218
		
		/** Value domain for particle sprite start rotation speed (rad/s) random (scalar) variable. */
		math::Domain		particleSpriteStartRotationSpeed; //221
		
		/** Value domain for particle sprite end rotation speed (rad/s) random (scalar) variable. */
		math::Domain		particleSpriteEndRotationSpeed; //224
		
		/** Gravity in world space Y-axis direction, m/(s*s). */
		float				gravity; //227
		
		/** Wind in world space, m/s. */
		math::float3		wind; //230

		/** Texture animation frame change rate, changes/second. */
		float				textureFrameRate; //233
				
		/** Number of texture frames embedded to the texture bitmap in NxN grid. Must be square of integer. */
		int					textureFrames; //236

		/** Name of the particle texture (without path) */
		std::string		textureName; //239

		/** Name of the particle shader */
		std::string		shaderName; //242

		/** Texture (animation) for the particle effect. */
		P(NS(gr,Texture))		texture; //245
		
		/** Sprite shader used to render particles. */
		P(gr::Shader)		shader; //248
		
		/** Defines how texture frames change over life time of particle effect. */
		AnimationType		textureAnimation; //251
		
		/** View mode defines how particles are rotated when camera is tilted. */
		ViewType			textureView; //254
		
		/** Kill mode describes how max particle limit is maintained. */
		KillType			emissionLimitKill; //257

		/** Kill mode describes how max emission limit is maintained. */
		KillType			systemLimitKill; //260

		/** If true then particles are updated even though they are not visible. */
		bool				particleUpdateAlways; //263

		/** True if particles are aligned at birth moment by setUserNormal field. */
		bool				particleAlignedToUserNormal; //266

		/**  */
		math::float3				particleUserNormal; //269

		Description(); //271

		/**
		 * Writes particle system description to output stream.
		 */
		void	write( io::OutputStream& s ); //276

		/**
		 * Reads particle system description from input stream.
		 */
		void	read( io::InputStream& s ); //281

	private:
		friend class ParticleSystem;

		void	write( io::OutputStream& s, int v, const std::string& variablename, const std::string& description ); //286
		void	write( io::OutputStream& s, bool v, const std::string& variablename, const std::string& description ); //287
		void	write( io::OutputStream& s, float v, const std::string& variablename, const std::string& description ); //288
		void	write( io::OutputStream& s, const math::float3& v, const std::string& variablename, const std::string& description ); //289
		void	write( io::OutputStream& s, const math::Domain& v, const std::string& variablename, const std::string& description ); //290
		void	write( io::OutputStream& s, const char* v, const std::string& variablename, const std::string& description ); //291
		void	write( io::OutputStream& s, const char* sz ); //292
		void	writeDescription( io::OutputStream* s, const std::string& description ); //293

		void	read( io::PropertyParser& prop, int& v, const char* variablename ); //295
		void	read( io::PropertyParser& prop, bool& v, const char* variablename ); //296
		void	readOpt( io::PropertyParser& prop, bool& v, const char* variablename, bool defaultval ); //297
		void	readOpt( io::PropertyParser& prop, math::float3& v, const char* variablename, const math::float3& defaultval ); //298
		void	read( io::PropertyParser& prop, float& v, const char* variablename ); //299
		void	read( io::PropertyParser& prop, std::string& v, const char* variablename ); //300
		void	read( io::PropertyParser& prop, math::float3& v, const char* variablename ); //301
		void	read( io::PropertyParser& prop, math::Domain& v, const char* variablename ); //302
		void	read( io::PropertyParser& prop, AnimationType& v, const char* variablename ); //303
		void	read( io::PropertyParser& prop, ViewType& v, const char* variablename ); //304
		void	read( io::PropertyParser& prop, KillType& v, const char* variablename ); //305

		void	check( const std::string& filename ) const; //307

		// intermediate values cached from the description
		float					textureFrameUV; //310
		std::vector<float>	uvcache; //311
	};

	/* Single particle. Private implementation class. */
	class Particle //315
	{
	public:
		float										time; //318
		float										life; //319
		float										rot; //320
		float										elasticity; //321
		ParticleSystem_Integral<float>				size; //322
		ParticleSystem_Integral<math::float3>	color; //323
		ParticleSystem_Integral<float>				alpha; //324
		ParticleSystem_Integral<float>				rotspeed; //325
		int											frame; //326
		math::float3								velocity; //327
		math::float3								position; //328
		math::float3x3							userRot; // world space | 329
	};

	/* Single emission from the particle system. Contains many particles. Private implementation class. */
	class Emission //333
	{
	public:
		float					time; //336
		float					stop; //337
		float					life; //338
		float					newParticles; //339
		math::float3			position; //340
		std::vector<Particle>	particles; //341
	};

	/**
	 * Loads a particle system from a file.
	 * @param context Rendering context to be used while loading.
	 * @param filename Scene file name relative to current working directory.
	 * @param res Resource manager to load textures and shaders from. 0 for default.
	 * @param texturepath Texture path relative to current working directory.
	 * @param shaderpath Shader path relative to current working directory.
	 * @exception IOException
	 * @exception LuaException
	 * @exception GraphicsException
	 */
	ParticleSystem( gr::Context* context, const std::string& filename, ResourceManager* res=0,
		const std::string& texturepath="", const std::string& shaderpath="" ); //355

	/**
	 * Makes particle system using user provided description object.
	 */
	explicit ParticleSystem( Description* desc ); //361

	/**
	 * Creates copy of particle system. Shares non-instance-specific data.
	 */
	explicit ParticleSystem( const ParticleSystem& other ); //366

	~ParticleSystem(); //368

	/**
	 * Returns clone of this node. Clones child nodes as well.
	 */
	virtual Node*	clone() const; //373

	/**
	 * Loads particle system from file.
	 * @exception IOException
	 * @exception LuaException
	 * @exception GraphicsException
	 */
	void	load( gr::Context* context, const std::string& filename, ResourceManager* res,
				const std::string& texturepath="", const std::string& shaderpath="" ); //381

	/**
	 * Updates particle animation.
	 * @param dt Time interval to update in seconds.
	 */
	void	update( float dt ); //388

	/** 
	 * Renders this particle system to the active device.
	 * @param context Rendering context.
	 * @param camera Active camera.
	 * @param priority Shader priority level which is to be rendered.
	 */
	void	render( gr::Context* context, Camera* camera, int priority ); //396

	/**
	 * Returns array of shaders used by this visual.
	 * NOTE: Implementation should not clear the list of returned shaders
	 * before adding new ones, since shadesr from multiple Visuals might be 
	 * collected at the same time.
	 */
	void	getShaders( std::vector<gr::Shader*>& shaders ); //404

	/**
	 * Sets rendering technique of the shaders used by this mesh.
	 */
	void	setTechnique( const char* name ); //409

	/**
	 * Resets particle system to its initial state.
	 */
	void	reset(); //414

	/**
	 * Computes bounding volume of the visual in model space.
	 */
	void	computeBound(); //419

	/**
	 * Sets time (seconds) to delay particle system instance simulation start.
	 * Default delay is 0.
	 * @param time Delay in seconds.
	 */
	void	setDelay( float time ); //426

	/**
	 * Sets velocity of parent node in world space to be taken into account while
	 * computing sprite elasticity effect.
	 */
	void	setParentVelocity( const math::float3& vel ); //432

	/** 
	 * Sets user defined normal (normalized, in world space). 
	 * @see particleAlignedToUserNormal
	 */
	void	setUserNormal( const math::float3& normal ); //438

	/**
	 * Returns description used by this particle system.
	 */
	Description*	description()					{return m_desc;} //443

	/**
	 * Returns total number of active particles.
	 */
	int				particles() const; //448

	/**
	 * 
	 */
	int				lifetime() const; //453

	/**
	 * Returns description used by this particle system.
	 */
	const Description*		description() const		{return m_desc;} //458

	/**
	 * Converts string to ViewType.
	 * @return VIEW_COUNT if not found.
	 */ 
	static ViewType			toViewType( const char* sz ); //464

	/**
	 * Converts string to AnimationType.
	 * @return ANIMATION_COUNT if not found.
	 */ 
	static AnimationType	toAnimationType( const char* sz ); //370

	/**
	 * Converts string to KillType.
	 * @return KILL_COUNT if not found.
	 */ 
	static KillType			toKillType( const char* sz ); //476

private:
	P(Description)				m_desc; //479
	std::vector<Emission>	m_emissions; //480
	float						m_time; //481
	float						m_timeSinceRender; //481
	float						m_newEmissions; //383
	float						m_systemStopTime; //484
	float						m_systemLifeTime; //485
	float						m_delay; //486
	math::float3				m_parentVelocity; //487
	math::float3x3			m_userRot; //488
	P(gr::Primitive)			m_prim; //489

	void		renderDX( gr::Context* context, Camera* camera ); //491
	void		renderGLES2( gr::Context* context, Camera* camera ); //492
	void		restart(); //493
	void		refreshCachedValues(); //494
	static void	getDomain( const std::string& particlename, NS(lua,LuaTable)& tab, const std::string& domainname, math::Domain* domain ); //495
	static int	log2i( int x ); //496

	template <class T> static void	killOld( std::vector<T>& array );
	template <class T> static T*	getNew( std::vector<T>& array, int limit, KillType killtype );

	ParticleSystem& operator=( const ParticleSystem& ); //501
};


} // hgr


#endif // HGR_NOPARTICLES
#endif // _HGR_PARTICLESYSTEM_H
