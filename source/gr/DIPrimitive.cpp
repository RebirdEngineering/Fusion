#include <gr/impl/DIPrimitive.h>
#include <gr/impl/SortBuffer.h>
#include <gr/VertexFormat.h>
#include <lang/Math.h>
#include <lang/Float.h>
#include <lang/Debug.h>
#include <math/float4.h>
#include <math/float4x4.h>
//Is std::sort correct?

using namespace lang;
using namespace math;


namespace gr
{


DIPrimitive::DIPrimitive() :
	m_interleaved( true ),
	m_posScaleBias(1,0,0,0),
	m_texcoordScaleBias(1,0,0,0),
	m_boundMin(0,0,0),
	m_boundMax(0,0,0),
	m_boundRadius(0),
	m_sysMemData( 0 ),
	m_usedBone( 0 ),
	m_vertices( 0 ),
	m_indices( 0 ),
	m_vertexRangeBegin( 0 ),
	m_vertexRangeEnd( 0 ),
	m_indexRangeBegin( 0 ),
	m_indexRangeEnd( 0 ),
	m_vf(),
	m_usedBones( 0 ),
	m_texcoordScaleBiasIsIdentity( true )
{
}

DIPrimitive::~DIPrimitive() //39-42
{
	reset(); //41
}

void DIPrimitive::reset()
{
	m_usedBones = 0;
	m_vf = VertexFormat();
	m_indices = 0;
	m_vertices = 0;
	m_vertexRangeBegin = 0;
	m_vertexRangeEnd = 0;
	m_indexRangeBegin = 0;
	m_indexRangeEnd = 0;

	if ( 0 != m_usedBone )
	{
		delete[] m_usedBone; 
		m_usedBone = 0;
	}

	deallocate();
}

void DIPrimitive::setVertexRangeBegin( int begin ) //64
{
	assert( begin >= 0 && begin < int(m_vertices) ); //[NOTE] Line 72
	m_vertexRangeBegin = begin;
}

void DIPrimitive::setVertexRangeEnd( int end ) //70
{
	assert( end >= 0 && end <= int(m_vertices) ); //[NOTE] Line 78
	m_vertexRangeEnd = end;
}

void DIPrimitive::setIndexRangeBegin( int begin ) //76
{
	assert( begin >= 0 && begin < int(m_indices) ); //[NOTE] Line 84
	m_indexRangeBegin = (uint16_t)begin;
}

void DIPrimitive::setIndexRangeEnd( int end ) //82
{
	assert( end >= 0 && end <= int(m_indices) ); //[NOTE] Line 90
	m_indexRangeEnd = (uint16_t)end;
}

int	DIPrimitive::vertexRangeBegin() const
{
	return m_vertexRangeBegin;
}

int	DIPrimitive::vertexRangeEnd() const
{
	return m_vertexRangeEnd;
}

int DIPrimitive::indexRangeBegin() const
{
	return m_indexRangeBegin;
}

int DIPrimitive::indexRangeEnd() const
{
	return m_indexRangeEnd;
}

void DIPrimitive::setFormat( const VertexFormat& vf, int vertices, int indices ) //108
{
	assert( vertices > 0 && vertices < 10000000 ); //[NOTE] Line 116
	assert( indices % 3 == 0 && indices < 0x10000 ); //[NOTE] Line 119

	reset(); //116

	m_vf = vf;
	m_vertices = vertices;
	m_indices = (uint16_t)indices;
	m_vertexRangeBegin = 0;
	m_vertexRangeEnd = vertices;
	m_indexRangeBegin = 0;
	m_indexRangeEnd = (uint16_t)indices;

	allocate( vf, vertices, indices );
}

void DIPrimitive::setVertexData( VertexFormat::DataType dt, int index, //129
	const void* data, VertexFormat::DataFormat df, int count ) //130
{
	VertexFormat::DataFormat dstdf = vf().getDataFormat(dt); //32
	assert( VertexFormat::DF_NONE != dstdf ); //[NOTE] Line 139
	if ( VertexFormat::DF_NONE == dstdf )
		return;

	uint8_t* dst; //137
	int dstpitch; //138
	getVertexDataPtr( dt, &dst, &dstpitch );
	dst += dstpitch*index;

	VertexFormat::copyData( dst, dstpitch, dstdf, data, VertexFormat::getDataSize(df), df, count );
}

void DIPrimitive::setVertexData( VertexFormat::DataType dt, int index, const float4* data, int count ) //145
{
	setVertexData( dt, index, data, VertexFormat::DF_V4_32, count );
}

void DIPrimitive::setIndexData( int v0, const void* data, int indexsize, int count ) //150
{
	assert( locked() & LOCK_WRITE ); //[NOTE] Line 158
	assert( v0 >= 0 && count > 0 && v0+count <= m_indices ); //[NOTE] Line 159
	assert( indexsize == 1 || indexsize == 2 || indexsize == 4 ); //[NOTE] Line 160

	uint16_t* d = 0; //156
	int isize = 0; //157
	getIndexDataPtr( &d, &isize );
	assert( isize == 2 ); //[NOTE] Line 165
	d += v0;

	switch ( indexsize )
	{
	case 1:{
		const uint8_t* s = reinterpret_cast<const uint8_t*>(data); //165
		for ( int i = 0 ; i < count ; ++i ) //166
			d[i] = s[i];
		break;}

	case 2:{
		const uint16_t* s = reinterpret_cast<const uint16_t*>(data); //171
		for ( int i = 0 ; i < count ; ++i ) //172
			d[i] = s[i];
		break;}

	case 4:{
		const uint32_t* s = reinterpret_cast<const uint32_t*>(data); //177
		for ( int i = 0 ; i < count ; ++i ) //178
		{
			d[i] = (uint16_t)s[i];
			assert( d[i] == s[i] ); //[NOTE] Line 187
		}
		break;}
	}
}

void DIPrimitive::getVertexData( VertexFormat::DataType dt, int index, float4* data, int count ) const //187
{
	assert( locked() & LOCK_READ ); //[NOTE] Line 195
	assert( index >= 0 && count > 0 && index+count <= m_vertices ); //[NOTE] Line 196
	assert( (unsigned)dt < (unsigned)VertexFormat::DT_SIZE ); //[NOTE] Line 197
	
	uint8_t* src = 0; //193
	int pitch = 0; //193
	const_cast<DIPrimitive*>(this)->getVertexDataPtr( dt, &src, &pitch );
	src += index * pitch;
	VertexFormat::DataFormat df = m_vf.getDataFormat( dt ); //197
	
	VertexFormat::copyData( data, sizeof(float4), VertexFormat::DF_V4_32, src, pitch, df, count );
}

void DIPrimitive::setVertexPositions( int index, const float4* data, int count ) //202
{
	setVertexData( VertexFormat::DT_POSITION, index, data, count ); //204
}

void DIPrimitive::setVertexTransformedPositions( int index, const float4* data, int count ) //207
{
	setVertexData( VertexFormat::DT_POSITIONT, index, data, count ); //209
}

void DIPrimitive::setVertexNormals( int index, const float4* data, int count ) //212
{
	setVertexData( VertexFormat::DT_NORMAL, index, data, count ); //214
}

void DIPrimitive::setVertexDiffuseColors( int index, const float4* data, int count ) //217
{
	setVertexData( VertexFormat::DT_DIFFUSE, index, data, count ); //219
}

void DIPrimitive::setVertexSpecularColors( int index, const float4* data, int count ) //222
{
	setVertexData( VertexFormat::DT_SPECULAR, index, data, count ); //224
}

void DIPrimitive::setVertexTangents( int index, const float4* data, int count ) //227
{
	setVertexData( VertexFormat::DT_TANGENT, index, data, count ); //229
}

void DIPrimitive::setVertexBoneWeights( int index, const float4* data, int count ) //232
{
	setVertexData( VertexFormat::DT_BONEWEIGHTS, index, data, count ); //234
}

void DIPrimitive::setVertexBoneIndices( int index, const float4* data, int count ) //237
{
	setVertexData( VertexFormat::DT_BONEINDICES, index, data, count ); //239
}

void DIPrimitive::setVertexTextureCoordinates( int index, int layer, const float4* data, int count ) //242
{
	assert( layer >= 0 && layer < m_vf.textureCoordinates() ); //[NOTE] Line 250

	VertexFormat::DataType dt = (VertexFormat::DataType)(VertexFormat::DT_TEX0 + layer); //246
	setVertexData( dt, index, data, count ); //247
}

void DIPrimitive::setIndices( int index, const int* data, int count ) //250
{
	uint16_t* d = 0; //252
	int indexsize = 0; //253
	getIndexDataPtr( &d, &indexsize );
	assert( indexsize == 2 ); //[NOTE] Line 261

	d += index;
	for ( int i = 0 ; i < count ; ++i ) //258
	{
		uint16_t ix = (uint16_t)data[i]; //260
		assert( (int)ix == data[i] );		// ensure output == input //[NOTE] Line 267
		assert( (int)ix < m_vertices ); //[NOTE] Line 268
		d[i] = ix;
	}
}

int DIPrimitive::vertexSize() const
{
	int totalsize = 0;
	for ( int i = 0 ; i < VertexFormat::DT_SIZE ; ++i )
	{
		VertexFormat::DataFormat df = m_vf.getDataFormat( (VertexFormat::DataType)i );
		int buffersize = VertexFormat::getDataSize( df );
		totalsize += buffersize;
	}

	assert( totalsize <= 255 && "DIPrimitive supports only max 255 byte vertices" ); //[NOTE] Line 283
	return totalsize;
}

int DIPrimitive::vertexDataSize() const
{
	int totalsize = 0;
	for ( int i = 0 ; i < VertexFormat::DT_SIZE ; ++i )
	{
		VertexFormat::DataFormat df = m_vf.getDataFormat( (VertexFormat::DataType)i );
		int buffersize = VertexFormat::getDataSize( df, m_vertices );
		totalsize += buffersize;
	}
	return totalsize;
}

int DIPrimitive::indexSize() const
{
	return 2;
}

int DIPrimitive::memoryUsed() const
{
	return BUFFER_HEADER_SIZE + vertexDataSize() + indexSize()*indices();
}

void DIPrimitive::getVertexPositions( int index, float4* data, int count ) const //296
{
	getVertexData( VertexFormat::DT_POSITION, index, data, count );
}

void DIPrimitive::getVertexNormals( int index, float4* data, int count ) const //301
{
	getVertexData( VertexFormat::DT_NORMAL, index, data, count );
}

void DIPrimitive::getVertexDiffuseColors( int index, float4* data, int count ) const //306
{
	getVertexData( VertexFormat::DT_DIFFUSE, index, data, count );
}

void DIPrimitive::getVertexSpecularColors( int index, float4* data, int count ) const //311
{
	getVertexData( VertexFormat::DT_SPECULAR, index, data, count );
}

void DIPrimitive::getVertexTangents( int index, float4* data, int count ) const //316
{
	getVertexData( VertexFormat::DT_TANGENT, index, data, count );
}

void DIPrimitive::getVertexBoneWeights( int index, float4* data, int count ) const //321
{
	getVertexData( VertexFormat::DT_BONEWEIGHTS, index, data, count );
}

void DIPrimitive::getVertexBoneIndices( int index, float4* data, int count ) const //326
{
	getVertexData( VertexFormat::DT_BONEINDICES, index, data, count );
}

void DIPrimitive::getVertexTextureCoordinates( int index, int layer, float4* data, int count ) const //331
{
	assert( layer >= 0 && layer < m_vf.textureCoordinates() ); //[NOTE] Line 339

	VertexFormat::DataType dt = (VertexFormat::DataType)(VertexFormat::DT_TEX0 + layer); //335
	getVertexData( dt, index, data, count );
}

void DIPrimitive::getIndices( int index, int* data, int count ) const //339
{
	uint16_t* s = 0; //341
	int indexsize = 0; //242
	const_cast<DIPrimitive*>(this)->getIndexDataPtr( &s, &indexsize );
	assert( indexsize == 2 ); //[NOTE] Line 350

	s += index;
	for ( int i = 0 ; i < count ; ++i ) //347
		data[i] = s[i];
}

void DIPrimitive::packBones()
{
	assert( locked() & LOCK_READ ); //[NOTE] Line 359
	assert( 0 == m_usedBone ); // packBones is destructive and it can be done only once //[NOTE] Line 360

	if ( m_vf.hasData(VertexFormat::DT_BONEINDICES) ) //356
	{
		// count number of used bones
		bool boneused[MAX_BONES]; //359
		for ( int i = 0 ; i < MAX_BONES ; ++i ) //360
			boneused[i] = false;
		int vertices = this->m_vertices; //362
		m_usedBones = 0;
		for ( int i = 0 ; i < vertices ; ++i ) //364
		{
			float4 bw, bi; //366
			getVertexBoneWeights( i, &bw, 1 );
			getVertexBoneIndices( i, &bi, 1 );
			for ( int k = 0 ; k < 4 ; ++k ) //385
			{
				int ix = (int)bi[k]; //371
				assert( ix >= 0 && ix < MAX_BONES ); //[NOTE] Line 378
				if ( bw[k] > 0.f && !boneused[ix] )
				{
					assert( m_usedBones < MAX_BONES ); //[NOTE] Line 381
					boneused[ix] = true;
					++m_usedBones;
				}
			}
		}
		
		// build used bone list
		delete[] m_usedBone; m_usedBone=0;
		m_usedBone = new uint8_t[m_usedBones];
		int k = 0; //385
		for ( int i = 0 ; i < MAX_BONES ; ++i ) //386
		{
			if ( boneused[i] )
			{
				assert( k < int(m_usedBones) ); //[NOTE] Line 398
				m_usedBone[k++] = (uint8_t)i;
				assert( m_usedBone[k-1] == i ); // wrapped //[NOTE] Line 400
			}
		}
		assert( m_usedBones == k ); //[NOTE] Line 403

		// remap vertex bone indices to new bone list
		int bonemap[MAX_BONES]; //398
		for ( int i = 0 ; i < MAX_BONES ; ++i ) //399
			bonemap[i] = 0;
		for ( int i = 0 ; i < (int)m_usedBones ; ++i ) //401
			bonemap[ m_usedBone[i] ] = i;
		for ( int i = 0 ; i < vertices ; ++i ) //403
		{
			float4 bi; //405
			getVertexBoneIndices( i, &bi, 1 );
			for ( int k = 0 ; k < 4 ; ++k ) //407
			{
				int ix = (int)bi[k]; //409
				assert( ix >= 0 && ix < MAX_BONES ); //[NOTE] Line 418
				bi[k] = (float)bonemap[ix];
			}
			setVertexBoneIndices( i, &bi, 1 );
		}
	}
}

void DIPrimitive::setUsedBones( const uint8_t* usedbonearray, int usedbones ) //418
{
	assert( locked() & LOCK_WRITE ); //[NOTE] Line 428
	assert( usedbones >= 0 && usedbones < 0x100 ); //[NOTE] Line 429

	if ( m_usedBone != 0 )
	{
		delete[] m_usedBone;
		m_usedBone = 0;
	}
	
	m_usedBones = (uint8_t)usedbones;

	if ( usedbones > 0 )
	{
		m_usedBone = new uint8_t[usedbones];
		memcpy( m_usedBone, usedbonearray, usedbones );
	}
}

const uint8_t* DIPrimitive::usedBoneArray() const
{
	return m_usedBone;
}

int DIPrimitive::usedBones() const
{
	return m_usedBones;
}

int DIPrimitive::vertices() const
{
	return m_vertices;
}

int	DIPrimitive::indices() const
{
	return m_indices;
}

const VertexFormat&	DIPrimitive::vertexFormat() const
{
	return m_vf;
}

void DIPrimitive::allocate( const VertexFormat& vf, int vertices, int indices ) //463 | [NOTE] TODO
{
	assert( m_sysMemData == 0 ); //[NOTE] Line 473
	assert( m_vf == vf ); //[NOTE] Line 474

	// allocate memory for buffers
	int indexdatasize = indexSize() * indices; //469
	int memsize = BUFFER_HEADER_SIZE + vertexDataSize() + indexdatasize; //470
	uint8_t* mem = new uint8_t[ memsize ]; //471
	memset( mem, 0, memsize );
	m_sysMemData = reinterpret_cast<uint8_t**>(mem);
	
	// setup vbuffer table
	uint8_t* p = mem + BUFFER_HEADER_SIZE; //476
	for ( int i = 0 ; i < VertexFormat::DT_SIZE ; ++i ) //477
	{
		VertexFormat::DataType dt = (VertexFormat::DataType)i; //479
		VertexFormat::DataFormat df = vf.getDataFormat( dt ); //480
		
		m_sysMemData[i] = 0;
		if ( df != VertexFormat::DF_NONE )
		{
			m_sysMemData[i] = p;
			m_interleaved ? p += VertexFormat::getDataSizeAligned(df,vf.alignEach()) : p += VertexFormat::getDataSizeAligned(df,vf.alignEach()) * vertices;
		}
	}

	// setup index table
	m_sysMemData[VertexFormat::DT_SIZE] = (m_indices>0 ? p : 0);
	p += indexdatasize;
}

void DIPrimitive::deallocate()
{
	if ( 0 != m_sysMemData )
	{
		delete[] reinterpret_cast<uint8_t*>(m_sysMemData);	
		m_sysMemData = 0;
	}
}

void DIPrimitive::getVertexDataPtr( VertexFormat::DataType dt, uint8_t** data, int* pitch ) //509
{
	//Debug::printf( "getVertexDataPtr(%s)\n", VertexFormat::toString(dt) );
	assert( m_vf.hasData(dt) ); //[NOTE] Line 521 | 516 (ABS OSX 3.0.0)
	assert( locked() != LOCK_NONE ); //[NOTE] Line 522 | 517 (ABS OSX 3.0.0)

	*data = m_sysMemData[dt];
	*pitch = VertexFormat::getDataSize( m_vf.getDataFormat(dt) );
}

void DIPrimitive::getIndexDataPtr( uint16_t** data, int* indexsize ) //521
{
	assert( m_indices > 0 ); //[NOTE] Line 533
	assert( locked() != LOCK_NONE ); //[NOTE] Line 534
	assert( m_sysMemData[VertexFormat::DT_SIZE] != 0 && "No index data" ); //[NOTE] Line 535

	*data = reinterpret_cast<uint16_t*>( m_sysMemData[VertexFormat::DT_SIZE] );
	*indexsize = 2;
}

void DIPrimitive::sortFrontToBack( const float3& refpos, const float4x4& worldtm, //531
	const float4x4* boneworldtm, int boneworldtmcount, SortBuffer& tmp ) //532
{
	assert( indexCount() > 0 && "Only indexed primitives can be sorted" ); //[NOTE] Line 544

	int tricount = indexCount()/3; //536
	tmp.reset( tricount+indexCount(), tricount );
	uint16_t* intbuffer = tmp.intBuffer(); //538
	float* floatbuffer = tmp.floatBuffer(); //539

	getTriangleDistances( refpos, worldtm, boneworldtm, boneworldtmcount, intbuffer, floatbuffer, tricount );
	std::sort(intbuffer, intbuffer + tricount, SortLess(floatbuffer)); //542 | Correct?
	assert( floatbuffer[intbuffer[tricount-1]] >= floatbuffer[intbuffer[0]] ); //[NOTE] Line 553
	reorderTriangles( intbuffer, intbuffer+tricount );
}

void DIPrimitive::sortBackToFront( const float3& refpos, const float4x4& worldtm, //547
	const float4x4* boneworldtm, int boneworldtmcount, SortBuffer& tmp ) //548
{
	assert( indexCount() > 0 && "Only indexed primitives can be sorted" ); //[NOTE] Line 560

	int tricount = indexCount()/3; //552
	tmp.reset( tricount+indexCount(), tricount );
	uint16_t* intbuffer = tmp.intBuffer(); //554
	float* floatbuffer = tmp.floatBuffer(); //555

	getTriangleDistances( refpos, worldtm, boneworldtm, boneworldtmcount, intbuffer, floatbuffer, tricount );
	std::sort( intbuffer, intbuffer+tricount, SortGreater(floatbuffer) ); //558
	assert( floatbuffer[intbuffer[tricount-1]] <= floatbuffer[intbuffer[0]] ); //[NOTE] Line 569
	reorderTriangles( intbuffer, intbuffer+tricount );
}

void DIPrimitive::sortInsideOut( SortBuffer& tmp ) //563
{
	assert( indexCount() > 0 && "Only indexed primitives can be sorted" ); //[NOTE] Line 575

	int tricount = indexCount()/3; //567
	tmp.reset( tricount+indexCount(), tricount );
	uint16_t* intbuffer = tmp.intBuffer(); //569
	float* floatbuffer = tmp.floatBuffer(); //570

	const float4x4 id( 1.f ); //572
	getTriangleDistances( center(), id, 0, 0, intbuffer, floatbuffer, tricount );
	std::sort( intbuffer, intbuffer+tricount, SortLess(floatbuffer) ); //574
	assert( floatbuffer[intbuffer[tricount-1]] >= floatbuffer[intbuffer[0]] ); //[NOTE] Line 585
	reorderTriangles( intbuffer, intbuffer+tricount );
}

void DIPrimitive::sortOutsideIn( SortBuffer& tmp ) //568
{
	assert( indexCount() > 0 && "Only indexed primitives can be sorted" ); //[NOTE] Line 591

	int tricount = indexCount()/3; //583
	tmp.reset( tricount+indexCount(), tricount );
	uint16_t* intbuffer = tmp.intBuffer(); //585
	float* floatbuffer = tmp.floatBuffer(); //586

	const float4x4 id( 1.f ); //588
	getTriangleDistances( center(), id, 0, 0, intbuffer, floatbuffer, tricount );
	std::sort( intbuffer, intbuffer+tricount, SortGreater(floatbuffer) ); //590
	assert( floatbuffer[intbuffer[tricount-1]] <= floatbuffer[intbuffer[0]] ); //[NOTE] Line 601
	reorderTriangles( intbuffer, intbuffer+tricount );
}

float3 DIPrimitive::center() const
{
	assert( locked() != LOCK_NONE ); //[NOTE] Line 607
	
	float3 boxmax( -Float::MAX_VALUE, -Float::MAX_VALUE, -Float::MAX_VALUE ); //599
	float3 boxmin( Float::MAX_VALUE, Float::MAX_VALUE, Float::MAX_VALUE ); //600
	
	uint8_t* vposdata = 0; //602
	int vpospitch = 0; //603
	int vertices = m_vertices; //604
	const_cast<DIPrimitive*>(this)->getVertexDataPtr( VertexFormat::DT_POSITION, &vposdata, &vpospitch );
	VertexFormat::DataFormat vposdatafmt = m_vf.getDataFormat( VertexFormat::DT_POSITION );

	for ( int i = 0 ; i < vertices ; ++i ) //608
	{
		float4 v; //610
		VertexFormat::getData( vposdatafmt, vposdata, &v );

		for ( int k = 0 ; k < 3 ; ++k ) //613
		{
			boxmax[k] = Math::max( boxmax[k], v[k] ); //615
			boxmin[k] = Math::min( boxmin[k], v[k] ); //616
		}

		vposdata += vpospitch;
	}

	return (boxmax + boxmin) * .5f; //622
}

void DIPrimitive::getTriangleDistances( const NS(math,float3)& worldpos, const NS(math,float4x4)& worldtm, const NS(math,float4x4)* boneworldtm, int boneworldtmcount, uint16_t* trix, float* tridist, int tricount ) const //625
{
	assert( tricount == (indexCount() > 0 ? indexCount()/3 : vertexCount()/3) && "Invalid triangle count" ); //[NOTE] Line 637
	assert( locked() != LOCK_NONE ); //[NOTE] Line 638
	assert( boneworldtmcount >= 0 && boneworldtmcount < 256 ); boneworldtmcount=boneworldtmcount; //[NOTE] Line 639

	uint8_t* vposdata = 0; //631
	int vpospitch = 0; //632
	VertexFormat::DataFormat vposdatafmt = m_vf.getDataFormat( VertexFormat::DT_POSITION ); //633
	const_cast<DIPrimitive*>(this)->getVertexDataPtr( VertexFormat::DT_POSITION, &vposdata, &vpospitch );

	uint8_t* vboneindexdata = 0; //636
	uint8_t* vboneweightdata = 0; //637
	int vboneindexpitch = 0; //638
	int vboneweightpitch = 0; //639
	VertexFormat::DataFormat vboneindexdatafmt = m_vf.getDataFormat( VertexFormat::DT_BONEINDICES ); //640
	VertexFormat::DataFormat vboneweightdatafmt = m_vf.getDataFormat( VertexFormat::DT_BONEWEIGHTS ); //641
	if ( m_vf.hasData(VertexFormat::DT_BONEWEIGHTS) ) //642
	{
		const_cast<DIPrimitive*>(this)->getVertexDataPtr( VertexFormat::DT_BONEINDICES, &vboneindexdata, &vboneindexpitch );
		const_cast<DIPrimitive*>(this)->getVertexDataPtr( VertexFormat::DT_BONEWEIGHTS, &vboneweightdata, &vboneweightpitch );
	}

	float4 v0,v1,v2,v; //648
	float4 worldpos4(worldpos,1.f); //649
	float4 v0bi,v1bi,v2bi; //650
	float4 v0bw,v1bw,v2bw; //651

	if ( indexCount() > 0 ) //653
	{
		uint16_t* indexdata; //655
		int indexsize; //656
		const_cast<DIPrimitive*>(this)->getIndexDataPtr( &indexdata, &indexsize );

		if ( m_vf.hasData(VertexFormat::DT_BONEWEIGHTS) && boneworldtm != 0 ) //659
		{
			// indexed and skinned
			const int WEIGHTS_USED = 2; //662
			int i = 0; //663
			for ( int tri = 0 ; tri < tricount ; ++tri ) //664
			{
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i], &v0 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i+1], &v1 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i+2], &v2 );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata+vboneindexpitch*indexdata[i], &v0bi );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata+vboneindexpitch*indexdata[i+1], &v1bi );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata+vboneindexpitch*indexdata[i+2], &v2bi );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata+vboneweightpitch*indexdata[i], &v0bw );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata+vboneweightpitch*indexdata[i+1], &v1bw );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata+vboneweightpitch*indexdata[i+2], &v2bw );
				i += 3;

				v0.w = v1.w = v2.w = 1.f;
				v.x = v.y = v.z = 0.f;
				float4 sumw(0,0,0,0); //679
				for ( int k = 0 ; k < WEIGHTS_USED ; ++k ) //680
				{
					int ix0 = (int)v0bi[k]; //683
					int ix1 = (int)v1bi[k]; //684
					int ix2 = (int)v2bi[k]; //685
					assert( ix0 >= 0 && ix0 < boneworldtmcount ); //[NOTE] Line 695
					assert( ix1 >= 0 && ix1 < boneworldtmcount ); //[NOTE] Line 696
					assert( ix2 >= 0 && ix2 < boneworldtmcount ); //[NOTE] Line 697
					if ( k == (WEIGHTS_USED-1) )
					{
						v0bw[k] = 1.f - sumw[0];
						v1bw[k] = 1.f - sumw[1];
						v2bw[k] = 1.f - sumw[2];
					}
					else
					{
						sumw[0] += v0bw[k];
						sumw[1] += v1bw[k];
						sumw[2] += v2bw[k];
					}

					{
						const float4x4& m = boneworldtm[ix0]; //702
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f ); //703
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f ); //704
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f ); //705
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f ); //706
						v += float4( dot(r0,v0)+r3.x, dot(r1,v0)+r3.y, dot(r2,v0)+r3.z, 0.f ) * v0bw[k] * (1.f/3.f); //707
					}

					{
						const float4x4& m = boneworldtm[ix1]; //711
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f ); //712
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f ); //713
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f ); //714
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f ); //715
						v += float4( dot(r0,v1)+r3.x, dot(r1,v1)+r3.y, dot(r2,v1)+r3.z, 0.f ) * v1bw[k] * (1.f/3.f); //716
					}

					{
						const float4x4& m = boneworldtm[ix2]; //720
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f ); //721
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f ); //722
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f ); //723
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f ); //724
						v += float4( dot(r0,v2)+r3.x, dot(r1,v2)+r3.y, dot(r2,v2)+r3.z, 0.f ) * v2bw[k] * (1.f/3.f); //725
					}
				}
				v.w = 1.f;

				trix[tri] = (uint16_t)tri;
				tridist[tri] = (v-worldpos4).lengthSquared(); //731
			}
		}
		else
		{
			// indexed and non-skinned
			int i = 0; //737
			for ( int tri = 0 ; tri < tricount ; ++tri ) //738
			{
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i], &v0 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i+1], &v1 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch*indexdata[i+2], &v2 );
				i += 3;

				v = (v0+v1+v2)*(1.f/3.f); //745
				v.w = 1.f;
				v = worldtm.transform( v );
				trix[tri] = (uint16_t)tri;
				tridist[tri] = (v-worldpos4).lengthSquared(); //749
			}
		}
	}
	else
	{
		const int vpospitch2 = vpospitch+vpospitch; //755
		const int vpospitch3 = vpospitch+vpospitch2; //756
		const int vboneindexpitch2 = vboneindexpitch+vboneindexpitch; //757
		const int vboneweightpitch2 = vboneweightpitch+vboneweightpitch; //758

		if ( m_vf.hasData(VertexFormat::DT_BONEWEIGHTS) ) //760
		{
			// non-indexed and skinned
			const int WEIGHTS_USED = 2; //763
			for ( int tri = 0 ; tri < tricount ; ++tri )
			{
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch, &v0 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch2, &v1 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch3, &v2 );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata, &v0bi );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata+vboneindexpitch, &v1bi );
				VertexFormat::getData( vboneindexdatafmt, vboneindexdata+vboneindexpitch2, &v2bi );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata, &v0bw );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata+vboneweightpitch, &v1bw );
				VertexFormat::getData( vboneweightdatafmt, vboneweightdata+vboneweightpitch2, &v2bw );

				v0.w = v1.w = v2.w = 1.f;
				v.x = v.y = v.z = 0.f;
				float4 sumw(0,0,0,0); //778
				for ( int k = 0 ; k < WEIGHTS_USED ; ++k ) //779
				{
					int ix0 = (int)v0bi[k]; //781
					int ix1 = (int)v1bi[k]; //782
					int ix2 = (int)v2bi[k]; //783
					assert( ix0 >= 0 && ix0 < boneworldtmcount ); //[NOTE] Line 794
					assert( ix1 >= 0 && ix1 < boneworldtmcount ); //[NOTE] Line 795
					assert( ix2 >= 0 && ix2 < boneworldtmcount ); //[NOTE] Line 796
					if ( k == (WEIGHTS_USED-1) )
					{
						v0bw[k] = 1.f - sumw[0];
						v1bw[k] = 1.f - sumw[1];
						v2bw[k] = 1.f - sumw[2];
					}
					else
					{
						sumw[0] += v0bw[k];
						sumw[1] += v1bw[k];
						sumw[2] += v2bw[k];
					}

					{
						const float4x4& m = boneworldtm[ix0]; //801
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f ); //802
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f ); //803
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f ); //804
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f ); //805
						v += float4( dot(r0,v0)+r3.x, dot(r1,v0)+r3.y, dot(r2,v0)+r3.z, 0.f ) * v0bw[k] * (1.f/3.f); //806
					}

					{
						const float4x4& m = boneworldtm[ix1];
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f );
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f );
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f );
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f );
						v += float4( dot(r0,v1)+r3.x, dot(r1,v1)+r3.y, dot(r2,v1)+r3.z, 0.f ) * v1bw[k] * (1.f/3.f);
					}

					{
						const float4x4& m = boneworldtm[ix2];
						float4 r0( m(0,0), m(0,1), m(0,2), 0.f );
						float4 r1( m(1,0), m(1,1), m(1,2), 0.f );
						float4 r2( m(2,0), m(2,1), m(2,2), 0.f );
						float4 r3( m(3,0), m(3,1), m(3,2), 0.f );
						v += float4( dot(r0,v2)+r3.x, dot(r1,v2)+r3.y, dot(r2,v2)+r3.z, 0.f ) * v2bw[k] * (1.f/3.f);
					}
				}
				v.w = 1.f;

				trix[tri] = (uint16_t)tri;
				tridist[tri] = (v-worldpos4).lengthSquared();
			}
		}
		else
		{
			// non-indexed and non-skinned
			for ( int tri = 0 ; tri < tricount ; ++tri )
			{
				VertexFormat::getData( vposdatafmt, vposdata, &v0 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch, &v1 );
				VertexFormat::getData( vposdatafmt, vposdata+vpospitch2, &v2 );
				v = (v0+v1+v2)*(1.f/3.f);
				v.w = 1.f;
				v = worldtm.transform( v );
				trix[tri] = (uint16_t)tri;
				tridist[tri] = (v-worldpos4).lengthSquared();
				vposdata += vpospitch3;
			}
		}
	}
}

