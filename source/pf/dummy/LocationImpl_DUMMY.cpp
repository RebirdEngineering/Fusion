#include <pf/Location.h>

using namespace lang;

namespace pf
{
	class Location::LocationImpl : public Object
	{
	public:
		LocationImpl()
		{
		}

		~LocationImpl()
		{
		}

		const GeoCoordinate& emptyGeoCoordinate();

		bool isValidGeoCoordinate(const GeoCoordinate&);

		bool isSupported();

		bool isGpsAvailable();

		void startUpdating() const;

		void stopUpdating() const;

		void setDistanceFilter(float) const;

		void setAccuracy(AccuracyLevel) const;

		DeviceStatus getStatus() const;

		const GeoCoordinate& currentLocation() const;

		void startMonitoringForRegions(const std::vector<Region>&);

		void stopMonitoringAllRegions();

		int numOfMonitoredRegions() const;

		int maxNumOfMonitoredRegions();

		void addListener(LocationListener*);

		void removeListener(LocationListener*);
	};

//#include <pf/common/Location.h> //Doesn't exist?

}