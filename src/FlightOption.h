//
// Created by afdom on 23/12/2023.
//

#ifndef GRAPHPROJECT_FLIGHTOPTION_H
#define GRAPHPROJECT_FLIGHTOPTION_H

#include "Data.h"
#include "Airport.h"
#include "Airline.h"
#include "Menu.h"

/**
 * @class FlightOption
 * @brief Represents the different flight options with filters.
 * It shows available functionalities and their corresponding outputs in a clear, organized,
 * and logical manner, facilitating seamless program utilization and straightforward result
 * interpretation.
 */
class FlightOption {
private:
    Menu m;
public:
    FlightOption(Menu m);
    void flight_airport_airport(string source, string target, bool f1, bool f2, bool f3);
    void flight_airport_city(string source, string target, bool f1, bool f2, bool f3);
    void flight_airport_coordinates(string source, double lat, double longi, bool f1, bool f2, bool f3);
    void flight_city_airport(string source, string target, bool f1, bool f2, bool f3);
    void flight_city_city(string source, string target, bool f1, bool f2, bool f3);
    void flight_city_coordinates(string source, double lat, double lon, bool f1, bool f2, bool f3);
    void flight_coordinates_airport(double lat, double lon,string target, bool f1, bool f2, bool f3);
    void flight_coordinates_city(double lat, double lon,string target, bool f1, bool f2, bool f3);
    void flight_coordinates_coordinates(double lat1, double lon1, double lat2, double lon2, bool f1, bool f2, bool f3);

};


#endif //GRAPHPROJECT_FLIGHTOPTION_H
