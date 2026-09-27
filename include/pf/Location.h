#ifndef _PF_LOCATION_H
#define _PF_LOCATION_H

#include <lang/Object.h>

namespace pf //9
{

struct GeoCoordinate //14
{
	double latitude; //16
	double longitude; //17
};

struct Region //20
{
	long int regionId; //22
	GeoCoordinate coord; //23
	int informRadius; //24
};

class LocationListener //36
{
public:
	~LocationListener(); //39
	virtual void locationPermissionDenied(); //40
	virtual void locationChanged(); //41
	virtual void regionEntered(const Region&); //42
	virtual void regionExited(const Region&); //43
};

class Location : //52
	public lang::Object
{
public:
	enum DeviceStatus //59
	{
		OFFLINE,
		READY,
	};

	enum AccuracyLevel //68
	{
		LOW,
		NORMAL,
		BEST,
	};

	Location(); //78

	Location(float, AccuracyLevel); //85

	~Location(); //90

	const GeoCoordinate& emptyGeoCoordinate(); //95

	bool isValidGeoCoordinate(const GeoCoordinate&); //105

	bool isSupported(); //115

	bool isGpsAvailable(); //121

	void startUpdating() const; //126

	void stopUpdating() const; //132

	void setDistanceFilter(float) const; //137

	void setAccuracy(AccuracyLevel) const; //143

	DeviceStatus getStatus() const; //148

	const GeoCoordinate& currentLocation() const; //153

	void startMonitoringForRegions(const std::vector<Region>&); //160

	void stopMonitoringAllRegions(); //165

	int numOfMonitoredRegions() const; //170

	int maxNumOfMonitoredRegions(); //175

	void addListener(LocationListener*); //181
	
	void removeListener(LocationListener*); //187
private:
	class LocationImpl;
	P(LocationImpl) m_impl; //190
	Location(const Location&); //191
	Location& operator=(const Location&); //192
};

}

#endif