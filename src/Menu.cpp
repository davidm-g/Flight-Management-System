
#include <set>
#include <unordered_set>
#include <algorithm>
#include "Menu.h"
#include <cmath>
#include <limits.h>
#include <float.h>

using namespace std;
/**
 * Menu constructor - parse the csv files
 */
Menu::Menu() {
    this->d = Data();
    d.parse_airports();
    d.parse_airlines();
    d.parse_flights();
}

/**
 * function that retrieves total nr of airports - complexity O(1)
 * @return nr of airports
 */
int Menu::totalAirports(){
    return d.getAP().getVertexSet().size();
}

/**
 * function that retrieves total nr of flights - complexity O(V) where V is the number of vertices in the graph
 * @return nr of flights
 */
int Menu::totalFlights(){
    int tflights = 0;
    for(auto v : d.getAP().getVertexSet()){
        tflights += v->getAdj().size();
    }
    return tflights;
}

/**
 * countries flyable from a given city - complexity O(V * E * log M) where V is the number of vertices, E is the average number of edges per vertex within the specified city, and M is the number of unique countries encountered in these edges.
 * @param city that we fly from
 * @return nr of countries that the city flies to
 */
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

/**
 * countries flyable from a given airport - complexity O(E * log M) where E is the number of adjacent edges for the specified airport and M is the number of unique countries encountered in these edges.
 * @param acode of the airport that we fly from
 * @return nr of countries that the airport flies to
 */
int Menu::num_countries_airport(std::string acode) {
    int count=0;
    set<string> used_countries;
    for(auto edge:d.getAirports()[acode]->getAdj()){
        if(used_countries.find(edge.getDest()->getInfo().getCountry()) == used_countries.end()){
            count++;
            used_countries.insert(edge.getDest()->getInfo().getCountry());
        }
    }


    return count;
}


/**
 * nr of flights and different airlines from a given airport - complexity O(E * log N) where E is the number of adjacent edges for the specified airport code and N is the number of unique airlines encountered in these edges.
 * @param apcode of the source airport
 */
void Menu::numFlightsAirlines(string apcode){
    set<string> used_airlines;
    Graph<Airport> grafo=d.getAP();
    int n_voos = 0;
    int n_airlines=0;

    n_voos += d.getAirports()[apcode]->getAdj().size();
    for (auto edge: d.getAirports()[apcode]->getAdj()) {
        if (used_airlines.find(edge.getAirlinecode()) == used_airlines.end()) {
            n_airlines++;
            used_airlines.insert(edge.getAirlinecode());
        }
    }
    cout << n_voos << " flights out of " << apcode << " airport from "
         << n_airlines << " different airlines." << '\n';

}
/**
 * retrieves the amount of flights that a city receives and release - complexity O(V) where V is the number of vertices in the graph
 * @param name of the desired city
 * @return the number of in and out flights in a determined city.
 */
int Menu::num_flights_city(string name){
    int count = 0;
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getCity() == name){
            count += (v->getAdj().size() + v->getIndegree());
        }
    }
    return count;
}
/**
 * retrieves the amount of flights that an airline does - complexity O(V * E) where V is the number of vertices and E the number of edges in the graph
 * @param acode of the airline
 * @return the number of in and out flights in a determined airline.
 */
int Menu::num_flights_airlines(std::string acode) {
    int n_voos = 0;
    for(auto v : d.getAP().getVertexSet()){
        for(auto e : v->getAdj()){
            if(e.getAirlinecode() == acode)n_voos++;
        }
    }
    return n_voos;
}

/**
 * Reachable destinations with x stops - complexity O(V + E) where V is the number of vertices and E the number of edges in the graph
 * @param acode
 * @param max_stops
 */
