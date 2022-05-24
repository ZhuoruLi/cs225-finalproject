/**
 * @file graph.h
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <string>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include "airport.h"
#include "route.h"
#include "cs225/PNG.h"
#include "stickers/StickerSheet.h"
#include "stickers/Image.h"
#include "exceptions.h"

using namespace cs225;
using namespace std;
using V = Airport;
using E = Route;


class Graph {
    typedef typename std::list<E>::iterator edgeListIter;
    typedef pair<string, double> dv;

private:
    /**
     * @brief Directory to data and files needed.
     * 
     */
    string dir;
    
public:
    Graph() : dir("data/") {}
    Graph(const string &dir) : dir(dir) {}

    int size() const;
    int edges() const;
    void setDir(const string &dir);
    void insertVertex(V & a);
    V & insertVertex(std::string key);
    void insertEdge(E & r);
    E & insertEdge(const std::string key1, const std::string key2);
    E & insertEdge(V & a1, V & a2);
    void removeVertex(V & a);
    void removeEdge(const E & e);
    void removeEdge(const edgeListIter & it);
    void removeEdge(string a1, string a2);
    list<E> incidentEdges(V & a);
    list<E> incidentEdges(const std::string key) const;
    bool areAdjacent(V & a1, V & a2);
    std::list<std::string> shortestpath(const std::string start, const std::string end);
    

    std::list<E> edgeList;
    std::unordered_map<std::string, V> vertexTable;
    std::unordered_map<std::string, std::list<edgeListIter>> adjList;
    
    /**
     * @brief Draw paths along the passed list of ID of vertices.
     * 
     * @param a 
     * @param path 
     * @return Image 
     * @throw __fail_to_open_file
     */
    Image drawpath(Image & a, list<string> path);

private:
    int sign(double value);
    pair<double, double> getposition(V & start, PNG a);
    void _clear();
    void _copy(const Graph &rhs);
};
