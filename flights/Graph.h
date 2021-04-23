#pragma once
#include "Airport.h"
#include <vector>
#include <map>
#include "Route.h"

class Graph{

 private:

  // A hashmap to retrieve edges for a respective airport
  // Where the key represents the IATA code
  // TODO! Use a set instead of a vector?
  std::map<std::string, std::vector<Route>> edges;
  std::vector<Airport> airports;

public:

  /**
   *@brief Creates an empty graph
   */
  Graph();

  /**
   * @brief Construct a graph given airports and routes in vectors
   *
   * @param inputAirports vector of Airports
   * @param routes vector of Routes
   */
  Graph(std::vector<Airport> inputAirports, std::vector<Route> routes);

  /**
   *@brief Construct a graph given airports and routes as 2d vectors of strings
   *
   *@param inputAirports 2d vector containing strings representing Airports
   *@param routes 2d vector containing strings representing Routes
   */
  Graph(std::vector<std::vector<std::string>> inputAirports, std::vector<std::vector<std::string>> routes);

  /**
   *@brief adds an Airport to the graph
   *
   *@param input the Airport to add
   */
  void addAirport(Airport input);
  void addAirport(std::vector<std::string> input);

  /**
   *@brief adds a Route to the graph
   *
   *@param input the Route to add
   */
  void addRoute(Route input);
  void addRoute(std::vector<std::string> input);
};
