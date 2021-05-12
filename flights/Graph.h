#pragma once
#include <map>     //need map to make graph with those airports and routes
#include <vector>  //need vectors to fill with airports and routess

#include "Airport.h"  //need airports
#include "Route.h"    //need routes

class Graph {
public: /*public member variables*/
  /**
   * Represents a node in the graph
   * Contains a vector of directed edges
   * As well as the airport that these edges belong to
   */
  struct Node {
    Airport data;              // a single airports
    std::vector<Route> edges;  // the airports able to be flown to from there
  };

  /**
   * Represents an edge from a node
   * Keeps track of the current distance
   * Keeps track of where it came from
   */
  struct Dijkstry {
    double dist;  // the distance of this edge
    Node* prev;   // the node it came from
  };

private:
  // Debug flag to turn on debug print statements
  bool debug = false;

  /* Hashmap storing Node pointers, accessible using airport IATA IDs */
  std::map<std::string, Node*> airports;  // this allows us to easily see which nodes connect which edges

  // Stores the number of edges in the graph.
  int edgeCount;

  // Stores the number of nodes in the graph.
  int vertexCount;

  /**
   *@brief returns the distance (km) between two airports in a route
   *       !!!Sourced from https://stackoverflow.com/a/21623206!!!
   *
   *@param route the route in question
   */
  double routeDist(Route route);

  /**
   * @brief Helper function to calculate distance using two Airport objects.
   *
   * @param start The starting airport
   * @param finish The destination airport
   * @return double distance between the two airports in km.
   */
  double routeDist(Airport start, Airport finish);

  /**
   * @brief Helper function to calculate distance using two Airport ids.
   *
   * @param start_id The starting airport id.
   * @param finish_id The ending airport id.
   * @return double distance between the two airports in km.
   */
  double routeDist(std::string start_id, std::string finish_id);

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

  /**
   * @brief Helper function to add airport to graph based on vector of strings
   *
   * @param input vector containing the airport data
   */
  void addAirport(std::vector<std::string> input);

  /**
   *@brief adds a Route to the graph
   *
   *@param input the Route(s) to add
   */
  void addRoute(Route input);

  /**
   * @brief Helper function to add a Route to the graph based on vector of strings
   *
   * @param input
   */
  void addRoute(std::vector<std::string> input);

  /**
   *@brief returns the shortest path between two airports
   *
   * ex: if the path is A -> B -> C -> D, the function will return a
   * vector: < "D", "C", "B" >
   *
   *@param start the start airport
   *@param end the destination airport
   */
  std::vector<std::string> shortestPath(std::string start, std::string end);

  /**
   *@brief returns an airport
   *
   *@param airport The standard abbreviated name of the airport
   */
  Airport getAirport(std::string name);

  /**
   * @brief Calculates the betweenness heuristic for two given airports.
   *
   * @param startingAirport The starting airport.
   * @param endingAirport The destination airport.
   * @return std::map<std::string, double> A map containing the betweenness heuristics for all airports.
   */
  std::map<std::string, double> calculateBetweennessCentrality(std::string startingAirport, std::string endingAirport);

  /**
   * @brief Get the Routes To Adjacent Airports. Simple getter based on the airports opject.
   *
   * @param airport_id to get the adjacent routes from.
   * @return std::vector<Route> containing routes to all adjacent airports.
   */
  std::vector<Route> getRoutesToAdjacentAirports(std::string airport_id);

  /**
   * @brief Get the Central Airport to the two given airports using the betweenness centrality algorithm.
   *
   * @param startingAirport The starting airport.
   * @param endingAirport The destination airport.
   * @return std::string IATA id corresponding to the most central airport.
   */
  std::string getCentralAirport(std::string startingAirport, std::string endingAirport);

  /**
   * @return int Count of the airports(nodes) in the current graph.
   */
  int getAirportCount() const;

  /**
   * @return int Count of the routes(edges) in the current graph.
   */
  int getRouteCount() const;
};
