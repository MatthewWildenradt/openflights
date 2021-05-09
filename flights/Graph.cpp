#include "Graph.h"
#include <cmath>
#include <limits>
#include <set>
#include <functional>
#include <iostream>
#include <queue>

using std::string;
using std::vector;
using std::map;
using std::queue;

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
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){
  airports.at(input.src)->edges.push_back(input);
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
  }
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
  // This set will keep track of the node's we've traversed
  std::set<string> traversed;
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
    // setting the smallest distance between current node and a route to be the max
    // double value
    double sRDist = std::numeric_limits<double>::max();
    // get the current node;s
    Node* currentNode = q.front();
    q.pop();
    // currentNode's distance from start
    double curDist = pathMap.at(currentNode->data.name).dist;
    for(Route r : currentNode->edges){
      //std::cout << "current node: " << currentNode->data.name << std::endl;
      // If we've traversed this endpoint, don't mess wit hit
      if(traversed.find(r.dest) == traversed.end()){
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
	  sRDist = rD;
	}
      }
    }

    traversed.insert(currentNode->data.name);
    if(shortestRoute != NULL){
      //std::cout << shortestRoute->data.name << std::endl;
      q.push(shortestRoute);
    }
  }

  // begin backtracking to find the shortest path
  vector<string> backwardPath;
  string currentAirport = end;
  while(currentAirport != start){
    backwardPath.push_back(currentAirport);
    currentAirport = pathMap.at(currentAirport).prev->data.name;
  }

  return backwardPath;
}

Airport Graph::getAirport(string name){
  try{
    return airports.at(name)->data;
  } catch(int e){
    std::cout << "Airport not found" << std::endl;
    return Airport("N/A", 0, 0);
  }
}


// This version uses DFS, current version uses BFS(?)
/*
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
*/
