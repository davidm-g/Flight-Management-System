//
// Created by afdom on 23/12/2023.
//

#include "FlightOption.h"
using namespace std;

/**
 * FlightOption constructor - build a new menu
 */
FlightOption::FlightOption() {
    this->m = Menu();
}
Menu FlightOption::getMenu(){
    return this->m;
}
/**
 * available flights between two given airports with or without filters
 * @param source airport that we fly from
 * @param target airport that we fly to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_airport_airport(std::string source, std::string target, bool f1, bool f2, bool f3) {

    vector<vector<Vertex<Airport>*>> temp;

    if(f1) {
        temp = m.f1_shortest_paths(source, target);

    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        temp = m.f2_shortest_paths(source,target,air);

    }
    else if (f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        temp = m.f3_shortest_paths(source,target,countries);

    }
    else {
        temp = m.shortest_paths2(source,target);
    }
    if(temp.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two airports are:" << '\n';
    for (auto v: temp) {
        for (int i = 0; i < v.size() - 1; i++) {
            cout << v[i]->getInfo().getName() << " --> ";
        }
        cout << v[(v.size() - 1)]->getInfo().getName();
        cout << "\n";
    }

}
/**
 * available flights between a given airport and all the airports of a given city, with or without filters
 * @param source airport that we fly from
 * @param target city that we fly to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_airport_city(std::string source, std::string target, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    vector<string> airports;
    if(m.getData().getCity_by_country()[target].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[target].size() << " cities with the same name!" << '\n';
        cout << "Enter the desired target city's country:";
        string country;
        cin >> country;
        airports = m.city_airports_by_country(target,country);
    }
    else{ airports = m.city_airports(target);}

    if(f1){
        for(string airport_code : airports) {
            for (auto v: m.f1_shortest_paths(source, airport_code)) {
                res.push_back(v);
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string airport_code : airports) {
            for (auto v: m.f2_shortest_paths(source, airport_code,air)) {
                res.push_back(v);
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string airport_code : airports) {
            for (auto v: m.f3_shortest_paths(source, airport_code,countries)) {
                res.push_back(v);
            }
        }
    }
    else {
        for(string airport_code : airports) {
            for (auto v: m.shortest_paths2(source, airport_code)) {
                res.push_back(v);
            }
        }
    }

    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between that airport and that city are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}
/**
 * available flights between a given airport and all the closest airports to a given pair of coordinates, with or without filters
 * @param source airport that we fly from
 * @param lat latitude of the destination
 * @param longi longitude of the destination
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_airport_coordinates(std::string source, float lat, float longi, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    if(f1){
        for(string airport_code : m.findNearestAirports(lat, longi)) {
            for (auto v: m.f1_shortest_paths(source, airport_code)) {
                res.push_back(v);
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string airport_code : m.findNearestAirports(lat, longi)) {
            for (auto v: m.f2_shortest_paths(source, airport_code, air)) {
                res.push_back(v);
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string airport_code : m.findNearestAirports(lat, longi)) {
            for (auto v: m.f3_shortest_paths(source, airport_code, countries)) {
                res.push_back(v);
            }
        }
    }
    else {
        for(string airport_code : m.findNearestAirports(lat, longi)) {
            for (auto v: m.shortest_paths2(source, airport_code)) {
                res.push_back(v);
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}
/**
 * available flights between all the airports of a given city and a given airport, with or without filters
 * @param source city that we fly from
 * @param target airport that we fly to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */

