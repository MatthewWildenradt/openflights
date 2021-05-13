#include <iostream>
#include <sstream>
#include <vector>

#include "../Airport.h"
#include "../Graph.h"
#include "../Route.h"
#include "../cs225/catch/catch.hpp"
#include "../csv_reader.h"

TEST_CASE("Example", "[weight=0][part=1][part=1a]") {
  // Just to check that the tests ran properly
  REQUIRE( 1==1 );
}

std::string vectToString(std::vector<std::string> input) {
  std::string output = "";
  output += "< ";
  for (std::string yarn : input) {
    output += yarn + " ";
  }
  output += ">";
  return output;
}

// calculating distances for examples using: https://www.nhc.noaa.gov/gccalc.shtml
TEST_CASE("dijk_simple", "[Dijk][weight=4][part=2][value=0]") {
  Airport one("A", 0, 0);
  Airport two("B", 1, 1);
  Airport three("C", 2, 2);
  Airport four("D", .75, .75);

  std::stringstream testing;
  std::vector<Route> routes = {Route("A", "D"), Route("D", "A"), Route("A", "B"), Route("B", "A"), Route("A", "C"), Route("C", "A"),
                               Route("B", "C"), Route("C", "B"), Route("B", "D"), Route("D", "B"), Route("C", "D"), Route("D", "C")};
  std::vector<Airport> airports = {one, two, three, four};
  Graph graphOne(airports, routes);

  std::vector<std::string> outputOne = graphOne.shortestPath("A", "D");

  REQUIRE(vectToString(outputOne) == "< A D >");

  routes.erase(routes.begin(), routes.begin() + 2);

  Graph graphTwo(airports, routes);
  std::vector<std::string> outputTwo = graphTwo.shortestPath("A", "D");

  REQUIRE(vectToString(outputTwo) == "< A B D >");
}

TEST_CASE("dijk_slow", "[Dijk]") {
  CSVReader AirportF("../data/airports.dat");
  CSVReader RouteF("../data/routes.dat");
  std::vector<std::vector<std::string>> routes;
  std::vector<std::vector<std::string>> airports;
  std::vector<std::string> dummy;

  while (not AirportF.eof()) {
    airports.push_back(AirportF.nextLine());
  }

  airports.pop_back();

  while (not RouteF.eof()) {
    routes.push_back(RouteF.nextLine());
  }

  routes.pop_back();

  Graph bGraph(airports, routes);

  std::vector<std::string> outputOne = bGraph.shortestPath("SEA", "JFK");

  REQUIRE(vectToString(outputOne) == "< SEA JFK >");
}

TEST_CASE("dijk_unclear", "[Dijk]") {
  std::vector<Airport> airports = {Airport("A", 0, 0),   Airport("B", 3, 3),   Airport("C", 2, 2), Airport("D", 1, 1),
                                   Airport("E", 20, 20), Airport("F", 15, 15), Airport("G", 5, 5)};

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("A", "C"), Route("C", "A"), Route("A", "D"), Route("D", "A"), Route("C", "G"),
                               Route("G", "C"), Route("D", "G"), Route("G", "D"), Route("D", "F"), Route("F", "D"), Route("D", "E"), Route("E", "D")};

  Graph myGraph(airports, routes);
  std::vector<std::string> outputOne = myGraph.shortestPath("A", "G");
  // Note: A -> D -> G is of an equal length to A -> C -> G
  REQUIRE(vectToString(outputOne) == "< A D G >");

  myGraph.addAirport(Airport("H", 17, 17));
  myGraph.addRoute(Route("F", "H"));
  myGraph.addRoute(Route("H", "F"));

  std::vector<std::string> outputTwo = myGraph.shortestPath("A", "H");
  REQUIRE(vectToString(outputTwo) == "< A D F H >");
}

TEST_CASE("dijk_invalid", "[Dijk]") {
  Airport one("A", 0, 0);
  Airport two("B", 1, 1);
  Airport three("C", 2, 2);
  Airport four("D", .75, .75);

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("D", "C"), Route("C", "D")};
  std::vector<Airport> airports = {one, two, three, four};
  Graph graphOne(airports, routes);

  // Note: There are no paths from A to D
  std::vector<std::string> outputOne = graphOne.shortestPath("A", "D");

  REQUIRE(vectToString(outputOne) == "< >");
}

