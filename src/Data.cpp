#include <iostream>
#include "Data.h"

using namespace std;

Graph<Airport> Data::getAP(){
    return ap;
}

unordered_map<string, Airline> Data::getAirlines() {
    return airlines;
}
unordered_map<string, Vertex<Airport>* > Data::getAirports() {
    return airports;
}

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
        Vertex<Airport>* aero_vertex=  new Vertex<Airport>(aero);
        ap.addVertex(  aero_vertex);
        airports[code]=aero_vertex;
    }

}
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
        for (auto a : ap.getVertexSet())
            if(a->getInfo().getCode() == target)
                a->setIndegree(a->getIndegree() + 1);
    }

}