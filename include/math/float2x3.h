#ifndef _MATH_FLOAT2X3_H
#define _MATH_FLOAT2X3_H


#include <lang/pp.h>
#include <math/float3.h>
#include <lang/assert.h>


BEGIN_NAMESPACE(math)

class float3x3;

/**
 * 2x3 column-major matrix of scalar type float.
 * NOTE: The class behaves like C basic types what it comes to initialization
 * so default constructor leaves the components to unspecified value.
 * 
 * @ingroup math
 */
class float2x3
{
public:

#ifdef _DEBUG
	/** Constructs undefined matrix.*/
	float2x3()																		{float v = getNaN(); for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) m[i][j] = v;}
#else
	float2x3()																		{}
#endif

	/** Identity matrix multiplied with specified scalar. */
	explicit float2x3(float diagonal); //27

	/** Affine tm from generic 3x3. */
	explicit float2x3(const float3x3& o); //30
	
	/** Matrix construction from elements. */
	float2x3( const float m00, const float m01, const float m02,
		const float m10, const float m11, const float m12 );

	/**  */
	float2x3( float , const float2& );

	/**  */
	float2x3(float, const float2&, const float2&);

	/**  */
	float2x3(const float2&, const float2&);

	/**  */
	float2x3(const float2&, const float2&, const float2&);

	/** Component-wise addition of matrices.*/
	float2x3&		operator+=( const float2x3& other )							{for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) m[i][j] += other.m[i][j]; return *this;}
	
	/** Component-wise subtraction of matrices.*/
	float2x3&		operator-=( const float2x3& other )							{for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) m[i][j] -= other.m[i][j]; return *this;}
	
	/** Sets element at (row,column) in the matrix.*/
	void			set( int row, int column, float value )							{m[row][column]=value;}

	/** Sets ith column of the matrix. */
	void			setColumn( int i, const float2& c )							{m[0][i]=c[0]; m[1][i]=c[1]; m[2][i]=c[2];}

	/** Sets ith row of the matrix. */
	void			setRow( int i, const float3& c )								{m[i][0]=c[0]; m[i][1]=c[1]; m[i][2]=c[2];}

	/**  */
	void            setRotation(const float2& rot);

	/**  */
	void            setRotation(float rot);

	/** Sets right column (excluding the last row) of the matrix. */
	void            setTranslation(const float2& t);

	/**
	 * Sets this matrix as inverse transform of float(rot,t).
	 * Assumes that the matrix is orthonormal.
	 */
	void            setInverseOrthonormalTransform(const float2& rot, const float2& t);

	/**  */
	void            setReflection(const float3& );

	 /** Access element at (row,column) in the matrix.*/
    float&          operator()( int row, int column )                               {assert(row<2&&column<3); return m[row][column];}

	/** Returns this matrix multiplied with a scalar.*/
    float2x3        operator*( float s ) const                                      {float2x3 a; for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) a.m[i][j] = m[i][j] * s; return a;}

	/** Component-wise equality.*/
    bool            operator==( const float2x3& other ) const                       {for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) if ( m[i][j] != other.m[i][j] ) return false; return true;}
     
    /** Component-wise inequality.*/
    bool            operator!=( const float2x3& other ) const                       {for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) if ( m[i][j] != other.m[i][j] ) return true; return false;}

	/** Matrix multiplication.*/
    float2x3        operator*( const float2x3& other ) const;

	/** Returns component-wise addition of matrices.*/
    float2x3        operator+( const float2x3& other ) const                        {float2x3 a; for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) a.m[i][j] = m[i][j] + other.m[i][j]; return a;}
     
    /** Returns component-wise subtraction of matrices.*/
	float2x3        operator-( const float2x3& other ) const                        {float2x3 a; for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) a.m[i][j] = m[i][j] - other.m[i][j]; return a;}
 
    /** Returns component-wise negation.*/
	float2x3        operator-() const                                               {float2x3 a; for ( int i = 0 ; i < 2 ; ++i ) for ( int j = 0 ; j < 3 ; ++j ) a.m[i][j] = -m[i][j]; return a;}
 
    /* Matrix multiplication with 4-vector as 1-column matrix.*/
    float3          operator*( const float3& v ) const;
 
    /** Access element at (row,column) in the matrix.*/
    const float&    operator()( int row, int column ) const                         {assert(row<2&&column<3); return m[row][column];}

	/** Returns element at (row,column) in the matrix.*/
	float			get( int row, int column ) const								{return m[row][column];}

	/** Returns ith column of the matrix. */
	float2			getColumn( int i ) const										{float2 d; d[0]=m[0][i]; d[1]=m[1][i]; d[2]=m[2][i]; return d;}

	/** Returns ith row of the matrix. */
	const float3&	getRow( int i ) const											{return *reinterpret_cast<const float3*>(m[i]);}

	/**  */
	float getRotationRadians(  ) const;

	/**  */
	float2 getRotationFloat2(  ) const;

	 /** Returns top-right 2x1 submatrix. */
    float2          translation() const                                             {return float2( m[0][2], m[1][2] );}
 
    /** Returns top-right 2x1 submatrix. */
    void            getTranslation( NS(math,float2)* t ) const                      {t->x=m[0][2]; t->y=m[1][2];}

	/**  */
	float2			scale() const;

	/**  */
	float2			transform(const float2& v) const;

	/**  */
	float3			transform(const float3& v) const;

	/**  */
	void			transform(const float2& v, float2* v1) const;

	/**  */
	void			transform(const float3& v, float3* v1) const;

	/**  */
    float2          rotate( const float2& v ) const;
 
    /**  */
    void            rotate( const float2& v, float2* v1 ) const;

	/** Returns true if all components are in finite range. */
    bool            finite() const;

	/** Returns determinant of 2x3 top left sub-matrix. */
	float           determinant2() const;

	/** Returns inverse transform. */
	float2x3        inverse() const;

private:
	float			m[2][3]; //165
};


END_NAMESPACE() // math


#endif // _MATH_FLOAT2X3_H

// Copyright (C) 2004-2006 Pixelgene Ltd. All rights reserved. Consult your license regarding permissions and restrictions.
