#ifndef _PF_COMMON_ACCELEROMETER_H
#define _PF_COMMON_ACCELEROMETER_H

//Includes and namespaces are redundant since we're including this file in the namespace

Accelerometer::Accelerometer()
{
	m_impl = new Impl();
}

Accelerometer::~Accelerometer()
{
}

bool Accelerometer::isSupported()
{
	return m_impl->isSupported();
}

bool Accelerometer::start()
{
	return m_impl->start();
}

void Accelerometer::stop()
{
	m_impl->stop();
}

float3 Accelerometer::getData() //NOT IN IOS HEADER
{
	return m_impl->getData();
}

float3 Accelerometer::getDataFiltered()
{
	return m_impl->getDataFiltered();
}

#endif // !_PF_COMMON_ACCELEROMETER_H