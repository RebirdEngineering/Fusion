#ifndef _HGR_VISUAL_H
#define _HGR_VISUAL_H

#include <hgr/Node.h>

namespace gr
{
	class Shader;
	class Primitive;
}

namespace math
{ 
	class float4x4;
}

namespace hgr
{

/**
 * Base class for objects to be rendered on screen.
 *
 * @ingroup hgr
 */
class Visual : //20
	public Node
{
public:
	/** 
	 * Maximum bounding volume size.
	 */
	static const float	MAX_BOUND; //27

	/**
	 * Used by camera to store result of previous frame frustum check.
	 */
	int					frustumCheckHint; //32

	///
	Visual(); //35

	/** 
	 * Copy by value. 
	 */
	Visual( const Visual& other ); //40

	///
	virtual ~Visual(); //43

	/**
	 * Returns clone of this node. Clones child nodes as well.
	 */
	virtual Node*	clone() const; //48

	/** 
	 * Renders this visual to the rendering context.
	 * @param context Rendering context.
	 * @param camera Active camera.
	 * @param priority Shader priority level which is to be rendered.
	 */
	virtual void	render( gr::Context* context, Camera* camera, int priority ) = 0; //56

	/**
	 * Returns array of shaders used by this visual.
	 * NOTE: Implementation should not clear the list of returned shaders
	 * before adding new ones, since shadesr from multiple Visuals might be 
	 * collected at the same time.
	 */
	virtual void	getShaders( std::vector<gr::Shader*>& shaders ) = 0; //64

	/**
	 * Computes bounding volume of the visual in model space.
	 */
	virtual void	computeBound() = 0; //69

	/**
	 * Sets bounding radius in model space.
	 * Value ranges is between [0,MAX_BOUND].
	 */
	void			setBoundRadius( float r ); //75

	/**
	 * Sets bounding box minimum and maximum of the visual in model space.
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 * World space bounding box and model space bounding box are mutually exclusive.
	 */
	void			setBoundBox( const math::float3& boxmin, const math::float3& boxmax ); //82

	/**
	 * Sets bounding box minimum and maximum of the visual in world space.
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 * World space bounding box and model space bounding box are mutually exclusive.
	 */
	void			setBoundBoxWorld( const math::float3& boxmin, const math::float3& boxmax ); //89

	/**
	 * Sets 'infinite' bounding box.
	 * 'Infinite' bounding box is equal to [-MAX_BOUND,MAX_BOUND] size.
	 * Infinite box is considered to be defined in world space.
	 */
	void			setBoundInfinity(); //96

	/**
	 * Returns bounding radius.
	 */
	float					boundRadius() const; //101

	/**
	 * Returns bounding volume center (average of box min/max).
	 */
	math::float3			boundCenter() const; //106

	/**
	 * Gets bounding box minimum of the visual in model space.
	 * Requires that bounding box has been set with setBoundBox().
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 */
	const math::float3&	boundBoxMin() const; //113

	/**
	 * Gets bounding box maximum of the visual in model space.
	 * Requires that bounding box has been set with setBoundBox().
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 */
	const math::float3&	boundBoxMax() const; //120

	/**
	 * Gets bounding box minimum of the visual in world space.
	 * Requires that bounding box has been set with setBoundBoxWorld().
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 */
	const math::float3&	boundBoxMinWorld() const; //127

	/**
	 * Gets bounding box maximum of the visual in world space.
	 * Requires that bounding box has been set with setBoundBoxWorld().
	 * Value ranges are between [-MAX_BOUND,MAX_BOUND].
	 */
	const math::float3&	boundBoxMaxWorld() const; //134

	/**
	 * Returns true if this Visual's bounding volumes is infinite,
	 * i.e. visual is always visible.
	 */
	bool		isBoundInfinity() const; //140

	/**
	 * Returns true if this Visual's bounding volumes are
	 * defined in world space (instead of default, model space).
	 */
	bool		isBoundWorld() const; //146

	/**
	 * Returns transformations which remove world space scaling
	 * and move pivot to geometric center.
	 * Useful for example to setup rigid body simulations
	 * and other applications which do not tolerate scaling and
	 * require pivot to be in geometric center.
	 *
	 * @param bodyworldtm [out] Receives geometric pivot transformation in uniformly scaled world space (ptr can be 0 if value not needed).
	 * @param bodytm [out] Visual world transform multiplied with this results uniform world transform (ptr can be 0 if value not needed).
	 * @param bodyvertextm [out] Visual vertex transformed with this results a vertex compatible with uniform world transform (ptr can be 0 if value not needed).
	 */
	void		getBodyTransform( math::float3x4* bodyworldtm, math::float3x4* bodytm=0, math::float3x4* bodyvertextm=0 ) const; //159

private:
	math::float3	m_boundBoxMin; //162
	math::float3	m_boundBoxMax; //163
	float			m_boundRadius; //164

	void	setBoundModel(); //166
	void	setBoundWorld(); //167

	Visual& operator=( const Visual& other ); //169
};


#include <hgr/Visual.inl> //Needed?


} // hgr


#endif // _HGR_VISUAL_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
