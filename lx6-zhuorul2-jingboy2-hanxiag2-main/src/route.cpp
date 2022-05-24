/**
 * @file route.cpp
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string>

#include "exceptions.h"
#include "route.h"

using std::vector;
using std::string;

Route::Route(vector<string> attributes) : airline(attributes[0]) {
    if (attributes[3] == "\\\\N")
        throw __critical_data_not_found("start");
    if (attributes[5] == "\\\\N")
        throw __critical_data_not_found("destination");

    start = attributes[3];
    destination = attributes[5];
}

Route::Route(string start, string des, double weight) {
    this->start = start;
    this->destination = des;
    this->weight = weight;
}

string Route::getStart() const {
    return start;
}

string Route::getDestination() const {
    return destination;
}

string Route::getAirline() const {
    return airline;
}

double Route::getWeight() const {
    return weight;
}
