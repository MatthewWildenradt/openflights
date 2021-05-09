
#include "../cs225/catch/catch.hpp"
#include "../Graph.h"
#include "../csv_reader.h"
#include <vector>

using namespace std;



vector<Airport> makeSimpleAirports() {
    vector<Airport> airports;
    Airport airport1("ONE", 0, 0);
    Airport airport2("TWO", 129, 39);
    Airport airport3("THR", 13, 30);
    airports.push_back(airport1);
    airports.push_back(airport2);
    airports.push_back(airport3);
    return airports;
}

vector<Route> makeSimpleRoutes() {
    vector<Route> routes;
    Route route1("ONE", "TWO");
    Route route2("TWO", "THR");
    routes.push_back(route1);
    routes.push_back(route2);
    return routes;
}


TEST_CASE("Constructors") {
  vector<Airport> inputA = makeSimpleAirports();
  vector<Route> inputR = makeSimpleRoutes();
  Graph simpleGraph(inputA, inputR);
  REQUIRE((simpleGraph.getAirport("ONE") == Airport("ONE", 0, 0)));
  REQUIRE((simpleGraph.getAirport("THR") == Airport("THR", 13, 30)));

}

TEST_CASE("Add Route") {
  Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
  simpleGraph.addRoute(Route("THR","ONE"));
  REQUIRE((simpleGraph.getAirport("ONE") == Airport("ONE", 0, 0)));
  REQUIRE((simpleGraph.getAirport("THR") == Airport("THR", 13, 30)));

}

TEST_CASE("Add Airport") {
  Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
  simpleGraph.addAirport(Airport("FOU", 44, 44));
  REQUIRE((simpleGraph.getAirport("ONE") == Airport("ONE", 0, 0)));
  REQUIRE((simpleGraph.getAirport("THR") == Airport("THR", 13, 30)));
  REQUIRE((simpleGraph.getAirport("FOU") == Airport("FOU", 44, 44)));

}

TEST_CASE("Get Airport") {
  Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
  REQUIRE((simpleGraph.getAirport("ONE") == Airport("ONE", 0, 0)));


}
