#ifndef _GR_DX11_PRIMITIVE_H
#define _GR_DX11_PRIMITIVE_H

#include <gr/Shader.h>
#include <gr/Context.h>
#include <gr/VertexFormat.h>
#include <gr/impl/DIPrimitive.h>
#include <math/float4.h>
//#include "DX_common.h"


namespace math
{ 
	class float4;}
	

namespace gr
{
	

class Shader;
class DX11_Shader;
class DX11_Context;
	
	
/**
 * DirectX geometry primitive.
 */
class DX11_Primitive : //0x130 bytes.
	public DIPrimitive
{
public:
	DX11_Primitive( DX11_Context* context, PrimType prim, const VertexFormat& vf, int vertices, int indices, NS(gr,Context)::UsageFlags usage );
	~DX11_Primitive();

	void	setShader( Shader* fx );

	/**
	 * Renders the primitive.
	 */
	void	render();

	/**
	 * Returns pointer to vertex data of specified component.
	 * Primitive needs to be locked before calling this method.
	 * WARNING: Low level operation, better to use getVertexPositions etc. methods.
	 */
	void	getVertexDataPtr( VertexFormat::DataType dt, uint8_t** data, int* pitch );

	/**
	 * Returns pointer to face index data.
	 * Primitive needs to be locked before calling this method.
	 * WARNING: Low level operation, better to use getIndices etc. methods.
	 */
	void	getIndexDataPtr( uint16_t** data, int* indexsize );

	/**
	 * Sets shader to be used while rendering the primitive.
	 */
	Shader*	shader() const;

	/**
	 * Returns number of triangles the primitive has in triangle list.
	 * NOTE: Only indexed and non-indexed triangle lists are counted,
	 * i.e. triangle strips, triangle fans and lines return 0 as triangle list size.
	 */
	int		triangleListSize() const	{return m_prim!=PRIM_TRI ? 0 : (indexCount()>0 ? indexCount()/3 : vertexCount()/3);}

	/**
	 * Returns primitive type.
	 */
	PrimType		type() const;

	/**
	 * Returns object string description.
	 */
	std::string	toString() const;

private:
	
	DX11_Context* m_context; //0x7C
	DX11_Shader* m_fx;
	PrimType m_prim; //0x84
	LockType m_locked;
	int m_usage; //0x8C

	/*
		_DWORD dword7C;
		_DWORD dword80;
		_DWORD dword84;
		_DWORD dword88;
		_DWORD dword8C;
		_BYTE byte90;
		_BYTE gap91[71];
		_DWORD dwordD8;
		_DWORD dwordDC;
		_DWORD dwordE0;
		__declspec(align(8)) _DWORD dwordE8;
		_DWORD dwordEC;
		_DWORD dwordF0;
		_DWORD dwordF4;
		_BYTE gapF8[4];
		_BYTE byteFC;
		_DWORD dword100;
		_DWORD dword104;
		_DWORD dword108;
		_DWORD dword10C;
		_BYTE gap110[8];
		_DWORD dword118;
		_DWORD dword11C;
		_BYTE gap120[4];
		_DWORD dword124;
		_DWORD dword128;
		_DWORD dword12C;
	*/

	void		deviceLost();
	void		deviceReset();
	void		allocate( const VertexFormat& vf, int vertices, int indices );
	void		deallocate();
	void		lock( LockType lock );
	void		unlock();
	bool		createVertexBuffer();
	bool		createIndexBuffer();
	int			setupDeviceVertexDataOffset( int offset, VertexFormat::DataType dt );
	void		setupDeviceVertexFormat();
	LockType	locked() const;
	VertexFormat validateDeviceVertexFormat( const VertexFormat& origvf ) const;

	DX11_Primitive( const DX11_Primitive& );
	DX11_Primitive& operator=( const DX11_Primitive& );
};
	
	
} // gr


#endif // _GR_DX11_PRIMITIVE_H