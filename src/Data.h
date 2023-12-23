//
// Created by afdom on 18/12/2023.
//

#include "graph.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Airport.h"
#include "unordered_map"


#ifndef GRAPHPROJECT_DATA_H
#define GRAPHPROJECT_DATA_H
/**
 * @class Data
 * @brief Represents the data that was parsed from the csv files.
 */
using namespace std;
class Data {
    private:
        Graph<Airport> ap;
        std::unordered_map<string,Airline> airlines;
        std::unordered_map<string,Vertex<Airport>*> airports;
        std::unordered_multimap<string,Vertex<Airport>*> airports_by_city;
    public:
        void parse_airports();
        Graph<Airport> getAP();
        void parse_flights();
        void parse_airlines();
        unordered_map<string, Airline> getAirlines();
        unordered_map<string, Vertex<Airport>*> getAirports();
        unordered_multimap<string, Vertex<Airport>*> getAirportsByCity();
};


#endif //GRAPHPROJECT_DATA_H
