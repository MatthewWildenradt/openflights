#include "csv_reader.h" //need the header file

#include <iostream> //need to be able to print things
#include <sstream> //need to deal with strings

CSVReader::CSVReader(std::string path) { //constructor for the CSV reader
    path_ = path; // the path is the path
    file_.open(path_, std::fstream::in); //open the file for reading

    if (!file_.good()) { //make sure the file works
        throw std::invalid_argument("Error loading file: `" + path_ + "`."); //otherwise say that there was a problem
    }
}

CSVReader::~CSVReader() { //destructor for the reader
    file_.close(); //just need to make sure the file is closed
}

<<<<<<< HEAD
std::vector<std::string> CSVReader::nextLine() { //nextline function, goes to the next distinct item in the file
    std::vector<std::string> row; //have a vector of strings called row
=======
bool CSVReader::eof()
{
  return file_.eof();
}


std::vector<std::string> CSVReader::nextLine() {
    std::vector<std::string> row;
>>>>>>> 9293556ec5f2fc437e335852cc20da24ff1ca474

    std::string current; //have a string called current
    std::getline(file_, current); //we get the line and put it into current

    std::stringstream current_stream(current); //we use that string to make a stringstream
    std::string cell; //then we have an individual cell string

    while (std::getline(current_stream, cell, ',')) { //we go through that string stream until we see a comma
        // Trimming the cell and removing surrounding quotes
        cell.erase(0, cell.find_first_not_of(' ')); //get rid of space
        cell.erase(0, cell.find_first_not_of('"')); //get rid of "
        cell.erase(cell.find_last_not_of(' ') + 1); //get rid of space
        cell.erase(cell.find_last_not_of('"') + 1); //get rid of "

        row.push_back(cell); //then put the cell into that row vector
    }

<<<<<<< HEAD
    return row; //then return the row as a nice, easy to deal with vector
}
=======
    return row;
}
>>>>>>> 9293556ec5f2fc437e335852cc20da24ff1ca474
