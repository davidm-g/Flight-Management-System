#include <iostream>
#include "Data.h"

using namespace std;
/**
 * function that retrieves the graph contain all the information about the flight management system - complexity O(1)
 * @return graph whose vertices correspond to Airports and the Edges to flights
 */
Graph<Airport> Data::getAP(){
    return ap;
}
/**
 * function that retrieves an unordered_map that stores key value pairs
 * of airline codes and their corresponding Airlines, allowing for constant lookup of Airlines by their code - complexity O(1)
 * @return unordered_map that stores key value pairs
 * of airline codes and their corresponding Airlines
 */
unordered_map<string, Airline> Data::getAirlines() {
    return airlines;
}
/**
  * function that retrieves an unordered_map that stores key value pairs
 * of airport codes and their corresponding Airports, allowing constant lookup of Airports by their code - complexity O(1)
 * @return unordered_map that stores key value pairs
 * of airport codes and their corresponding Airports
 */
unordered_map<string, Vertex<Airport>* > Data::getAirports() {
    return airports;
}
/**
  * function that retrieves an unordered_multimap that stores key value pairs
 * of cities and their corresponding Airports, allowing constant lookup of Airports by their city - complexity O(1)
 * @return unordered_map that stores key value pairs
 * of cities and their corresponding Airports
 */
unordered_multimap<string, Vertex<Airport>*> Data::getAirportsByCity(){
    return airports_by_city;
}

/**
 * function that parses the data from the airports.csv file and uses it to build a graph accordingly - complexity O(N) where N is the number of lines in the file
 */
void Data::parse_airports() {
    ifstream apfile("airports.csv");
    string line;
    getline(apfile, line); // ler e ignorar a primeira linha

    while (getline(apfile, line)) {
        string code, name, city, country, latitude, longitude;

        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, latitude, ',');
        getline(iss, longitude);
        float lat = stof(latitude);
        float lon = stof(longitude);
        Airport aero = Airport(code,name,city,country,lat,lon);
        Vertex<Airport>* aero_vertex =  new Vertex<Airport>(aero);
        ap.addVertex(  aero_vertex);
        airports[code]=aero_vertex;
        airports[city] = aero_vertex;
    }

}
/**
 * function that parses the data from the airlines.csv file and uses it to build a graph accordingly - complexity O(N) where N is the number of lines in the file
 */
void Data::parse_airlines() {
    ifstream alfile("airlines.csv");
    string line;
    getline(alfile, line); // ler e ignorar a primeira linha

    while (getline(alfile, line)) {
        string code, name, callsign, country;

        istringstream iss(line);
        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callsign, ',');
        getline(iss, country);
        Airline newairline = Airline(code,name,callsign,country);
        airlines[code] = newairline;
    }

}


/**
 * function that parses the data from the flights.csv file and uses it to build a graph accordingly - complexity O(N) where N is the number of lines in the file
 */
void Data::parse_flights() {
    ifstream ffile("flights.csv");
    string line;
    getline(ffile, line); // ler e ignorar a primeira linha

    while (getline(ffile, line)) {
        string src, target, al_code;
        istringstream iss(line);
        getline(iss, src, ',');
        getline(iss, target, ',');
        getline(iss, al_code);

        ap.addEdge(Airport(src), Airport(target),al_code, 0.0);
    }

}
/**
 * function that calculates the indegree of each vertex - complexity O(V + E) where V is the number of vertices and E the number of edges of each vertex
 */
void Data::calculate_indegree(){
    for(auto v : ap.getVertexSet()){
        for(auto e : v->getAdj()){
            e.getDest()->setIndegree(e.getDest()->getIndegree() + 1);
        }
    }
}
