#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../route.h"
#include "../airport.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

using cs225::HSLAPixel;
using cs225::PNG;

TEST_CASE("Graph::shortestpath finds a shortest path", "[weight=2]") {
    Graph g;
    Image test_map;
    Image original_map;
    original_map.readFromFile("data/map.png");
    test_map = original_map;
    PNG out_put;
    string a0[] = {"75","Pond Inlet Airport","Pond Inlet","Canada","YIO","CYIO","72.6832962036","-77.9666976929","181","-5","A","America/Toronto","airport","OurAirports"};
    string a1[] = {"76","St Jean Airport","St. Jean","Canada","YJN","CYJN","45.29439926147461","-73.28109741210938","136","-5","A","America/Toronto","airport","OurAirports"};
    vector<string> apa0(a0, a0 + sizeof(a0) / sizeof(string));
    vector<string> apa1(a1, a1 + sizeof(a1) / sizeof(string));
    Airport airport0(apa0);
    Airport airport1(apa1);
    Route route1(airport0.getID(), airport1.getID(), 7856.2);
    g.insertVertex(airport0);
    g.insertVertex(airport1);
    g.insertEdge(route1);

    list<string> path = g.shortestpath("75", "76");
    out_put = g.drawpath(test_map, path);
    REQUIRE(out_put != original_map);
}