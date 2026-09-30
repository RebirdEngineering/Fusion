#include <gr/Color.h>

using namespace math;

namespace gr
{

Color::Color(unsigned int color) //5
{
	setColor(color); //7
}

Color::Color(float alpha, float red, float green, float blue) //10
{
	m_color = float4(alpha, red, green, blue); //12
}

Color::Color(const float4& color) //15
{
	m_color = color;
}

Color::~Color() //-22
{
}

float Color::red() const
{
	return m_color.x;
}

float Color::green() const
{
	return m_color.y;
}

float Color::blue() const
{
	return m_color.z;
}

float Color::alpha() const
{
	return m_color.w;
}

float4 Color::getColorAsFloat4() const //Not seen in ABS 4.1.0 iOS
{
	/*float4 color;
	int alphaBits = alpha();
	int redBits = red();
	int greenBits = green();
	int blueBits = blue();
	color = float4(alphaBits, redBits, greenBits, blueBits);
	return color;*/
	assert("unsigned int Color::getColorAsInt() const was not yet decompiled. Returning blank vector4 color.");
	return float4();
}

unsigned int Color::getColorAsInt() const
{
	/*float4 color = saturate(color); //71
	int alphaBits = alpha(); //72
	int redBits = red(); //73
	int greenBits = green(); //74
	int blueBits = blue(); //75
	color.x = alphaBits;
	color.y = redBits;
	color.z = greenBits;
	color.w = blueBits;
	return color;*/
	assert("unsigned int Color::getColorAsInt() const was not yet decompiled.");
	return 0;
}

void Color::setColor(unsigned int color) //85
{
	/*m_color.x = color >> 24 & 0xFF;
	m_color.y = color >> 16 & 0xFF;
	m_color.z = color >> 8 & 0xFF;
	m_color.w = color & 0xFF;*/

	/*m_color.x = (BYTE1(color)) / 255.0f;
	m_color.y = (BYTE2(color)) / 255.0f;
	m_color.z = (BYTE3(color)) / 255.0f;
	m_color.w = (HIBYTE(color)) / 255.0f;*/

	//PCF version
	m_color.x = (float)(color >> 24 & 0xFF);
	m_color.y = (float)(color >> 16 & 0xFF);
	m_color.z = (float)(color >> 8 & 0xFF);
	m_color.w = (float)(color & 0xFF);
}

Color& Color::operator+=(const Color& rhs)
{
	return *this = *this + rhs;
}

Color& Color::operator*=(const Color& rhs)
{
	return *this = *this * rhs;
}

Color Color::operator+(const Color& rhs)
{
	return Color(m_color + rhs.m_color);
}

Color Color::operator*(const Color& rhs) //118
{
	return Color(m_color * rhs.m_color); //120
}

}