//========================================================
// Flight.cpp
// Implementation file for the Flight class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include <cstring>
#include <cmath>

#include "Aircraft.h"
#include "CityMap.h"
#include "Flight.h"


//--------------------------------------------------------------
// Read information on flight details
// Args:  sDepartureCity - Pointer to a char array to hold departure city name
//		  sDestinationCity - Pointer to a char array to hold destination city name
//		  iDepartureHour - int array to hold departure hour
//		  iDepartureMinute - int array to hold departure minute		  
//-------------------------------------------------------------
Flight::Flight(const char * sDepartureCity, const char * sDestinationCity, int iDepartureHour, int iDepartureMinute){
  strcpy(m_sDepartureCity, sDepartureCity);
  strcpy(m_sDestinationCity, sDestinationCity);
  m_iDepartureHour = iDepartureHour;
  m_iDepartureMinute = iDepartureMinute;

  m_dDepartTime = iDepartureHour * 60.0 + iDepartureMinute * 1.0;

  m_bIsEnroute = false;
  m_bIsArrived = false;
}

//------------------------------------------
// Destructor
//------------------------------------------
Flight::~Flight()
{

}


//------------------------------------------
// Setters and Getters
//------------------------------------------
void Flight::setAirline (const char* airline){
  strcpy(m_sAirline, airline);
}

const char* Flight::getAirline () {
  return m_sAirline;
}

void Flight::setFlightNumber (int flightNumber) {
  m_iFlightNumber = flightNumber;
}

int Flight::getFlightNumber (){
  return m_iFlightNumber;
}

bool Flight::isEnroute() {
  return m_bIsEnroute;
}

bool Flight::isArrived() {
  return m_bIsArrived;
}

const char* Flight::getDepartureCity() {
  return m_sDepartureCity;
}

const char* Flight::getDestinationCity() {
  return m_sDestinationCity;
}

double Flight::getCurrentLatitude() {
  return m_dCurLatitude;
}

double Flight::getCurrentLongitude() {
  return m_dCurLongitude;
}

double Flight::getCurDistanceFromEnd() {
  return m_dCurDistFromEnd;
}

double Flight::getCurDistanceFromStart() {
  return m_dCurDistFromStart;
}

double Flight::getCurrentAltitude() {
  return m_dCurAlt;
}

double Flight::getCurrentSpeed() {
  return m_dCurSpeed;
}

double Flight::getDepartureTime() {
  return m_dDepartTime;
}

double Flight::getArriveTime() {
  return m_dArriveTime;
}

void Flight::setCurDistanceFromEnd(double dCurDistFromEnd) {
  m_dCurDistFromEnd = dCurDistFromEnd;
}

void Flight::setCurDistanceFromStart(double dCurDistFromStart) {
  m_dCurDistFromStart = dCurDistFromStart;
}

double Flight::getDistance() {
  return m_dDistance;
}

void Flight::setDistance(double dDistance) {
  m_dDistance = dDistance;
}

void Flight::setCurrentAltitude(double dCurAlt) {
  m_dCurAlt = dCurAlt;
}

void Flight::setCurrentLatitude(double dCurrentLatitude) {
  m_dCurLatitude = dCurrentLatitude;
}

void Flight::setCurrentLongitude(double dCurrentLongitude) {
  m_dCurLongitude = dCurrentLongitude;
}

void Flight::setCurrentTime(double dCurTime) {
  m_dCurTime = dCurTime;
}

void Flight::setStatus(bool bEnroute, bool bArrived) {
  m_bIsArrived = bArrived;
  m_bIsEnroute = bEnroute;
}

void Flight::setCurrentSpeed(double dCurSpeed) {
  m_dCurSpeed = dCurSpeed;
}

void Flight::setArriveTime(double dArriveTime) {
  m_dArriveTime = dArriveTime;
}

void Flight::setAircraft(Aircraft* pAircraft) {
  m_pAircraft = pAircraft;
}

Aircraft* Flight::getAircraft() {
  return m_pAircraft;
}