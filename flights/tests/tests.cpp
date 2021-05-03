#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include "../Route.h"
#include "../Airport.h"
#include <sstream>
#include <vector>
#include <iostream>
/*
TEST_CASE("Example", "[weight=0][part=1][part=1a]") {
  REQUIRE( 1==1 );
  }*/

std::vector<Route> connectedAirports(std::vector<std::string> routeNames){
  std::vector<Route> output;
  while(routeNames.size() > 1){
    int lastIdx = routeNames.size()-1;
    for(size_t i = 0; i < routeNames.size()-2; i++){
      output.push_back(Route(routeNames.at(i), routeNames.at(lastIdx)));
      output.push_back(Route(routeNames.at(lastIdx), routeNames.at(i)));
    }
    routeNames.pop_back();
  }
  return output;
}


/*
TEST_CASE("Graph_Constructor_1" "[weight=4][part=2][set=0]") {
  // Using first 3 airports
  Airport one("GKA", -6.081680834590001, 145.391998291);
  Airport two("MAG", -5.20707988739, 145.789001465);
  Airport three("HGU", -5.826789855957031, 144.29600524902344);

  std::vector<Airport> = {one, two, three};

  Graph myGraph();

}
*/
std::string vectToString(std::vector<std::string> input){
  std::string output = "";
  output += "< ";
  for(std::string yarn : input){
    output += yarn + " ";
  }
  output += ">";
  return output;
}


// calculating distances for examples using: https://www.nhc.noaa.gov/gccalc.shtml
TEST_CASE("simple Dijk", "[weight=4][part=2][value=0]"){


  Airport one("A", 0, 0);
  Airport two("B", 1, 1);
  Airport three("C", 2, 2);
  Airport four("D", .75, .75);

  std::stringstream testing;
  std::vector<Route> routes = { Route("A", "D"), Route("D" , "A"),
				Route("A" , "B"), Route("B", "A"),
				Route("A" , "C") , Route("C", "A"),
				Route("B", "C"), Route("C", "B"),
				Route("B", "D"), Route("D", "B"),
				Route("C", "D"), Route("D", "C")
  };
  std::vector<Airport> airports = {one, two, three, four};
  Graph graphOne(airports, routes);


  //std::cout << "graphOne created" << std::endl;
  std::vector<std::string>  outputOne = graphOne.shortestPath("A", "D");
  //std::cout << "shortest Path found #1" << std::endl;

  REQUIRE( vectToString(outputOne) == "< D >");

  //std::cout << "Passed first" << std::endl;

  routes.erase(routes.begin(), routes.begin()+2);

  Graph graphTwo(airports, routes);
  std::vector<std::string> outputTwo = graphTwo.shortestPath("A", "D");
  //std::cout << "shortest Path found #2" << std::endl;
  REQUIRE( vectToString(outputTwo) == "< D B >");
  //std::cout << "Passed second" << std::endl;

}
