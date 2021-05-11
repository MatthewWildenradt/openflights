#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include "../Route.h"
#include "../Airport.h"
#include "../csv_reader.h"
#include <sstream>
#include <vector>
#include <iostream>
/*
TEST_CASE("Example", "[weight=0][part=1][part=1a]") {
  REQUIRE( 1==1 );
  }*/

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
TEST_CASE("dijk_simple", "[Dijk][weight=4][part=2][value=0]"){


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

TEST_CASE("dijk_slow", "[Dijk]"){

  CSVReader AirportF("../data/airports.dat");
  CSVReader RouteF("../data/routes.dat");
  std::vector<std::vector<std::string>> routes;
  std::vector<std::vector<std::string>> airports;
  std::vector<std::string> dummy;

  while(not AirportF.eof()){
    airports.push_back(AirportF.nextLine());
  }

  //std::cout << "Airports loaded" << std::endl;
  airports.pop_back();

  while(not RouteF.eof()){
    routes.push_back(RouteF.nextLine());
  }

  //std::cout << "Routes loaded" << std::endl;
  routes.pop_back();

  Graph bGraph(airports, routes);

  //std::cout << "Graph created" << std::endl;
  std::vector<std::string> outputOne = bGraph.shortestPath("HND", "FUK");
  //std::cout << "shortest path found" << std::endl;
  REQUIRE( vectToString(outputOne) == "< FUK >");


}

TEST_CASE("dijk_unclear", "[Dijk]"){
  std::vector<Airport> airports = {Airport("A", 0, 0), Airport("B", 3, 3), Airport("C" , 2, 2),
				   Airport("D", 1, 1), Airport("E", 20,20),
				   Airport("F", 15, 15), Airport("G", 5, 5)};

  std::vector<Route> routes = {Route("A","B"), Route("B","A"), Route("A","C"), Route("C","A"),
			       Route("A","D"), Route("D","A"), Route("C","G"), Route("G","C"),
			       Route("D","G"), Route("G","D"), Route("D","F"), Route("F","D"),
			       Route("D","E"), Route("E","D")};


  Graph myGraph(airports,routes);
  std::vector<std::string> outputOne = myGraph.shortestPath("A","G");
  // Note: A -> D -> G is of an equal length to A -> C -> G
  REQUIRE(vectToString(outputOne) == "< G D >");

  //std::cout << "Added airport H" << std::endl;
  myGraph.addAirport(Airport("H", 17, 17));
  myGraph.addRoute(Route("F","H"));
  myGraph.addRoute(Route("H","F"));
  //std::cout << "Added Routes for H" << std::endl;

  std::vector<std::string> outputTwo = myGraph.shortestPath("A", "H");
  REQUIRE(vectToString(outputTwo) == "< H F D >");

}

TEST_CASE("dijk_zero_weight"){
  std::vector<Airport> airports = {Airport("A", 0, 0), Airport("B", 1, 0), Airport("C", 0, 1), Airport("D", 1, 1),
			  Airport("E", 1, 0), Airport("F", 1, 2), Airport("G", 1, 1)};

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("A", "D"), Route("D","A"), Route("A","C"),
			       Route("C","A"), Route("B","F"), Route("F","B"), Route("C","E"), Route("E","C"),
			       Route("F","G"), Route("G", "F"), Route("E","G"), Route("G", "E")};

  Graph myGraph(airports, routes);


  // test node with zero weight edge
  std::vector<std::string> outputOne = myGraph.shortestPath("A", "G");
  REQUIRE(vectToString(outputOne) == "< G E C >");

  // test other paths
  std::vector<std::string> outputTwo = myGraph.shortestPath("A", "F");
  REQUIRE(vectToString(outputTwo) == "< F B >");

  std::vector<std::string> outputThree = myGraph.shortestPath("A", "E");
  REQUIRE(vectToString(outputThree) == "< E C >");

  std::vector<std::string> outputFour = myGraph.shortestPath("A", "C");
  REQUIRE(vectToString(outputFour) == "< C >");

  std::vector<std::string> outputFive = myGraph.shortestPath("A", "D");
  REQUIRE(vectToString(outputFive) == "< D >");

  std::vector<std::string> outputSix = myGraph.shortestPath("A", "B");
  REQUIRE(vectToString(outputSix) == "< B >");

  std::vector<std::string> outputX = myGraph.shortestPath("D", "G");
  REQUIRE(vectToString(outputX) == "< G E C A >");



}
