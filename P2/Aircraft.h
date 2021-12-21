#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <fstream>

class Aircraft {
private:
	char m_sMake[32];			// Make of an aircraft
	char m_sDesc[32];			// Model of an aircraft
	double m_dRateofClimb;	// Rate of Climb of an aircraft
	double m_dWingSpan;		// Wing Span of an aircraft
	double m_dLength;			// Fuselage Length of an aircraft
	double m_dCruiseSpeed;	// Cruise Speed of an aircraft
	double m_dCruiseAlt;		// Cruise Altitude of an aircraft

public:
Aircraft();		// Default constructor
~Aircraft();		// Destructor
// setters and getters
  void setAircraftMake (const char* sMake);
  const char* getAircraftMake();
  void setAircraftDescription (const char* sDesc);
  const char* getAircraftDescription();
  void setAircraftCruiseSpeed (double dCruiseSpeed);
  double getAirCruiseSpeed();
  void setAirCruiseAltitude (double dCruiseAlt);
  double getAirCruiseAltitude ();
  void setAircraftRateOfClimb (double dRateOfClimb);
  double getAircraftRateOfClimb ();
  void setAircraftWingSpan(double dWingSpan);
  double getAircraftWingSpan();
  void setAircraftLength(double dLength);
  double getAircraftLength();
};

class PassengerJet : public Aircraft {		//class for PassengerJet

};

class BusinessJet : public Aircraft {	   //class for BusinessJet

};

class SingleEnginePlane : public Aircraft {	//class for SingleEnginePlane

};

#endif // AIRCRAFT_H
