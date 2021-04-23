#include "Graph.h"



Graph::Graph(){
  // does nothing
}

Graph::Graph(std::vector<Airport> inputAirports, std::vector<Route> routes){

  for(Airport crnt : inputAirports){
    addAirport(crnt);
  }

  for(Route crnt : routes){
    addRoute(crnt);
  }
}

Graph::Graph(std::vector<std::vector<std::string>> inputAirports, std::vector<std::vector<std::string>> routes){
  for(std::vector<std::string> line : inputAirports){
    addAirport(line);
  }

  for(std::vector<std::string> line : routes){
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
  airports.insert(std::pair<std::string, Node*>(input.name, airportNode));
}

void Graph::addAirport(std::vector<std::string> input){
  Airport addThis(input[4], std::stod(input[6]), std::stod(input[7]));
  Node* airportNode = new Node();
  airportNode->data = addThis;
  airports.insert(std::pair<std::string, Node*>(addThis.name, airportNode));
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){
  airports.at(input.src)->edges.push_back(input);
}

void Graph::addRoute(std::vector<std::string> input){
  Route addThis(input[2], input[4]);
  Node* crntNode = airports.at(addThis.src);
  crntNode->edges.push_back(addThis);
}
