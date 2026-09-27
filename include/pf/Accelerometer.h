#ifndef _PF_ACCELEROMETER_H
#define _PF_ACCELEROMETER_H

#include <math/float3.h>
#include <lang/Object.h>

namespace pf
{

class Accelerometer :
	public lang::Object
{
public:
	Accelerometer(); //37

	~Accelerometer(); //42

	bool isSupported(); //47

	bool start(); //53

	void stop(); //58

	NS(math, float3) getData(); //65

	NS(math, float3) getDataFiltered(); //72
private:
	class Impl;
	P(Impl) m_impl; //77

	Accelerometer(const Accelerometer&); //79
	Accelerometer& operator=(const Accelerometer&); //80
};

}

#endif // !_PF_TEXTINPUT_H