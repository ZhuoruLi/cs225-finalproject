#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../route.h"
#include "../airport.h"

string a0[] = {"75","Pond Inlet Airport","Pond Inlet","Canada","YIO","CYIO","72.6832962036","-77.9666976929","181","-5","A","America/Toronto","airport","OurAirports"};
string a1[] = {"76","St Jean Airport","St. Jean","Canada","YJN","CYJN","45.29439926147461","-73.28109741210938","136","-5","A","America/Toronto","airport","OurAirports"};
string a2[] = {"77","Stephenville Airport","Stephenville","Canada","YJT","CYJT","48.5442008972168","-58.54999923706055","84","-3.5","A","America/St_Johns","airport","OurAirports"};
string a3[] = {"1","Goroka Airport","Goroka","Papua New Guinea","GKA","AYGA","-6.081689834590001","145.391998291","5282","10","U","Pacific/Port_Moresby","airport","OurAirports"};
string a4[] = {"2","Madang Airport","Madang","Papua New Guinea","MAG","AYMD","-5.20707988739","145.789001465","20","10","U","Pacific/Port_Moresby","airport","OurAirports"};
string a5[] = {"3","Mount Hagen Kagamuga Airport","Mount Hagen","Papua New Guinea","HGU","AYMH","-5.826789855957031","144.29600524902344","5388","10","U","Pacific/Port_Moresby","airport","OurAirports"};
vector<string> apa0(a0, a0 + sizeof(a0) / sizeof(string));
vector<string> apa1(a1, a1 + sizeof(a1) / sizeof(string));
vector<string> apa2(a2, a2 + sizeof(a2) / sizeof(string));
vector<string> apa3(a3, a3 + sizeof(a3) / sizeof(string));
vector<string> apa4(a4, a4 + sizeof(a4) / sizeof(string));
vector<string> apa5(a5, a5 + sizeof(a5) / sizeof(string));

Airport airport0(apa0);
Airport airport1(apa1);
Airport airport2(apa2);
Airport airport3(apa3);
Airport airport4(apa4);
Airport airport5(apa5);


Route route1(airport0.getID(), airport1.getID(), 7856.2);
Route route2(airport0.getID(), airport1.getID(), 7856.2);
Route route3(airport0.getID(), airport2.getID(), 4554.64);
Route route4(airport0.getID(), airport4.getID(), 7702.8);
Route route5(airport1.getID(), airport3.getID(), 5453.54);
Route route6(airport3.getID(), airport4.getID(), 5523.78); 
Route route7(airport3.getID(), airport2.getID(), 7014.59);
Route route8(airport3.getID(), airport5.getID(), 5875.47);

Graph createTestGraph_shortestPath() {
  
  Graph gra;
  
    gra.insertVertex(airport0);
    gra.insertVertex(airport1);
    gra.insertVertex(airport2);
    gra.insertVertex(airport3);
    gra.insertVertex(airport4);
    gra.insertVertex(airport5);
    
    gra.insertEdge(route1); 
    gra.insertEdge(route2); 
    gra.insertEdge(route3); 
    gra.insertEdge(route4); 
    gra.insertEdge(route5);  
    gra.insertEdge(route6); 
    gra.insertEdge(route7); 
    gra.insertEdge(route8);
    
  return gra;
}

TEST_CASE("Graph::shortestpath finds a shortest path1", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport0.getID(), airport1.getID());
  
  REQUIRE( path.size() == 2 );
  REQUIRE( path.front() == "75" );
  REQUIRE( path.back() == "76" );
}

TEST_CASE("Graph::shortestpath finds a shortest path2", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport0.getID(), airport2.getID());
  
  REQUIRE( path.size() == 2 );
  REQUIRE( path.front() == "75" );
  REQUIRE( path.back() == "77" );
}

TEST_CASE("Graph::shortestpath finds a shortest path3", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport3.getID(), airport2.getID());
  
  REQUIRE( path.size() == 2 );
  REQUIRE( path.front() == "1" );
  REQUIRE( path.back() == "77" );
}

TEST_CASE("Graph::shortestpath finds a shortest path4", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport0.getID(), airport4.getID());  
  REQUIRE( path.size() == 2 );
  std::list<std::string> testpath;
  testpath.push_front("2");
  testpath.push_front("75");
  REQUIRE(path == testpath);
}

TEST_CASE("Graph::shortestpath finds a shortest path5", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport0.getID(), airport3.getID());
  // 75->76->1
  REQUIRE( path.size() == 3 );
  std::list<std::string> testpath;
  testpath.push_front("1");
  testpath.push_front("76");
  testpath.push_front("75");
  REQUIRE(path == testpath);
}

TEST_CASE("Graph::shortestpath finds a shortest path6", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport1.getID(), airport4.getID());
  // 76->1->2
  REQUIRE( path.size() == 3 );
  std::list<std::string> testpath;
  testpath.push_front("2");
  testpath.push_front("1");
  testpath.push_front("76");
  REQUIRE(path == testpath);
}

TEST_CASE("Graph::shortestpath finds a shortest path7", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport1.getID(), airport2.getID());
  // 76->1->77
  std::list<std::string> testpath;
  testpath.push_front("77");
  testpath.push_front("1");
  testpath.push_front("76");
  REQUIRE(path == testpath);
  REQUIRE( path.size() == 3 );
}

TEST_CASE("Graph::shortestpath finds a shortest path8", "[weight=2]") {
  Graph gra = createTestGraph_shortestPath();

  std::list<std::string> path = gra.shortestpath(airport0.getID(), airport5.getID());
  // 75->76->1->3
  std::list<std::string> testpath;
  testpath.push_front("3");
  testpath.push_front("1");
  testpath.push_front("76");
  testpath.push_front("75");
  REQUIRE(path == testpath);
  REQUIRE( path.size() == 4 );
}
