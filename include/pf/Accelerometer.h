#ifndef _PF_ACCELEROMETER_H
#define _PF_ACCELEROMETER_H

#include <math/float3.h>
#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

class Accelerometer : //16 bytes
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
	P(Impl) m_impl; //77 | Impl sizes: [Win32+OSX+WP8: 12 bytes {DUMMY}, iOS: 44 bytes, Android: 80 bytes]

	Accelerometer(const Accelerometer&); //79
	Accelerometer& operator=(const Accelerometer&); //80
};

END_NAMESPACE()

#endif // !_PF_ACCELEROMETER_H