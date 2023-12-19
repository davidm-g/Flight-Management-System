
#include <set>
#include <unordered_set>
#include "Menu.h"
using namespace std;
Menu::Menu() {
    this->d = Data();
    d.parse_airports();
    d.parse_airlines();
    d.parse_flights();
}

int Menu::totalAirports(){
    return d.getAP().getVertexSet().size();
}
int Menu::totalFlights(){
    int tflights = 0;
    for(auto v : d.getAP().getVertexSet()){
        tflights += v->getAdj().size();
    }
    return tflights;
}
 int Menu::num_countries_city(std::string city){
    int count=0;
    set<string> used_countries;
     for(auto v : d.getAP().getVertexSet()){
         if(v->getInfo().getCity() == city){
                for(auto edge:v->getAdj()){
                        if(used_countries.find(edge.getDest()->getInfo().getCountry())== used_countries.end()){
                            count++;
                            used_countries.insert(edge.getDest()->getInfo().getCountry());
                        }
                }
         }
     }
         return count;
}

int Menu::num_countries_airport(std::string acode) {
    int count=0;
    set<string> used_countries;
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getCode() == acode){
            for(auto edge:v->getAdj()){
                if(used_countries.find(edge.getDest()->getInfo().getCountry()) == used_countries.end()){
                    count++;
                    used_countries.insert(edge.getDest()->getInfo().getCountry());
                }
            }
        }
    }
    return count;
}
int Menu::num_cities_airport(std::string acode) {
    int count=0;
    set<string> used_cities;
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getCode() == acode){
            for(auto edge:v->getAdj()){
                if(used_cities.find(edge.getDest()->getInfo().getCity())== used_cities.end()){
                    count++;
                    used_cities.insert(edge.getDest()->getInfo().getCity());
                }
            }
        }
    }
    return count;
}
int Menu::num_airports_airport(string acode){
    int count=0;
    set<string> used_airports;
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getCode() == acode){
            for(auto edge:v->getAdj()){
                if(used_airports.find(edge.getDest()->getInfo().getCode()) == used_airports.end()){
                    count++;
                    used_airports.insert(edge.getDest()->getInfo().getCode());
                }
            }
        }
    }
    return count;
}


pair<int, int> Menu::numFlightsAirlines(string apcode){
    set<string> used_airlines;
    Graph<Airport> grafo=d.getAP();
    int n_voos = 0;
    int n_airlines=0;
    for(auto v : grafo.getVertexSet()){
        if(v->getInfo().getCode() == apcode) {
            n_voos += v->getAdj().size();
            for (auto edge: v->getAdj()) {
                if (used_airlines.find(edge.getAirlinecode()) == used_airlines.end()) {
                    n_airlines++;
                    used_airlines.insert(edge.getAirlinecode());
                }
            }
            break;
        }
    }
    return make_pair(n_voos, n_airlines);
}
int Menu::num_flights_city(string name){
    int count = 0;
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getCity() == name){
            count += (v->getAdj().size() + v->getIndegree());
        }
    }
    return count;
}

int Menu::num_flights_airlines(std::string acode) {
    int n_voos = 0;
    for(auto v : d.getAP().getVertexSet()){
        for(auto e : v->getAdj()){
            if(e.getAirlinecode() == acode)n_voos++;
        }
    }
    return n_voos;
}

void Menu::dfs_Stops(std::string acode, int max_stops) {
    int n_countries=0;
    int n_cities = 0;
    int n_airports = 0;
    unordered_set<string> countries;
    unordered_set<string> cities;
    for(auto v : d.getAP().getVertexSet()) v->setVisited(false);
    auto v=  d.getAP().findVertex(acode);
    dfs_Visit_Stops(v,max_stops,countries,cities,n_airports,n_cities,n_countries);
    cout << "The number of new reachable airports, cities and countries from "<<v->getInfo().getName()
    <<" with "<<max_stops<<" max lay-overs is,respectively: "
    << n_airports<< " "<< n_cities<<" "<<n_countries<<'\n';
}
void Menu::dfs_Visit_Stops(Vertex<Airport> *v, int max_stops, unordered_set<std::string> &countries,
                           unordered_set<std::string> &cities,  int &n_airports,
                           int &n_cities, int &n_countries) {
    v->setVisited(true);
    if(max_stops >= 0){ //se a distância não é máxima
        for(auto e : v->getAdj()){
            if(!e.getDest()->isVisited()) {
                n_airports++;
                if (countries.find(e.getDest()->getInfo().getCountry()) == countries.end()) {
                    n_countries++;
                    countries.insert(e.getDest()->getInfo().getCountry());
                }    //Encontrar novos countries
                if (cities.find(e.getDest()->getInfo().getCity())== cities.end()) {
                    n_cities++;
                    cities.insert(e.getDest()->getInfo().getCity());
                }
                dfs_Visit_Stops(e.getDest(),max_stops - 1,countries,cities,n_airports,n_cities,n_countries);
            }
        }
    }

}
vector<pair<int, pair<Airport,Airport> >> Menu::graph_diameter() {
    int m_distance = 0;
    vector<pair<int,pair<Airport,Airport>>> re;
    vector<pair<int,pair<Airport,Airport>>> res;
    for(auto v : d.getAP().getVertexSet()) v->setVisited(false);
    for(auto v : d.getAP().getVertexSet()){
        queue<pair<int,Vertex<Airport> *>> Q;
        Q.push(make_pair(0,v));
        v->setVisited(true);
        while(!Q.empty()){
            auto current = Q.front().second;
            int distance = Q.front().first;
            for(auto e : current->getAdj()){
                if(!e.getDest()->isVisited()){
                    e.getDest()->setVisited(true);
                    Q.push(make_pair(distance + 1, e.getDest()));
                }
            }
            if(distance >= m_distance){
                m_distance = distance;
                re.push_back(make_pair(distance, make_pair(v->getInfo(),current->getInfo())));
            }
            Q.pop();
        }

    }

    for(auto v : re){
        if(v.first == m_distance) res.push_back(make_pair(m_distance, v.second));
    }
    return res;

}
