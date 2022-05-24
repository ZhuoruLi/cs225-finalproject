# Final Project Results

Our goal is to build a shortest flight path with its visualization on the world map. This work is mainly composed of five parts:
## Part one, the processing of data:

Our original data is downloaded from the Open flights data set (https://openflights.org/data.html), we mainly used two files from it which gives us enough information to build the graph. The first file we use is airports.csv which includes information of the airport position, and its name which we will use as a key. The second file we use is route.csv which contains information about the start and destination. We then build a csv_parser which can transfer the data into a vector of string, during which we handled empty sets and illegal paths. (How to do and how to test)

_Here is part of our test cases of the parser. The idea is simple. Considering that the size of our dataset is large (about 78000 lines), we first tried to load the full dataset into two vectors and see if the program holds. It turned out to be fine. Then we proceed by manually constructing a vector of airports, namely expected airports. We then run the deserialization module and generates a vector called actual airports, and we compare their corresponding element to see if they are equal.

## Part two, build of the directed graph with adjacency list:

Under the graph class we have two subclasses, Airport and Route. Airport represents the points in the graph and contains the basic data of the airport, including a unique airport id, the longitude and latitude of the airport. Route includes the start airport and destination airport. Both classes create constructor through attribute formed after csv_parser.

We implemented this directed graph with adjacency list which also include a list of edges and a hash table of vertex, we use the id of the Airport as the key. The ADT we implemented includes insert/remove vertex and edges. Areadjacent function to determine if two vertices are adjacent to each other, incidentedges function which will return a list of incident edges of a specific vertex. We also implemented the Airport class as the vertex and Route class as the edges which includes weight calculated from the geographical location of the two airports. In the graph file, we provide different interface functions to implement the same operation, which are easy to call later. For example, we provide insertEdges function that accepts one parameter of type Route, two parameters of type string and two parameters of type Airport.

As for test this part, we built test_graph.cpp which under the test folder. We create a directed graph with 8 points and 9 edges by inserting a route with a start point and an end point. We checked whether each call to the insertVertex and insertEdge functions could accurately change the graph.


## Part three, the BFS traversal of the graph:

For the graph traversal’s part, we choose BFS traversal.
The architecture of BFS module follows what we have done in the previous MPs. Similar to traversing a vector and a list, we loop through the graph via an customized iterator, which is defined inside our BFSTraversal class. The iterator resides in a user-specified vertex, and moves along the graph upon the iteration of loop. Whenever the self-increment operator of iterator is invoked, which is exactly when a iteration occur, the BFS algorithm will determine which vertices should be added to the queue. And by dereferencing the iterator, we can get access to the current vertex of graph.

By the way, our program does not necessarily need a BFS traversal. To implement it is solely due to my personal interest.

## Part four, the Dijkstra’s algorithm’s implantation:

This shortest path algorithm is chosen as our covered algorithm, we want to return a list of string which can represent our path step by step. We fallowed the Pseudo-code and use unvordered map to store our predecessor and distance from the original point. We then use std priority queue to pop next vertex to the iteration, then we go through back the predecessor map and push every vertex to the list from the end and back to the start.

To test Dijkstra’s algorithm, we built test_theshortestpath.cpp. We form a directed graph by inserting the vertex and the route with weights using the data after the parser. We examine the paths with 2, 3 and 4 vertices respectively, and check the number of vertices contained in the string lists output by theshortestpath function and the order of the output.

## Part five, the graphic project of our graph on the world map with Mercator projection:

How can we project our graph to a 2-D map of earth, this become a question and we solved this by using Mercator projections which is a cylindrical map projection. The image on the sphere is projected into a cylinder with a diameter equal to his. And the image of the sphere onto the rectangular surface of the cylinder. The projection relationship shows below which y is the latitude after scale and Φ is original latitude of airport.

        y = sign(Φ)*ln(tan(45° + abs(Φ/2))

We then draw our path on the map of the calculated coordinate and we use sticker in this part. We use sticker to mark the start of each route and the end of the last route.

Link to the presentation video : https://drive.google.com/file/d/1cT5GCIj6pbFondNOg10J0FrA02K0n2cP/view?usp=sharing