TEST_CASE("dijk_zero_weight") {
  std::vector<Airport> airports = {Airport("A", 0, 0), Airport("B", 1, 0), Airport("C", 0, 1), Airport("D", 1, 1),
                                   Airport("E", 1, 0), Airport("F", 1, 2), Airport("G", 1, 1)};

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("A", "D"), Route("D", "A"), Route("A", "C"), Route("C", "A"), Route("B", "F"),
                               Route("F", "B"), Route("C", "E"), Route("E", "C"), Route("F", "G"), Route("G", "F"), Route("E", "G"), Route("G", "E")};

  Graph myGraph(airports, routes);

  // test node with zero weight edge
  std::vector<std::string> outputOne = myGraph.shortestPath("A", "G");
  REQUIRE(vectToString(outputOne) == "< A C E G >");

  // test other paths
  std::vector<std::string> outputTwo = myGraph.shortestPath("A", "F");
  REQUIRE(vectToString(outputTwo) == "< A B F >");

  std::vector<std::string> outputThree = myGraph.shortestPath("A", "E");
  REQUIRE(vectToString(outputThree) == "< A C E >");

  std::vector<std::string> outputFour = myGraph.shortestPath("A", "C");
  REQUIRE(vectToString(outputFour) == "< A C >");

  std::vector<std::string> outputFive = myGraph.shortestPath("A", "D");
  REQUIRE(vectToString(outputFive) == "< A D >");

  std::vector<std::string> outputSix = myGraph.shortestPath("A", "B");
  REQUIRE(vectToString(outputSix) == "< A B >");

  std::vector<std::string> outputX = myGraph.shortestPath("D", "G");
  REQUIRE(vectToString(outputX) == "< D A C E G >");
}

TEST_CASE("centrality_simple", "[central]") {
  Airport one("A", 0, 0);
  Airport two("B", 1, 1);
  Airport three("C", 2, 2);

  std::vector<Airport> airports = {one, two, three};

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("B", "C"), Route("C", "B")};

  Graph myGraph(airports, routes);

  std::string output = myGraph.getCentralAirport("A", "C");

  REQUIRE(output == "B");
}

TEST_CASE("centrality_diamond", "[central]") {
  std::vector<Airport> airports = {Airport("A", 5, 5), Airport("B", 4, 5), Airport("C", 5, 4), Airport("D", 5, 6), Airport("E", 6, 5)};

  std::vector<Route> routes = {Route("A", "B"), Route("B", "A"), Route("C", "A"), Route("A", "C"),
                               Route("A", "E"), Route("E", "A"), Route("D", "A"), Route("A", "D")};

  Graph myGraph(airports, routes);

  REQUIRE(myGraph.getCentralAirport("B", "D") == "A");
  REQUIRE(myGraph.getCentralAirport("B", "E") == "A");
  REQUIRE(myGraph.getCentralAirport("C", "E") == "A");

  std::vector<Route> moreRoutes = {Route("B", "D"), Route("D", "B"), Route("D", "E"), Route("E", "D"),
                                   Route("E", "C"), Route("C", "E"), Route("B", "C"), Route("C", "B")};

  routes.insert(routes.end(), moreRoutes.begin(), moreRoutes.end());

  Graph myGraph2(airports, routes);

  REQUIRE(myGraph2.getCentralAirport("D", "B") == "A");
  REQUIRE(myGraph2.getCentralAirport("D", "C") == "A");
  REQUIRE(myGraph2.getCentralAirport("D", "E") == "A");

  std::vector<Airport> moreAirports = {Airport("F", 5, 7), Airport("G", 3, 5), Airport("H", 5, 3), Airport("I", 7, 5)};

  std::vector<Route> neoRoutes = {Route("G", "B"), Route("B", "G"), Route("F", "D"), Route("D", "F"), Route("I", "E"), Route("E", "I"),
                                  Route("C", "H"), Route("H", "C"), Route("G", "F"), Route("F", "G"), Route("G", "H"), Route("H", "G"),
                                  Route("H", "I"), Route("I", "H"), Route("I", "F"), Route("F", "I")};

  routes.insert(routes.end(), neoRoutes.begin(), neoRoutes.end());
  airports.insert(airports.end(), moreAirports.begin(), moreAirports.end());

  Graph myGraph3(airports, routes);

  REQUIRE(myGraph3.getCentralAirport("F", "H") == "E");
}
