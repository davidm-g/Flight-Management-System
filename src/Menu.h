#ifndef GRAPHPROJECT_MENU_H
#define GRAPHPROJECT_MENU_H
#include "Data.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <set>
#include <algorithm>
#include <map>

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
    vector<pair<int,Airport>> greatest_air_traffic(int k);
    set<Airport> Articu_points();
    void dfs_arti(Vertex<Airport>* v, stack<Airport>& s, set<Airport>& res, int& i);
    vector<vector<Airport>> shortest_distance_airports(string source, string target);
    vector<Airport> findNearestAirports(double lat, double lon);
    vector<std::vector<Airport>> shortest_paths(string start,string end);
};


#endif //GRAPHPROJECT_MENU_H
