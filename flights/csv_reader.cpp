#include "csv_reader.h"

#include <iostream>
#include <sstream>

CSVReader::CSVReader(std::string path) {
    path_ = path;
    file_.open(path_, std::fstream::in);

    if (!file_.good()) {
        throw std::invalid_argument("Error loading file: `" + path_ + "`.");
    }
}

CSVReader::~CSVReader() {
    file_.close();
}

bool CSVReader::eof()
{
  return file_.eof();
}


std::vector<std::string> CSVReader::nextLine() {
    std::vector<std::string> row;

    std::string current;
    std::getline(file_, current);

    std::stringstream current_stream(current);
    std::string cell;

    while (std::getline(current_stream, cell, ',')) {
        // Trimming the cell and removing surrounding quotes
        cell.erase(0, cell.find_first_not_of(' '));
        cell.erase(0, cell.find_first_not_of('"'));
        cell.erase(cell.find_last_not_of(' ') + 1);
        cell.erase(cell.find_last_not_of('"') + 1);

        row.push_back(cell);
    }

    return row;
}
