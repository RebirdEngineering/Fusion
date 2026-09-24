#ifndef _PF_ACCELEROMETER_H
#define _PF_ACCELEROMETER_H

#include <math/float3.h>

namespace pf
{

class Accelerometer :
	public lang::Object
{
public:
	Accelerometer();

	~Accelerometer();

	bool isSupported();

	bool start();

	void stop();

	NS(math, float3) getData();

	NS(math, float3) getDataFiltered();
private:
	class Impl;
	P(Impl) m_impl;

	Accelerometer(const Accelerometer&);
	Accelerometer& operator=(const Accelerometer&);
};

}

#endif // !_PF_TEXTINPUT_H