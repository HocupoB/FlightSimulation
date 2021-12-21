//========================================================
// FlightSim.cpp
// Implementation file for the Flight Simulation class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include <cstring>
#include <ctime>
#include <cmath>

#include "FlightSim.h"

//------------------------------------------
// Create an instance of a FlightSim
//------------------------------------------
FlightSim* FlightSim::getInstance(const char* sFlightSimDataFile) {
  static FlightSim* theInstance = NULL;
  if (theInstance == NULL) {
    theInstance = new FlightSim(sFlightSimDataFile);
  }

  return theInstance;
}

//------------------------------------------
// Read lines from a file
//------------------------------------------
bool FlightSim::getNextLine(fstream * inFile, char * buffer) {
 bool    done = false;
	char    tempBuf[128];
	char	*temp;
    while(!done)
    {
        inFile->getline(tempBuf, 128); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(strlen(tempBuf) == 0)     // Skip any blank lines
               continue;
		   else if(strncmp(tempBuf, "<!--", 4) == 0) // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(buffer, "");  // Clear the buffer array
            return false;        // Flag end of file
        }
    } // end while
	// Remove white space from end of string
	temp = &tempBuf[strlen(tempBuf)]; // point to closing \0
	temp--; // back up 1 space
	while(isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = tempBuf;
	while(isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	strcpy(buffer, temp);
    return true;  // Flag a successful read
}

//------------------------------------------
// Default constructor
// Args: sFlightSimDataFile - Pointer to an char to hold the
//				              name of the data file
//------------------------------------------

  FlightSim::FlightSim (const char* sFlightSimDataFile) {
    // Read file
    fstream * inFSD = new fstream();
    inFSD->open(sFlightSimDataFile, fstream::in);
    if (!inFSD->is_open()) {
      cout << "Failed to open the Flight Data file.\nProgram terminating...\n";
      exit(0);
    }

    char line[128];
    getNextLine(inFSD, line);

    m_pCityMap = new CityMap();
    m_pCityMap->buildCityMap(line);

    getNextLine(inFSD, line);

    fdp = FlightDataParser::getInstance();
    fdp->InitFlightData(line);

    fdp->getStartTime(&m_iStartHour, &m_iStartMin);

    m_dStartTime = (double)(m_iStartHour * 60.0 + m_iStartMin * 1.0);

    delete inFSD;
  }

//------------------------------------------
// Destructor
//------------------------------------------

  FlightSim::~FlightSim () {
    delete m_pCityMap;
    delete fdp;

    for (int i = 0; i < (int)vAircraftTypes.size(); i++) {
      delete vAircraftTypes[i];
    }

    for (int i = 0; i < (int)vFlights.size(); i++) {
      delete vFlights[i];
    }

    // delete aircraft factories
    delete PassengerJetFactory::getInstance();
    delete BusinessJetFactory::getInstance();
    delete SingleEnginePlaneFactory::getInstance();
  }

//------------------------------------------
// Run simulation
// Args: sFlightSimDataFile - Int to hold the speed
//				              of the Simulation
//------------------------------------------
  void FlightSim::RunSim(int speed) {
    m_iFlightsIncomplete = vFlights.size();

    time_t start;
    time_t current;

    time(&start);

    // Calculate next update time
    double updateSec = 1.0 / (double)speed;
    double reportSec = 5.0;
    double elapsedSec = 0.0;

    cout << endl << "*** Starting simulation at " << setfill('0') << setw(2) << m_iStartHour;
    cout << ":" << setfill('0') << setw(2) << m_iStartMin << " ***" << endl;

    // Loop until all flights are done.
    while (m_iFlightsIncomplete) {
        // Get current time
        time(&current);
        elapsedSec = difftime(current, start);

        // Convert to current speed time
        m_dCurSimTime = m_dStartTime + elapsedSec * (double)speed; // 1 sec = 1 sim min

        // Update
        if (elapsedSec >= updateSec) {

            m_iFlightsIncomplete = vFlights.size();

            for (int i = 0; i < (int)vFlights.size(); i++) {
                if (updateFlight(vFlights[i])) {
                  m_iFlightsIncomplete--;
                }
            }

            // Next update
            updateSec += 1.0 / (double)speed;
        }

        // Report
        if (elapsedSec >= reportSec) {
            postReport();

            // Next report
            reportSec += 5.0;
        }
    }
  }
  //-----------------------------------------------------------------
  // Building Flight Vector to set all info regarding the flights
  //-----------------------------------------------------------------
  void FlightSim::buildFlightVector () {
    int iFlightCount = fdp->getFlightCount();

    Flight* pFlight = NULL;

    char sAirline[32];
    char sPlaneType[32];
    int iFlightNumber;
    char sDepartureCity[4];
    char sDestinationCity[4];
    int iDepartureHour;
    int iDepartureMinute;

    Aircraft* pAircraft = NULL;

    for (int i = 0; i < iFlightCount; i++) {
      if (fdp->getFlightData(sAirline, sPlaneType, &iFlightNumber, sDepartureCity, &iDepartureHour, &iDepartureMinute, sDestinationCity)) {
        pFlight = new Flight(sDepartureCity, sDestinationCity, iDepartureHour, iDepartureMinute);

        pFlight->setAirline(sAirline);
        pFlight->setFlightNumber(iFlightNumber);
        
        pAircraft = PassengerJetFactory::getInstance()->getAircraft(sPlaneType);

        if (!pAircraft) {
          pAircraft = BusinessJetFactory::getInstance()->getAircraft(sPlaneType);
        }

        if (!pAircraft) {
          pAircraft = SingleEnginePlaneFactory::getInstance()->getAircraft(sPlaneType);
        }

        pFlight->setAircraft(pAircraft);

        vFlights.push_back(pFlight);
      }
    }
  }
  //-----------------------------------------------------------------
// It calculates flight stats
// Args: flight - Pointer to Flight class for calculation purposes
//-----------------------------------------------------------------
  void FlightSim::updateFlightStats(Flight* flight) {
    City * departCity = m_pCityMap->getInstance(flight->getDepartureCity());
    City * destinationCity = m_pCityMap->getInstance(flight->getDestinationCity());

    double dTripTime =  flight->getArriveTime() - flight->getDepartureTime();
    double elapsed = m_dCurSimTime - flight->getDepartureTime();

    flight->setCurrentLatitude(departCity->getCityLatitude() + (destinationCity->getCityLatitude() - departCity->getCityLatitude()) * elapsed / dTripTime);
    flight->setCurrentLongitude(departCity->getCityLongitude() + (destinationCity->getCityLongitude() - departCity->getCityLongitude()) * elapsed / dTripTime);

    flight->setCurDistanceFromStart(elapsed / dTripTime * flight->getDistance());
    flight->setCurDistanceFromEnd(flight->getDistance() - flight->getCurDistanceFromStart());

    Aircraft* plane = flight->getAircraft();
    double MACA = plane->getAirCruiseAltitude() / plane->getAircraftRateOfClimb();

    if (elapsed >= MACA && elapsed <= (dTripTime - MACA)) {
      flight->setCurrentAltitude(plane->getAirCruiseAltitude());
    } else if (elapsed < MACA) {
      flight->setCurrentAltitude(plane->getAirCruiseAltitude() * elapsed / MACA);
    } else {
      flight->setCurrentAltitude(plane->getAirCruiseAltitude() * (dTripTime - elapsed) / (dTripTime - MACA));
    }
  }

//---------------------------------------------------------------------
// It updates flight stats
// Args: flight - Pointer to Flight class for calculation purposes
//  It also shows flights enroute, arriving flights and many more stats
//---------------------------------------------------------------------
  bool FlightSim::updateFlight(Flight* flight) {
     flight->setCurrentTime(m_dCurSimTime);

      if (flight->isArrived()) {
        return true;
      } else {
        if (flight->isEnroute()) {
          if (m_dCurSimTime >= flight->getArriveTime()) {

            flight->setStatus(false, true);

            City * departCity = m_pCityMap->getInstance(flight->getDepartureCity());
            City * destinationCity = m_pCityMap->getInstance(flight->getDestinationCity());

            cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Now arriving: " << flight->getAirline() << " flight " << flight->getFlightNumber();
            cout << ", " << flight->getAircraft()->getAircraftMake() << endl;
            cout << "        From " << departCity->getCityName() << ", " << departCity->getCityState() << endl;
            cout << "                 enroute to " << destinationCity->getCityName() << ", " << destinationCity->getCityState() << endl;
            cout << "Current clock time: " << setfill('0') << setw(2) << (int)(m_dCurSimTime / 60.0);
            cout << ":" << setfill('0') << setw(2) << (int)fmod(m_dCurSimTime, 60.0) << endl << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;

            return true;
        } else {
          updateFlightStats(flight);
        }
      } else {
        if (flight->getDepartureTime() <= m_dCurSimTime) {
          City * departCity = m_pCityMap->getInstance(flight->getDepartureCity());
          City * destinationCity = m_pCityMap->getInstance(flight->getDestinationCity());

          double distance, triptime;

          distance = m_pCityMap->getDistanceBetweenCities(flight->getDepartureCity(), flight->getDestinationCity());
          flight->setDistance(distance);

          Aircraft* plane = flight->getAircraft();

          triptime = (60.0 * distance / plane->getAirCruiseSpeed());

          flight->setCurrentSpeed(plane->getAirCruiseSpeed());
          flight->setArriveTime(flight->getDepartureTime() + triptime);

          updateFlightStats(flight);

          cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
          cout << "Now departing: " << flight->getAirline() << " flight " << flight->getFlightNumber() << ", " << plane->getAircraftMake() << endl;
          cout << "        From " << departCity->getCityName() << ", " << departCity->getCityState() << endl;
          cout << "                 enroute to " << destinationCity->getCityName() << ", " << destinationCity->getCityState() << endl;
          cout << "        Estimated Time of Arrival: " << setfill('0') << setw(2) << (int)(flight->getArriveTime() / 60.0) << ":" << setfill('0') << setw(2) << (int)fmod(flight->getArriveTime(), 60.0) << endl;
          cout << "Current clock time: " << setfill('0') << setw(2) << (int)(m_dCurSimTime / 60.0) << ":" << setfill('0') << setw(2) << (int)fmod(m_dCurSimTime, 60.0) << endl;
          cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;

          // Update status
          flight->setStatus(true, false);
        }
      }
      return false;
    }
  }


 //-----------------------------------------------------------------
 // Get start time of the simulation
 //-----------------------------------------------------------------

  double FlightSim::getStartTime () {
    return m_dStartTime;
  }

  //-----------------------------------------------------------------
  // Post report about current flights
  //-----------------------------------------------------------------
  void FlightSim::postReport () {
    int hour = (int)(m_dCurSimTime / 60.0);
    int minute = (int)fmod(m_dCurSimTime, 60.0);

    cout << endl;
    cout << "=============================================================" << endl;
    cout << "| Flight Simulation - Status report on all flights enroute. |" << endl;
    cout << "=============================================================" << endl;
    cout << "Current clock time: " << setfill('0') << setw(2) << hour;
    cout << ":" << setfill('0') << setw(2) << minute << endl;

    Flight* f;
    City* depart, *dest;

    for (int i = 0; i < (int)vFlights.size(); i++) {
      f = vFlights[i];
      if (f->isEnroute()) { // give report on enroute flights only
        cout << f->getAirline() << " Flight ";
        cout << f->getFlightNumber() << " - " << f->getAircraft()->getAircraftMake() << endl;

        depart = m_pCityMap->getInstance(f->getDepartureCity());
        dest = m_pCityMap->getInstance(f->getDestinationCity());

        cout << "        Departs: " << depart->getCitySymbol();
        cout << " (" << setprecision(1) << fixed << depart->getCityLatitude();
        cout << ", " << depart->getCityLongitude();
        cout << ") at " << setfill('0') << setw(2) << (int)(f->getDepartureTime() / 60.0);
        cout << ":" << setfill('0') << setw(2) << (int)fmod(f->getDepartureTime(), 60.0);
        cout << endl;

        cout << "        Arrives: " << dest->getCitySymbol();
        cout << " (" << setprecision(1) << fixed << dest->getCityLatitude();
        cout << ", " << dest->getCityLongitude();
        cout << ") at " << setfill('0') << setw(2) << (int)(f->getArriveTime() / 60.0);
        cout << ":" << setfill('0') << setw(2) << (int)fmod(f->getArriveTime(), 60.0);
        cout << endl;

        cout << "        Current location: (" << setprecision(4) << fixed << f->getCurrentLatitude();
        cout << ", " << f->getCurrentLongitude() << ")" << endl;

        cout << "                " << setprecision(1) << fixed << f->getCurDistanceFromStart();
        cout << " miles from " << depart->getCitySymbol();
        cout << ", " << f->getCurDistanceFromEnd() << " miles to " << dest->getCitySymbol() << endl;

        cout << "        Current speed: " << setprecision(0) << fixed << f->getCurrentSpeed();
        cout << " MPH" << endl;

        cout << "        Current altitude: " << f->getCurrentAltitude() << " feet" << endl;
        }
    }

    cout << endl << "=============================================================" << endl;
  }
//-----------------------------------------------------------------
// Get map of the cities
//-----------------------------------------------------------------
  CityMap* FlightSim::getCityMap() {
    return m_pCityMap;
  }