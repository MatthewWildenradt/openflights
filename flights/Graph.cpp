#include "Graph.h"  //need the graph  header

#include <algorithm>  // for reverse function
#include <cmath>      //need math for our algorithms
#include <iostream>   //need iostream for basic usability
#include <limits>     //need limits as well
#include <list>
#include <queue>
#include <stack>
#include <unordered_set>  //and sets

using std::map;  // need a map to access things based on their names
using std::queue;
using std::string;  // need strings for location names
using std::vector;  // need vectors for collections of routes and airports

Graph::Graph() {  // just your regular default consstructor
  // does nothing
}

Graph::Graph(vector<Airport> inputAirports, vector<Route> routes) {  // make a graph using a vector of airports and a vector of routes

  for (Airport crnt : inputAirports) {  // put all of the airports into the graph
    addAirport(crnt);
  }

  for (Route crnt : routes) {  // put all of the routes into the graph
    addRoute(crnt);
  }
}

Graph::Graph(vector<vector<string>> inputAirports,  // same thing as above
             vector<vector<string>> routes) {       // only using string vectors of names and not objects

  for (vector<string> line : inputAirports) {  // put all airports in again
    addAirport(line);
  }

  for (vector<string> line : routes) {  // put all routes in again
    addRoute(line);
  }
}

Graph::~Graph() {                                                 // destructor
  for (auto it = airports.begin(); it != airports.end(); it++) {  // for every node
    delete it->second;                                            // delete that node
  }
}

void Graph::addAirport(Airport input) {
  Node* airportNode = new Node();
  airportNode->data = input;
  airports.insert(std::pair<string, Node*>(input.name, airportNode));
  vertexCount++;
}

void Graph::addAirport(vector<string> input) {
  int inputLen = input.size();
  if (inputLen == 0) {
    return;
  }

  std::string airportName = input.at(inputLen - 10);
  double lon = std::stod(input.at(inputLen - 8));
  double lat = std::stod(input.at(inputLen - 7));
  // Skip airports without essential information.
  if (airportName.length() < 3 || lon == 0 || lat == 0) {
    return;
  }
  Airport addThis(airportName, lon, lat);
  this->addAirport(addThis);
}

// TODO! ignore if duplicate
void Graph::addRoute(Route input) {
  auto srcExists = airports.find(input.src) != airports.end();
  auto destExists = airports.find(input.dest) != airports.end();

  if (srcExists && destExists) {
    airports.at(input.src)->edges.push_back(input);
    edgeCount++;
  } else if (debug) {
    if (srcExists) {
      if (destExists) {
        std::cout << "WARNING: Route not added. Start airport " << input.src << " not in graph." << std::endl;
      } else {
        std::cout << "WARNING: Route not added. Start airport " << input.src << " and destination airport " << input.dest << " are not in the graph."
                  << std::endl;
      }
    } else if (!destExists) {
      std::cout << "WARNING: Route not added. Destination airport " << input.dest << " not in graph." << std::endl;
    }
  }
}

void Graph::addRoute(vector<string> input) {
  if (input.size() == 0) {
    return;
  }

  Route addThis(input[2], input[4]);
  this->addRoute(addThis);
}

// Returns KM
double Graph::routeDist(Route route) {  // gives the disance associated with a route

  return routeDist(route.src, route.dest);
}

double Graph::routeDist(std::string start_id, std::string finish_id) {
  Airport start = airports.at(start_id)->data;    // extract our starting airport
  Airport finish = airports.at(finish_id)->data;  // extract our ending airport

  return routeDist(start, finish);
}

double Graph::routeDist(Airport start, Airport finish) {
  double p = M_PI / 180;                                            // divide pi by 180
  double a = 0.5 - std::cos((finish.lat - start.lat) * p) / 2 +     // necessary calculations
             std::cos(start.lat * p) * std::cos(finish.lat * p) *   // more calculations
                 (1 - std::cos((finish.lon - start.lon) * p)) / 2;  // even more calculations

  return 12742 * std::asin(std::sqrt(a));  // return our final distance result;
}

