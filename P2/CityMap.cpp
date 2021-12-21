//========================================================
// CityMap.cpp
// Implementation file for the city map class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include <cstring>

#include "CityDataParser.h"
#include "CityMap.h"

//------------------------------------------
// Default constructor
//------------------------------------------
CityMap::CityMap () {}

CityMap::~CityMap() {
  // free up vector
  for (vector<City*>::iterator it = m_vCities.begin(); it != m_vCities.end(); it++) {
    delete *it;
  }

  delete[] m_pdDistancesArray;

  char * symbol = NULL;
  for (int i = 0; (symbol = m_hcCitySymbols[i]); i++) {
    delete[] m_hcCitySymbols[i]; // delete each string in the array
  }
  delete[] m_hcCitySymbols;
}
//--------------------------------------------------------------
// Read information on city symbols
// Args:  sCitySymbol - Pointer to a char array to hold symbol of a city name
// Returns NULL if all symbols have been read.
//--------------------------------------------------------------
City* CityMap::getInstance (const char * sCitySymbol) {
  for (int i = 0; i < m_iCityCount; i++) {
    if (strcmp(sCitySymbol, m_vCities[i]->getCitySymbol()) == 0) {
      return m_vCities[i];
    }
  }
  return NULL;
}
//--------------------------------------------------------------
// Build map of cities
// Args:  sDataFile - Pointer to a char array to hold name of the data
//--------------------------------------------------------------
void CityMap::buildCityMap (const char* sDataFile) {
  strcpy(m_sDataFile, sDataFile);

  CityDataParser* cParser = CityDataParser::getInstance();

  cParser->InitCityData(m_sDataFile);
  cParser->getCitySymbolsArray(&m_hcCitySymbols);
  cParser->getDistTable(&m_pdDistancesArray);
  m_iCityCount = cParser->getCityCount();

  City* pCity = NULL;

  char sCityName[32];
  char sCityState[32];
  char sCitySymbol[32];
  double dLatitude;
  double dLongitude;

  for (int i = 0; i < m_iCityCount; i++) {
      pCity = new City();

      if (!cParser->getCityData(sCityName, sCityState, sCitySymbol, &dLatitude, &dLongitude)) {
          printf("Failed to read all cities.\nTerminating program.");
          exit(-1);
      }

      pCity->setCityName(sCityName);
      pCity->setCityState(sCityState);
      pCity->setCitySymbol(sCitySymbol);
      pCity->setCityLatitude(dLatitude);
      pCity->setCityLongitude(dLongitude);

      m_vCities.push_back(pCity);
  }

  delete cParser;
}
//--------------------------------------------------------------
// Get locations of cities
// Args:  sCitySymbol - Pointer to a char array to hold symbol of a city
//--------------------------------------------------------------
const char* CityMap::getCityLocation (const char* sCitySymbol) {
    for (size_t i = 0; i < m_vCities.size(); i++) {
      if (strcmp(m_vCities[i]->getCityName(), sCitySymbol) == 0 ) {
        return m_vCities[i]->getCityName();
      }
    }

    return NULL; // not found
}
//--------------------------------------------------------------
// Get distances between cities
// Args:  sCitySymbol1 - Pointer to a char array to hold symbol of one city
//		  sCitySymbol2 - Pointer to a char array to hold symbol of another city
//--------------------------------------------------------------
double CityMap::getDistanceBetweenCities (const char * sCitySymbol1, const char * sCitySymbol2) {
    int iCity1 = -1, iCity2 = -1;
	//start reading distances in the vector of cities from beginning to end
    for (int i = 0; i < m_iCityCount; i++) {
      if (strcmp(sCitySymbol1, m_vCities[i]->getCitySymbol()) == 0) {
        iCity1 = i;
      }
	  //start reading distances in the vector of cities from end to beginning
      if (strcmp(sCitySymbol2, m_vCities[i]->getCitySymbol()) == 0) {
        iCity2 = i;
      }
    }

    if (iCity1 == -1 || iCity2 == -1) {
      return -1; // cities not found
    } else {
      return m_pdDistancesArray[iCity1 * m_iCityCount + iCity2];
    }
}
//--------------------------------------------------------------
// Get name of cities
// Args:  sCitySymbol - Pointer to a char array to hold symbol of a city
//--------------------------------------------------------------
const char* CityMap::getCityName (const char* sCitySymbol) {
  for (int i = 0; i < m_iCityCount; i++) {
    if (strcmp(sCitySymbol, m_vCities[i]->getCitySymbol()) == 0) {
      return m_vCities[i]->getCityName();
    }
  }

  return NULL;
}
//--------------------------------------------------------------
// Get stane name of cities
// Args:  sCitySymbol - Pointer to a char array to hold symbol of a city
//--------------------------------------------------------------
const char* CityMap::getState (const char* sCitySymbol) {
  for (int i = 0; i < m_iCityCount; i++) {
    if (strcmp(sCitySymbol, m_vCities[i]->getCitySymbol()) == 0) {
      return m_vCities[i]->getCityState();
    }
  }

  return NULL;
}
