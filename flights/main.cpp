#include <iostream> //import iostream to print "Hello Airports"
#include "csv_reader.h" //import the csv reader
#include "Graph.h"  //include the graph classs we've made
int main() {    //normal main function
    std::cout << "Hello Airports" << std::endl; //print "Hello Airports" so that we know we're executing
    CSVReader reader("../data/airports.dat");   //start reading the file we retrieved
    std::cout << reader.nextLine()[1] << std::endl; //print a line from it to test that we read properly
    return 0; 
}
