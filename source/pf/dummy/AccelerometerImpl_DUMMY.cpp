#include <pf/Accelerometer.h>

USING_NAMESPACE(lang)
USING_NAMESPACE(math)

BEGIN_NAMESPACE(pf)

class Accelerometer::Impl : public Object //OSX and likely Win
{
public:
	Impl()
	{
	}

	~Impl()
	{
	}

	bool isSupported() const
	{
		return false;
	}

	bool start() const
	{
		return false;
	}

	void stop()
	{
	}

	float3 getData()
	{
		return m_data;
	}

	float3 getDataFiltered()
	{
		return m_dataSmoothed;
	}
	
	//Guesses from iOS impl
	float3 m_data;
	float3 m_dataSmoothed;
};

#include <pf/common/Accelerometer.h>

END_NAMESPACE()