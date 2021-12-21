//========================================================
// City.cpp
// Implementation file for the city class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include <cstring>

#include "City.h"

//------------------------------------------
// Default constructor
//------------------------------------------
City::City()
{

}


//------------------------------------------
// Destructor
//------------------------------------------
City::~City()
{

}

//------------------------------------------
// Set the name of a city
// Args: sCityName - Pointer to an char to hold the
//				name of a city
//------------------------------------------
void City::setCityName(const char* sCityName) {
  strcpy(m_sCityName, sCityName);
}

//------------------------------------------
// Get the name of a city
//------------------------------------------
const char* City::getCityName() {
  return m_sCityName;
}


//------------------------------------------
// Set the state of a city
// Args: sCityState - Pointer to an char to hold the
//				state of a city
//------------------------------------------
void City::setCityState(const char* sCityState) {
  strcpy(m_sCityState, sCityState);
}

//------------------------------------------
// Get the state of a city
//------------------------------------------
const char* City::getCityState() {
  return m_sCityState;
}


//------------------------------------------
// Set the symbol of a city
// Args: sCitySymbol - Pointer to an char to hold the
//				symbol of a city
//------------------------------------------
void City::setCitySymbol (const char* sCitySymbol) {
  strcpy(m_sCitySymbol, sCitySymbol);
}

//------------------------------------------
// Get the symbol of a city
//------------------------------------------
const char* City::getCitySymbol () {
  return m_sCitySymbol;
}


//------------------------------------------
// Set the latitude of a city
// Args: dLatitude - double to hold the
//				latitude of a city
//------------------------------------------
void City::setCityLatitude (double dLatitude) {
  m_dLatitude = dLatitude;
}


//------------------------------------------
// Get the latitude of a city
//------------------------------------------
double City::getCityLatitude () {
  return m_dLatitude;
}


//------------------------------------------
// Set the longtitude of a city
// Args: dLongtitude - double to hold the
//				longtitude of a city
//------------------------------------------
void City::setCityLongitude (double dLongitude) {
  m_dLongitude = dLongitude;
}



//------------------------------------------
// Get the longtitude of a city
//------------------------------------------
double City::getCityLongitude () {
  return m_dLongitude;
}
