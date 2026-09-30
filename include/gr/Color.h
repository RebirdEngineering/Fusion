#ifndef _GR_COLOR_H
#define _GR_COLOR_H

#include <math/float4.h>

namespace gr
{

class Color //11
{
public:
	explicit Color( unsigned int color ); //27
	
	/*
	* 
	* @param alpha 
	* @param red
	* @param green
	* @param blue
	*/
	Color( float alpha, float red, float green, float blue); //36
	
	/*
	*
	* @param color
	*/
	Color( const NS(math, float4) & color ); //42
	
	~Color( ); //44
	
	float red( ) const; //49
	
	float green( ) const; //53
	
	float blue( ) const; //57
	
	float alpha( ) const; //61
	
	NS(math, float4) getColorAsFloat4( ) const; //66
	
	unsigned int getColorAsInt( ) const; //72
	
	void setRed( float ); //78
	
	void setGreen( float ); //83
	
	void setBlue( float ); //88
	
	void setAlpha( float ); //93
	
	void setColor( const NS(math, float4)& ); //99
	
	void setColor( unsigned int color ); //105

	void setColor( float, float, float, float ); //114
	
	Color& operator+=( const Color& rhs ); //119 | Assumption
	
	Color& operator*=( const Color& rhs ); //124
	
	Color operator+( const Color& rhs ); //129 | Assumption
	
	Color operator*( const Color& rhs ); //134

private:
	NS(math, float4) m_color; //137
};

}

#endif