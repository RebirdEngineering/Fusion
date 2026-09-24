#ifndef _PF_LOCATION_H
#define _PF_LOCATION_H

#include <lang/Exception.h> //For now

namespace pf
{

struct GeoCoordinate
{
	double latitude;
	double longitude;
};

struct Region
{
	long int regionId;
	GeoCoordinate coord;
	int informRadius;
};

class LocationListener
{
public:
	~LocationListener();
	virtual void locationPermissionDenied();
	virtual void locationChanged();
	virtual void regionEntered(const Region&);
	virtual void regionExited(const Region&);
};

class Location :
	public Object
{
public:
	enum DeviceStatus
	{
		OFFLINE,
		READY,
	};

	enum AccuracyLevel
	{
		LOW,
		NORMAL,
		BEST,
	};

	Location();

	Location(float, AccuracyLevel);

	~Location();

	const GeoCoordinate& emptyGeoCoordinate(const GeoCoordinate&);

	bool isValidGeoCoordinate(const GeoCoordinate&);

	bool isSupported();

	bool isGpsAvailable();

	void startUpdating() const;

	void stopUpdating() const;

	void setDistanceFilter(float);

	void setAccuracy(AccuracyLevel) const;

	DeviceStatus getStatus() const;

	const GeoCoordinate& currentLocation() const;

	void startMonitoringForRegions(const std::vector<Region>&);

	void stopMonitoringAllRegions();

	int numOfMonitoredRegions() const;

	int maxNumOfMonitoredRegions();

	void addListener(LocationListener*);
	
	void removeListener(LocationListener*);
private:
	class LocationImpl;
	P(LocationImpl) m_impl;

	Location(const Location&);
	Location& operator=(const Location&);
};

}

#endif