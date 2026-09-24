#ifndef _PF_COMMON_ACCELEROMETER_H
#define _PF_COMMON_ACCELEROMETER_H

#include <pf/Accelerometer.h>

BEGIN_NAMESPACE(pf)

Accelerometer::Accelerometer()
{
	m_impl = new Impl();
}

Accelerometer::~Accelerometer()
{
}

bool Accelerometer::isSupported()
{
	return false; //False on Apple? Why?
}

void Accelerometer::start()
{
	m_impl->start();
}

void Accelerometer::stop()
{
	m_impl->stop();
}

float3 Accelerometer::getData() //NOT IN IOS HEADER
{
	m_impl->getData();
}

float3 Accelerometer::getDataFiltered()
{
	m_impl->getDataFiltered();
}


}

#endif // !_PF_TEXTINPUT_H