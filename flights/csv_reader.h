
#pragma once

#include <fstream> //need this to deal with file
#include <string> //need this to deal with what's in the file
#include <vector> //need this to organize what's in the file

class CSVReader { //the class for the CSV reader
  public: //the public members
    /**
     * @brief Creates a CSVReader that corresponds to the given path.
     *
     * @param path to the csv formatted file to read.
     */
    CSVReader(std::string path); //constructor for a CSVReader

    ~CSVReader(); //default destructor 

    /**
     * @brief Returns the next row of the csv as a vector of string values.
     *
     * @return std::vector<std::string> row
     */
    std::vector<std::string> nextLine(); //nextline function, goes to next distinct item in file

  private: //the private members
    std::string path_; //helps us deal with 

    std::fstream file_; //helps us deal with reading the file
};