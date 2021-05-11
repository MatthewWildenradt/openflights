#include "Graph.h" //need the graph  header
#include <cmath> //need math for our algorithms
#include <limits> //need limits as well
#include <set> //and sets
#include <functional> //and functional
#include <iostream> //need iostream for basic usability
#include <stack>
#include <list>

using std::string; //need strings for location names
using std::vector; //need vectors for collections of routes and airports
using std::map; //need a map to access things based on their names
using std::queue;

Graph::Graph(){ //just your regular default consstructor
  // does nothing
}

Graph::Graph(vector<Airport> inputAirports, vector<Route> routes){ //make a graph using a vector of airports and a vector of routes

  for(Airport crnt : inputAirports){ //put all of the airports into the graph
    addAirport(crnt);
  }

  for(Route crnt : routes){ //put all of the routes into the graph
    addRoute(crnt);
  }
}

Graph::Graph(vector<vector<string>> inputAirports, //same thing as above
	     vector<vector<string>> routes){ //only using string vectors of names and not objects

  for(vector<string> line : inputAirports){ //put all airports in again
    addAirport(line);
  }

  for(vector<string> line : routes){ //put all routes in again
    addRoute(line);
  }
}

Graph::~Graph(){ //destructor
  for(auto it = airports.begin(); it != airports.end(); it++){ //for every node
    delete it->second; //delete that node
  }
}

void Graph::addAirport(Airport input){
  Node* airportNode = new Node();
  airportNode->data = input;
  airports.insert(std::pair<string, Node*>(input.name, airportNode));
  vertexCount++;
}

void Graph::addAirport(vector<string> input){
  //std::cout << "Inner values" << std::endl;
  //int i = 0;
  //for(string s : input){
  //std::cout << i <<": " <<  s << std::endl;
  //i++;
  //}
  int inputLen = input.size();

  Airport addThis(input.at(inputLen-10), std::stod(input.at(inputLen-8)), std::stod(input.at(inputLen-7)));
  Node* airportNode = new Node();
  airportNode->data = addThis;
  airports.insert(std::pair<string, Node*>(addThis.name, airportNode));
  vertexCount++;
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){
  auto start = airports.find(input.src);
  auto end = airports.find(input.dest);
  if(start == airports.end()){

    if(end != airports.end()){
      std::cout << "WARNING: Route not added. Start airport " << input.src << " not in graph." << std::endl;
    } else{
      std::cout << "WARNING: Route not added. Start airport " << input.src << " and destination airport " << input.dest << " are not in the graph." << std::endl;
    }

  } else if(end == airports.end()){
    std::cout << "WARNING: Route not added. Destination airport " << input.dest << " not in graph." << std::endl;

  } else{
    airports.at(input.src)->edges.push_back(input);
    edgeCount++;
  }
}

void Graph::addRoute(vector<string> input){
  //std::cout << "Inner values" << std::endl;
  //int i = 0;
  //for(string s : input){
  //  std::cout << i <<": " <<  s << std::endl;
  //  i++;
  //}

  Route addThis(input[2], input[4]);
  auto start = airports.find(addThis.src);
  auto end = airports.find(addThis.dest);
  if(start == airports.end()){
    if(end != airports.end()){
      std::cout << "WARNING: Route not added. Start airport " << addThis.src << " not in graph." << std::endl;
    } else{
      std::cout << "WARNING: Route not added. Start airport " << addThis.src << " and destination airport " << addThis.dest << " are not in the graph." << std::endl;
    }
  } else if(end == airports.end()){
    std::cout << "WARNING: Route not added. Destination airport " << addThis.dest << " not in graph." << std::endl;
  } else{
    Node* crntNode = airports.at(addThis.src);
    crntNode->edges.push_back(addThis);
    edgeCount++;
  }
}


