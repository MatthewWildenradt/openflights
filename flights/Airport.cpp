#include "Airport.h"

Airport::Airport(){
  name = "";
  lat = 0;
  lon = 0;
}

Airport::Airport(std::string IATA, double laat, double loon){

  name = IATA;
  lat = laat;
  lon = loon;
}
