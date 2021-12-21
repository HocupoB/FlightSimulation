//========================================================
// AircraftFactory.cpp
// Implementation file for the AircraftFactory class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include "AircraftFactory.h"

AircraftFactory::AircraftFactory() : m_pFD(FlightDataParser::getInstance()) {}

AircraftFactory::~AircraftFactory() {
    // delete the items in the map
    for (map<string, Aircraft*>::iterator it = m_map.begin(); it != m_map.end(); it++) {
        delete it->second;
    }
}

/* Passenger Jet Factory Definitions */

PassengerJetFactory::PassengerJetFactory() {
    // Data points
    char sMake[32];
    char sDesc[32];
    double dRateofClimb;
    double dWingSpan;
    double dLength;
    double dCruiseSpeed;
    double dCruiseAlt;

    PassengerJet * pj = NULL;

    // Parse all the data of this type
    while (m_pFD->getAircraftData(PASSENGERJET, sMake, sDesc, &dRateofClimb,
    &dWingSpan, &dLength, &dCruiseSpeed, &dCruiseAlt)) {
        pj = new PassengerJet();

        pj->setAircraftMake(sMake);
        pj->setAircraftDescription(sDesc);
        pj->setAircraftRateOfClimb(dRateofClimb);
        pj->setAircraftWingSpan(dWingSpan);
        pj->setAircraftLength(dLength);
        pj->setAircraftCruiseSpeed(dCruiseSpeed);
        pj->setAirCruiseAltitude(dCruiseAlt);

        string strMake = sMake;

        m_map[strMake] = pj; // store in the map
    }
}

PassengerJetFactory::~PassengerJetFactory() {

}

Aircraft* PassengerJetFactory::getAircraft(const char * sMake) {
    return m_map[sMake];
}

PassengerJetFactory* PassengerJetFactory::getInstance() {
    static PassengerJetFactory* instance = NULL;

    if (instance == NULL) {
        instance = new PassengerJetFactory();
    }

    return instance;
}

/* Business Jet Factory Definitions */

BusinessJetFactory::BusinessJetFactory() {
    // Data points
    char sMake[32];
    char sDesc[32];
    double dRateofClimb;
    double dWingSpan;
    double dLength;
    double dCruiseSpeed;
    double dCruiseAlt;

    BusinessJet * pj = NULL;

    // Parse all the data of this type
    while (m_pFD->getAircraftData(BUSINESSJET, sMake, sDesc, &dRateofClimb,
    &dWingSpan, &dLength, &dCruiseSpeed, &dCruiseAlt)) {
        pj = new BusinessJet();

        pj->setAircraftMake(sMake);
        pj->setAircraftDescription(sDesc);
        pj->setAircraftRateOfClimb(dRateofClimb);
        pj->setAircraftWingSpan(dWingSpan);
        pj->setAircraftLength(dLength);
        pj->setAircraftCruiseSpeed(dCruiseSpeed);
        pj->setAirCruiseAltitude(dCruiseAlt);

        string strMake = sMake;

        m_map[strMake] = pj; // store in the map
    }
}

BusinessJetFactory::~BusinessJetFactory() {
}

Aircraft* BusinessJetFactory::getAircraft(const char * sMake) {
    return m_map[sMake];
}

BusinessJetFactory* BusinessJetFactory::getInstance() {
    static BusinessJetFactory* instance = NULL;

    if (instance == NULL) {
        instance = new BusinessJetFactory();
    }

    return instance;
}

/* Single Engine Plane Factory Definitions */

SingleEnginePlaneFactory::SingleEnginePlaneFactory() {
    // Data points
    char sMake[32];
    char sDesc[32];
    double dRateofClimb;
    double dWingSpan;
    double dLength;
    double dCruiseSpeed;
    double dCruiseAlt;

    SingleEnginePlane * se = NULL;

    // Parse all the data of this type
    while (m_pFD->getAircraftData(SINGLEENGINE, sMake, sDesc, &dRateofClimb,
    &dWingSpan, &dLength, &dCruiseSpeed, &dCruiseAlt)) {
        se = new SingleEnginePlane();

        se->setAircraftMake(sMake);
        se->setAircraftDescription(sDesc);
        se->setAircraftRateOfClimb(dRateofClimb);
        se->setAircraftWingSpan(dWingSpan);
        se->setAircraftLength(dLength);
        se->setAircraftCruiseSpeed(dCruiseSpeed);
        se->setAirCruiseAltitude(dCruiseAlt);

        string strMake = sMake;

        m_map[strMake] = se; // store in the map
    }
}

SingleEnginePlaneFactory::~SingleEnginePlaneFactory() {

}

Aircraft* SingleEnginePlaneFactory::getAircraft(const char * sMake) {
    return m_map[sMake];
}

SingleEnginePlaneFactory* SingleEnginePlaneFactory::getInstance() {
    static SingleEnginePlaneFactory* instance = NULL;

    if (instance == NULL) {
        instance = new SingleEnginePlaneFactory();
    }

    return instance;
}