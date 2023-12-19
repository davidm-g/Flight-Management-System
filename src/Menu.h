#ifndef GRAPHPROJECT_MENU_H
#define GRAPHPROJECT_MENU_H
#include "Data.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

class Menu {
private:
    Data d;

public:
    Menu();
    int totalAirports();
    int totalFlights();
    pair<int, int> numFlightsAirlines(string apcode);
    int num_flights_airlines(string acode);
    int num_flights_city(string name);
    int num_countries_city(string city);
    int num_countries_airport(string acode);
    int num_cities_airport(string acode);
    int num_airports_airport(string acode);
    void dfs_Stops(string acode, int max_stops);
    void dfs_Visit_Stops(Vertex<Airport> * v , int max_stops, unordered_set<string>& countries,unordered_set<string>& cities, int& n_airports, int& n_cities, int& n_countries);
    vector<pair<int,pair<Airport,Airport>>>graph_diameter();
};


#endif //GRAPHPROJECT_MENU_H
