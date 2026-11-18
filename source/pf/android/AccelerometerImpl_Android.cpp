#include <pf/Accelerometer.h>

//TODO

USING_NAMESPACE(lang)
USING_NAMESPACE(math)

BEGIN_NAMESPACE(pf)

class Accelerometer::Impl : public Object //0x50 bytes.
{
public:
	Impl() //TODO
	{
		//"com/rovio/fusion/AccelerometerWrapper"
	}

	~Impl()
	{
	}

	bool isSupported() const
	{
		return true;
	}

	bool start() const //TODO
	{
		return false;
	}

	void stop() //TODO
	{
	}

	float3 getData() //TODO
	{
		return float3(0, 0, 0);
	}

	float3 getDataFiltered() //TODO
	{
		return float3(0, 0, 0);
	}

	private:
		GlobalRef java__globalrefC;
		jobject start_jobject10;
		jmethodID start_jmethodID14;
		jobject stop_jobject18;
		jmethodID stop_jmethodID1C;
		jobject getX_jobject20;
		jmethodID getX_jmethodID24;
		jobject getY_jobject28;
		jmethodID getY_jmethodID2C;
		jobject getZ_jobject30;
		jmethodID getZ_jmethodID34;
		jobject getFilteredX_jobject38;
		jmethodID getFilteredX_jmethodID3C;
		jobject getFilteredY_jobject40;
		jmethodID getFilteredY_jmethodID44;
		jobject getFilteredZ_jobject48;
		jmethodID* getFilteredZMethod4C;
};

#include <pf/common/Accelerometer.h>

END_NAMESPACE()