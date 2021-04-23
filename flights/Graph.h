#pragma once
#include "Airport.h"
#include <vector>
#include <map>
#include "Route.h"

class Graph{

 public:

  /**
   * Represents a node in the graph
   * Contains a vector of directed edges
   * As well as the airport that these edges belong to
   */
  struct Node{
    Airport data;
    std::vector<Route> edges;
  };


 private:

  /* Hashmap storing Node pointers, accessible using airport IATA IDs */
  std::map<std::string, Node*> airports;

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
   * Deallocates the graph's memory
   */
  ~Graph();
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
