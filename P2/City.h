//========================================================
// City.h
// Interface file for City class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================


#ifndef CITY_H
#define CITY_H

class City {
private:
	char m_sCityName[32];       // Name of a city
	char m_sCityState[32];	  // State where a city is located
	char m_sCitySymbol[32];	  // Symbol of a city
	double m_dLatitude;		  // Latitude where a city is located
	double m_dLongitude;		  // Longtitude where a city is located

public:
  City ();		// Default constructor
  ~City ();		// Destructor
//setters and getters
  void setCityName (const char* sCityName);
  const char* getCityName ();
  void setCityState (const char* sCityState);
  const char* getCityState ();
  void setCitySymbol (const char* sCitySymbol);
  const char* getCitySymbol ();
  void setCityLatitude (double dLatitude);
  double getCityLatitude ();
  void setCityLongitude (double dLongitude);
  double getCityLongitude ();

};

#endif
