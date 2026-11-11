#include <pf/Accelerometer.h>

USING_NAMESPACE(lang)
USING_NAMESPACE(math)

BEGIN_NAMESPACE(pf)

class Accelerometer::Impl : public Object //Win32
{
public:
	Impl() :
		m_startedAccelerometer(false)
	{
	}

	~Impl()
	{
	}

	bool isSupported() const
	{
		return true;
	}

	bool start() //4C6040
	{
		m_startedAccelerometer = true;
		return true;
	}

	void stop() //4C6050
	{
		m_startedAccelerometer = false;
	}

	float3 getData() //?
	{
		return float3(0, 0, 0);
	}

	float3 getDataFiltered() //4C6060
	{
		return float3(0.0, m_startedAccelerometer ? -1.0 : 0.0, 0);
	}

private:
	bool m_startedAccelerometer;
};

#include <pf/common/Accelerometer.h>

END_NAMESPACE()