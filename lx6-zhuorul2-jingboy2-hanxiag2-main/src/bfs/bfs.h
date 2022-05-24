/**Input: Graph, G
Output: A labeling of the edges on

G as discovery and cross edges

**/

#include "../graph.h"
#include "../route.h"

#include <queue>
#include <string>
#include <unordered_map>

using std::string;
using vertex = Airport;
using edge = Route;
using ID = string;

enum class Label {
    Unexplored,
    Visited,
    Discovery,
    Cross
};

class BFSTraversal {
private:
    class iterator : std::iterator<std::forward_iterator_tag, Airport> {
    public:
        iterator() : traversal(nullptr) {}
        iterator(BFSTraversal* trav);

        iterator & operator++();
        Airport operator*();
        bool operator!=(const iterator & other);

    private:
        /**
         * @brief Set a vertex to a status.
         * It can be either "Unexplored", "Visited", "Discovery", or "Cross".
         * 
         * @param v 
         * @param label 
         */
        void setLabel(vertex &v, Label label);

        /**
         * @brief Set an edge to a status.
         * It can be either "Unexplored", "Visited", "Discovery", or "Cross".
         * 
         * @param v1 
         * @param v2 
         * @param label 
         */
        void setLabel(vertex &v1, vertex &v2, Label label);

        /**
         * @brief Get the Label of given Airport object.
         * 
         * @param v Airport object to inspect.
         */
        Label getLabel(vertex &v);

        /**
         * @brief Get the label of given edge.
         * 
         * @param v1 
         * @param v2 
         * @return Label 
         */
        Label getLabel(vertex &v1, vertex &v2);

    private:
        BFSTraversal* traversal;

        /**
         * @brief Current vertex being considered.
         * 
         */
        vertex _current_vtx;

        /**
         * @brief Hashmap mapping a vertex's ID to its label.
         * 
         */
        std::unordered_map<ID, Label> v_to_label;

        /**
         * @brief Hashmap mapping an edge to its label.
         * 
         */
        std::unordered_map<edge, Label> e_to_label;
    };

private:
    /**
     * @brief Vertices queueing.
     * 
     */
    std::queue<vertex> vq;

    /**
     * @brief Pointer to the graph object to be traversed.
     * 
     */
    Graph* g;

    /**
     * @brief Starting vertex of the traversal.
     * 
     */
    vertex* start;

public:
    /**
     * @brief Default constructor.
     * 
     */
    BFSTraversal() {}

    /**
     * @brief Parameterized constructor.
     * 
     */
    BFSTraversal(Graph &graph, const vertex &start) : g(&graph) {
        this->start = &(g->vertexTable[start.getID()]);
    }

    BFSTraversal(Graph &graph, const string &start) : g(&graph) {
        vertex* v = &(g->vertexTable[start]);
        this->start = v;
    }

    ~BFSTraversal();

    /**
     * @brief Breadth first traversal procedure.
     * 
     * @param g Graph to be traversed.
     */
    void BFS(Graph g);

    BFSTraversal::iterator begin();

    BFSTraversal::iterator end();

    /**
     * @brief Add a vertex to the queue.
     * 
     * @param v Vertex to be added.
     */
    void add(vertex & v);

    /**
     * @brief Remove then return the next vertex.
     * 
     * @return vertex 
     */
    vertex pop();

    /**
     * @brief Return but not remove the next vertex.
     * 
     * @return vertex 
     */
    vertex peek() const;

    /**
     * @brief Whether the queue is empty.
     * 
     * @return true 
     * @return false 
     */
    bool empty() const;

    /**
     * @brief Private helper function of BFS.
     * 
     * @param g 
     * @param v 
     */
    void BFS(Graph g, Airport v);

    /**
     * @brief Get the starting point of the traversal.
     * 
     * @return vertex& The starting point.
     */
    vertex & getStart();

    /**
     * @brief Get a vector of vertices that are neighbors of 
     * the given vertex.
     * 
     * @param v 
     * @return std::vector<vertex> 
     */
    std::vector<vertex> getIncidentVertices(vertex v);
};
