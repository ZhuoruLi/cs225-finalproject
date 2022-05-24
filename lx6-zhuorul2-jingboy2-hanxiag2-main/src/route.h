#pragma once

#include <string>
#include <cmath>
#include <iostream>

#include "airport.h"

using namespace std;
using ID = string;

class Route {
    public:
        Route(vector<string> attributes);

        Route(ID start, ID des, double weight);

        ID getStart() const;

        ID getDestination() const;

        ID getAirline() const;

        double getWeight() const;

        static double computeWeight(Airport & start, Airport & destination) {
            double startLat, destLat, startLng, destLng;
            startLat = start.getLatitude();
            destLat = destination.getLatitude();
            startLng = start.getLongitude();
            destLng = destination.getLongitude();

            return 
                (3963.0 * acos(sin(startLat) * sin(destLat))
                + cos(startLat) * cos(destLat) * cos(destLng - startLng));
        }

        bool operator==(const Route & other) const {
            return (start == other.getStart()) && (destination == other.getDestination());
        }

    private:
        string start;
        string destination;
        string airline;
        double weight;
};

// Inject std::hash<Route> to allow Route to be used as a key to std::unordered_map;
namespace std {

template<> 
struct hash<Route> {
    std::size_t operator()(const Route & e) const noexcept {
        size_t hash1 = std::hash<string>()(e.getStart());
        size_t hash2 = std::hash<string>()(e.getDestination());
        return hash1 ^ hash2;
    }
};

}