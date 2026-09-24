#ifndef _GR_COLOR_H
#define _GR_COLOR_H

#include <lang/Object.h>
#include <math/float4.h>

BEGIN_NAMESPACE(gr)

class Color :
	public lang::Object
{
public:
	explicit Color( unsigned int color );
	
	Color( float alpha, float red, float green, float blue);
	
	Color( const NS(math, float4) & color );
	
	~Color( );
	
	float red( ) const;
	
	float green( ) const;
	
	float blue( ) const;
	
	float alpha( ) const;
	
	NS(math, float4) getColorAsFloat4( ) const;
	
	unsigned int getColorAsInt( ) const;
	
	void setRed( float );
	
	void setGreen( float );
	
	void setBlue( float );
	
	void setAlpha( float );
	
	void setColor( const NS(math, float4)& );
	
	void setColor( unsigned int color );
	
	Color& operator+=( const Color& );
	
	Color& operator*=( const Color& );
	
	Color& operator+( const Color& );
	
	Color& operator*( const Color& rhs);
private:
	NS(math, float4) m_color;
};

}

#endif