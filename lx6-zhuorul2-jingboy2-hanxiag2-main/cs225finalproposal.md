# CS 225 Final Project Proposal

Zhuoru Li(zhuorul2), Longcong Xu(lx6), Hanxia Guo(hanxiag2), Jingbo Yang(jingboy2)

Professor Name Evens, G
Subject Name: Shortest Path algorithm to find preferred routes.

NOV 05, 2021
 
## Leading Question: ##

For this final project, our ultimate goal is to find the shortest paths and the airports with largest throughput using the given airport database and routes database. We want to end up with a command-line program that, after entering the origin and destination, gets the recommended flight number and route. We find that from a given data set we can obtain :

(1) airport coordinate data -- used to calculate flight distance 

(2) flight information on each route 

(3) number of stops on each route. We will process the data and create our own program.

Our team has a clear and consistent view of the end goal, and we believe that the goal problem can be solved. We have preliminarily designed the project timeline to ensure a scientific and rational allocation of time to complete the project.


## Dataset Acquisition and Processing ##
What dataset we have chosen to use: “OpenFlights” which we will generally use two parts of. 

(1)Airport database        

(2)Route database

Additonally, we will go through 

The airport part will give us information about the positions of airports and then we can calculate the distance between them. And the Route part will become the edges of our graph.
How we will download, store, and process our data:
We will download directly from the website: https://openflights.org/data.html where stores the main database we will use. And we will store it on our virtual machine(or own machine) and on the github website. To process our data we will do some data clean jobs like delete the missing data. When we meet the NULL situation we will simply give it a nullptr or change it to an empty project. And slice our data to different parts so that when we want to choose to use it we can simply pick.

The airport database originally contain the following information:
507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"

Above is a simple example of the entries and we will slice it part by part and put the information into different lists. Like the latitude and longitude will be used to calculate the distance and will use it to weight the graph and we will do the same for the route graph to get the number of route (edge) and measure it which will give us the way to find the airport with the highest throughput.  

Since our goal is to choose the most convenient and efficient route for travelers to get from one place to another, we need to fix each airport as vertices in the diagram and then each route as edges, with respective weights on the edges to help us choose the priority. The weights consist of two parts multiplied by each other: price and company's reputation. we suppose that the Price is proportional to distance, flight reputation is proportional to airline size. For mathmatical example:
```
Assuming that the number of routes per airline is xi (the subordination can be established by matching the Airline ID of Routes and Airlines.), we can calculate the share of airlines p as:

  P = xi/sum(xi).(0<p<1)  

The distance can be computed using Haversine formula. Let lat1, 2 be the radians of latitudes of two points; long1, 2 be the radians of longitudes of two points (by "points" we mean the points on a sphere, which is the Earth. The points are also equivalent to the vertices of the graph, and two distinct Airports), the distance D can be calculated as:  

  D = 3963.0 * arccos( (sin(lat1) * sin(lat2)) + cos(lat1) * cos(lat2) * cos(long2 – long1) )  
```
Using TOPSIS model, the weight of edge between two vertices can be determined by P and D. Determining the directions of edges is straightforward, by simply parsing the Source airport and the Destination airport in Route.csv.  

We will then calculate the shortest path from the source to the destination using Dijkstra's Algorithm, with the weight formerly computed.

Once the path comes out, we project the source, the path, and the destination onto a world map, then present to the user. The visualization step takes the shortest path calculated (which as expected should be a vector of vertices, including the source and the destination) and a PNG that contains the world map, and returns a modified map that maps the critical points mentioned above.


## Graph algorithms ##
Algorithms implementation waitlist:
### Shortest Path:
- Dijkstra’s Algorithm.
  - Accepts a weight graph, the starting point and the destination, returns a vector of `Airport` that leads to the path of least sum of weights.
### Graph Traversal:
- Breadth First Search of graph.
  - Accepts a graph, returns an iterator that does the traversal.
### Weight Quantification:
  - Accepts multiple criteria of `Airport`s, `Airline`s, and `Route`s (positions, reputations, etc.), returns a normalized numerical weight used by edges of the graph.
### Data Visualization:
- Simply project the source, the destination, and the path of shortest sum of weight onto a world map.

### Expected running time:
(For the following context, `E` denotes the set of edges, and `V` denotes the set of vertices.)
1. For Dijkstra’s Algorithm optimized with binary heap, the worst time complexity is `O((|E|+|V|)`
2. BFS would be `\theta(|V|)`, since they visit every single vertex within the graph.
3. Since the quantity of properties of `Airport`s, `Airlines` and `Route`s is limited, and the computational processes are basically numeric, TOPSIS has a time complexity of `O(1)`.


## Timeline ##

|  Time   | Tasks  |
|  :----:  |:----:|
| 11.2 - 11.8  | Identify the selected topic and sort out the framework for doing it. Complete the Contract and Proposal of the Project.|
| 11.9 - 11.20| Complete the cleaning of data and filter out the valid data. Complete the graph class and functions, discuss the algorithm implementation (write at least one pseudo-code of the algorithm).|
|11.20- 11.28|Prepare the first mid-project checkin, summarize the issues, and identify the remaining tasks.|
|11.29 - 12.5|Visualization of the completed diagram|
|12.6 - 12.10|Prepare presentation for final project|