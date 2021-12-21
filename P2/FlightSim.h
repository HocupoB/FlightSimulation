//========================================================
// FlightSim.h
// Implementation file for the Flight Simulation class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#ifndef FLIGHTSIM_H
#define FLIGHTSIM_H

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#include "AircraftFactory.h"
#include "CityDataParser.h"
#include "FlightDataParser.h"
#include "CityMap.h"
#include "Aircraft.h"
#include "Flight.h"

using namespace std;


class FlightSim {
private:
  CityMap* m_pCityMap;					// Build city map
  vector <Aircraft*> vAircraftTypes;	// Store aircraft types
  vector <Flight*> vFlights;			// Store flights
  int m_iStartHour;						// Start hour
  int m_iStartMin;						// Start minute
  double m_dStartTime;					// Simulation start time
  double m_dCurSimTime;					// Current time on simulation
  int m_iFlightsIncomplete;				// Number of incomplete flights
  FlightDataParser* fdp;
  FlightSim (const char* sFlightSimDataFile);
  bool getNextLine(fstream * inFile, char * buffer);		// Reading lines of a file

public:
  static FlightSim* getInstance(const char* sFlightSimDataFile);		//Constructor

  ~FlightSim ();				// Destructor
  void RunSim(int speed);		// Run simulation
  void buildFlightVector ();	// Stores flight details
  double getStartTime ();		// Get start time of the simulation
  void postReport ();			// Post report
  CityMap* getCityMap();		// Get City Map

  bool updateFlight(Flight* flight);		// Update flight 
  void updateFlightStats(Flight* flight);	// Update flight stats
};

#endif
