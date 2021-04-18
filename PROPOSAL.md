
# FINAL PROJECT PROPOSAL (padhi3-miw3-jorteg38-wpark26)

### Leading Questions:
- What is the shortest available route between two given airports?
- What the the most central aiport relative to >=2 other airports?
 
 Our intention is to use the OpenFlights data sets “airports.dat” and “routes.dat” to create a directed and weighted graph of all of the airports and the routes between them, weighted by the distance from one airport to the other. We will implement a BFS traversal along with Djikstra's algorithm and betweenness centrality mapping to determine the best way to get from one location to another, and the ideal place to be if one wanted to visit a selection of different locations from that point. In other words, the end result will be intended to produce answers to two very specific problem, finding the ideal path, and finding the ideal location.
  
As previously stated, we will be using the “airports.dat”  and “routes.dat” data sets. To download these, we will first go to OpenFlight’s Github, then simply download those two files, as they are available there. They will then be stored in our Github and on our local cloned repositories, as the files themselves take up less than four MB together. From there, it’s simply  a matter of reading out of the file, which is a CSV. One thing which can make this difficult is missing entries and partial entries. A missing entry simply is not there and throws off the assumed number of entries based on the reported number of entries that the file lists. To account for this we need to check how many are missing and not assume that the file can be trusted to report the amount of airports/routes it records. Another issue will be accounting for entries which do not have some values filled in or have them filled with an incompatible type which could throw off the algorithm reading out of the file. The solution for this is to replace those parts of the entry with valid values which also indicate that there is nothing there, such as NULL or “NA”. Another issue is what type of reading method to use, although switching from CSV to a space delimited file and using if stream will probably work. After the routes and airports are properly read, we can proceed to make a graph with the airports as vertices and the routes as directed edges.
  
The two algorithms we will be implementing are Djikstra's and betweenness centrality mapping, with djikstra's first helping us find shortest paths from one point to the next, and beetwenness centrality mapping us find the most central airport given a set of airports one would be interested in visiting. The actual traversal will be a BFS as there will be many airports spread all over the globe, making a DFS that starts on the wrong node run for a prohibitive amount of time. We expect Djikstra's algorithm to take two pointers to nodes in a directed weighted graph of the airports with the routes and their distances as edges, and use these to find the shortest path from one to the other considering the distances. The simplest implementation of Djikstra's algorithm yield `O(V^2)`, where V is the number of vertices in the graph, but if we implement it ideally with a fibonnacci heap, we could get it down to `O(E+VlogV)`, with E as the nummber of edges. The return value will be a vector of all the points on the graph (airports) visited to get from the start to the finish. For betweenness centrality mapping, the input will be a vector of points on the graph (airports), which one may want to visit from their original location. The output will be a singular point which is the most central point relative to the input. Calculating betweenness requires finding shortest paths for every pair of vertices, which takes O(V^3), where V is the number of vertices in the graph, but if we can find a way to treat the specific nodes we're looking at as a sparse graph, we could use Johnson's algorithm to get `O(V^2log(V)+VE)`.

### Timeline:
- Week of 4/12: Data Acquisition and Processing
- Week of 4/19: Complete graph and BFS traversal for graph
- Week of 4/26: Complete Djikstra's algorithm
- Week of 5/3: Complete Betweenness centrality mapping algorithm
- Week of 5/10: Refine the Documentation for the project and produce final presentation