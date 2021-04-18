#include <iostream>

#include "csv_reader.h"

int main() {
    std::cout << "Hello Airports" << std::endl;
    CSVReader reader("../data/airports.dat");
    std::cout << reader.nextLine()[1] << std::endl;
    return 0;
}