// Returns KM
double Graph::routeDist(Route route){ //gives the disance associated with a route

  Airport start = airports.at(route.src)->data; //extract our starting airport
  Airport finish = airports.at(route.dest)->data; //extract our ending airport

  double p = M_PI/180; //divide pi by 180
  double a = 0.5 - std::cos((finish.lat - start.lat) * p)/2 + //necessary calculations
             std::cos(start.lat * p) * std::cos(finish.lat * p) * //more calculations
             (1 - std::cos((finish.lon - start.lon) * p))/2; //even more calculations

  return 12742 * std::asin(std::sqrt(a)); //return our final distance result;

}

vector<string> Graph::shortestPath(string start, string end){ //shortest path algorithms that runs on Dijkstra's
  auto printMap = [](map<string, Dijkstry> &input){
    auto it = input.begin();
    std::cout << "key  | km-from-start | prev node " << std::endl;
    while(it != input.end()){
      std::cout << it->first << " | " << it->second.dist << "km | ";
      if(it->second.prev == NULL){
	std::cout << "NULL"<< std::endl;
      } else{
	std::cout << it->second.prev->data.name << std::endl;
      }
      it++;
    }
  };
  // This set will keep track of the node's we've traversed
  // switched to an unordered set for performance
  std::unordered_set<string> traversed;
  //Make a dictionary with each node that'll be responsible for keeping track of:
  // shortest distance from start airport, previous node
  map<string, Dijkstry> pathMap;
  // Initial entry for first node in traversal
  Dijkstry newEnt;
  newEnt.dist = 0;
  newEnt.prev = NULL;
  // insert entry
  //std::cout << "Inserting entry" << std::endl;
  pathMap[start] = newEnt;
  //std::cout << "Entry inserted" << std::endl;
  //std::function<void(Node* currentNode)> shortestHelper;
  // queue for BFS traversal
  queue<Node*> q;
  // starting the traversal with the startpoint of interest
  q.push(airports.at(start));

  //std::cout << "Starting while loop" << std::endl;
  while(not q.empty()){

    // setting inital conditions per iteration
    Node* shortestRoute = NULL;
    Route shortestRouteRoute = Route("N/A", "N/A");
    // setting the smallest distance between current node and a route to be the max
    // double value
    double sRDist = std::numeric_limits<double>::max();
    // get the current node;s
    Node* currentNode = q.front();
    q.pop();
    // currentNode's distance from start
    //std::cout << "Searching for: " << currentNode->data.name << std::endl;
    double curDist = pathMap.at(currentNode->data.name).dist;
    //std::cout << "curDist established" << std::endl;
    if(traversed.find(currentNode->data.name) == traversed.end()){
      for(Route r : currentNode->edges){
	//std::cout << "In route loop" << std::endl;
	//std::cout << "current node: " << currentNode->data.name << std::endl;
	// If we've traversed this endpoint, don't mess wit hit
	if(traversed.find(r.dest) == traversed.end()){
	  //std::cout << "Not traversed" << std::endl;
	  //printMap(pathMap);
	  double rD = routeDist(r);
	  double combinedDist = curDist + rD;
	  if(pathMap.find(r.dest) == pathMap.end()){
	    Dijkstry newEnt;
	    // calculate destination's relative distance to start
	    newEnt.dist = combinedDist;
	    newEnt.prev = currentNode;
	    // add entry to map
	    pathMap[r.dest] = newEnt;
	  } else{
	    // if there's already an entry, check if the current total distance is
	    // smaller than the entry's distance
	    double maybeShorter = combinedDist;
	    if(maybeShorter < pathMap.at(r.dest).dist){
	      // if that's the case, update the entry
	      pathMap[r.dest].dist = maybeShorter;
	      pathMap[r.dest].prev = currentNode;
	    }
	  }
	  // if the current distance is the shortest distance between a route and a current node, set it as the
	  // current best
	  if(rD < sRDist){
	    shortestRoute = airports.at(r.dest);
	    shortestRouteRoute = r;
	    sRDist = rD;
	  }
	}
      }
      // Adds the current node to the list of traversed nodes
      traversed.insert(currentNode->data.name);

      if(shortestRoute != NULL){
	// adds the shortest route forward to the queue, such that we'll traverse it next
	q.push(shortestRoute);

      }

      for(Route r : currentNode->edges){
	if(traversed.find(r.dest) == traversed.end()){
	  //std::cout << "Adding " << r.dest << "to queue" << std::endl;
	  q.push(airports.at(r.dest));
	}
      }
    }

  }

  // begin backtracking to find the shortest path
  vector<string> backwardPath;
  string currentAirport = end;
  while(currentAirport != start){
    backwardPath.push_back(currentAirport);
    //std::cout << "Getting " << currentAirport << "\'s previous airport" << std::endl;
    currentAirport = pathMap.at(currentAirport).prev->data.name;
  }
  // NOTE: This returns a "path" starting from the destination, that doesn't include the starting airport
  return backwardPath;
}

