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

using namespace std;
class Data {
    private:
        Graph<Airport> ap;
        std::unordered_map<string,Airline> airlines;
    public:
        void parse_airports();
        Graph<Airport> getAP();
        void parse_flights();
        void parse_airlines();
        unordered_map<string, Airline> getAirlines();
};


#endif //GRAPHPROJECT_DATA_H
