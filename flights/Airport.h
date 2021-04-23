#pragma once
#include <string>

class Airport{
 public:

  /**
   * Airport default constructor
   */
  Airport();

  /**
   *@brief Constructs an Airport
   *
   *@param IATA the Airport's IATA ID
   *@param laat the Airport's latitude
   *@param loon the Airport's longitude
   */
  Airport(std::string IATA, double laat, double loon);


  std::string name; /* The Airport's IATA ID */
  double lat;       /* The Airport's latitude */
  double lon;       /* The Airport's longitude */



};