vector<string> Graph::shortestPath(string start, string end) {  // shortest path algorithms that runs on Dijkstra's
  auto printMap = [](map<string, Dijkstry>& input) {
    auto it = input.begin();
    std::cout << "key  | km-from-start | prev node " << std::endl;
    while (it != input.end()) {
      std::cout << it->first << " | " << it->second.dist << "km | ";
      if (it->second.prev == NULL) {
        std::cout << "NULL" << std::endl;
      } else {
        std::cout << it->second.prev->data.name << std::endl;
      }
      it++;
    }
  };
  // This set will keep track of the node's we've traversed
  // switched to an unordered set for performance
  std::unordered_set<string> traversed;
  // Make a dictionary with each node that'll be responsible for keeping track of:
  // shortest distance from start airport, previous node
  map<string, Dijkstry> pathMap;
  // Initial entry for first node in traversal
  Dijkstry newEnt;
  newEnt.dist = 0;
  newEnt.prev = NULL;
  // insert entry

  pathMap[start] = newEnt;

  // queue for BFS traversal
  queue<Node*> q;
  // starting the traversal with the startpoint of interest
  q.push(airports.at(start));

  while (not q.empty()) {
    // setting inital conditions per iteration
    Node* shortestRoute = NULL;
    Route shortestRouteRoute = Route("N/A", "N/A");
    // setting the smallest distance between current node and a route to be the max double value
    double sRDist = std::numeric_limits<double>::max();

    // get the current node;s
    Node* currentNode = q.front();
    q.pop();
    // currentNode's distance from start
    double curDist = pathMap.at(currentNode->data.name).dist;
    if (traversed.find(currentNode->data.name) == traversed.end()) {
      for (Route r : currentNode->edges) {
        // If we've traversed this endpoint, don't mess wit hit
        if (traversed.find(r.dest) == traversed.end()) {
          double rD = routeDist(r);
          double combinedDist = curDist + rD;

          if (pathMap.find(r.dest) == pathMap.end()) {
            Dijkstry newEnt;
            // calculate destination's relative distance to start
            newEnt.dist = combinedDist;
            newEnt.prev = currentNode;
            // add entry to map
            pathMap[r.dest] = newEnt;
          } else {
            // if there's already an entry, check if the current total distance is smaller than the entry's distance
            double maybeShorter = combinedDist;
            if (maybeShorter < pathMap.at(r.dest).dist) {
              // if that's the case, update the entry
              pathMap[r.dest].dist = maybeShorter;
              pathMap[r.dest].prev = currentNode;
            }
          }
          // if the current distance is the shortest distance between a route and a current node, set it as the current best
          if (rD < sRDist) {
            shortestRoute = airports.at(r.dest);
            shortestRouteRoute = r;
            sRDist = rD;
          }
        }
      }
      // Adds the current node to the list of traversed nodes
      traversed.insert(currentNode->data.name);

      if (shortestRoute != NULL) {
        // adds the shortest route forward to the queue, such that we'll traverse it next
        q.push(shortestRoute);
      }

      for (Route r : currentNode->edges) {
        if (traversed.find(r.dest) == traversed.end()) {
          q.push(airports.at(r.dest));
        }
      }
    }
  }

  // begin backtracking to find the shortest path
  vector<string> backwardPath;
  string currentAirport = end;
  while (currentAirport != start) {
    backwardPath.push_back(currentAirport);

    auto curNode = pathMap.find(currentAirport);
    if (curNode == pathMap.end()) {
      std::cout << "No path between " << start << " and " << end << std::endl;
      return vector<string>();
    }
    currentAirport = curNode->second.prev->data.name;
  }
  // NOTE: This returns a "path" starting from the destination, that doesn't include the starting airport
  backwardPath.push_back(start);
  std::reverse(backwardPath.begin(), backwardPath.end());
  return backwardPath;
}

Airport Graph::getAirport(string name) {
  // Searches for airport
  auto it = airports.find(name);
  if (it == airports.end()) {
    // If the airport isn't found, return a "sentinel" airport
    // and print an error message
    std::cout << name << " not found" << std::endl;
    return Airport("N/A", 0, 0);
  } else {
    // If it is found, return the airport.
    return it->second->data;
  }
}

