#pragma once
#include "Graph.h"

class PathFinder {
  public:
    PathFinder();
    PathFinder(Graph graph);
    /**
    * @brief Returns a vector of the shortest route based on weights determined by Djikstra's 
    * algorithm
    * 
    * @param start Name of the starting airport
    * @param end Name of the ending airport
    */
    std::vector<Node*> findShortestRoute(std::string startName, std::string endName);

    /**
     * @brief Returns a vector of the shortest route based on the number of airports visited
     *
     * @param start Name of the starting airport
     * @param end Name of the ending airport
     */
    std::vector<Node*> findLandmarkRoute(std::string startName, std::string endName);


  private: 
    Graph graph;

};