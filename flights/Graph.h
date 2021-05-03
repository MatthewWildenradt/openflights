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
  // Give better name
  struct Dijkstry{
    double dist;
    Node* prev;
  };


 private:

  /* Hashmap storing Node pointers, accessible using airport IATA IDs */
  std::map<std::string, Node*> airports;


  /**
   *@brief returns the distance (km) between two airports in a route
   *       Sourced from https://stackoverflow.com/a/21623206 (annotate?)
   *
   *@param route the route in question
   */
  double routeDist(Route route);

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
   *@param input the Route(s) to add
   */
  void addRoute(Route input);
  void addRoute(std::vector<std::string> input);

  /**
   *@brief returns the shortest path between two airports
   *
   *@param start the start airport
   *@param end the destination airport
   */
  std::vector<std::string> shortestPath(std::string start, std::string end);

};
