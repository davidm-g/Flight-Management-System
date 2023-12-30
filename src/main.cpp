#include <iostream>
#include <climits>
#include <sstream>
#include "FlightOption.h"
using namespace std;
int main() {
    FlightOption f = FlightOption();
    Menu m = f.getMenu();
    int choice;
    bool filter_min_airlines = false;
    bool filter_airlines_list = false;
    bool filter_avoid_countries = false;
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
        if(filter_min_airlines)
        cout << "|FILTER MINIMUM AIRLINES ENABLED          |" << '\n';
        else if(filter_airlines_list)
        cout << "|FILTER AIRLINES LIST ENABLED             |" << '\n';
        else if(filter_avoid_countries)
        cout << "|FILTER AVOID COUNTRIES ENABLED           |" << '\n';
        else
        cout << "|FILTERS DISABLED                         |" << '\n';
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
                m.numFlightsAirlines(acode);
                break;
            }
            case 4:{
                cout<<"1. Number of flights per city"<<endl;
                cout<<"2. Number of flights per airline"<<endl;
                cout << "Please enter your desired choice:";
                int escolha;
                cin>>escolha;
                cin.ignore();
                switch (escolha) {
                    case 1:{
                        cout<<"Enter the desired city:";
                        string city;
                        getline(cin,city);
                        if(m.getData().getCity_by_country()[city].size() > 1) {
                            cout << "There are " << m.getData().getAirportsByCity()[city].size() << " cities with the same name!" << '\n';
                            cout << "Enter the desired city's country:";
                            string country;
                            cin >> country;
                            cout << "There are "<<m.num_flights_city_country(city,country)<<" in and out flights from/to "<< city << ", "<< country<< '\n' << '\n';
                        }
                        else {
                            cout << "The number of in and out flights from/to " << city << " is : "
                                 << m.num_flights_city(city) << '\n' << '\n';
                        }
                        break;
                    }
                    case 2:{
                        cout << "Enter the desired airline code:";
                        string acode;
                        cin >> acode;
                        cout << "The airline " << acode <<" operates in total : " << m.num_flights_airlines(acode) << " flights\n" << '\n';
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
                cout<<"1. Number of different countries that a given city flights to"<<endl;
                cout<<"2. Number of different countries that a given airport flights to"<<endl;
                cout << "Please enter your desired choice:";
                int escolha;
                cin >> escolha;
                cin.ignore(); // ignore the newline character that remained
                switch (escolha) {
                    case 1:{
                        cout << "Enter the desired city:";
                        string city;
                        getline(cin,city);
                        if(m.getData().getCity_by_country()[city].size() > 1){
                            cout << "There are " << m.getData().getAirportsByCity()[city].size() << " cities with the same name!" << '\n';
                            cout << "Enter the desired city's country:";
                            string country;
                            cin >> country;
                            cout<< "The city of " << city << " from "<<country <<" flies to "<< m.num_countries_city2(city,country)<< " different countries\n";
                        }
                        else {
                            cout << "The city of " << city << " flies to " << m.num_countries_city(city)
                                 << " different countries\n";
                        }
                        break;
                    }
                    case 2:{
                        cout << "Enter the desired airport code:";
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
                cout << "Please enter the desire airport code:";
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
                cout<<"Please enter the number of airports to display in terms of number of flights ranking:";
                int k;
                cin>>k;
                cout <<"The top " << k << " airports with the greatest air traffic capacity are: \n";
                for(auto ap : m.greatest_air_traffic(k)){
                    cout << "- " << ap.second.getName() << " located in " << ap.second.getCity()
                    << ", " << ap.second.getCountry() <<" with "<< ap.first << " flights.\n";
                }
                break;
            }
            case 10:  {
                cout << "The airports that are essential to networks circulation capability are:\n";
                int counter=0;
                for(auto ap : m.Articu_points()){
                    cout << ap->getInfo().getName() << " located in " << ap->getInfo().getCity() << ", " << ap->getInfo().getCountry() << ".\n";
                    counter++;
                }
                cout << '\n';
                cout << "There are in total " <<   counter  << " essential airports\n";
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
                cout << "Please select your desired method:";
                int so;
                cin >> so;
                cin.ignore();
                switch (so) {
                    case 1:{

                        cout << "Insert a source airport code/name:";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target airport code/name:";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        cout << "The best flight options between those two airports are:" << '\n';
                        f.flight_airport_airport(source,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        break;
                    }

                    case 2:{
                        cout << "Insert a source airport code/name:";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target city:";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        f.flight_airport_city(source,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //airport ---> city
                        break;
                    }

                    case 3: {
                        string source;
                        cout << "Insert a source airport code/name:";
                        cin >> source;
                        float lat, lon;
                        cout << "Insert the latitude of the target airport:";
                        cin >> lat;
                        cout << '\n';
                        cout << "Insert the longitude of the target airport:";
                        cin >> lon;
                        cout << '\n';
                        cout << "The best flight options between those two cities are:" << '\n';
                        f.flight_airport_coordinates(source,lat,lon,filter_min_airlines,filter_airlines_list,filter_avoid_countries);

                        //airport ---> coordinates
                        break;
                    }
                    case 4:{
                        cout << "Insert a source city:";
                        string source;
                        getline(cin,source);
                        cout << "Insert a target airport code/name:";
                        string target;
                        getline(cin,target);
                        cout << '\n';
                        f.flight_city_airport(source,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //city ---> airport
                        break;
                    }
                    case 5: {
                        cout << "Insert a source city:";
                        string source;
                        getline(cin, source);
                        cout << "Insert a target city:";
                        string target;
                        getline(cin, target);
                        cout << '\n';
                        f.flight_city_city(source,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //city ---> city
                        break;
                    }
                    case 6: {
                        string source;
                        cout << "Insert a source city:";
                        cin >> source;
                        float lat, lon;
                        cout << "Insert the latitude of the target airport:";
                        cin >> lat;
                        cout << "Insert the longitude of the target airport:";
                        cin >> lon;
                        cout << '\n';
                        f.flight_city_coordinates(source,lat,lon,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //city ---> coordinates
                        break;
                    }
                    case 7:{
                        float lat, lon;
                        cout << "Insert the latitude of the source airport:";
                        cin >> lat;
                        cout << "Insert the longitude of the source airport:";
                        cin >> lon;
                        string target;
                        cout << "Insert a target airport code/name:";
                        cin >> target;
                        cout << '\n';
                        cout << "The best flight options between those two cities are:" << '\n';
                        f.flight_coordinates_airport(lat,lon,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //coordinates ---> airport
                        break;
                    }
                    case 8:{
                        float lat, lon;
                        cout << "Insert the latitude of the source airport:";
                        cin >> lat;
                        cout << "Insert the longitude of the source airport:";
                        cin >> lon;
                        string target;
                        cout << "Insert a target city:";
                        cin >> target;
                        cout << '\n';
                        f.flight_coordinates_city(lat,lon,target,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
                        //coordinates ---> city
                        break;
                    }
                    case 9:{
                        double lat1, lon1;
                        cout << "Insert the latitude of the source airport:";
                        cin >> lat1;
                        cout << "Insert the longitude of the source airport:";
                        cin >> lon1;
                        float lat2, lon2;
                        cout << "Insert the latitude of the target airport:";
                        cin >> lat2;
                        cout << "Insert the longitude of the target airport:";
                        cin >> lon2;
                        cout << '\n';
                        cout << "The best flight options between those two cities are:" << '\n';
                        f.flight_coordinates_coordinates(lat1,lon1,lat2,lon2,filter_min_airlines,filter_airlines_list,filter_avoid_countries);
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