void Menu::bfs_Stops(std::string acode, int max_stops) {
    int n_airports = 0;
    queue<pair<int,Vertex<Airport>*>> q;
    unordered_set<string> countries;
    unordered_set<string> cities;
    for(auto v : d.getAP().getVertexSet()) v->setVisited(false);
    auto v =  d.getAP().findVertex(acode);
    v->setVisited(true);
    q.push(make_pair(0,v));
    while(!q.empty()){
        auto current = q.front().second;
        int distance = q.front().first;
        if(distance <= max_stops){
            for(auto e : current->getAdj()){
                if(!e.getDest()->isVisited()) {
                    n_airports++;
                    if (countries.find(e.getDest()->getInfo().getCountry()) == countries.end()) {
                        countries.insert(e.getDest()->getInfo().getCountry());
                    }
                    if (cities.find(e.getDest()->getInfo().getCity())== cities.end()) {
                        cities.insert(e.getDest()->getInfo().getCity());
                    }
                    e.getDest()->setVisited(true);
                    q.push(make_pair(distance + 1, e.getDest()));
                }
            }
        }
        q.pop();

    }
    cout << "The number of reachable airports, cities and countries from " << v->getInfo().getName()
    << " with " << max_stops <<" max lay-overs is, respectively: "
    << n_airports << " " << cities.size() << " "<< countries.size() <<'\n';
}

/**
 * Nr of destinations from airport - complexity O(V + E) where V is the number of vertices and E the number of edges in the graph
 * @param acode of the starting airport
 */
void Menu::dfs_Des(string acode){
    int n_airports = 0;
    unordered_set<string> countries;
    unordered_set<string> cities;
    for(auto v : d.getAP().getVertexSet()) v->setVisited(false);
    auto v=  d.getAP().findVertex(acode);
    dfs_Visit_Des(v,countries,cities,n_airports);
    cout << "The number of reachable airports, cities and countries from "<<v->getInfo().getName()
         <<" is,respectively: "
         << n_airports<< ", "<< cities.size()<<", "<<countries.size()<<'\n';

}

/**
 * auxiliary function for dfs_des
 * @param v vertex being visited
 * @param countries set of countries already visited
 * @param cities set of cities already visited
 * @param n_airports nr of airports already visited
 */
void Menu::dfs_Visit_Des(Vertex<Airport> * v , unordered_set<string>& countries,
                          unordered_set<string>& cities, int& n_airports){

    v->setVisited(true);
    for(auto e : v->getAdj()){
        if(!e.getDest()->isVisited()) {
            n_airports++;
            if (countries.find(e.getDest()->getInfo().getCountry()) == countries.end()) {
                countries.insert(e.getDest()->getInfo().getCountry());
            }
            if (cities.find(e.getDest()->getInfo().getCity())== cities.end()) {

                cities.insert(e.getDest()->getInfo().getCity());
            }
            dfs_Visit_Des(e.getDest(),countries,cities,n_airports);
        }
    }

}

/**
 * calculates the flight trip(s) with the greatest number of stops - complexity O(V * (V + E)) where V is the number of vertices and E the number of edges in the graph
 * @return The maximum number of stops between two airports and the airports
 */
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
/**
 * retrieves the top k airports by air traffic - complexity O(V * log V) where V is the number of vertices in the graph
 * @param k
 * @return vector of pairs, first is air traffic count and second is the airport
 */
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
/**
 * Delivers the airports that are essential to networks circulation capability - complexity O(V + E) where V is the number of vertices and E the number of edges in the graph
 * @return a set of articulation points
 */
unordered_set<Vertex<Airport>*>Menu::Articu_points(){
    stack<Airport> S;
    unordered_set<Vertex<Airport>*> res;
    int index = 1;
    for(auto v : d.getAP().getVertexSet()){
        v->setVisited(false);
        v->setProcessing(false);
        v->setNum(0);
        v->setLow(0);
    }
    for(auto v : d.getAP().getVertexSet()){
        if(!v->isVisited()){
            dfs_arti(v,S,res,index);
        }
    }

    return res;
}

/**
 *
 * @param v
 * @param s
 * @param res
 * @param i
 */
void Menu::dfs_arti(Vertex<Airport>* v, stack<Airport>& s, unordered_set<Vertex<Airport>*>& res, int& i) {
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
            if ((v->getNum() != 1 && e.getDest()->getLow() >= v->getNum()) || (children > 1 && v->getNum() == 1))
                res.insert(v);

        } else if (e.getDest()->isProcessing()) {
            v->setLow(min(v->getLow(), e.getDest()->getNum()));
        }
    }
    s.pop();
    v->setProcessing(false);
}

