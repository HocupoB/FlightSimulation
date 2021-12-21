#ifndef FLIGHT_H
#define FLIGHT_H

#include "Aircraft.h"

class Flight {
private:
  char m_sAirline[32];			// Name of an airline
  Aircraft * m_pAircraft;       // pointer to aircraft class to get type of a plane
  int m_iFlightNumber;			// Flight number
  char m_sDepartureCity[4];		// Departure city
  char m_sDestinationCity[4];   // Destination city
  int m_iDepartureHour;			// Departure hour
  int m_iDepartureMinute;		// Departuer minute
  int m_iStartHour;				// Start hour
  int m_iStartMin;				// Start minute
  double m_dSimStartTime;		// Simulation start time
  double m_dDepartTime;			// Departure time
  double m_dCurTime;			// Current time
  double m_dCurAlt;				// Current altitude
  double m_dCurLatitude;		// Current latitude
  double m_dCurLongitude;		// Current longtitude
  double m_dCurSpeed;			// Current speed
  double m_dCurDistFromEnd;		// Current distance from a destination city
  double m_dCurDistFromStart;	// Current distance from a departure city
  double m_dArriveTime;			// Arrival time
  double m_dDistance;			// Distance
  bool m_bIsEnroute;			// Check if a flight is enroute
  bool m_bIsArrived;			// Check if a flight is arrived

public:
  Flight (const char * sDepartureCity, const char * sDestinationCity, int iDepartureHour, int iDepartureMinute);  // Default constructor
  ~Flight ();		// Destructor

  //Setters and Getters
  void setAirline (const char* airline);
  const char* getAirline ();
  void setAircraft (Aircraft* pAircraft);
  Aircraft* getAircraft ();
  void setFlightNumber (int flightNumber);
  int getFlightNumber ();
  bool isEnroute();
  bool isArrived();
  const char* getDepartureCity();
  const char* getDestinationCity();
  double getCurrentLatitude();
  double getCurrentLongitude();
  double getCurDistanceFromEnd();
  double getCurDistanceFromStart();
  double getCurrentAltitude();
  double getCurrentSpeed();
  double getDepartureTime();
  double getArriveTime();
  double getDistance();
  void setDistance(double dDistance);
  void setCurDistanceFromEnd(double dCurDistFromEnd);
  void setCurDistanceFromStart(double dCurDistFromStart);
  void setStartTime(double dStartTime);
  void setCurrentLatitude(double dCurrentLatitude);
  void setCurrentLongitude(double dCurrentLongitude);
  void setCurrentAltitude(double dCurAlt);
  void setCurrentTime(double dCurTime);
  void setCurrentSpeed(double dCurSpeed);
  void setStatus(bool bEnroute, bool bArrived);
  void setArriveTime(double dArriveTime);
};


#endif
