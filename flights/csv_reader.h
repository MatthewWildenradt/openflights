
#pragma once

#include <fstream>
#include <string>
#include <vector>

class CSVReader {
  public:
    /**
     * @brief Creates a CSVReader that corresponds to the given path.
     *
     * @param path to the csv formatted file to read.
     */
    CSVReader(std::string path);

    ~CSVReader();

    /**
     * @brief Returns the next row of the csv as a vector of string values.
     *
     * @return std::vector<std::string> row
     */
    std::vector<std::string> nextLine();

  private:
    std::string path_;

    std::fstream file_;
};