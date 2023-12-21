#include <iostream>
#include "Data.h"
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
#include "Menu.h"
using namespace std;
int main() {
    Menu m = Menu();
    int choice;
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
        cout << "|12. Best flight option with filters      |" << '\n';
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
                cout << "Airport " << acode << " flies to: " << m.num_countries_airport(acode)
                << " countries, " << m.num_cities_airport(acode) << " cities and "
                    << m.num_airports_airport(acode) << " airports.\n";
                break;
            }
            case 7: {
                string acode;
                cout << "Please enter the desire airport code:";
                cin >> acode;
                int max_stops;
                cout << "Please enter the maximum number of lay-overs:";
                cin >> max_stops;
                m.dfs_Stops(acode,max_stops);
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
                cout << "1. Flight between two airports" << '\n';
                cout << "2. (Temporary) Find nearest airports" << '\n';
                cout << "Please select your desired method: ";
                int so;
                cin >> so;
                cin.ignore();
                switch (so) {
                    case 1:{
                        cout << "Please insert a source airport code/name: ";
                        string source;
                        getline(cin,source);
                        cout << "Please insert a target airport code/name: ";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        cout << "The best flight options between those two airports are:\n";
                        for(auto v : m.shortest_paths(source,target)){
                            for(int i = 0; i < v.size() - 1; i++){
                                cout << v[i].getName() << " --> ";
                            }
                            cout << v[(v.size() - 1)].getName();
                            cout << "\n";
                        }

                        break;
                    }

                    case 2:{
                        double lat, lon;
                        cout << "Latitude:";
                        cin >> lat;
                        cout << '\n' << "Longitude:";
                        cin >> lon; \
                        cout << '\n';
                        for(auto ap : m.findNearestAirports(lat, lon))
                            cout << ap.getName() << '\n';
                        //airport ---> city
                        break;
                    }

                    case 3:{
                        string apcode;
                        cin >> apcode;
                        double lat, lon;
                        cin >> lat;
                        cin >> lon;
                        //airport ---> coordinates
                        break;
                    }
                    case 4:{
                        //city ---> airport
                        break;
                    }
                    case 5:{
                        //city ---> city
                        break;
                    }
                    case 6:{
                        //city ---> coordinates
                        break;
                    }
                    case 7:{
                        //coordinates ---> airport
                        break;
                    }
                    case 8:{
                        //coordinates ---> city
                        break;
                    }
                    case 9:{
                        //coordinates ---> coordinates
                        break;
                    }

                    default:{
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
