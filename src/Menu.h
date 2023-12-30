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
#include <limits>
/**
 * @class Menu
 * @brief Represents the user-friendly interface for the flight management system.
 * It shows available functionalities and their corresponding outputs in a clear, organized,
 * and logical manner, facilitating seamless program utilization and straightforward result
 * interpretation.
 */
class Menu {
private:
    Data d;

public:
    Menu();
    int totalAirports();
    int totalFlights();
    void numFlightsAirlines(string apcode);
    int num_flights_airlines(string acode);
    int num_flights_city(string name);
    int num_countries_city(string city);
    int num_countries_airport(string acode);
    void bfs_Stops(string acode, int max_stops);
    void dfs_Des(string acode);
    void dfs_Visit_Des(Vertex<Airport> * v , unordered_set<string>& countries,set<pair<string,string>>& cities, int& n_airports);
    vector<pair<int,pair<Airport,Airport>>>graph_diameter();
    vector<pair<int,Airport>> greatest_air_traffic(int k);
    unordered_set<Vertex<Airport>*> Articu_points();
    void dfs_arti(Vertex<Airport>* v, stack<Airport>& s, unordered_set<Vertex<Airport>*>& res, int& i);
    vector<string> findNearestAirports(double lat, double lon);
    vector<string> city_airports(string city);
    vector<vector<Vertex<Airport>*>> f1_shortest_paths(string start, string target);
    vector<vector<Vertex<Airport>*>> shortest_paths2(string source, string target);
    vector<vector<Vertex<Airport>*>> f2_shortest_paths(string start, string target, set<string> air);
    vector<vector<Vertex<Airport>*>> f3_shortest_paths(string start, string target, set<string> countries);
    Data getData();
    int num_flights_city_country(string city, string country);
    int num_countries_city2(string city, string country);
    vector<string> city_airports_by_country(string city,string country);
};


#endif //GRAPHPROJECT_MENU_H
