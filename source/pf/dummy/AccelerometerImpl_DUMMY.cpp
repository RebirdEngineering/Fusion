#include <pf/Accelerometer.h>

USING_NAMESPACE(lang)
USING_NAMESPACE(math)

BEGIN_NAMESPACE(pf)

class Accelerometer::Impl : public Object //Win32+OSX+WP8
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
		return float3(0, 0, 0);
	}

	float3 getDataFiltered()
	{
		return float3(0, 0, 0);
	}
};

#include <pf/common/Accelerometer.h>

END_NAMESPACE()