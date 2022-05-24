/**
 * @file bfs_traversal.cpp
 * @author Unidentity (jingboy2@illinois.edu)
 * @date 2021-12-06
 * 
 */

#include "bfs.h"

#include <assert.h>

using vertex = Airport;
using edge = Route;

BFSTraversal::iterator::iterator(BFSTraversal* trav) :
        traversal(trav)
{
    traversal->add(traversal->getStart());
    _current_vtx = traversal->peek();
}

BFSTraversal::iterator & BFSTraversal::iterator::operator++() {
    if (! traversal->empty()) {
        _current_vtx = traversal->pop();
        setLabel(_current_vtx, Label::Visited);
        vector<vertex> incidentVertices = traversal->getIncidentVertices(_current_vtx);
        for (vertex v0 : incidentVertices) {
            if (getLabel(v0) == Label::Unexplored) {
                setLabel(_current_vtx, v0, Label::Discovery);
                setLabel(v0, Label::Visited);
                traversal->add(v0);
            }
            else if (getLabel(_current_vtx, v0) == Label::Unexplored) {
                setLabel(_current_vtx, v0, Label::Cross);
            }
        }
    }

    return *this;
}

Airport BFSTraversal::iterator::operator*() {
    return traversal->peek();
}

bool BFSTraversal::iterator::operator!=(const iterator & other) {
    bool thisEmpty = false;
    bool otherEmpty = false;

    if (traversal == nullptr) thisEmpty = true;
    if (other.traversal == nullptr) otherEmpty = true;

    if (!thisEmpty) thisEmpty = traversal->empty();
    if (!otherEmpty) otherEmpty = other.traversal->empty();

    if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
    else if ( (!thisEmpty) && (!otherEmpty) ) return (traversal != other.traversal); //both not empty then compare the traversals
    else return true; // one is empty while the other is not, return true
}

inline void BFSTraversal::iterator::setLabel(vertex &v, Label label) {
    v_to_label[v.getID()] = label;
}

inline void BFSTraversal::iterator::setLabel(vertex &v1, vertex &v2, Label label) {
    edge e(v1.getID(), v2.getID(), -1);
    e_to_label[e] = label;
}

inline Label BFSTraversal::iterator::getLabel(vertex &v) {
    string ID = v.getID();
    if (!v_to_label.count(ID))
        v_to_label[ID] = Label::Unexplored;
    return v_to_label[ID];
}

inline Label BFSTraversal::iterator::getLabel(vertex &v1, vertex &v2) {
    edge e(v1.getID(), v2.getID(), -1);
    if (!e_to_label.count(e))
        e_to_label[e] = Label::Unexplored;
    return e_to_label[e];
}
