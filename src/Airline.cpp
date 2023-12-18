//
// Created by afdom on 18/12/2023.
//

#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    this->code = code;
    this->name = name;
    this->callsign = callsign;
    this->country = country;
}

string Airline::getCode() const {
    return code;
}

string Airline::getName() const {
    return name;
}

string Airline::getCallsign() const {
    return callsign;
}

string Airline::getCountry() const {
    return country;
}

bool Airline::operator==(const Airline &rhs) const {
    return code == rhs.code;
}


