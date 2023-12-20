#include "string"

using namespace std;

#ifndef GRAPHPROJECT_AIRPORT_H
#define GRAPHPROJECT_AIRPORT_H

class Airport {
    private:
        string code;
        string name;
        string city;
        string country;
        float  latitude;
        float longitude;
public:
    Airport() = default;
    string getCode() ;
    string getCountry() ;
    string getName() ;
    string getCity() ;
    float getLatitude() ;
    float getLongitude() ;
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    bool operator==(const Airport &rhs) ;
    bool operator<(const Airport &rhs) const ;
    Airport(string code);
};


#endif //GRAPHPROJECT_AIRPORT_H
