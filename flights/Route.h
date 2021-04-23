#pragma once
#include <string>

class Route{
 public:

  /**
   *@brief Constructs a Route given a source and destination
   *
   *@param source the starting Airport's IATA ID
   *@param destination the ending Airport's IATA ID
   */
  Route(std::string source, std::string destination);

  std::string src; /* the route's starting airport */
  std::string dest;/* the route's ending airport */



};
