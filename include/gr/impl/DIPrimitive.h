#ifndef _GR_DIPRIMITIVE_H
#define _GR_DIPRIMITIVE_H

#include <gr/Primitive.h>
#include <gr/VertexFormat.h>
#include <gr/impl/SortBuffer.h>
#include <math/float4.h>

namespace math
{ 
	class float3;
	class float4;
	class float4x4;}

namespace gr
{

class Shader;

/**
 * System memory device independent geometry primitive list.
 * Platform dependent gr implementation can use this as
 * primitive list base class to get better startpoint for the 
 * platform specific implementation.
 */
class DIPrimitive : //25
	public Primitive
{
public:
	/**
	 * Leaves buffers uninitialized.
	 * Call setFormat to initialize buffers.
	 */
	DIPrimitive(); //35

	~DIPrimitive(); //35

	/** 
	 * Sets new vertex format and initializes buffers accordingly.
	 * Warning: All previously set data in the primitive is lost.
	 */
	void	setFormat( const VertexFormat& fmt, int vertices, int indices ); //41

	/**
	 * Sets vertex position coordinates.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexPositions( int index, const math::float4* data, int count ); //51

	/**
	 * Sets transformed vertex position coordinates.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Position coordinate data.
	 * @param count Position coordinate count.
	 */
	void	setVertexTransformedPositions( int index, const math::float4* data, int count ); //61

	/**
	 * Sets vertex normals.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexNormals( int index, const math::float4* data, int count ); //71

	/**
	 * Sets vertex diffuse RGBA colors.
	 * Colors are expected in [0,255] range.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexDiffuseColors( int index, const math::float4* data, int count ); //82

	/**
	 * Sets vertex specular RGBA colors.
	 * Colors are expected in [0,255] range.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexSpecularColors( int index, const math::float4* data, int count ); //93

	/**
	 * Sets vertex tangents.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexTangents( int index, const math::float4* data, int count ); //103

	/**
	 * Sets vertex bone blending weights used in skinning.
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexBoneWeights( int index, const math::float4* data, int count ); //111

	/**
	 * Sets vertex bone blending indices used in skinning.
	 * @param index First vertex to set.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	setVertexBoneIndices( int index, const math::float4* data, int count ); //119

	/**
	 * Sets vertex texture coordinates.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to set.
	 * @param layer Texture layer index.
	 * @param data Texture coordinate data.
	 * @param count Texture coordinate count.
	 */
	void	setVertexTextureCoordinates( int index, int layer, const math::float4* data, int count ); //130

	/**
	 * Sets scale & bias for unpacking texture coordinate data.
	 * @param scalebias scale=x, bias=yzw
	 * v(1) = v(0) * scale + bias
	 */
	void	setVertexTextureCoordinateScaleBias( const math::float4& scalebias ); //137

	/**
	 * Sets scale & bias for unpacking vertex position coordinate data.
	 * @param scalebias scale=x, bias=yzw
	 * v(1) = v(0) * scale + bias
	 */
	void	setVertexPositionScaleBias( const math::float4& scalebias ); //144

	/**
	 * Sets primitive vertex indices.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index Index of the first index to set.
	 * @param data Index data.
	 * @param count Number of indices to set.
	 */
	void	setIndices( int index, const int* data, int count ); //154

	/**
	 * Optimizes bone list so that the bones used by this primitive are
	 * numbered from 0 (inclusive) to n (exclusive), where n is total number 
	 * bones used by this primitive. usedBoneArray return list of actual
	 * skin mesh bone indices.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @see usedBoneArray
	 * @see usedBones
	 */
	void	packBones(); //166

	/**
	 * Sets list of bones used by this primitive. List contains indices
	 * numbered from 0 (inclusive) to n (exclusive), where n is total number 
	 * bones used by this primitive. usedBoneArray return lists of actual
	 * skin mesh bone indices.
	 * Primitive needs to be locked for writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @see usedBoneArray
	 * @see usedBones
	 */
	void	setUsedBones( const uint8_t* usedbonearray, int usedbones ); //178

	/**
	 * Sorts primitive polygons front-to-back order.
	 * Primitive needs to be locked for reading and writing before calling this method.
	 * Note: If the primitive does not contain triangles, then this method
	 * does might leave buffer well-defined state.
	 * @param refpos World space origin to use for sorting.
	 * @param worldtm Model-to-world transform if any.
	 * @param boneworldtm Bone-to-world transforms if any.
	 * @param boneworldtmcount Number of bone-to-world transforms.
	 * @param tmp Temporary buffer used in sorting.
	 */
	void	sortFrontToBack( const math::float3& refpos, const math::float4x4& worldtm, //191
				const math::float4x4* boneworldtm, int boneworldtmcount,
				SortBuffer& tmp );

	/**
	 * Sorts primitive polygons back-to-front order.
	 * Primitive needs to be locked for reading and writing before calling this method.
	 * Note: If the primitive does not contain triangles, then this method
	 * does might leave buffer well-defined state.
	 * @param refpos World space origin to use for sorting.
	 * @param worldtm Model-to-world transform if any.
	 * @param boneworldtm Bone-to-world transforms if any.
	 * @param boneworldtmcount Number of bone-to-world transforms.
	 * @param tmp Temporary buffer used in sorting.
	 */
	void	sortBackToFront( const math::float3& refpos, const math::float4x4& worldtm, //206
				const math::float4x4* boneworldtm, int boneworldtmcount, 
				SortBuffer& tmp );

	/**
	 * Sorts primitive polygons inside-out order.
	 * Primitive needs to be locked for reading and writing before calling this method.
	 * Note: If the primitive does not contain triangles, then this method
	 * does might leave buffer well-defined state.
	 * @param tmp Temporary buffer used in sorting.
	 */
	void	sortInsideOut( SortBuffer& tmp ); //217

	/**
	 * Sorts primitive polygons outside-in order.
	 * Primitive needs to be locked for reading and writing before calling this method.
	 * Note: If the primitive does not contain triangles, then this method
	 * does might leave buffer well-defined state.
	 * @param tmp Temporary buffer used in sorting.
	 */
	void	sortOutsideIn( SortBuffer& tmp ); //226

	/**
	 * Returns pointer to vertex data of specified component.
	 * Primitive needs to be locked before calling this method.
	 */
	virtual void	getVertexDataPtr( VertexFormat::DataType dt, uint8_t** data, int* pitch ); //232

	/**
	 * Returns pointer to face index data.
	 * Primitive needs to be locked before calling this method.
	 */
	virtual void	getIndexDataPtr( uint16_t** data, int* indexsize ); //238

	/**
	 * Sets range of vertices used in rendering.
	 * Range must be below maximum vertex count specified in object creation.
	 * Range specifies the first vertex used to render the primitive.
	 */
	void	setVertexRangeBegin( int begin ); //245

	/**
	 * Sets range of vertices used in rendering.
	 * Range must be below or equal to maximum vertex count specified in object creation.
	 * Range specifies one beyond the last vertex used to render the primitive.
	 */
	void	setVertexRangeEnd( int end ); //252

	/**
	 * Sets range of indices used in rendering.
	 * Range must be below maximum index count specified in object creation.
	 * Range specifies the first index used to render the primitive.
	 */
	void	setIndexRangeBegin( int begin ); //259

	/**
	 * Sets range of indices used in rendering.
	 * Range must be below or equal to maximum index count specified in object creation.
	 * Range specifies one beyond the last index used to render the primitive.
	 */
	void	setIndexRangeEnd( int end ); //266

	/** 
	 * Sets vertex components. Supports format conversion. 
	 */
	void 	setVertexData( VertexFormat::DataType dt, int index, //271
				const math::float4* data, int count );

	/** 
	 * Sets vertex indices. Supports format conversion. 
	 * Primitive needs to be locked for writing before calling this method.
	 * @param v0 First vertex index to set.
	 * @param data Pointer to source data.
	 * @param indexsize Byte size of single index (1,2 or 4).
	 * @param count Number of indices to set.
	 */
	void 	setIndexData( int v0, const void* data, int indexsize, int count ); //282

	/** 
	 * Sets vertex components. Supports format conversion. 
	 * Primitive needs to be locked for writing before calling this method.
	 * @param dt Vertex data type to set.
	 * @param index First vertex to set.
	 * @param data Pointer to source data.
	 * @param df Format of source data. 
	 * @param count Number of vertices to set.
	 */
	void 	setVertexData( VertexFormat::DataType dt, int index, //293
				const void* data, VertexFormat::DataFormat df, int count );

	/**
	 * Sets primitive bounding volume.
	 */
	void	setBound( const math::float3& boundmin, const math::float3& boundmax, float boundradius ); //299

	/** 
	 * Gets vertex components. Supports format conversion. 
	 * @param dt Vertex data type to get.
	 * @param index First vertex to get.
	 * @param data Pointer to buffer for data.
	 * @param count Number of vertices to get.
	 */
	void 	getVertexData( VertexFormat::DataType dt, int index, math::float4* data, int count ) const; //308

	/**
	 * Gets range of vertices used in rendering.
	 */
	int		vertexRangeBegin() const; //313

	/**
	 * Gets range of vertices used in rendering.
	 */
	int		vertexRangeEnd() const; //318

	/**
	 * Gets range of indices used in rendering.
	 */
	int		indexRangeBegin() const; //323

	/**
	 * Gets range of indices used in rendering.
	 */
	int		indexRangeEnd() const; //328

	/**
	 * Returns vertex format.
	 */
	const VertexFormat&	vertexFormat() const; //333

	/**
	 * Returns vertex format.
	 * Used in drivers as optimization to avoid virtual call involved
	 * in using vertexFormat() method.
	 */
	const VertexFormat&	vf() const 			{return m_vf;} //340

	/**
	 * Returns list of bones used by this primitive.
	 * Indices returned by this function represent skin mesh bone indices.
	 * Beware that changing skin mesh might invalidate the indices
	 * returned by the primitive, unless primitive is updated accordingly.
	 */
	const uint8_t*	usedBoneArray() const; //348

	/**
	 * Returns number of bones used by this primitive.
	 */
	int		usedBones() const; //353

	/** 
	 * Returns number of bytes used by single vertex. 
	 */
	int		vertexSize() const; //358

	/** 
	 * Returns number of bytes used by single index. 
	 */
	int		indexSize() const; //363

	/**
	 * Returns number of vertices in the primitive. (from Primitive)
	 */
	int		vertices() const; //368

	/**
	 * Returns number of indices in the primitive. (from Primitive)
	 */
	int		indices() const; //373

	/**
	 * Returns number of bytes of heap memory allocated by this primitive.
	 */
	int		memoryUsed() const; //378

	/**
	 * Gets vertex position coordinates.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexPositions( int index, math::float4* data, int count ) const; //388

	/**
	 * Gets vertex normals.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexNormals( int index, math::float4* data, int count ) const; //398

	/**
	 * Gets vertex diffuse RGBA colors.
	 * Colors are returned in [0,255] range.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexDiffuseColors( int index, math::float4* data, int count ) const; //409

	/**
	 * Gets vertex specular RGBA colors.
	 * Colors are returned in [0,255] range.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexSpecularColors( int index, math::float4* data, int count ) const; //420

	/**
	 * Gets vertex tangents.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexTangents( int index, math::float4* data, int count ) const; //430

	/**
	 * Gets vertex bone blending weights used in skinning.
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexBoneWeights( int index, math::float4* data, int count ) const; //438

	/**
	 * Gets vertex bone blending indices used in skinning.
	 * @param index First vertex to get.
	 * @param data Vertex data.
	 * @param count Vertex count.
	 */
	void	getVertexBoneIndices( int index, math::float4* data, int count ) const; //446

	/**
	 * Gets vertex texture coordinates.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index First vertex to get.
	 * @param layer Texture layer index.
	 * @param data Texture coordinate data.
	 * @param count Texture coordinate count.
	 */
	void	getVertexTextureCoordinates( int index, int layer, math::float4* data, int count ) const; //457

	/**
	 * Gets primitive vertex indices.
	 * Primitive needs to be locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param index Index of the first index to get.
	 * @param data Index data.
	 * @param count Number of indices to get.
	 */
	void	getIndices( int index, int* data, int count ) const; //467

	/**
	 * Returns distances of individual triangle (in world space) to specified world space point.
	 * Distance is computed from triangle center.
	 * Assumes that the primitive is locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param worldpos World space reference point.
	 * @param worldtm World transform (if any).
	 * @param worldtm Model-to-world transform if any.
	 * @param boneworldtm Bone-to-world transforms if any.
	 * @param boneworldtmcount Number of bone-to-world transforms.
	 * @param trix [out] Receives triangle indices from 0 to n.
 	 * @param tridist [out] Receives squared triangle center distances to specified world space point.
	 * @param tricount Number of triangles in primitive.
	 */
	void	getTriangleDistances( const math::float3& worldpos, const math::float4x4& worldtm, const math::float4x4* boneworldtm, int boneworldtmcount, uint16_t* trix, float* tridist, int tricount ) const; //483

	/**
	 * Computers axis aligned bounding box center point of the primitive.
	 * Center point is computed from all vertices and their bounding box.
	 * Assumes that the primitive is locked for reading before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @return Axis aligned bounding box center point of the primitive.
	 */
	math::float3			center() const; //492

	bool vertexTextureCoordinateScaleBiasIsIdentity() const; //494

	/**
	 * Returns vertex texture coordinate scale/bias.
	 */
	const math::float4&		vertexTextureCoordinateScaleBias() const; //499

	/**
	 * Returns vertex position scale/bias.
	 */
	const math::float4&		vertexPositionScaleBias() const; //504

	/**
	 * Tries to find two set of faces which divide primitive so that
	 * maximum of n bones are used by a single face set.
	 * Note that you might need to do this iteratively to if splitted
	 * primitives has still too many bones.
	 * The function assumes that the primitive bone indices are packed, i.e.
	 * optimized to use usedBoneArray() and usedBones().
	 * This function needed mainly by the exporters.
	 * Requires that the vertices can be locked for reading.
	 *
	 * @param maxbones Maximum count for used bones of individual primitive.
	 * @param faceset1 [out] Receives the first face set (1 index/triangle).
	 * @param faceset2 [out] Receives the second face set (1 index/triangle).
	 */
	void	findSplit( int maxbones, std::vector<int>& faceset1, std::vector<int>& faceset2 ) const; //520

	/**
	 * Returns bounding box min.
	 */
	const math::float3&		boundMin() const; //525

	/**
	 * Returns bounding box max.
	 */
	const math::float3&		boundMax() const; //530

	/**
	 * Returns bounding radius.
	 */
	float						boundRadius() const; //535

protected:
	/** Non-virtual version of vertices(), for optimization. */
	int						vertexCount() const		{return m_vertices;} //539
	
	/** Non-virtual version of vertexRangeBegin(), for optimization. */
	int						vertexBegin() const		{return m_vertexRangeBegin;} //542
	
	/** Non-virtual version of vertexRangeEnd(), for optimization. */
	int						vertexEnd() const		{return m_vertexRangeEnd;} //545
	
	/** Non-virtual version of indices(), for optimization. */
	int						indexCount() const		{return m_indices;} //548
	
	/** Non-virtual version of indexRangeBegin(), for optimization. */
	int						indexBegin() const		{return m_indexRangeBegin;} //551
	
	/** Non-virtual version of indexRangeEnd(), for optimization. */
	int						indexEnd() const		{return m_indexRangeEnd;} //554
	
	/** Allocates device vertex buffer. */
	virtual void			allocate( const VertexFormat& vf, int vertices, int indices ); //557

	/** Allocates device vertex buffer. */
	virtual void			deallocate(); //560
	
	bool					m_interleaved; //562

private:
	enum { BUFFER_HEADER_SIZE = ((VertexFormat::DT_SIZE+48)*4+15&~15) }; //Previously 64, idk how this was generated
	
	/** 
	 * Default data buffer or 0 if not used. 
	 * One buffer for each vertex component, 0 allowed if component not exist. 
	 * Buffer index [DT_SIZE] has indices if any. 
	 * If default data buffer is not used then allocate() and deallocate() methods 
	 * are overriden by derived class, as well as getVertexDataPtr() and getIndexDataPtr().
	 */
	math::float4			m_posScaleBias; //574
	math::float4			m_texcoordScaleBias; //575
	math::float3			m_boundMin; //576
	math::float3			m_boundMax; //577
	float					m_boundRadius; //578
	uint8_t**				m_sysMemData; //579
	uint8_t*				m_usedBone; //580
	int						m_vertices; //581
	int						m_indices; //582
	int						m_vertexRangeBegin; //583
	int						m_vertexRangeEnd; //584
	int						m_indexRangeBegin; //585
	int						m_indexRangeEnd; //586
	gr::VertexFormat		m_vf; //587
	uint8_t					m_usedBones; //588
	bool					m_texcoordScaleBiasIsIdentity;//589

	/** Resets primitive to original (uninitialized) state. */
	void			reset(); //592

	/**
	 * Re-orders primitive triangles.
	 * Assumes that the primitive is locked for reading and writing before calling this method.
	 * @see NS(ContextObject,Lock)
	 * @param order Triangle indices representing new order. Size must be number of indices / 3.
	 * @param buffer Temporary buffer. Size must be at least number of indices.
	 */
	void			reorderTriangles( const uint16_t* order, uint16_t* buffer ); //601

	/** Returns number of bytes used by vertex data. */
	int				vertexDataSize() const; //604
};
	
	
} // gr


#endif // _GR_DIPRIMITIVE_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
