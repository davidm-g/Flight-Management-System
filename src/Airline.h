#include <string>

using namespace std;

#ifndef GRAPHPROJECT_AIRLINE_H
#define GRAPHPROJECT_AIRLINE_H
/**
 * @class Airline
 * @brief Portrays an airline, identified it by code, name, callsign and country
 */

class Airline {
    private:
        string code;
        string name;
        string callsign;
        string country;
    public:
        Airline() = default;
        string getCode() const;
        string getName() const;
        string getCallsign() const;
        string getCountry() const;
        bool operator==(const Airline &rhs) const;
        Airline(string code, string name, string callsign, string country);
};


#endif //GRAPHPROJECT_AIRLINE_H