void FlightOption::flight_city_airport(std::string source, std::string target, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    vector<string> airports;
    if(m.getData().getCity_by_country()[source].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[source].size() << " cities with the same name!" << '\n';
        cout << "Enter the desired source city's country:";
        string country;
        cin >> country;
        airports = m.city_airports_by_country(target,country);
    }
    else{ airports = m.city_airports(source);}
    if(f1){
        for(string airport_code : airports) {
            for (auto v: m.f1_shortest_paths(airport_code, target)) {
                res.push_back(v);
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string airport_code : airports) {
            for (auto v: m.f2_shortest_paths(airport_code, target, air)) {
                res.push_back(v);
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string airport_code : airports) {
            for (auto v: m.f3_shortest_paths(airport_code, target, countries)) {
                res.push_back(v);
            }
        }
    }
    else {
        for(string airport_code : airports) {
            for (auto v: m.shortest_paths2(airport_code, target)) {
                res.push_back(v);
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between that city and that airport are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}
/**
 * available flights between all the airports of two given cities, with or without filters
 * @param source city that we fly from
 * @param target city that we fly to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_city_city(std::string source, std::string target, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    vector<string> airports_source;
    vector<string> airports_target;
    if(m.getData().getCity_by_country()[source].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[source].size() << " source cities with the same name!" << '\n';
        cout << "Enter the desired source city's country:";
        string country;
        cin >> country;
        airports_source = m.city_airports_by_country(source,country);
    }
    else{ airports_source = m.city_airports(source);}


    if(m.getData().getCity_by_country()[target].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[target].size() << " target cities with the same name!" << '\n';
        cout << "Enter the desired target city's country:";
        string country;
        cin >> country;
        airports_target = m.city_airports_by_country(target,country);
    }
    else{ airports_target = m.city_airports(target);}

    if(f1){
        for (string airport_code: airports_source) {
            for (string t: airports_target){
                for (auto v: m.f1_shortest_paths(airport_code, t)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for (string airport_code: airports_source) {
            for (string t: airports_target) {
                for (auto v: m.f2_shortest_paths(airport_code, t, air)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for (string airport_code: airports_source) {
            for (string t: airports_target) {
                for (auto v: m.f3_shortest_paths(airport_code, t, countries)) {
                    res.push_back(v);
                }
            }
        }
    }
    else {
        for (string airport_code: airports_source) {
            for (string t: airports_target) {
                for (auto v: m.shortest_paths2(airport_code, t)) {
                    res.push_back(v);
                }
            }
        }
    }
    int min = INT_MAX;
    for (auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for (auto path: res) {
        if (path.size() == min) {
            for (int i = 0; i < path.size() - 1; i++) {
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}
/**
 * available flights between all the airports of a given city and all the closest airports to a given pair of coordinates, with or without filters
 * @param source city that we fly from
 * @param lat latitude of the destination
 * @param lon longitude of the destination
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_city_coordinates(std::string source, float lat, float lon, bool f1, bool f2, bool f3) {
    vector<string> airports;
    if(m.getData().getCity_by_country()[source].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[source].size() << " cities with the same name!" << '\n';
        cout << "Enter the desired source city's country:";
        string country;
        cin >> country;
        airports = m.city_airports_by_country(source,country);
    }
    else{ airports = m.city_airports(source);}
    vector<vector<Vertex<Airport>*>> res;
    if(f1){
        for(string ap_code_s : airports) {
            for (string ap_code_t: m.findNearestAirports(lat, lon)) {
                for (auto v: m.f1_shortest_paths(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string ap_code_s : airports) {
            for (string ap_code_t: m.findNearestAirports(lat, lon)) {
                for (auto v: m.f2_shortest_paths(ap_code_s, ap_code_t, air)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string ap_code_s : airports) {
            for (string ap_code_t: m.findNearestAirports(lat, lon)) {
                for (auto v: m.f3_shortest_paths(ap_code_s, ap_code_t, countries)) {
                    res.push_back(v);
                }
            }
        }
    }
    else {
        for(string ap_code_s : airports) {
            for (string ap_code_t: m.findNearestAirports(lat, lon)) {
                for (auto v: m.shortest_paths2(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}

/**
 * available flights between all the closest airports to a given pair of coordinates and a given airport, with or without filters
 * @param lat latitude of the source
 * @param lon longitude of the source
 * @param target airport that we flight to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_coordinates_airport(float lat, float lon, std::string target, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    if(f1){
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (auto v: m.f1_shortest_paths(ap_code_s, target)) {
                res.push_back(v);
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (auto v: m.f2_shortest_paths(ap_code_s, target, air)) {
                res.push_back(v);
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (auto v: m.f3_shortest_paths(ap_code_s, target, countries)) {
                res.push_back(v);
            }
        }
    }
    else {
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (auto v: m.shortest_paths2(ap_code_s, target)) {
                res.push_back(v);
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }

}
/**
 * available flights between all the closest airports to a given pair of coordinates and all the airports of a given city, with or without filters
 * @param lat latitude of the source
 * @param lon longitude of the source
 * @param target city that we flight to
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_coordinates_city(float lat, float lon, std::string target, bool f1, bool f2, bool f3) {
    vector<string> airports;
    if(m.getData().getCity_by_country()[target].size() > 1){
        cout << "There are " << m.getData().getCity_by_country()[target].size() << " cities with the same name!" << '\n';
        cout << "Enter the desired target city's country:";
        string country;
        cin >> country;
        airports = m.city_airports_by_country(target,country);
    }
    else{ airports = m.city_airports(target);}
    vector<vector<Vertex<Airport>*>> res;
    if(f1){
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (string ap_code_t: airports) {
                for (auto v: m.f1_shortest_paths(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (string ap_code_t: airports) {
                for (auto v: m.f2_shortest_paths(ap_code_s, ap_code_t, air)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (string ap_code_t: airports) {
                for (auto v: m.f3_shortest_paths(ap_code_s, ap_code_t, countries)) {
                    res.push_back(v);
                }
            }
        }
    }
    else {
        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
            for (string ap_code_t: airports) {
                for (auto v: m.shortest_paths2(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}

/**
 * available flights between all the closest airports to two given pairs of coordinates, with or without filters
 * @param lat1 latitude of the source
 * @param lon1 longitude of the source
 * @param lat2 latitude of the destination
 * @param lon2 longitude of the destination
 * @param f1 minimal use of different airlines filter
 * @param f2 use a specific set of airlines filter
 * @param f3 avoid a set of countries filter
 */
void FlightOption::flight_coordinates_coordinates(float lat1, float lon1, float lat2, float lon2, bool f1, bool f2, bool f3) {
    vector<vector<Vertex<Airport>*>> res;
    if(f1) {
        for (string ap_code_s: m.findNearestAirports(lat1, lon1)) {
            for (string ap_code_t: m.findNearestAirports(lat2, lon2)) {
                for (auto v: m.f1_shortest_paths(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f2){
        set<string> air;
        string acode;
        cout << "Please insert the preferred airline codes separated by a ',':";
        string line;
        getline(cin, line);
        air.insert(acode);
        istringstream iss(line);
        while(getline(iss, acode, ',')) {
            air.insert(acode);
        }
        for (string ap_code_s: m.findNearestAirports(lat1, lon1)) {
            for (string ap_code_t: m.findNearestAirports(lat2, lon2)) {
                for (auto v: m.f2_shortest_paths(ap_code_s, ap_code_t,air)) {
                    res.push_back(v);
                }
            }
        }
    }
    else if(f3){
        set<string> countries;
        string country;
        cout << "Please insert the countries to avoid separated by a ',':";
        string line;
        getline(cin, line);
        countries.insert(country);
        istringstream iss(line);
        while(getline(iss, country, ',')) {
            countries.insert(country);
        }
        for (string ap_code_s: m.findNearestAirports(lat1, lon1)) {
            for (string ap_code_t: m.findNearestAirports(lat2, lon2)) {
                for (auto v: m.f3_shortest_paths(ap_code_s, ap_code_t,countries)) {
                    res.push_back(v);
                }
            }
        }
    }
    else{
        for (string ap_code_s: m.findNearestAirports(lat1, lon1)) {
            for (string ap_code_t: m.findNearestAirports(lat2, lon2)) {
                for (auto v: m.shortest_paths2(ap_code_s, ap_code_t)) {
                    res.push_back(v);
                }
            }
        }
    }
    int min=INT_MAX;
    for(auto path: res) {
        if (path.size() <= min) {
            min = path.size();
        }
    }
    if(res.empty()){
        cout << "There are no flights between these two locations\n\n";
        return;
    }
    cout << "The best flight options between those two cities are:" << '\n';
    for(auto path : res){
        if(path.size()==min){
            for(int i = 0; i < path.size() - 1; i++){
                cout << path[i]->getInfo().getName() << " --> ";
            }
            cout << path[(path.size() - 1)]->getInfo().getName();
            cout << "\n";
        }
    }
}





