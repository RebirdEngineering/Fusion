#include <gr/Color.h>

using namespace math;

namespace gr
{

Color::Color(unsigned int color)
{
	setColor(color);
}

void Color::setColor(unsigned int color)
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

Color::Color(float alpha, float red, float green, float blue)
{
	m_color.x = alpha;
	m_color.y = red;
	m_color.z = green;
	m_color.w = blue;
}

Color::Color(const float4& color)
{
	m_color = color;
}

Color::~Color()
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

float4 Color::getColorAsFloat4() const
{
	float4 color;
	int alphaBits = alpha();
	int redBits = red();
	int greenBits = green();
	int blueBits = blue();
	color.x = alphaBits;
	color.y = redBits;
	color.z = greenBits;
	color.w = blueBits;
	return color;
	//saturate
}

}