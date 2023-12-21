
#include <set>
#include <unordered_set>
#include <algorithm>
#include "Menu.h"
#include <cmath>
#include <limits.h>
#include <float.h>

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

vector<pair<int,Airport>> Menu::greatest_air_traffic(int k){

    vector<pair<int,Airport>> temp;
    vector<pair<int,Airport>> res;
    for(auto v : d.getAP().getVertexSet()){
        temp.push_back(make_pair(v->getAdj().size()+ v->getIndegree(),v->getInfo()));

    }
    sort(temp.begin(), temp.end(),[](pair<int,Airport> a, pair<int,Airport> b){ return a.first > b.first;});
    for(int i = 0; i < k; i++){
        res.push_back(temp[i]);
    }
    return res;

}

set<Airport>Menu::Articu_points(){
    stack<Airport> S;
    set<Airport> res;
    int index = 1;
    for(auto v : d.getAP().getVertexSet()){
        v->setVisited(false);
    }
    for(auto v : d.getAP().getVertexSet()){
        if(!v->isVisited()){
            dfs_arti(v,S,res,index);
        }
    }

    return res;
}

void Menu::dfs_arti(Vertex<Airport>* v, stack<Airport>& s, set<Airport>& res, int& i) {
    v->setVisited(true);
    v->setLow(i);
    v->setNum(i);
    i++;
    v->setProcessing(true);
    s.push(v->getInfo());
    int children = 0;
    for (auto e: v->getAdj()) {
        if (!e.getDest()->isVisited()) {
            children++;
            dfs_arti(e.getDest(), s, res, i);
            v->setLow(min(v->getLow(), e.getDest()->getLow()));
            if ((v->getNum() == 1 && children > 1) || (v->getNum() != 1 && e.getDest()->getLow() >= v->getNum()))
                res.insert(v->getInfo());
        } else if (e.getDest()->isProcessing()) {
            v->setLow(min(v->getLow(), e.getDest()->getNum()));
        }
    }
    v->setProcessing(false);
}

vector<vector<Airport>> Menu::shortest_paths(string source, string target) {
    std::queue<std::vector<Airport>> queue;
    std::set<Airport> visited;
    std::vector<std::vector<Airport>> paths; // todos os caminhos possiveis
    std::vector<std::vector<Airport>> res;  //caminhos mais curtos
    int m = INT_MAX;
    if (d.getAirports().find(source) == d.getAirports().end()) {
        for(auto v : d.getAP().getVertexSet()){
            if(v->getInfo().getName() == source){
                source = v->getInfo().getCode();
                break;
            }
        }
    }
    if (d.getAirports().find(target) == d.getAirports().end()) {
        for(auto v : d.getAP().getVertexSet()){
            if(v->getInfo().getName() == target){
                target = v->getInfo().getCode();
                break;
            }
        }
    }

    queue.push({d.getAirports()[source]->getInfo()});

    while (!queue.empty()) {
        std::vector<Airport> path = queue.front();
        Airport current_node = path.back();
        queue.pop();

        if (current_node.getCode() == target) {
            paths.push_back(path);
        }

        if (visited.find(current_node) == visited.end()) {
            visited.insert(current_node);
            for (auto e : d.getAirports()[current_node.getCode()]->getAdj()) {
                if (visited.find(e.getDest()->getInfo()) == visited.end()) {
                    std::vector<Airport> new_path = path;
                    new_path.push_back(e.getDest()->getInfo());
                    queue.push(new_path);
                }
            }
        }
    }
    for(auto v : paths){
        if(v.size() <= m) m = v.size();
    }
    for(auto v : paths){
        if(v.size() == m) res.push_back(v);
    }

    return res;
}




static double haversine(double lat1, double lon1,
                        double lat2, double lon2)
{
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

vector<Airport> Menu::findNearestAirports(double lat, double lon) {
    vector<pair<double, Airport>> tmp;
    vector<Airport> res;
    double minDist = DBL_MAX;
    for (auto ap : d.getAP().getVertexSet()) {
        if(haversine(lat, lon, ap->getInfo().getLatitude(), ap->getInfo().getLongitude()) <= minDist) {
            minDist = haversine(lat, lon, ap->getInfo().getLatitude(), ap->getInfo().getLongitude());
            tmp.push_back(make_pair(minDist, ap->getInfo()));
        }
    }
    for (auto p : tmp) {
        if(p.first == minDist)
            res.push_back(p.second);
    }
    return res;
}


