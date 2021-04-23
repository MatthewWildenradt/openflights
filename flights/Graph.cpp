#include "Graph.h"



Graph::Graph(){
  // does nothing
}

Graph::Graph(std::vector<Airport> inputAirports, std::vector<Route> routes){

  airports = inputAirports;

  for(Route crnt : routes){
    addRoute(crnt);
  }
}

Graph::Graph(std::vector<std::vector<std::string>> inputAirports, std::vector<std::vector<std::string>> routes){
  std::vector<Route> dummy;
  for(std::vector<std::string> line : inputAirports){
    addAirport(line);
  }

  for(std::vector<std::string> line : routes){
    Route addThis(line[2], line[4]);
  }
}


void Graph::addAirport(Airport input){
  airports.push_back(input);
  std::vector<Route> dummy;
  edges.insert(std::pair<std::string, std::vector<Route>>(input.name, dummy));
}

void Graph::addAirport(std::vector<std::string> input){
  Airport addThis(input[4], std::stod(input[6]), std::stod(input[7]));
  airports.push_back(addThis);
  std::vector<Route> dummy;
  edges.insert(std::pair<std::string, std::vector<Route>>(input[4], dummy));
}


// TODO! ignore if duplicate
void Graph::addRoute(Route input){

  if(edges.find(input.src) == edges.end()){
    std::vector<Route> dummy;
    dummy.push_back(input);
    edges.insert(std::pair<std::string, std::vector<Route>>(input.src, dummy));
  } else{
    edges[input.src].push_back(input);
  }
}

void Graph::addRoute(std::vector<std::string> input){
  Route addThis(input[2], input[4]);

  // check if the src airport is in the map
  if(edges.find(input[2]) == edges.end()){
    // not in the map
    std::vector<Route> dummy;
    dummy.push_back(addThis);
    edges.insert(std::pair<std::string, std::vector<Route>>(input[2], dummy));
  } else{
    edges[input[2]].push_back(addThis);
  }
}
