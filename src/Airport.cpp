//
// Created by afdom on 18/12/2023.
//

#include "Airport.h"

Airport::Airport(std::string code, std::string name, std::string city, std::string country, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getCode() {
    return code;
}
string Airport::getCity() {
    return city;
}
string Airport::getName() {
    return name;
}
string Airport::getCountry()  {
    return country;
}

float Airport::getLatitude()  {
    return latitude;
}

float Airport::getLongitude()  {
    return longitude;
}

bool Airport::operator==(const Airport &rhs) {
    return code == rhs.code;
}

Airport::Airport(std::string code) {
    this->code = code;
}
