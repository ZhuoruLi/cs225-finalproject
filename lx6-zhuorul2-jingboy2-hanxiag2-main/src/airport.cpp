#include <iostream>
#include <vector>

#include "airport.h"
#include "exceptions.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

Airport::Airport() : _airportId(""), _city(""), _latitude(114514.0), _longitude(114514.0) {}

Airport::Airport(vector<string> attributes) {
    _airportId = attributes.at(0);
    _city = attributes.at(2);

    // Complain if either latitude or longitude is missing.
    if (attributes.at(6) == "\\\\N")
        throw __critical_data_not_found("Latitude");
    if (attributes.at(7) == "\\\\N")
        throw __critical_data_not_found("Longitude");

    if (attributes.size() < 14)
        throw __vector_len_does_not_match();

    _latitude = std::stod(attributes.at(6));
    _longitude = std::stod(attributes.at(7));
}

Airport::Airport(string airportId) : _airportId(airportId) {
}

Airport::Airport(const Airport &other) {
    _copy(other);
}

Airport::~Airport() {
    _clear();
}

string Airport::getID() const {
    return _airportId;
}

string Airport::getCity() const {
    return _city;
}

double Airport::getLatitude() const {
    return _latitude;
}

double Airport::getLongitude() const {
    return _longitude;
}

Airport & Airport::operator=(const Airport & rhs) {
    if (this == &rhs) return *this;

    _clear();
    _copy(rhs);
    return *this;
}

void Airport::_copy(const Airport & rhs) {
    this->_airportId = rhs.getID();
    this->_city = rhs.getCity();
    this->_latitude = rhs.getLatitude();
    this->_longitude = rhs.getLongitude();
}

void Airport::_clear() {
    // @todo
}