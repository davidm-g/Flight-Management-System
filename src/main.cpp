#include <iostream>
#include <climits>
#include "Data.h"
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
#include "Menu.h"
using namespace std;
int main() {
    Menu m = Menu();
    int choice;
    bool filter_min_airlines;
    bool filter_airlines_list;
    bool filter_avoid_countries;
    while (true) {
        cout << " _________________________________________ " << '\n';
        cout << "|      Flight Management System           |" << '\n';
        cout << "|                                         |" << '\n';
        cout << "|1.  Nr of airports                       |" << '\n';
        cout << "|2.  Nr of flights                        |" << '\n';
        cout << "|3.  Nr of out flights from an airport    |" << '\n';
        cout << "|    and different airlines               |" << '\n';
        cout << "|4.  Nr of flights per city/airline       |" << '\n';
        cout << "|5.  Nr of countries from airport/city    |" << '\n';
        cout << "|6.  Nr of destinations from airport      |" << '\n';
        cout << "|7.  Reachable destinations with x stops  |" << '\n';
        cout << "|8.  Maximum trip                         |" << '\n';
        cout << "|9.  Top-k airports by air traffic        |" << '\n';
        cout << "|10. Articulation points                  |" << '\n';
        cout << "|11. Best flight option                   |" << '\n';
        cout << "|12. Flight filters configurations        |" << '\n';
        cout << "|13. Exit                                 |" << '\n';
        cout << "|_________________________________________|" << "\n";
        cout << "Please enter your choice:";
        cin >> choice;
        if(!cin) {
            std::cout << "Invalid option." << '\n'
                      << "The program will stop.";
            break;
        }

        switch (choice) {
            case 1: {
                cout << "The total number of airports is " << m.totalAirports() << '\n';
                break;
            }
            case 2: {
                cout << "The total number of flights is " << m.totalFlights() << '\n';
                break;
            }
            case 3 :{
                string acode;
                cout << "Type in the wanted airport code:";
                cin >> acode;
                pair<int, int> p = m.numFlightsAirlines(acode);
                cout << p.first << "flights out of " << acode << " airport from "
                    << p.second << "different airlines." << '\n';
                break;
            }
            case 4:{
                cout<<"1. Number of flights per city"<<endl;
                cout<<"2. Number of flights per airline"<<endl;
                cout << "Please enter your desired choice: ";
                int escolha;
                cin>>escolha;
                switch (escolha) {
                    case 1:{
                        cout<<"Enter the desired city: ";
                        string city;
                        cin>>city;
                        cout << "The number of in and out flights in " << city << " is : " << m.num_flights_city(city) << '\n' << '\n';
                        break;
                    }
                    case 2:{
                        cout << "Enter the desired airline code: ";
                        string acode;
                        cin >> acode;
                        cout << "The number of in and out flights from airline " << acode <<" is : " << m.num_flights_airlines(acode) << '\n' << '\n';
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please enter a valid option." << '\n';
                        break;
                    }
                }
                break;
            }
            case 5: {
                cout<<"1. Number of different countries for a given city: "<<endl;
                cout<<"2. Number of different countries for a given airport: "<<endl;
                cout << "Please enter your desired choice: ";
                int escolha;
                cin >> escolha;
                cin.ignore(); // ignore the newline character that remained
                switch (escolha) {
                    case 1:{
                        cout << "Enter the desired city: ";
                        string city;
                        getline(cin,city);
                        cout << "The city of " << city << " flies to "  << m.num_countries_city(city) << " different countries\n";
                        break;
                    }
                    case 2:{
                        cout << "Enter the desired airport code: ";
                        string acode;
                        cin >> acode;
                        cout << "The airport " << acode << " flies to "  << m.num_countries_airport(acode) << " different countries\n";
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please enter a valid option." << '\n';
                        break;
                    }
                }
                break;
            }
            case 6: {
                string acode;
                cout << "Please enter the desire airport code:\n";
                cin >> acode;
                m.dfs_Des(acode);
                break;
            }
            case 7: {
                string acode;
                cout << "Please enter the desired airport code:";
                cin >> acode;
                int max_stops;
                cout << "Please enter the maximum number of lay-overs:";
                cin >> max_stops;
                m.bfs_Stops(acode,max_stops);
                break;
            }
            case 8:{
                cout << "The maximum number of stops between two airports is: "<<m.graph_diameter()[0].first<<'\n';
                for(auto p : m.graph_diameter()){
                    cout << "And that distance is between " << p.second.first.getName()
                    << " and "<< p.second.second.getName() << " airports\n";
                }
                break;
            }
            case 9: {
                cout<<"Please enter the number of airports to display in terms of number of flights ranking:"<<'\n';
                int k;
                cin>>k;
                cout <<"The top " << k << " airports with the greatest air traffic capacity are: \n";
                for(auto ap : m.greatest_air_traffic(k)){
                    cout << ap.second.getName() << " located in " << ap.second.getCity()
                    << ", " << ap.second.getCountry() <<" with "<< ap.first << " flights.\n";
                }
                break;
            }
            case 10:  {
                cout << "The airports that are essential to networks circulation capability are:\n";
                for(auto ap : m.Articu_points()){
                    cout << ap.getName() << " located in " << ap.getCity() << ", " << ap.getCountry() << ".\n";
                }
                cout << '\n';
                cout << "There are in total " << m.Articu_points().size() << " essential airports\n";
                break;
            }
            case 11: {
                cout << " ___________________________________________ " << '\n';
                cout << "|           Best Flight Options             |" << '\n';
                cout << "|1. Best flight airport --> airport         |" << '\n';
                cout << "|2. Best flight airport --> city            |" << '\n';
                cout << "|3. Best flight airport --> coordinates     |" << '\n';
                cout << "|4. Best flight city --> airport            |" << '\n';
                cout << "|5. Best flight city --> city               |" << '\n';
                cout << "|6. Best flight city --> coordinates        |" << '\n';
                cout << "|7. Best flight coordinates --> airport     |" << '\n';
                cout << "|8. Best flight coordinates --> city        |" << '\n';
                cout << "|9. Best flight coordinates --> coordinates |" << '\n';
                cout << "|___________________________________________|" << '\n';
                cout << "Please select your desired method: ";
                int so;
                cin >> so;
                cin.ignore();
                switch (so) {
                    case 1:{

                        cout << "Insert a source airport code/name: ";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target airport code/name: ";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        cout << "The best flight options between those two airports are:" << '\n';
                        vector<vector<Vertex<Airport>*>> temp;
                        if(filter_min_airlines) {
                            temp = m.f1_shortest_paths(source, target);

                            for (auto v: temp) {
                                for (int i = 0; i < v.size() - 1; i++) {
                                    cout << v[i]->getInfo().getName() << " --> ";
                                }
                                cout << v[(v.size() - 1)]->getInfo().getName();
                                cout << "\n";
                            }
                        }
                        else {
                            for (auto v: m.shortest_paths2(source, target)) {
                                for (int i = 0; i < v.size() - 1; i++) {
                                    cout << v[i]->getInfo().getName() << " --> ";
                                }
                                cout << v[(v.size() - 1)]->getInfo().getName();
                                cout << "\n";
                            }
                        }

                        break;
                    }

                    case 2:{
                        cout << "Insert a source airport code/name: ";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target city: ";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        cout << "The best flight options between that airport and that city are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string airport_code : m.city_airports(target)) {
                            for (vector<Airport> v: m.shortest_paths(source, airport_code)) {
                                res.push_back(v);
                            }
                        }

                        int min=INT_MAX;
                        for(auto path: res) {
                            if (path.size() <= min) {
                                min = path.size();
                            }
                        }
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //airport ---> city
                        break;
                    }

                    case 3: {
                        string source;
                        cout << "Insert a source airport code/name: ";
                        cin >> source;
                        double lat, lon;
                        cout << "Insert the latitude of the target airport: ";
                        cin >> lat;
                        cout << '\n';
                        cout << "Insert the longitude of the target airport: ";
                        cin >> lon;
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string airport_code : m.findNearestAirports(lat, lon)) {
                            for (vector<Airport> v: m.shortest_paths(source, airport_code)) {
                                res.push_back(v);
                            }
                        }
                        int min=INT_MAX;
                        for(auto path: res) {
                            if (path.size() <= min) {
                                min = path.size();
                            }
                        }
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //airport ---> coordinates
                        break;
                    }
                    case 4:{
                        cout << "Insert a source city: ";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target airport code/name: ";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        cout << "The best flight options between that city and that airport are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string airport_code : m.city_airports(source)) {
                            for (vector<Airport> v: m.shortest_paths(airport_code, target)) {
                                res.push_back(v);
                            }
                        }
                        int min=INT_MAX;
                        for(auto path: res) {
                            if (path.size() <= min) {
                                min = path.size();
                            }
                        }
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //city ---> airport
                        break;
                    }
                    case 5: {
                        cout << "Insert a source city: ";
                        string source;
                        getline(cin, source);
                        cout << "Insert a target city: ";
                        string target;
                        getline(cin, target);
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for (string airport_code: m.city_airports(source)) {
                            for (string t: m.city_airports(target)) {
                                for (vector<Airport> v: m.shortest_paths(airport_code, t)) {
                                    res.push_back(v);
                                }
                            }
                        }
                        int min = INT_MAX;
                        for (auto path: res) {
                            if (path.size() <= min) {
                                min = path.size();
                            }
                        }
                        for (auto path: res) {
                            if (path.size() == min) {
                                for (int i = 0; i < path.size() - 1; i++) {
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //city ---> city
                        break;
                    }
                    case 6: {
                        string source;
                        cout << "Insert a source city: ";
                        cin >> source;
                        double lat, lon;
                        cout << "Insert the latitude of the target airport: ";
                        cin >> lat;
                        cout << "Insert the longitude of the target airport: ";
                        cin >> lon;
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string ap_code_s : m.city_airports(source)) {
                            for (string ap_code_t: m.findNearestAirports(lat, lon)) {
                                for (vector<Airport> v: m.shortest_paths(ap_code_s, ap_code_t)) {
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
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //city ---> coordinates
                        break;
                    }
                    case 7:{
                        double lat, lon;
                        cout << "Insert the latitude of the source airport: ";
                        cin >> lat;
                        cout << "Insert the longitude of the source airport: ";
                        cin >> lon;
                        string target;
                        cout << "Insert a target airport code/name: ";
                        cin >> target;
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
                            for (vector<Airport> v: m.shortest_paths(ap_code_s, target)) {
                                res.push_back(v);
                            }

                        }
                        int min=INT_MAX;
                        for(auto path: res) {
                            if (path.size() <= min) {
                                min = path.size();
                            }
                        }
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //coordinates ---> airport
                        break;
                    }
                    case 8:{
                        double lat, lon;
                        cout << "Insert the latitude of the source airport: ";
                        cin >> lat;
                        cout << "Insert the longitude of the source airport: ";
                        cin >> lon;
                        string target;
                        cout << "Insert a target city: ";
                        cin >> target;
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string ap_code_s : m.findNearestAirports(lat, lon)) {
                            for (string ap_code_t: m.city_airports(target)) {
                                for (vector<Airport> v: m.shortest_paths(ap_code_s, ap_code_t)) {
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
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //coordinates ---> city
                        break;
                    }
                    case 9:{
                        double lat1, lon1;
                        cout << "Insert the latitude of the source airport: ";
                        cin >> lat1;
                        cout << "Insert the longitude of the source airport: ";
                        cin >> lon1;
                        double lat2, lon2;
                        cout << "Insert the latitude of the target airport: ";
                        cin >> lat2;
                        cout << "Insert the longitude of the target airport: ";
                        cin >> lon2;
                        cout << '\n';
                        cout << "The best flight options between those two cities are: " << '\n';
                        vector<vector<Airport>> res;
                        for(string ap_code_s : m.findNearestAirports(lat1, lon1)) {
                            for (string ap_code_t: m.findNearestAirports(lat2, lon2)) {
                                for (vector<Airport> v: m.shortest_paths(ap_code_s, ap_code_t)) {
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
                        for(auto path : res){
                            if(path.size()==min){
                                for(int i = 0; i < path.size() - 1; i++){
                                    cout << path[i].getName() << " --> ";
                                }
                                cout << path[(path.size() - 1)].getName();
                                cout << "\n";
                            }
                        }
                        //coordinates ---> coordinates
                        break;
                    }

                    default:{
                        cout << "Invalid choice. Please enter a valid option." << '\n';
                        break;
                    }

                }

                break;
            }
            case 12: {
                cout << " ___________________________________________ " << '\n';
                cout << "|                Filter List                |" << '\n';
                cout << "|1. Minimum airlines flight                 |" << '\n';
                cout << "|2. Preferred airlines flight               |" << '\n';
                cout << "|3. Flight avoiding countries               |" << '\n';
                cout << "|4. Turn off filters                        |" << '\n';
                cout << "|___________________________________________|" << '\n';
                cout << "Please select the filter to enable: ";
                int c;
                cin >> c;
                switch (c) {
                    case 1:{
                        filter_min_airlines = true;
                        filter_airlines_list = false;
                        filter_avoid_countries = false;
                        break;
                    }
                    case 2:{
                        filter_min_airlines = false;
                        filter_airlines_list = true;
                        filter_avoid_countries = false;
                        break;
                    }
                    case 3:{
                        filter_min_airlines = false;
                        filter_airlines_list = false;
                        filter_avoid_countries = true;
                        break;
                    }
                    case 4:{
                        filter_min_airlines = false;
                        filter_airlines_list = false;
                        filter_avoid_countries = false;
                        break;
                    }
                }
                break;
            }
            case 13: {
                cout << "Goodbye! :(" << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << '\n';
                break;
            }
        }
    }
}
