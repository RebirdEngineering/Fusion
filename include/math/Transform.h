#ifndef _MATH_TRANSFORM_H
#define _MATH_TRANSFORM_H

#include <math/float2.h>
#include <math/float2x3.h>
#include <math/float3x4.h>

namespace math
{
	//TODO
class Transform //19
{
public:
	enum Mode //25
	{
		MODE_2D,
		MODE_3D
	};

	Transform() //34
	{
		m_tm = float3x4(1.0);
		m_mode = MODE_2D;
	}

	explicit Transform(const float2&); //39

	Transform(float, float); //44

	Transform(float, float, float, Mode); //49

	Transform(const float2&, float); //54

	Transform(const float2&, float, const float2&); //59

	explicit Transform(const float2x3&); //64

	explicit Transform(const float3&); //69

	Transform(const float3&, const float3x3&); //74

	explicit Transform(const float3x4&); //79

	Transform operator*(const Transform&) const; //88

	float2 operator*(const float2&) const; //93

	float3 operator*(const float3&) const; //98

	Transform transform(const Transform&) const; //107

	float2 transform(const float2&)  const; //112

	float3 transform(const float3&) const; //117

	float2 rotate(const float2&) const; //122

	float3 rotate(const float3&) const; //127

	Transform inverse() const //132
	{
		m_tm.inverse();
		return *this;
	}

	void setTranslation(const float2&); //141

	void setTranslation(const float3&); //146

	void setTranslation(float); //151

	void setTranslation(const float3x3&); //156

	void setScale(const float2&); //161

	void setScale(const float3&) //166
	{
		//m_tm.set
	}

	void setMode(Mode mode) //171
	{
		m_mode = mode;
	}

	float2 getTranslation2D() const //180
	{
		//return m_tm.translation();
	}

	float3 getTranslation3D() const //185
	{
		return m_tm.translation();
	}

	float getRotation2D() const //190
	{
		return m_tm.rotation().determinant();
	}

	float3x3 getRotation3D() const //195
	{
		return m_tm.rotation();
	}

	float2 getScale2D() const //200
	{
		return m_tm.scale().xy();
	}

	float3 getScale3D() const //205
	{
		return m_tm.scale();
	}

	Mode getMode() const //210
	{
		return m_mode;
	}

	float2x3 toFloat2x3() const //215
	{
		return float2x3(m_tm.determinant3());
	}

	float3x4 toFloat3x4() const //220
	{
		return float3x4(m_tm.determinant3());
	}
private:
	float3x4 m_tm; //223
	Mode m_mode; //224

	Transform(float angle, float2& scale) //278 (?)
	{
		//float sin = scale; //282
		//float cos = scale; //283
		//m_tm.set
	}
};

} // math

#endif //_MATH_TRANSFORM_H
