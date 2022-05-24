#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>

#include "../graph.h"
#include "../bfs/bfs.h"
// #include "../csv_parser/csvparser.h"

using namespace std;

Graph createSmallTestGraph() {
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

    // Routes on `a`:
    //Route ab("a", "b", 1);
    gra.insertEdge("a", "b");

    //Route ac("a", "c", 1);
    gra.insertEdge("a", "c");

    //Route ad("a", "d", 1);
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
    gra.insertEdge("g", "f");

    // Additional edges on `g`:
    //Route gh("g", "h", 1);
    gra.insertEdge("h", "g");

    // Additional edges on `h`: 

    return gra;
}

Graph createBigTestGraph() {
    /*      ---  c   i ----j
           /     |    \
          /      |      \
        a ------ b ------ h --|
        |  ----/ |  \         |
        | /      |   \        |
        d ------ e --- f ---- g
                 |      |    /
                 |      |   /
                 l      | - k 
    */ 

    Graph ret;

    // Vertices.
    ret.insertVertex("a");
    ret.insertVertex("b");
    ret.insertVertex("c");
    ret.insertVertex("d");
    ret.insertVertex("e");
    ret.insertVertex("f");
    ret.insertVertex("g");    
    ret.insertVertex("h");
    ret.insertVertex("i");
    ret.insertVertex("j");
    ret.insertVertex("k");
    ret.insertVertex("l");
    ret.insertVertex("m");
    ret.insertVertex("n");

    // Edges
    ret.insertEdge("a", "b");
    ret.insertEdge("a", "d");
    ret.insertEdge("a", "c");
    ret.insertEdge("d", "b");
    ret.insertEdge("b", "c");
    ret.insertEdge("b", "e");
    ret.insertEdge("e", "l");
    ret.insertEdge("b", "f");
    ret.insertEdge("b", "h");
    ret.insertEdge("h", "i");
    ret.insertEdge("i", "j");
    ret.insertEdge("h", "g");
    ret.insertEdge("g", "k");
    ret.insertEdge("k", "f");
    ret.insertEdge("f", "e");

    return ret;
}

TEST_CASE("test small graph bfs.", "[weight=10][part=bfs]") {
    Graph graph = createSmallTestGraph();
    Airport start("a");
    BFSTraversal traversal(graph, start);

    /// Counter of iteration.
    int count = 0;
    for (auto it = traversal.begin(); it != traversal.end(); ++it) {
        clog << (*it).getID() << " -> " << flush;
        ++count;
    }
    clog << "|" << endl;

    REQUIRE(count == graph.size());
}
