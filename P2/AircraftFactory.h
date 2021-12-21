

#include <map>
#include <string>
#include "AircraftTypes.h"
#include "Aircraft.h"
#include "FlightDataParser.h"

using namespace std;

//------------------------------------------
// The abstract aircraft factory used as interface for all concrete classes.
//------------------------------------------
class AircraftFactory {   
    protected:
        map<string, Aircraft*> m_map;
        FlightDataParser * m_pFD;

    public: 
        AircraftFactory();
        virtual ~AircraftFactory();
        virtual Aircraft* getAircraft(const char * sMake) = 0;    
};

class PassengerJetFactory : public AircraftFactory {
    private:
        PassengerJetFactory();
    public:    
        ~PassengerJetFactory();        
        Aircraft* getAircraft(const char * sMake);  
        static PassengerJetFactory* getInstance();
};

class BusinessJetFactory : public AircraftFactory {
    private:
        BusinessJetFactory();
    public:            
        ~BusinessJetFactory();    
        Aircraft* getAircraft(const char * sMake); 
        static BusinessJetFactory* getInstance();  
};

class SingleEnginePlaneFactory : public AircraftFactory {
    private:
        SingleEnginePlaneFactory();
    public:           
        ~SingleEnginePlaneFactory();
        Aircraft* getAircraft(const char * sMake); 
        static SingleEnginePlaneFactory* getInstance();  
};