/**
 * function that returns the shortest path between two destinations - complexity O(V + E + P) where V is the number of vertices, E is the number of edges, and P is the number of paths found between the source and target nodes.
 * @param source the code of source airport
 * @param target the code of target airport
 * @return the best flight options between two airports in a vector of vectors of vertexes of airports
 */
vector<vector<Vertex<Airport>*>> Menu::shortest_paths2(string source, string target) {
    queue<std::vector<Vertex<Airport>*>> queue;
    set<Airport> visited;
    vector<std::vector<Vertex<Airport>*>> paths; // todos os caminhos possiveis
    vector<std::vector<Vertex<Airport>*>> res;  //caminhos mais curtos
    vector<Vertex<Airport>*> path;
    vector<Vertex<Airport>*> new_path;
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
    queue.push({d.getAirports()[source]});
    Airport current_node;
    while (!queue.empty()) {
        path = queue.front();
        current_node = path.back()->getInfo();
        queue.pop();

        if (current_node.getCode() == target) {
            if(find(paths.begin(), paths.end(), path) == paths.end())
                paths.push_back(path);
        }

        if (visited.find(current_node) == visited.end()) {
            visited.insert(current_node);
            for (auto e : d.getAirports()[current_node.getCode()]->getAdj()) {
                if (visited.find(e.getDest()->getInfo()) == visited.end()) {
                    new_path = path;
                    new_path.push_back(e.getDest());
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
/**
 * function to know the airports in a determined city - complexity O(V) where V is the number of vertices in the graph
 * @param city the name of the city
 * @return vector of airport codes that are established on a given city
 */
vector<string> Menu::city_airports(string city){
    vector<string> res;
    for(auto vertex: d.getAP().getVertexSet()){
        if(vertex->getInfo().getCity()==city)
            res.push_back(vertex->getInfo().getCode());
    }
    return res;
}
/**
 * function to know the distance between two airports, by using its coordinates - complexity O(1)
 * @param lat1 latitude of 1st airport
 * @param lon1 longitude of 1st airport
 * @param lat2 latitude of second airport
 * @param lon2 longitude of second airport
 * @return distance between two airports, in kilometers
 */
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
/**
 * function that finds the nearest Airport(s) based on the given latitude and longitude - complexity O(V) where V is the number of vertices in the graph
 * @param lat given latitude
 * @param lon given longitude
 * @return a vector of airport codes that are the nearest to the given coordinates
 */
vector<string> Menu::findNearestAirports(double lat, double lon) {
    vector<pair<double, string>> tmp;
    vector<string> res;
    double minDist = DBL_MAX;
    for (auto ap : d.getAP().getVertexSet()) {
        if(haversine(lat, lon, ap->getInfo().getLatitude(), ap->getInfo().getLongitude()) <= minDist) {
            minDist = haversine(lat, lon, ap->getInfo().getLatitude(), ap->getInfo().getLongitude());
            tmp.push_back(make_pair(minDist, ap->getInfo().getCode()));
        }
    }
    for (auto p : tmp) {
        if(p.first == minDist)
            res.push_back(p.second);
    }
    return res;
}

/**
 * function based on shortest_paths, except using a filter that turns the best flight - complexity O(P * N * E * log P) where V is the number of vertices, E is the number of edges, and P is the number of paths found between the source and target nodes.
 * option into the path that uses the minimum number of different airlines,
 * @param start code of source airport
 * @param target code of target airport
 * @return best flight options, based on the filter
 */
vector<vector<Vertex<Airport>*>> Menu::f1_shortest_paths(string source, string target) {
    auto res = shortest_paths2(source,target);
    vector<vector<Vertex<Airport>*>> res1;
    vector<pair<int, vector<Vertex<Airport>*>>> final;
    int m = 0;
    for(auto v : res){ //vector de vertices
        unordered_map<string,int> acode;
        for(int i = 0; i < v.size();i++){ //VERTICES
            for(auto e : v[i]->getAdj()){
                if(i + 1 < v.size() && e.getDest()==v[i+1]) {
                    if(acode.find(e.getAirlinecode()) == acode.end()) acode[e.getAirlinecode()] = 1;
                    else acode[e.getAirlinecode()]++;
                }
            }
        }
        int temp = 0;
        for(auto a : acode){
            if (a.second >= temp) temp = a.second;
        }

        if(temp >= m) m = temp;
        final.push_back(make_pair(temp,v));
    }
    for(auto v : final){
        if(v.first == m) res1.push_back(v.second);
    }
    return res1;

}
/**
 * function based on shortest_paths, except using a filter that turns the best flight - complexity O(V + E + P) where V is the number of vertices, E is the number of edges, and P is the number of paths found between the source and target nodes.
 * option into the path that uses the given pretended airlines
 * @param start code of source airport
 * @param target code of target airport
 * @param air set of wanted airline codes
 * @return best flight options, based on the filter
 */

vector<vector<Vertex<Airport>*>> Menu::f2_shortest_paths(string source, string target, set<string> air){

    queue<std::vector<Vertex<Airport>*>> queue;
    set<Airport> visited;
    vector<std::vector<Vertex<Airport>*>> paths; // todos os caminhos possiveis
    vector<std::vector<Vertex<Airport>*>> res;  //caminhos mais curtos
    vector<Vertex<Airport>*> path;
    vector<Vertex<Airport>*> new_path;
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
    queue.push({d.getAirports()[source]});
    Airport current_node;
    while (!queue.empty()) {
        path = queue.front();
        current_node = path.back()->getInfo();
        queue.pop();

        if (current_node.getCode() == target) {
            if(find(paths.begin(), paths.end(), path) == paths.end())
                paths.push_back(path);
        }

        if (visited.find(current_node) == visited.end()) {
            visited.insert(current_node);
            for (auto e : d.getAirports()[current_node.getCode()]->getAdj()) {
                if (visited.find(e.getDest()->getInfo()) == visited.end() && air.find(e.getAirlinecode()) != air.end()) {
                    new_path = path;
                    new_path.push_back(e.getDest());
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
/**
 * function based on shortest_paths, except using a filter that turns the best flight - complexity O(V + E + P) where V is the number of vertices, E is the number of edges, and P is the number of paths found between the source and target nodes.
 * option into the path that avoids the given countries
 * @param start code of source airport
 * @param target code of target airport
 * @param countries set of countries to avoid
 * @return best flight options, based on the filter
 */
vector<vector<Vertex<Airport>*>> Menu::f3_shortest_paths(string source, string target, set<string> countries) {

    queue<std::vector<Vertex<Airport> *>> queue;
    set<Airport> visited;
    vector<std::vector<Vertex<Airport> *>> paths; // todos os caminhos possiveis
    vector<std::vector<Vertex<Airport> *>> res;  //caminhos mais curtos
    vector<Vertex<Airport> *> path;
    vector<Vertex<Airport> *> new_path;
    int m = INT_MAX;
    if (d.getAirports().find(source) == d.getAirports().end()) {
        for (auto v: d.getAP().getVertexSet()) {
            if (v->getInfo().getName() == source) {
                source = v->getInfo().getCode();
                break;
            }
        }
    }
    if (d.getAirports().find(target) == d.getAirports().end()) {
        for (auto v: d.getAP().getVertexSet()) {
            if (v->getInfo().getName() == target) {
                target = v->getInfo().getCode();
                break;
            }
        }
    }
    queue.push({d.getAirports()[source]});
    Airport current_node;
    while (!queue.empty()) {
        path = queue.front();
        current_node = path.back()->getInfo();
        queue.pop();

        if (current_node.getCode() == target) {
            if (find(paths.begin(), paths.end(), path) == paths.end())
                paths.push_back(path);
        }

        if (visited.find(current_node) == visited.end() && countries.find(current_node.getCountry()) == countries.end()) {
            visited.insert(current_node);
            for (auto e: d.getAirports()[current_node.getCode()]->getAdj()) {
                if (visited.find(e.getDest()->getInfo()) == visited.end() &&
                    countries.find(e.getDest()->getInfo().getCountry()) == countries.end()) {
                    new_path = path;
                    new_path.push_back(e.getDest());
                    queue.push(new_path);
                }
            }
        }
    }
    for (auto v: paths) {
        if (v.size() <= m) m = v.size();
    }
    for (auto v: paths) {
        if (v.size() == m) res.push_back(v);
    }

    return res;


}

