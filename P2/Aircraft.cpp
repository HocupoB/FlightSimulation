//========================================================
// Aircraft.cpp
// Implementation file for the Aircfraft class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================


#include <cstring>

#include "Aircraft.h"

//------------------------------------------
// Default constructor
//------------------------------------------
Aircraft::Aircraft()
{

}
//------------------------------------------
// Destructor
//------------------------------------------
Aircraft::~Aircraft () 
{

}

//------------------------------------------
// Set the make of an aircraft
// Args: sMake - Pointer to an char to hold the
//				make of an aircraft
//------------------------------------------
void Aircraft::setAircraftMake(const char* sMake) {
	strcpy_s(m_sMake, sMake);
}

//------------------------------------------
// Get the make of an aircraft
//------------------------------------------
const char* Aircraft::getAircraftMake() {
	return m_sMake;
}


//------------------------------------------
// Set the model of an aircraft
// Args: sDesc - Pointer to an char to hold the
//				model of an aircraft
//------------------------------------------
void Aircraft::setAircraftDescription(const char* sDesc) {
  strcpy(m_sDesc, sDesc);
}

//------------------------------------------
// Get the model of an aircraft
//------------------------------------------
const char* Aircraft::getAircraftDescription () {
  return m_sDesc;
}

//------------------------------------------
// Set the Cruise Speed of an aircraft
// Args: dCruiseSpeed - double to hold the
//				cruise speed of an aircraft
//------------------------------------------
void Aircraft::setAircraftCruiseSpeed(double dCruiseSpeed) {
  m_dCruiseSpeed = dCruiseSpeed;
}

//------------------------------------------
// Get the Cruise Speed of an aircraft
//------------------------------------------
double Aircraft::getAirCruiseSpeed() {
  return m_dCruiseSpeed;
}

//------------------------------------------
// Set the Cruise Altitude of an aircraft
// Args: dCruiseAlt - double to hold the
//				cruise altitude of an aircraft
//------------------------------------------
void Aircraft::setAirCruiseAltitude(double dCruiseAlt) {
  m_dCruiseAlt = dCruiseAlt;
}

//------------------------------------------
// Get the Cruise Altitude of an aircraft
//------------------------------------------
double Aircraft::getAirCruiseAltitude () {
  return m_dCruiseAlt;
}

//------------------------------------------
// Set the Rate of Climb of an aircraft
// Args: dRateOfClimb - double to hold the
//				rate of climb of an aircraft
//------------------------------------------
void Aircraft::setAircraftRateOfClimb(double dRateOfClimb) {
  m_dRateofClimb = dRateOfClimb;
}

//------------------------------------------
// Get the Rate of Climb of an aircraft
//------------------------------------------
double Aircraft::getAircraftRateOfClimb() {
  return m_dRateofClimb;
}


//------------------------------------------
// Set the wing span of an aircraft
// Args: dWingSpan - double to hold the
//				wing span of an aircraft
//------------------------------------------
void Aircraft::setAircraftWingSpan(double dWingSpan) {
  m_dWingSpan = dWingSpan;
}

//------------------------------------------
// Get the wing span of an aircraft
//------------------------------------------
double Aircraft::getAircraftWingSpan() {
  return m_dWingSpan;
}

//------------------------------------------
// Set the length of an aircraft
// Args: dLength - double to hold the
//				length of an aircraft
//------------------------------------------
void Aircraft::setAircraftLength(double dLength) {
  m_dLength = dLength;
}

//------------------------------------------
// Get the length of an aircraft
//------------------------------------------
double Aircraft::getAircraftLength() {
  return m_dLength;
}