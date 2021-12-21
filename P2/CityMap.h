//========================================================
// CityMap.h
// Interface file for City Map class.
//
// Author: Ulugbek Nosirov
// Date: March 2021
//========================================================

#ifndef CITYMAP_H
#define CITYMAP_H

#include <vector>
#include <fstream>
#include <string>

#include "City.h"

using namespace std;

class CityMap {
private:
	int m_iCityCount;			// number of cities
	char m_sDataFile[100];		// name of data file
	double* m_pdDistancesArray;	// distances between cities
	char** m_hcCitySymbols;		// symbols of cities
	vector <City*> m_vCities;

public:
CityMap();			// Default constructor
~CityMap();			// Destructor
City* getInstance(const char * sCitySymbol);     // get an instance of a city symbol
void buildCityMap(const char * sDataFile);		// build city map
const char* getCityLocation(const char * sCitySymbol);		// get location of a city
double getDistanceBetweenCities(const char * sCitySymbol1, const char * sCitySymbol2);	//get distance between cities
const char* getCityName(const char* sCitySymbol);		//get name of a city
const char* getState(const char* sCitySymbol);			// get state where a city is located

};

#endif
