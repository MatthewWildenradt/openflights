#pragma once
#include "Airport.h"  //need airports
#include <vector> //need vectors to fill with airports and routess
#include <map>  //need map to make graph with those airports and routes
#include "Route.h" //need routes

class Graph{


 public: /*public member variables*/

  /**
   * Represents a node in the graph
   * Contains a vector of directed edges
   * As well as the airport that these edges belong to
   */
  struct Node{
    Airport data; //a single airports
    std::vector<Route> edges; //the airports able to be flown to from there
  };
  /**
   * Represents an edge from a node
   * Keeps track of the current distance
   * Keeps track of where it came from
  */
  struct Dijkstry{
    double dist; //the distance of this edge
    Node* prev; //the node it came from
  };


 private: /*private member variables/fucntions*/

  /* Hashmap storing Node pointers, accessible using airport IATA IDs */
  std::map<std::string, Node*> airports;  //this allows us to easily see which nodes connect which edges

  int edgeCount;
  int vertexCount;

  /**
   *@brief returns the distance (km) between two airports in a route
   *       !!!Sourced from https://stackoverflow.com/a/21623206!!!
   *
   *@param route the route in question
   */
  double routeDist(Route route);


 public: /*public member functions*/

  /**
   *@brief Creates an empty graph
   */
  Graph(); //default constructor

  /**
   * @brief Construct a graph given airports and routes in vectors
   *
   * @param inputAirports vector of Airports
   * @param routes vector of Routes
   */
  Graph(std::vector<Airport> inputAirports, std::vector<Route> routes); //make a graph using two airports and routes

  /**
   *@brief Construct a graph given airports and routes as 2d vectors of strings
   *
   *@param inputAirports 2d vector containing strings representing Airports
   *@param routes 2d vector containing strings representing Routes
   */
  Graph(std::vector<std::vector<std::string>> inputAirports, std::vector<std::vector<std::string>> routes); //make a graph using names of airports and routes

  /**
   * Deallocates the graph's memory
   */
  ~Graph(); //frees our memory
  /**
   *@brief adds an Airport to the graph
   *
   *@param input the Airport to add
   */
  void addAirport(Airport input); //add an airort using its object
  void addAirport(std::vector<std::string> input); //add and airport using its name

  /**
   *@brief adds a Route to the graph
   *
   *@param input the Route(s) to add
   */
  void addRoute(Route input); //addd a route using its object
  void addRoute(std::vector<std::string> input); //add a route using its name

  /**
   *@brief returns the shortest path between two airports
   *
   * ex: if the path is A -> B -> C -> D, the function will return a
   * vector: < "D", "C", "B" >
   *
   *@param start the start airport
   *@param end the destination airport
   */
  std::vector<std::string> shortestPath(std::string start, std::string end); //finds shortest path between two airports

  /**
   *@brief returns an airport
   *
   *@param airport The standard abbreviated name of the airport
   */
  Airport getAirport(std::string name); //gives you a pointer to the node of a named airport

  std::pair<double, double> betweennessCentrality(std::string startingAirport, std::string endingAirport);

  std::vector<Route> getRoutesToAdjacentAirports(std::string airport_id);

};
