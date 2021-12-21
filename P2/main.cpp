//========================================================
// main.cpp
// Implementation file for the main class.
//
// Author: Ulugbek Nosirov
// Date: April 2021
//========================================================

#include "FlightSim.h"

int main()
{
    string flightSimDataFile;
    int speed = 1;

    cout << "==============================================================" << endl;
    cout << "|          AIRLINE FLIGHT SIMULATION DEMONSTRATION           |" << endl;
    cout << "==============================================================" << endl << endl;

    cout << "Please enter the name of the simulation data file then press Enter:" << endl;
    cout << "         ";

    getline(cin, flightSimDataFile);

    cout << endl << "At what speed do you want to run the simulation? (1x, 2x, 3x)" << endl;
    cout << "         Please enter 1, 2, or 3 and press Enter" << endl;

    cin >> speed;

    while (speed > 3 || speed < 1) {
        cout << endl << "That is an invalid speed. Enter (1, 2, or 3). Try again." << endl;
        cin >> speed;
    }

    cout << endl;

    FlightSim* pFlightSim = FlightSim::getInstance(flightSimDataFile.c_str());

    pFlightSim->buildFlightVector();

    pFlightSim->RunSim(speed); //start the simulation

    cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "|             The simulation has run to completion           |" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    delete pFlightSim;
    
    return 0;
}
