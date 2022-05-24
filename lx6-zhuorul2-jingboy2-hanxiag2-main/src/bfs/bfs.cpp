/**
 * @file bfs.cpp
 * @author Unidentity (jingboy2@illinois.edu)
 * 
 * @brief Implementation of BFS.
 * @date 2021-12-03
 * 
 */

#include "bfs.h"

#include <assert.h>

using vertex = Airport;

BFSTraversal::~BFSTraversal()
{
}

void BFSTraversal::BFS(Graph g) {
    // for (Airport v : g.vertexTable) {
    //     setLabel(v, Label::Unexplored);
    // }
    // for (Route e : g.edgeList) {
    //     setLabel(e, Label::Unexplored);
    // }
    // for (Airport v : G.vertexTable) {
    //     if (getLabel(v) == Label::Unexplored)
    //         BFS(g, v);
    // }
}

BFSTraversal::iterator BFSTraversal::begin() {
    return BFSTraversal::iterator(this);
}

BFSTraversal::iterator BFSTraversal::end() {
    return BFSTraversal::iterator();
}

void BFSTraversal::add(vertex & v) {
    vq.push(v);
}

vertex BFSTraversal::pop() {
    vertex ret = vq.front();
    vq.pop();
    return ret;
}

vertex BFSTraversal::peek() const {
    return vq.empty() ? Airport() : g->vertexTable.at(vq.front().getID());
}

bool BFSTraversal::empty() const {
    return vq.empty();
}

vertex & BFSTraversal::getStart() {
    vertex & ret = g->vertexTable[start->getID()];
    return ret;
}

std::vector<vertex> BFSTraversal::getIncidentVertices(vertex v) {
    std::vector<vertex> ret;
    for (edge e : g->incidentEdges(v)) {
        ret.push_back( g->vertexTable[e.getDestination()] );
    }
    return ret;
}
