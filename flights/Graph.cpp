#include "Graph.h" //need the graph  header
#include <cmath> //need math for our algorithms
#include <limits> //need limits as well
#include <set> //and sets
#include <functional> //and functional
#include <iostream> //need iostream for basic usability

using std::string; //need strings for location names
using std::vector; //need vectors for collections of routes and airports
using std::map; //need a map to access things based on their names

Graph::Graph(){ //just your regular default consstructor
  // does nothing
}

Graph::Graph(vector<Airport> inputAirports, vector<Route> routes){ //make a graph using a vector of airports and a vector of routes

  for(Airport crnt : inputAirports){ //put all of the airports into the graph
    addAirport(crnt); //as stated
  }

  for(Route crnt : routes){ //put all of the routes into the graph
    addRoute(crnt); //as stated
  }
}

Graph::Graph(vector<vector<string>> inputAirports, //same thing as above
	     vector<vector<string>> routes){ //only using string vectors of names and not objects

  for(vector<string> line : inputAirports){ //put all airports in again
    addAirport(line); //as stated
  }

  for(vector<string> line : routes){ //put all routes in again
    addRoute(line); //as stated
  }

}

Graph::~Graph(){ //destructor
  for(auto it = airports.begin(); it != airports.end(); it++){ //for every node
    delete it->second; //delete that node
  }
}

void Graph::addAirport(Airport input){ //airport adder
  Node* airportNode = new Node(); //need to make a new node for each airport
  airportNode->data = input; //need to set that airport to the input
  airports.insert(std::pair<string, Node*>(input.name, airportNode)); //insert it with our given graph format
}

void Graph::addAirport(vector<string> input){ //same thing as above but a vector of strings
  Airport addThis(input[4], std::stod(input[6]), std::stod(input[7])); //constructs a corresponding airport called add this
  Node* airportNode = new Node(); //create a new node for our purposes
  airportNode->data = addThis; //just put the object we create's info into that new node
  airports.insert(std::pair<string, Node*>(addThis.name, airportNode)); //then insert it
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){ //route adder
  airports.at(input.src)->edges.push_back(input); //only need to copy these edges into the existing edge vector
}

void Graph::addRoute(vector<string> input){ //route adder but with strings
  Route addThis(input[2], input[4]); //make a route using the string vector format input (this makes sense given how the source file is formatted)
  Node* crntNode = airports.at(addThis.src); //gets the pointer of the node we want
  crntNode->edges.push_back(addThis); //use that pointer to add our edge to the graph
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


  std::set<string> traversed; //keep track of what we've traversed with a set
  map<string, Dijkstry> pathMap; //use a map to keep track fo the path we've made


  std::function<void(Node* currentNode)> shortestHelper; //make a helper function inside the shortest path algorithm

  shortestHelper = [this, &shortestHelper, &pathMap, &traversed](Node* currentNode){ //outline of the paramters taken
    Node* shortestRoute = NULL;

    double sRDist = std::numeric_limits<double>::max();
    // CurrentNode's distance from start
    double curDist = pathMap.at(currentNode->data.name).dist;

    for(Route r : currentNode->edges){
      // If we've traversed this endpoint, don't mess with it
      if(traversed.find(r.dest) == traversed.end()){
	// calculate the endpoint's distance from current node
	double rD = routeDist(r);
	// Checks if the destination already has an entry
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
	    // If that's the case, update the entry
	    pathMap[r.dest].dist = maybeShorter;
	    pathMap[r.dest].prev = currentNode;
	  }
	}
	if(rD < sRDist){
	  shortestRoute = airports.at(r.dest);
	  sRDist = rD;
	}
      }
    }

    traversed.insert(currentNode->data.name);
    if(shortestRoute != NULL){
      shortestHelper(shortestRoute);
    }
  };

  //Make a dictionary with each node that'll be responsible for keeping track of:
  // shortest distance from start airport, previous node

  Dijkstry initial;
  initial.dist = 0;
  initial.prev = NULL;

  pathMap[start] = initial;

  shortestHelper(airports[start]);


  // Backtrack to find find the shortest path

  vector<string> backwardPath;
  string currentAirport = end;
  while(currentAirport != start){
    backwardPath.push_back(currentAirport);
    currentAirport = pathMap.at(currentAirport).prev->data.name;
  }

  return backwardPath;

}
