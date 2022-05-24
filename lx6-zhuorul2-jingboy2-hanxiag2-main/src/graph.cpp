/**
 * @file graph.cpp
 * @date 2021-11-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <iostream>
#include <cmath>

#include "graph.h"
#include "route.h"
#include "exceptions.h"
#include "stickers/Image.h"
#include "stickers/StickerSheet.h"

#define DBL_MAX 1.7976931348623158e+308
#define pi 3.1415926

using namespace cs225;
using namespace std;
using std::count;


void Graph::_copy(const Graph &rhs) {
    this->edgeList = rhs.edgeList;
    this->vertexTable = rhs.vertexTable;
    this->adjList = rhs.adjList;
}

void Graph::_clear() {
    edgeList.clear();
    vertexTable.clear();
    adjList.clear();
}

int Graph::size() const {
    return vertexTable.size();
}


int Graph::edges() const {
    return edgeList.size();
}

void Graph::setDir(const string &dir) {
    this->dir = dir;
}

void Graph::insertVertex(V & a) {
    vertexTable.insert(pair<string, V&>(a.getID(), a));
    adjList.insert(pair<string, list<edgeListIter>>(a.getID(), list<edgeListIter>()));
}
V & Graph::insertVertex(std::string key) {
  	V & v = *(new V(key));
  	vertexTable.insert(pair<string, V&>(key, v));
  	adjList.insert(pair<string, list<edgeListIter>>(key, list<edgeListIter>()));
  	return v;
}

E & Graph::insertEdge(const std::string key1, const std::string key2) {
  return insertEdge( vertexTable.at(key1), vertexTable.at(key2) );
}

void Graph::insertEdge(E & r) {
    string startVertex = r.getStart();
    string endVertex = r.getDestination();
    if (vertexTable.find(startVertex) == vertexTable.end()) {
        throw __critical_data_not_found("startVertex not found");
    }
    if (vertexTable.find(endVertex) == vertexTable.end()) {
        throw __critical_data_not_found("endVertex not found");
    }

    edgeList.push_front(r);
    adjList.at(r.getStart()).push_front(edgeList.begin());
}


E & Graph::insertEdge(V & a1, V & a2) {
    double weight = Route::computeWeight(a1, a2);
    E & route = *(new E(a1.getID(), a2.getID(), weight));
    edgeList.push_front(route);
    adjList.at(a1.getID()).push_front(edgeList.begin());
    return route;
}


void Graph::removeVertex(V & a) {
    list<E> incidentEdgeList = incidentEdges(a);
    for (E routeit : incidentEdgeList) {
        removeEdge(routeit.getStart(), routeit.getDestination());
    }
}

/**
* Removes the given Edge from the Graph.
* @param e The Edge you want to remove
*/
void Graph::removeEdge(const E & e) {
    edgeListIter it = std::find(edgeList.begin(), edgeList.end(), e);
    removeEdge(it);
}
/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
void Graph::removeEdge(const edgeListIter & a) {
	std::string vertex1 = (*a).getStart();
	std::string vertex2 = (*a).getDestination();
	for (typename list<edgeListIter>::iterator it = adjList.at(vertex1).begin(); it != adjList.at(vertex1).end(); it++) {
		if ((*it) == a) {
			adjList.at(vertex1).erase(it);
			break;
		}
	}
    for (typename list<edgeListIter>::iterator it = adjList.at(vertex2).begin(); it != adjList.at(vertex2).end(); it++) {
        if ((*it) == a) {
            adjList.at(vertex2).erase(it);
            break;
        }
    }
	edgeList.erase(a);
}



void Graph::removeEdge(string a1, string a2) {
    edgeListIter eli = edgeList.end();
    //bool directedflag = false;
    for (typename list<edgeListIter>::iterator it = adjList.at(a1).begin(); it != adjList.at(a1).end(); it++) {
        E edge = (*(*it));
        if (edge.getStart() == a1 && edge.getDestination() == a2) {
            adjList.at(a1).erase(it);
            eli = *it;
            break;
        }
    }
    if (eli != edgeList.end()) 
        edgeList.erase(eli);
}



list<E> Graph::incidentEdges(V & a) {
    list<E> edges;
    for (edgeListIter edgeit : adjList.at(a.getID())) {
        edges.push_back(*edgeit);
    }
    return edges;
}

list<E> Graph::incidentEdges(const std::string key) const {
    list<E> edges;
    for (edgeListIter edgeit : adjList.at(key)) {
        edges.push_back(*edgeit);
    }
    return edges;
}

