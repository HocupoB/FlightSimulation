CC = g++
FLAGS = -Wall -g -std=c++11

all: as

as: AircraftFactory.o Aircraft.o City.o CityDataParser.o CityMap.o Flight.o FlightDataParser.o FlightSim.o main.o 
	$(CC) $(FLAGS) -o as AircraftFactory.o Aircraft.o City.o CityDataParser.o CityMap.o Flight.o FlightDataParser.o FlightSim.o main.o

AircraftFactory.o: AircraftFactory.cpp
	$(CC) $(FLAGS) -c -o AircraftFactory.o AircraftFactory.cpp

Aircraft.o: Aircraft.cpp
	$(CC) $(FLAGS) -c -o Aircraft.o Aircraft.cpp

City.o: City.cpp
	$(CC) $(FLAGS) -c -o City.o City.cpp

CityDataParser.o: CityDataParser.cpp
	$(CC) $(FLAGS) -c -o CityDataParser.o CityDataParser.cpp

CityMap.o: CityMap.cpp
	$(CC) $(FLAGS) -c -o CityMap.o CityMap.cpp

Flight.o: Flight.cpp
	$(CC) $(FLAGS) -c -o Flight.o Flight.cpp

FlightDataParser.o: FlightDataParser.cpp
	$(CC) $(FLAGS) -c -o FlightDataParser.o FlightDataParser.cpp

FlightSim.o: FlightSim.cpp
	$(CC) $(FLAGS) -c -o FlightSim.o FlightSim.cpp

clean:
	rm -f *.o as 