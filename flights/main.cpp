#include <iostream>

#include "Graph.h"
#include "csv_reader.h"

int main() {
    std::string airport_file_name = "../data/airports.dat";
    std::string routes_file_name = "../data/routes.dat";

    Graph* graph = new Graph();

    std::cout << "Loading Airports from: " << airport_file_name << std::endl;
    CSVReader airport_reader(airport_file_name);
    while (!airport_reader.eof()) {
        graph->addAirport(airport_reader.nextLine());
    }
    std::cout << "Finished loading airports: " << graph->getAirportCount() << std::endl;

    std::cout << "Loading Routes from: " << routes_file_name << std::endl;
    CSVReader route_reader(routes_file_name);
    while (!route_reader.eof()) {
        graph->addRoute(route_reader.nextLine());
    }
    std::cout << "Finished loading Routes: " << graph->getRouteCount() << std::endl;

    std::string userInput = "3";

    int command = 0;

    while (userInput.length() != 0) {
        try {
            command = std::stoi(userInput);
        } catch (std::invalid_argument) {
            userInput = "3";
            continue;
        }
        userInput = "3";

        if (command == 1 || command == 2) {

            std::string firstAirport, secondAirport;
            std::cout << "Enter the source airport:" << std::endl;
            getline(std::cin, firstAirport);
            std::cout << "Enter the desitnation airport:" << std::endl;
            getline(std::cin, secondAirport);

            if (command == 1) {
                auto shortestPath = graph->shortestPath(firstAirport, secondAirport);
                for(auto i = shortestPath.begin(); i != shortestPath.end(); ++i) {
                    std::cout << *i << " -> ";
                }
                std::cout << std::endl;
            } else {
                std::cout << graph->getCentralAirport(firstAirport, secondAirport);
            }
        } else {
            if (command == 4) {
                std::cout << "Quitting program..." << std::endl;
                return 0;
            } else if (command != 3) {
                std::cout << "Invalid command. Please try again!" << std::endl;
            }
            std::cout << "Enter the corresponding number to whichever action you would like to execute:\n"
                      << "1) Shortest Path\n"
                      << "2) Betweeness Centrality\n"
                      << "3) List Commands\n"
                      << "4) Quit" << std::endl;
            std::cin >> userInput;
            continue;
        }
    }
    return 0;
}