void DIPrimitive::reorderTriangles( const uint16_t* order, uint16_t* buffer ) //852
{
	assert( indexCount() > 0 && "Only indexed primitives can be re-ordered!" ); //[NOTE] Line 864

	if ( indexCount() > 0 ) //856
	{
		int tricount = indexCount()/3; //858

		uint16_t* indexdata; //860
		int indexsize; //861
		getIndexDataPtr( &indexdata, &indexsize );

		int ind = 0; //864
		for ( int i = 0 ; i < tricount ; ++i ) //865
		{
			int newtri = order[i]; //867
			assert( newtri >= 0 && newtri < tricount ); //[NOTE] Line 878
			int newind = unsigned(newtri) + unsigned(newtri)*2U; //869

			buffer[ind] = indexdata[newind];
			buffer[ind+1] = indexdata[newind+1];
			buffer[ind+2] = indexdata[newind+2];
			ind += 3;
		}

		ind = 0;
		for ( int i = 0 ; i < tricount ; ++i ) //878
		{
			indexdata[ind] = buffer[ind];
			indexdata[ind+1] = buffer[ind+1];
			indexdata[ind+2] = buffer[ind+2];
			ind += 3;
		}
	}
}

void DIPrimitive::findSplit( int maxbones,
	std::vector<int>&	faceset1, std::vector<int>& faceset2 ) const //Not on iOS
{
	assert( usedBones() > 0 ); //[NOTE] Line 901

	Lock lk( const_cast<DIPrimitive*>(this), LOCK_READ );

	std::vector<bool> boneset;
	int			bonesetsize = 0;
	std::vector<int>	facebones;
	std::vector<int>	newfacebones;

	// prepare bone set
	boneset.resize( usedBones(), false );
	faceset1.clear();
	faceset2.clear();

	// prepare source list of faceset1
	const int triangles = indices()/3;
	for ( int i = 0 ; i < triangles ; ++i )
		faceset2.push_back( i );

	// while room for more bones
	while ( faceset2.size() > 0 )
	{
		// select first face which expands bone set least
		int newface = -1;
		newfacebones.resize( usedBones() );
		for ( int i = 0 ; i < faceset2.size() ; ++i )
		{
			int face = faceset2[i];
			int ind[3];
			getIndices( face*3, ind, 3 );
			facebones.clear();
			for ( int k = 0 ; k < 3 ; ++k )
			{
				float4 boneind, bonew;
				getVertexBoneIndices( ind[k], &boneind, 1 );
				getVertexBoneWeights( ind[k], &bonew, 1 );
				for ( int n = 0 ; n < 4 ; ++n )
				{
					if ( bonew[n] > 0.f )
					{
						int boneix = (int)boneind[n];
						if ( !boneset[boneix] )
							facebones.push_back( boneix );
					}
				}
			}

			std::sort( facebones.begin(), facebones.end() );
			facebones.resize( unique(facebones.begin(),facebones.end())-facebones.begin() );

			if ( facebones.size() < newfacebones.size() )
			{
				newface = i;
				newfacebones = facebones;
			}
		}

		// check if max bone count would be exceeded
		if ( bonesetsize+newfacebones.size() > maxbones )
			break;

		// expand bone set
		for ( int i = 0 ; i < newfacebones.size() ; ++i )
		{
			assert( !boneset[ newfacebones[i] ] && "Bone already used?" ); //[NOTE] Line 965
			boneset[ newfacebones[i] ] = true;
			++bonesetsize;
		}

		// resize face sets
		int face = faceset2[newface];
		faceset2.pop_back( );
		faceset1.push_back( face );
	}
}

void DIPrimitive::setVertexPositionScaleBias( const NS(math,float4)& scalebias ) //967
{
	m_posScaleBias = scalebias;
}

void DIPrimitive::setVertexTextureCoordinateScaleBias( const NS(math,float4)& scalebias ) //972
{
	m_texcoordScaleBias = scalebias;
}

bool DIPrimitive::vertexTextureCoordinateScaleBiasIsIdentity() const
{
	return m_texcoordScaleBiasIsIdentity;
}

const float4& DIPrimitive::vertexTextureCoordinateScaleBias() const
{
	return m_texcoordScaleBias;
}

const float4& DIPrimitive::vertexPositionScaleBias() const
{
	return m_posScaleBias;
}

const float3& DIPrimitive::boundMin() const
{
	return m_boundMin;
}

const float3& DIPrimitive::boundMax() const
{
	return m_boundMax;
}

float DIPrimitive::boundRadius() const
{
	return m_boundRadius;
}

void DIPrimitive::setBound( const float3& boundmin, const float3& boundmax, float boundradius ) //1008
{
	m_boundMin = boundmin;
	m_boundMax = boundmax;
	m_boundRadius = boundradius;
}


} // gr

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
