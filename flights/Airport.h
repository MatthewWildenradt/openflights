#pragma once
#include <string> //need a string to deal with the name of the airport

class Airport{ //airport objects
 public: //public members

  /**
   * Airport default constructor
   */
  Airport(); //typical default

  /**
   *@brief Constructs an Airport
   *
   *@param IATA the Airport's IATA ID
   *@param laat the Airport's latitude
   *@param loon the Airport's longitude
   */
  Airport(std::string IATA, double laat, double loon); //need the ID, latitude, and longitude


  std::string name; /* The Airport's IATA ID */
  double lat;       /* The Airport's latitude */
  double lon;       /* The Airport's longitude */



};
