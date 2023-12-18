#include <iostream>
#include "Data.h"
#include "Airport.h"
#include "Airline.h"
#include "graph.h"
using namespace std;
int main() {

    Data d;
    d.parse_airports();
    d.parse_airlines();
    d.parse_flights();
    cout << "Airlines do Porto para Lisboa:" << '\n';
    for(auto v : d.getAP().getVertexSet()){
        if(v->getInfo().getName() == "Porto"){
            for(auto e : v->getAdj()){
                if(e.getDest()->getInfo().getName() == "Lisboa")
                    cout << e.getAirlinecode() << "\n";
            }
        }
    }


    return 0;
}
