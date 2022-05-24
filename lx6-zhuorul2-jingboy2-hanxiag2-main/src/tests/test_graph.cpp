#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../route.h"
#include "../airport.h"



Graph createTestGraph() {
  /*
         _ b   /--------- h
        /  | _/           |
      a -- c -- e    f -- g
        \_   _/
           d 
  */

  Graph gra;
  gra.insertVertex("a");
  gra.insertVertex("b");
  gra.insertVertex("c");
  gra.insertVertex("d");
  gra.insertVertex("e");
  gra.insertVertex("f");
  gra.insertVertex("g");
  gra.insertVertex("h");

  gra.insertEdge("a", "b");
  gra.insertEdge("a", "c");
  gra.insertEdge("a", "d");

  // Additional edges on `b`:
  //Route bc("b", "c", 1);
  gra.insertEdge("b", "c");

  // Additional edges on `c`:
  //Route ce("c", "e", 1);
  gra.insertEdge("c", "e");

  //Route ch("c", "h", 1);
  gra.insertEdge("c", "h");

  // Additional edges on `d`:
  //Route de("d", "e", 1);
  gra.insertEdge("d", "e");

  // Additional edges on `e`: 

  // Additional edges on `f`:
  //Route fg("f", "g", 1);
  gra.insertEdge("f", "g");

  // Additional edges on `g`:
  //Route gh("g", "h", 1);
  gra.insertEdge("g", "h");

  // Additional edges on `h`: 

  return gra;
}



TEST_CASE("Graph::size returns the vertex count", "[weight=1]") {
  Graph gra;
  gra.insertVertex("a");
  gra.insertVertex("b");  
  REQUIRE( gra.size() == 2 );

  gra.insertVertex("c");
  gra.insertVertex("d");
  gra.insertVertex("e");
  REQUIRE( gra.size() == 5 );
}


TEST_CASE("Graph::edges::size returns the edge count", "[weight=1]") {
  Graph gra;

  gra.insertVertex("a");
  gra.insertVertex("b");  
  gra.insertVertex("c");
  gra.insertVertex("d");
  gra.insertVertex("e");

  REQUIRE( gra.edges() == 0 );

  //Route ac("a", "c", 1);
  gra.insertEdge("a", "c");

  //Route bd("b", "d", 1);
  gra.insertEdge("b", "d");

  //Route ae("a", "e", 1);
  gra.insertEdge("a", "e");

  REQUIRE( gra.edges() == 3 );
}


TEST_CASE("Eight-vertex test graph has correct properties", "[weight=1]") {
  Graph gra = createTestGraph();
  REQUIRE( gra.size() == 8 );
  REQUIRE( gra.edges() == 9 );
}

TEST_CASE("Graph::incidentEdges contains incident edges (origin-only test)", "[weight=1]") {
  Graph gra = createTestGraph();
  REQUIRE( gra.incidentEdges("a").size() == 3 );
}


TEST_CASE("Graph::incidentEdges contains incident edges (dest-only test)", "[weight=1]") {
  Graph gra = createTestGraph();
  REQUIRE( gra.incidentEdges("h").size() == 0 );
}


TEST_CASE("Graph::incidentEdges contains incident edges (hybrid test)", "[weight=1]") {
  Graph gra = createTestGraph();
  REQUIRE( gra.incidentEdges("d").size() == 1 );
}


TEST_CASE("Graph::isAdjacent is correct (same-order test)", "[weight=1]") {
  Graph gra;
  Airport a("a");
  Airport d("d");
  gra.insertVertex("a");
  gra.insertVertex("d");
  gra.insertEdge(a, d);
  REQUIRE( gra.areAdjacent(a, d) == true );
}

