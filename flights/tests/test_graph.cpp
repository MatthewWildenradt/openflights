#include "../cs225/catch/catch.hpp"
#include "../Graph.cpp"
#include "../csv_reader.cpp"
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
    SECTION("Airport and Route constructor") {
        Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
        REQUIRE(simpleGraph.getAirport("ONE")->data = Airport("ONE", 0, 0));
        REQUIRE(simpleGraph.getAirport("THR")->data = Airport("THR", 13, 30));
    }
}

TEST_CASE("Add Route") {
    SECTION("Add cycling route") {
        Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
        simpleGraph.addRoute(Route("THR","ONE"));
        REQUIRE(simpleGraph.getAirport("ONE")->data = Airport("ONE", 0, 0));
        REQUIRE(simpleGraph.getAirport("THR")->data = Airport("THR", 13, 30));
    }
}

TEST_CASE("Add Airport") {
    SECTION("Add Airport") {
        Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
        simpleGraph.addAirport(Airport("FOU", 44, 44));
        REQUIRE(simpleGraph.getAirport("ONE")->data = Airport("ONE", 0, 0));
        REQUIRE(simpleGraph.getAirport("THR")->data = Airport("THR", 13, 30));
        REQUIRE(simpleGraph.getAirport("FOU")->data = Airport("FOU", 44, 44));
    }
}

TEST_CASE("Get Airport") {
    SECTION("Standard get airport") {
        Graph simpleGraph(makeSimpleAirports(), makeSimpleRoutes());
        REQUIRE(simpleGraph.getAirport("ONE")->data = Airport("ONE", 0, 0));
    }

    SECTION("Get Airport doesn't exist") {
    
    }
}