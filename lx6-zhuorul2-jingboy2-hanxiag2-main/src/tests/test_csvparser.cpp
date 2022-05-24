#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>

#include "../airport.h"
#include "../graph.h"
#include "../csv_parser/csvparser.h"

using namespace std;

TEST_CASE("test small airport dataset.", "[weight=10][part=csvparser]") {
    string a0[] = {"75","Pond Inlet Airport","Pond Inlet","Canada","YIO","CYIO","72.6832962036","-77.9666976929","181","-5","A","America/Toronto","airport","OurAirports"};
    string a1[] = {"76","St Jean Airport","St. Jean","Canada","YJN","CYJN","45.29439926147461","-73.28109741210938","136","-5","A","America/Toronto","airport","OurAirports"};
    string a2[] = {"77","Stephenville Airport","Stephenville","Canada","YJT","CYJT","48.5442008972168","-58.54999923706055","84","-3.5","A","America/St_Johns","airport","OurAirports"};

    vector<string> apa0(a0, a0 + sizeof(a0) / sizeof(string));
    vector<string> apa1(a1, a1 + sizeof(a1) / sizeof(string));
    vector<string> apa2(a2, a2 + sizeof(a2) / sizeof(string));

    Airport airport0(apa0);
    Airport airport1(apa1);
    Airport airport2(apa2);

    vector<Airport> expected_airports;
    expected_airports.push_back(airport0);
    expected_airports.push_back(airport1);
    expected_airports.push_back(airport2);

    try
    {
        vector<Airport> actual_airports;
        deserialize(actual_airports, "tests/small_airport_dataset.csv");
        for (size_t i = 0; i < actual_airports.size(); i++)
            REQUIRE(expected_airports[i] == actual_airports[i]);
    }
    catch(const std::exception& e)
    {
        FAIL(e.what());
    }
}

TEST_CASE("Load part of airports dataset does not crash.", "[weight=10][part=csvparser]") {
    try
    {
        vector<Airport> ret;
        deserialize(ret, "tests/medium_airport_dataset.csv");
        for (Airport airport : ret) {

        }
    }
    catch(const std::exception& e)
    {
        FAIL(e.what());
    }
}

TEST_CASE("Load full set of airports does not crash.", "[weight=10][part=csvparser]") {
    try
    {
        vector<Airport> ret;
        deserialize(ret, "data/airports.csv");
        for (Airport airport : ret) {

        }
    }
    catch(const std::exception& e)
    {
        FAIL(e.what());
    }
}

TEST_CASE("Load full set of routes does not crash.", "[weight=10][part=csvparser]") {
    try
    {
        vector<Route> ret;
        deserialize(ret, "data/routes.csv");
        for (Route route : ret) {
            REQUIRE(route.getStart() != "\\N");
            REQUIRE(route.getDestination() != "\\N");
        }
    }
    catch(const std::exception& e)
    {
        FAIL(e.what());
    }
}

TEST_CASE("test create graph from vectors (full).","[weight=10][part=csvparser]") {
    try {
        vector<Airport> airports;
        vector<Route> routes;
        deserialize(airports, "data/airports.csv");
        deserialize(routes, "data/routes.csv");
        Graph g = createGraphFromVector(airports, routes);
        REQUIRE(g.size() == airports.size());
    }
    catch (const std::exception & e) {
        FAIL(e.what());
    }
}

TEST_CASE("test generators' functionality.", "[weight=10][part=csvparser]") {
    try {
        unordered_map<string, Airport> city_airport_map = createAirportHashmap("tests/small_airport_dataset.csv");
        for (auto item : city_airport_map) {
            REQUIRE(item.first == item.second.getCity());
        }
    }
    catch (const std::exception &e) {
        FAIL(e.what());
    }
}

TEST_CASE("parser correctly omits data that contain severe incompletion.", "[weight=10][part=csvparser]") {
    try
    {
        vector<Route> ret;
        deserialize(ret, "tests/contaminated_route_dataset.csv");
        REQUIRE(ret.size() == 0);
    }
    catch(const std::exception& e)
    {
        FAIL(e.what());
    }
}

TEST_CASE("evaluation of \"\\\\N\" gives the expected outcome.", "[weight=10][part=csvparser]") {
    string n = "\\\\N";
    REQUIRE(n == "\\\\N");
    try {
        string a0[] = {"75","Pond Inlet Airport","Pond Inlet","Canada","YIO","CYIO","\\\\N","-77.9666976929","181","-5","A","America/Toronto","airport","OurAirports"};
        vector<string> apa0(a0, a0 + sizeof(a0) / sizeof(string));
        Airport ap0(apa0);

        FAIL("No exception thrown");
    }
    catch (const __unexpected_behavior &ub) {
        // pass
    }

    try {
        string r0[] = {"B","410","DME","4029","TGK","\\\\N","0","CR2"};
        string r1[] = {"2B","410","TGK","\\\\N","DME","4029","0","CR2"};

        vector<string> rv0(r0, r0 + sizeof(r0) / sizeof(string));
        vector<string> rv1(r1, r1 + sizeof(r1) / sizeof(string));
        Route rt0(rv0);
        Route rt1(rv1);

        FAIL("No exception thrown");
    }
    catch (const __unexpected_behavior &ub) {
        // pass
    }
}