Airport Graph::getAirport(string name){
  // Searches for airport
  auto it = airports.find(name);
  if(it == airports.end()){
    // If the airport isn't found, return a "sentinel" airport
    // and print an error message
    std::cout << name << " not found" << std::endl;
    return Airport("N/A", 0, 0);
  } else{
    // If it is found, return the airport.
    return it->second->data;
  }

}

std::pair<double, double> Graph::betweennessCentrality(std::string startingAirport, std::string endingAirport) {
    std::map<std::string, double> betweenness;

    std::map<Route*, double> edgeBetweenness;

    typedef std::pair<double, std::string> KeyValuePair;

    std::priority_queue<KeyValuePair, std::vector<KeyValuePair>, std::greater<KeyValuePair>> Q;
    std::stack<std::string> S;

    std::map<std::string, double> dist;
    std::map<std::string, double> sp;
    std::map<std::string, double> delta;
    std::map<std::string, bool> isInStack;
    std::map<std::string, std::list<Route*>> Pred;

    for (auto it = airports.begin(); it != airports.end(); it++) {
        for (auto i = airports.begin(); i != airports.end(); i++) {
            Pred[i->first].clear();
            dist[i->first] = std::numeric_limits<double>::max();
            sp[i->first] = 0;
            isInStack[i->first] = false;
        }
        dist[it->first] = 0;
        sp[it->first] = 1;
        Q.push(std::make_pair(dist[it->first], it->first));

        while(!Q.empty()) {
          std::string v = Q.top().second;
          Q.pop();

          if(!isInStack[v]) {
            isInStack[v] = true;
            S.push(v);

            std::vector<Route> adjRoutes = this->getRoutesToAdjacentAirports(v);
            for(auto& route : adjRoutes) {
              double distance = routeDist(route);

              // @TODO Maybe this might be swapped with the source? Check back after adjacent routes are implemented
              std::string w = route.dest;

              if(dist[w] > dist[v] + distance) {
                dist[w] = dist[v] + distance;
                Q.push(std::make_pair(dist[w], w));
                sp[w] = 0;
                Pred[w].clear();
              }

              // Way to check floating point numbers equality ignoring rounding errors
              if(std::abs(dist[w] - (dist[v] + distance)) < 0.000000001) {
                sp[w] = sp[w] + sp[v];
                Pred[w].push_back(&route);
              }
            }
          }
        }
    

    double c = 0;

    while(S.size() != 0) {
      std::string airport_id = S.top();
      S.pop();

      for(auto route : Pred[airport_id]) {
        std::string src = route->src;

        c = (sp[src] / sp[airport_id] * (1 + delta[airport_id]));

        edgeBetweenness[route] += c;
        delta[src] += c;
      }

      if(airport_id.compare(it->first) != 0) {
        betweenness[airport_id] += delta[airport_id];
      }
    }

  }
  // return std::make_pair(betweenness, edgeBetweenness);
  // Calculates the betweenness statistic, now we need to use it
  return std::make_pair(0,0);
}

std::vector<Route> Graph::getRoutesToAdjacentAirports(std::string airport_id) {
  return airports[airport_id]->edges;
}
