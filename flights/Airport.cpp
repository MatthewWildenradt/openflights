#include "Airport.h"  //need the airport header

Airport::Airport() {  // just the default
  name = "N/A";       // name is empty
  lat = 0;            // placed at 0 latitude
  lon = 0;            // placed at 0 longitude
}

Airport::Airport(std::string IATA, double laat, double loon) {  // takes the name and position
  name = IATA;                                                  // name
  lat = laat;                                                   // latitude
  lon = loon;                                                   // longitude
}
