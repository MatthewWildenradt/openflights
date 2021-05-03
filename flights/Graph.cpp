#include "Graph.h"
#include <cmath>
#include <limits>
#include <set>
#include <functional>
#include <iostream>

using std::string;
using std::vector;
using std::map;

Graph::Graph(){
  // does nothing
}

Graph::Graph(vector<Airport> inputAirports, vector<Route> routes){

  for(Airport crnt : inputAirports){
    addAirport(crnt);
  }

  for(Route crnt : routes){
    addRoute(crnt);
  }
}

Graph::Graph(vector<vector<string>> inputAirports,
	     vector<vector<string>> routes){

  for(vector<string> line : inputAirports){
    addAirport(line);
  }

  for(vector<string> line : routes){
    addRoute(line);
  }

}

Graph::~Graph(){
  for(auto it = airports.begin(); it != airports.end(); it++){
    delete it->second;
  }
}

void Graph::addAirport(Airport input){
  Node* airportNode = new Node();
  airportNode->data = input;
  airports.insert(std::pair<string, Node*>(input.name, airportNode));
}

void Graph::addAirport(vector<string> input){
  Airport addThis(input[4], std::stod(input[6]), std::stod(input[7]));
  Node* airportNode = new Node();
  airportNode->data = addThis;
  airports.insert(std::pair<string, Node*>(addThis.name, airportNode));
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){
  airports.at(input.src)->edges.push_back(input);
}

void Graph::addRoute(vector<string> input){
  Route addThis(input[2], input[4]);
  Node* crntNode = airports.at(addThis.src);
  crntNode->edges.push_back(addThis);
}


// Returns KM
double Graph::routeDist(Route route){

  Airport start = airports.at(route.src)->data;
  Airport finish = airports.at(route.dest)->data;

  double p = M_PI/180;
  double a = 0.5 - std::cos((finish.lat - start.lat) * p)/2 +
             std::cos(start.lat * p) * std::cos(finish.lat * p) *
             (1 - std::cos((finish.lon - start.lon) * p))/2;

  return 12742 * std::asin(std::sqrt(a));

}

vector<string> Graph::shortestPath(string start, string end){


  std::set<string> traversed;
  map<string, Dijkstry> pathMap;


  std::function<void(Node* currentNode)> shortestHelper;

  shortestHelper = [this, &shortestHelper, &pathMap, &traversed](Node* currentNode){
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




Node* Graph::getAirport(std::string name) {
    return Node();
}