std::map<std::string, double> Graph::calculateBetweennessCentrality(std::string startingAirport, std::string endingAirport) {
  double minDistance = 3 * routeDist(startingAirport, endingAirport);

  std::map<std::string, double> betweenness;

  std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> Q;
  std::stack<std::string> S;

  std::map<std::string, double> distances;
  std::map<std::string, double> sp;
  std::map<std::string, double> delta;
  std::map<std::string, bool> isInStack;
  std::map<std::string, std::list<std::string>> predecessor;

  int counter = 0;
  for (auto it = airports.begin(); it != airports.end(); it++) {
    // Complete an initial threshold check to see if the potential airport can feasibly be the central airport. If not, skip it.
    std::string currentAirport = it->first;
    ++counter;
    if (routeDist(currentAirport, startingAirport) + routeDist(currentAirport, endingAirport) > minDistance) {
      if (debug) {
        std::cout << "Skipping(Failed threshold): " << currentAirport << " " << counter << "/" << getAirportCount() << std::endl;
      }
      continue;
    } else if (debug) {
      std::cout << "Currently searching: " << currentAirport << " " << counter << "/" << getAirportCount() << std::endl;
    }

    // Update progress bar for cosmetic purposes
    double progress = ((double)counter) / getAirportCount();
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
      if (i < pos)
        std::cout << "=";
      else if (i == pos)
        std::cout << ">";
      else
        std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% - " << counter << "/" << getAirportCount() << "\r";
    std::cout.flush();

    // Reset all of the data holders and calculations for the new airport.
    for (auto i = airports.begin(); i != airports.end(); i++) {
      predecessor[i->first].clear();
      distances[i->first] = std::numeric_limits<double>::max();
      sp[i->first] = 0;
      isInStack[i->first] = false;
    }

    // Push the current distance, airport combo to the queue
    distances[currentAirport] = 0;
    sp[currentAirport] = 1;
    Q.push(std::make_pair(distances[currentAirport], currentAirport));

    // Loop through all airports until the Queue is empty.
    while (!Q.empty()) {
      std::string currentNode = Q.top().second;

      Q.pop();

      // Check to see if the destination note creats an eligible path for the centrality.
      if (!isInStack[currentNode]) {
        isInStack[currentNode] = true;
        S.push(currentNode);
        std::vector<Route> adjRoutes = this->getRoutesToAdjacentAirports(currentNode);
        for (auto& route : adjRoutes) {
          double currentDistance = routeDist(route);
          std::string destinationNode = route.dest;

          if (distances[destinationNode] > distances[currentNode] + currentDistance) {
            distances[destinationNode] = distances[currentNode] + currentDistance;
            Q.push(std::make_pair(distances[destinationNode], destinationNode));
            sp[destinationNode] = 0;
            predecessor[destinationNode].clear();
          }

          // Way to check floating point numbers equality ignoring rounding errors
          if (std::abs(distances[destinationNode] - (distances[currentNode] + currentDistance)) < 0.000000001) {
            sp[destinationNode] = sp[destinationNode] + sp[currentNode];
            predecessor[destinationNode].push_back(route.src);
          }
        }
      }
    }

    double c = 0;
    // Update the betweeness score based on the difference of distances and the previous calculations.
    while (S.size() != 0) {
      std::string airport_id = S.top();

      S.pop();

      for (std::string src : predecessor.at(airport_id)) {
        c = (sp[src] / sp[airport_id] * (1 + delta[airport_id]));

        delta[src] += c;
      }

      if (airport_id.compare(it->first) != 0) {
        betweenness[airport_id] += delta[airport_id];
      }
    }
  }

  return betweenness;
}

std::vector<Route> Graph::getRoutesToAdjacentAirports(std::string airport_id) {
  return airports[airport_id]->edges;
}

std::string Graph::getCentralAirport(std::string startingAirport, std::string endingAirport) {
  std::cout << "Finding the most central airport between: " << startingAirport << " and " << endingAirport << std::endl;
  std::cout << "Calculating betweenness for all airports:" << std::endl;
  std::map<std::string, double> betweenness = calculateBetweennessCentrality(startingAirport, endingAirport);
  std::cout << "Calculated." << std::endl;

  double largest = std::numeric_limits<double>::min();
  std::string mostCentral = "";

  // Find the maximum betweeness score to idenitify the most central airport.
  for (auto it = betweenness.begin(); it != betweenness.end(); it++) {
    if (mostCentral.compare("") == 0 || it->second > largest) {
      largest = it->second;
      mostCentral = it->first;
    }
  }

  return mostCentral;
}

int Graph::getAirportCount() const {
  return vertexCount;
}

int Graph::getRouteCount() const {
  return edgeCount;
}