bool Graph::areAdjacent(V & a1, V & a2) {
    for (edgeListIter eli : adjList.at(a1.getID())) {
        E cur_edge = (*eli);
        if (cur_edge.getStart() == a2.getID() || cur_edge.getDestination() == a2.getID()) {
            return true;
        }
    }
    return false;
}

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
std::list<std::string> Graph::shortestpath(const std::string start, const std::string end) {
	unordered_map<string, string> predecessor; //store every vertex's predecessor, so that a path list can be made 
	unordered_map<string, double> distances; //store track of distances from start
    for (auto key : vertexTable) {  //initialize the predecessor and distance
        predecessor[key.first] = "";
        distances[key.first] = DBL_MAX;
    }
    distances[start] = 0.0; // initial the distance if the first vertex
    struct myComp {  // define a compare rule in priority queue
        constexpr bool operator()(
            dv const& a,
            dv const& b)
            const noexcept
        {
            return a.second > b.second;
        }
    };
    priority_queue<dv, vector<dv>, myComp> pq; // build a priority queue
    dv a;
    a.first = start;
    a.second = 0;
    pq.push(a);
    vector<string> visited; // build a vector which inclued the visited vertex                                  
    while (!pq.empty()) { 
        string m = pq.top().first;
        pq.pop();
        int check = std::count(visited.begin(), visited.end(), m); // check if the vertex has been visited
        if (check!=0) continue; // if the vertex has been visitied, skip that vertex and continue
        visited.push_back(m);
        for (E neighbors: incidentEdges(m)) { //using loop to find all the neighbours
            string neighborskey = neighbors.getDestination();
            double weight = Route::computeWeight(vertexTable[m], vertexTable[neighborskey]);
            if (distances[m] + weight < distances[neighborskey]) { //if the new vertex cost less
                distances[neighborskey] = distances[m] + weight; 
                predecessor[neighborskey] = m; //update distance and predessesor
                dv n;
                n.first = neighborskey;
                n.second = distances[neighborskey];
                pq.push(n); // push a pair to priority queue
            }
        }
    }
    list<string> path;
  	string cur = end;
  	while (cur != "") { // Convert predecessor map to list
  		path.push_front(cur);
  		cur = predecessor[cur];
  	}
  	return path;
}

int Graph::sign(double value) {
    if (value < 0) return -1;
    else if (value == 0) return 0;
    return 1;
}

pair<double, double> Graph::getposition(V & startv, PNG a) {
    //draw route and airpoint
    double max_latitude = sign((85*pi)/180) * log(tan(pi/4 + abs((85*pi)/180/2)));
    double latitude_ratio = 
            (sign(pi * startv.getLatitude() / 180)
                * log(tan(pi/4 + abs(pi * startv.getLatitude() / 360)))
            ) / max_latitude;
    double longtitude_ratio = startv.getLongitude()/180;
    double x_start;
    double y_start;

    if (latitude_ratio >= 0) {
        double total = a.height()/2;
        double tosubtra = total*latitude_ratio;
        y_start = total - tosubtra;
    } else {
        double total = a.height()/2;
        double toadd = total*(-latitude_ratio);
        y_start = total + toadd;
    }
    if (longtitude_ratio >=0) {
        double total = a.width()/2;
        double toadd = total*longtitude_ratio;
        x_start = total + toadd;
    } else {
        double total = a.width()/2;
        double tosubtra = total*(-longtitude_ratio);
        x_start = total - tosubtra;
    }
    return pair<double, double>(x_start, y_start);
}

inline bool contains(list<string> &listOfEdges, const string& dest) {
    // Find the iterator if element in list
    auto it = find(listOfEdges.begin(), listOfEdges.end(), dest);
    // return if iterator points to end or not. It points to end then it means element
    // does not exists in list
    return it != listOfEdges.end();
}

inline void loadSticker(Image &sticker, const string &dir) {
    if (!sticker.readFromFile(dir))
        throw __fail_to_open_file(dir);   // Complain if file cannot be opened.
}

Image Graph::drawpath(Image & a, list<string> path) {
    list<E> new_path;
    for (string s : path) {
        list<E> listOfEdges = incidentEdges(vertexTable[s]);
        for (E e : listOfEdges) {
            if (contains(path, e.getDestination())) {
                new_path.push_back(e);
            }
        }
    }

    for (E e : new_path) {
        V startv = vertexTable[e.getStart()];
        pair<double, double> position0 = getposition(startv, a);
        V endv = vertexTable[e.getDestination()];
        pair<double, double> position1 = getposition(endv, a);
        double k = (position1.second - position0.second)/(position1.first - position0.first); // y = kx + b
        double b = position1.second - k * position1.first;
        double num = 1000;
        double interval = (position1.first - position0.first)/num;
        for (int i = 1; i <= num; i++) {
            double new_x = position0.first + i * interval;
            HSLAPixel & pixel = a.getPixel(new_x, k * new_x + b);
            pixel.h = 240;
            for (int j = 0; j < 4; j++) {
                HSLAPixel & pixeltop = a.getPixel(new_x, (k * new_x + b)-j);
                HSLAPixel & pixeldown = a.getPixel(new_x, (k * new_x + b)+j);
                HSLAPixel & pixelleft = a.getPixel((new_x)-j, k * new_x + b);
                HSLAPixel & pixelright = a.getPixel((new_x)+j, k * new_x + b);
        
                pixeltop.h = 240;
                pixeldown.h = 240;
                pixelleft.h = 240;
                pixelright.h = 240;
            }
        }
    }
    const string stickerName = "star.png";
    StickerSheet mysheet(a, 100);
    Image sticker;
    loadSticker(sticker, dir + stickerName);
    sticker.scale(0.04);

    auto new_path_it = new_path.begin();
    while (new_path_it != new_path.end()) {
        V startv = vertexTable[new_path_it->getStart()];
        pair<double, double> position0 = getposition(startv, a);
        mysheet.addSticker(
            sticker,
            position0.first - sticker.width() / 2,
            position0.second - sticker.height() / 2
        );
        ++new_path_it;
    }
    Image out = mysheet.render();

    return out;
}
